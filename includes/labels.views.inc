<?php

/**
 * Implements hook_views_data().
 */
function labels_views_data() {
  $data = array();

  $data['labels']['table']['group']  = t('Labels');

  $data['labels']['table']['base'] = array(
    'field' => 'machine_name',
    'title' => t('Labels'),
    'help' => t('Labels in the system.'),
    'defaults' => array(
      'field' => 'label',
    ),
  );

  // Expose the label value.
  $data['labels']['machine_name'] = array(
    'title' => t('Machine-name'),
    'help' => t('The machine-name for the label.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the label value.
  $data['labels']['label'] = array(
    'title' => t('Label'),
    'help' => t('The label.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the plural value.
  $data['labels']['plural'] = array(
    'title' => t('Plural'),
    'help' => t('The plural version of the label.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}
