<?php

/**
 * @file
 *
 * Plugin to provide a label context
 */

$plugin = array(
  'title' => t('Label'),
  'description' => t('A single label object.'),
  'context' => 'labels_context_label_create',
  'context name' => 'label',
  'edit form' => 'labels_context_label_settings_form',
  'defaults' => array('machine_name' => ''),
  'keyword' => 'label',
  'context name' => 'label',
  'convert list' => 'labels_context_label_convert_list',
  'convert' => 'labels_context_label_convert',
  // 'placeholder form' => array(
  //   '#type' => 'textfield',
  //   '#description' => t('Enter the label for this context.'),
  // ),
);

/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function labels_context_label_create($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('label');
  $context->plugin = 'label';

  if ($empty) {
    return $context;
  }

  if ($conf && isset($data['machine_name'])) {
    $data = labels_load($data['machine_name']);
  }

  if (!empty($data)) {
    $context->data     = $data;
    $context->title    = $data->label;
    $context->argument = $data->machine_name;
    return $context;
  }
}

function labels_context_label_settings_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $options = array();
  foreach (labels_load_all() as $label) {
    $options[$label->machine_name] = $label->label;
  }

  $form['machine_name'] = array(
    '#title' => t('Label'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $conf['machine_name'],
    '#description' => t('Select the label for this form.'),
  );

  return $form;
}

function labels_context_label_settings_form_submit($form, &$form_state) {
  $form_state['conf']['machine_name'] = $form_state['values']['machine_name'];
}

function labels_context_label_convert_list($plugin) {
  $list = array();
  $tokens = token_info();

  if (isset($tokens['tokens']['label'])) {
    foreach ($tokens['tokens']['label'] as $id => $info) {
      if (!isset($list[$id])) {
        $list[$id] = $info['name'];
      }
    }
  }

  return $list;
}

function labels_context_label_convert($context, $type, $options = array()) {
  $tokens = token_info();

  $values = token_generate('label', array($type => $type), array('label' => $context->data), $options);
  if (isset($values[$type])) {
    return $values[$type];
  }
}
