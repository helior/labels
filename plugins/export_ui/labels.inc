<?php

/**
 * Export UI plugin for labels.
 */
$plugin = array(
  'title' => t('Labels'),
  'schema' => 'labels',
  'access' => 'administer labels',
  'handler' => array(
    'class' => 'labels_export_ui',
    'parent' => 'ctools_export_ui',
  ),

  'title singular' => t('label'),
  'title singular proper' => t('Label'),
  'title plural' => t('labels'),
  'title plural proper' => t('Labels'),
);
