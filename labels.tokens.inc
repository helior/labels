<?php

/**
 * Implements hook_token_info().
 */
function labels_token_info() {
  $types['label'] = array(
    'name' => t('Labels'),
    'description' => t('Tokens related to labels.'),
    'needs-data' => 'label',
  );

  $label['machine_name'] = array(
    'name' => t('Machine name'),
    'description' => t('The machine name of the label.'),
  );

  $label['label'] = array(
    'name' => t('Label'),
    'description' => t('The actual label string.'),
  );

  $label['plural'] = array(
    'name' => t('Plural'),
    'description' => t('The plural version of the label.'),
  );

  return array(
    'types' => $types,
    'tokens' => array('label' => $label),
  );
}

/**
 * Implements hook_tokens().
 */
function labels_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $sanitize = !empty($options['sanitize']);
  $replacements = array();

  if ($type == 'label' && !empty($data['label'])) {
    $label = $data['label'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'machine_name':
          $replacements[$original] = $label->machine_name;
          break;

        case 'label':
          $replacements[$original] = $label->label;
          break;

        case 'plural':
          $replacements[$original] = $label->plural;
          break;
      }
    }
  }

  return $replacements;
}
