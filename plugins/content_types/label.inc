<?php

$plugin = array(
  'title' => t('Label'),
  'description' => t('Render a label of your choice.'),
  'defaults' => array('machine_name' => NULL),
  'edit form' => 'labels_content_types_label_settings',
  'render callback' => 'labels_content_types_label_render',
  'category' => 'Miscellaneous',
);

/**
 * Edit form callback.
 */
function labels_content_types_label_settings($form, &$form_state) {
  $conf = $form_state['conf'];

  $options = array();
  foreach (labels_load_all() as $label) {
    $options[$label->machine_name] = $label->label;
  }

  $form['machine_name'] = array(
    '#title' => t('Label'),
    '#type' => 'radios',
    '#options' => $options,
    '#required' => TRUE,
    '#default_value' => $conf['machine_name'],
  );

  return $form;
}

/**
 * Edit form submit callback.
 */
function labels_content_types_label_settings_submit($form, &$form_state) {
  foreach ($form_state['plugin']['defaults'] as $key => $default) {
    $form_state['conf'][$key] = isset($form_state['values'][$key]) ? $form_state['values'][$key] : $default;
  }
}

/**
 * Render callback.
 */
function labels_content_types_label_render($subtype, $conf, $args, $context) {
  // Prepare for the worse.
  if (empty($conf) || empty($conf['machine_name'])) {
    return;
  }

  $label = labels_load($conf['machine_name']);
  $element = new stdClass();
  $element->module = 'labels';
  $element->content = $label->label;

  return $element;
}
