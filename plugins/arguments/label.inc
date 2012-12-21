<?php

$plugin = array(
  'title' => t('Label'),
  'description' => t('Creates a label context from a string argument.'),
  'context' => 'labels_argument_label_create',
  'keyword' => 'label',
  'name' => 'label',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter a value for this argument'),
  ),
);

function labels_argument_label_create($arg = NULL, $conf = NULL, $empty = FALSE) {
  if ($empty) {
    return ctools_context_create_empty('label');
  }

  if (is_object($arg)) {
    return ctools_context_create('label', $arg);
  }

  $original_arg = $arg;
  $arg = str_replace('-', '_', $arg);
  $label = labels_load($arg);

  if (!$label) {
    return FALSE;
  }

  $context = ctools_context_create('label', $label);
  $context->original_argument = $original_arg;

  return $context;
}
