<?php

$plugin = array(
  'title' => t('Label from field'),
  'description' => t('Creates a label context from a label field.'),
  'context' => 'labelfield_relationships_label_from_field_context',
  'keyword' => 'label',
  'edit form' => 'labelfield_relationships_label_from_field_edit_form',
  'get child' => 'labelfield_relationships_label_from_field_get_child',
  'get children' => 'labelfield_relationships_label_from_field_get_children',
  'defaults' => array('delta' => 0),
);

/**
 * Context callback.
 */
function labelfield_relationships_label_from_field_context($context, $conf) {
  $delta = !empty($conf['delta']) ? intval($conf['delta']) : 0;
  $plugin = $conf['name'];

  list($plugin, $plugin_name) = explode(':', $plugin);
  list($field_name, $entity_name) = explode('-', $plugin_name, 2);
  $entity_info = entity_get_info($entity_name);

  if (empty($context->data) || !isset($context->data->{$entity_info['entity keys']['id']})) {
    return ctools_context_create_empty('entity:' . $entity_name, NULL);
  }

  if (isset($context->data->{$entity_info['entity keys']['id']})) {
    $id = $context->data->{$entity_info['entity keys']['id']};
    $entity = entity_load($entity_name, array($id));
    $entity = $entity[$id];

    if ($items = field_get_items($entity_name, $entity, $field_name)) {
      if (isset($items[$delta])) {
        $item = $items[$delta];
        ctools_context_create('label', $item['label']);
      }
      else {
        return ctools_context_create_empty('entity:' . $entity_name, NULL);
      }
    }
  }
}

/**
 * Get Child callback.
 */
function labelfield_relationships_label_from_field_get_child($plugin, $parent, $child) {
  $plugin = labelfield_relationships_label_from_field_get_children($plugin, $parent);
  return $plugin[$parent . ':' . $child];
}

/**
 * Get Children callback.
 */
function labelfield_relationships_label_from_field_get_children($parent_plugin, $parent) {
  ctools_include('fields');

  $entity_infos = entity_get_info();
  $context_types = array();
  $entities = array();
  $plugins = array();


  // Get a list of all bundles and entities that use the labelfield.
  foreach (ctools_fields_get_fields_by_type('labelfield') as $field_name => $field_info) {
    foreach ($field_info['bundles'] as $entity => $bundles) {
      foreach ($bundles as $bundle) {
        $name = $field_name . '-' . $entity;
        $plugin_id = $parent . ':' . $name;

        // Record the bundle for later.
        $context_types[$plugin_id]['types'][$bundle] = $entity_infos[$entity]['bundles'][$bundle]['label'];

        if (!isset($plugins[$plugin_id])) {
          $plugin = $parent_plugin;
          $replacements = array(
            '@entity' => $entity_infos[$entity]['label'],
            '@field_name' => $field_name,
            '@field_label' => ctools_field_label($field_name),
          );

          $plugin['title'] = t('Label from @entity: @field_label (@field_name)', $replacements);
          $plugin['name'] = $plugin_id;
          $plugin['context name'] = $name;
          $plugin['description'] = t('Creates a label context from @entity using the @field_name field on @entity', $replacements);
          $plugin['entity'] = $entity;
          $plugin['field name'] = $field_name;
          $plugin['parent'] = $parent;

          $plugins[$plugin_id] = $plugin;
        }
      }
    }
  }

  foreach ($context_types as $key => $context) {
    list($parent, $plugin_name) = explode(':', $key);
    list($field_name, $entity) = explode('-', $plugin_name, 2);
    $plugins[$key]['required context'] = new ctools_context_required($entity_infos[$entity]['label'], $entity, array('type' => array_keys($context['types'])));
  }

  return $plugins;
}

/**
 * Edit form callback.
 */
function labelfield_relationships_label_from_field_edit_form($form, &$form_state) {
  $field = field_info_field($form_state['plugin']['field name']);
  $conf = $form_state['conf'];

  if ($field && $field['cardinality'] != 1) {
    $unlimited = ($field['cardinality'] == -1);

    $form['delta'] = array(
      '#type' => $unlimited ? 'textfield' : 'select',
      '#title' => t('Delta'),
      '#size' => $unlimited ? 2 : NULL,
      '#options' => $unlimited ? NULL : range(1, $field['cardinality']),
      '#description' => t('This relationship can only create one context, but multiple items can be related. Please !action which one.', array('!action' => $unlimited ? t('type') : t('select'))),
      '#default_value' => !empty($conf['delta']) ? $conf['delta'] : 0,
    );
  }

  return $form;
}
