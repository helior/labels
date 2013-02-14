<?php

$plugin = array(
  'title' => t('Label'),
  'description' => t('Render a label of your choice.'),
  'defaults' => array(
    'machine_name' => NULL,
    'use_plural' => FALSE,
    ),
  'edit form' => 'labels_content_types_label_settings',
  'admin info' => 'label_content_type_admin_info',
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
    '#type' => 'radios',
    '#title' => t('Label'),
    '#options' => $options,
    '#required' => TRUE,
    '#default_value' => $conf['machine_name'],
  );

  $form['use_plural'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use plural'),
    '#description' => t('Use the plural version of the label, if available.'),
    '#default_value' => $conf['use_plural'],
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
 * Admin info callback.
 */
function label_content_type_admin_info($subtype, $conf) {
  $label = labels_load($conf['machine_name']);

  // Use plural value upon request.
  if ($conf['use_plural']) {
    if (empty($label->plural)) {
      $output = t("Warning: plural value for %label doesn't exist!", array('%label' => $label->label));
    }
    else {
      $output = t('@label (plural)', array('@label' => $label->plural));
    }
  }
  else {
    $output = $label->label;
  }

  $element = new stdClass();
  $element->title = $output;

  return $element;
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
  $element->content = $conf['use_plural'] ? $label->plural : $label->label;

  return $element;
}
