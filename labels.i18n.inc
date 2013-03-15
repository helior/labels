<?php

/**
 * Implements hook_i18n_object_info().
 */
function labels_i18n_object_info() {
  $info['label'] = array(
    'title' => t('Label'),
    'key' => 'machine_name',
    'load callback' => 'labels_load',
    'placeholders' => array(
      '%ctools_export_ui' => 'machine_name',
    ),
    'edit path' => 'admin/structure/labels/list/%ctools_export_ui/edit',
    'translate tab' => 'admin/structure/labels/list/%ctools_export_ui/translate',
    'list callback' => 'labels_load_all',
    'string translation' => array(
      'textgroup' => 'label',
      'type' => 'label',
      'table' => 'label',
      'properties' => array(
        'singular' => t('Singular'),
        'plural' => t('Plural'),
      ),
      'translate path' => 'admin/structure/labels/list/%ctools_export_ui/translate/%i18n_language',
    ),
  );

  return $info;
}


/**
 * Implements hook_i18n_string_info().
 */
function labels_i18n_string_info() {
  $groups['label'] = array(
    'title' => t('Label'),
    'description' => t('Translatable labels.'),
    'format' => FALSE,
    'list' => TRUE,
  );

  return $groups;
}
