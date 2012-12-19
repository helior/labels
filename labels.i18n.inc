<?php

/**
 * Implements hook_i18n_string_info().
 */
function labels_i18n_string_info() {
  $groups['labels'] = array(
    'title' => t('Labels'),
    'description' => t('Translatable labels.'),
    'format' => FALSE, // This group doesn't have strings with format
    'list' => TRUE, // This group can list all strings
  );

  return $groups;
}
