<?php

/**
 * Implements hook_field_views_data().
 */
function labelfield_field_views_data($field) {
  $data = field_views_field_default_views_data($field);

  foreach ($data as $table_name => $table_data) {
    // Add the relationship only on the label field.
    $data[$table_name][$field['field_name'] . '_label']['relationship'] = array(
      'handler' => 'views_handler_relationship',
      'base' => 'labels',
      'base field' => 'machine_name',
      'label' => t('Label from !field_name', array('!field_name' => $field['field_name'])),
    );
  }
  return $data;
}
