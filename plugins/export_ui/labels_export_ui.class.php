<?php

class labels_export_ui extends ctools_export_ui {
  function edit_form(&$form, &$form_state) {
    parent::edit_form($form, $form_state);

    // Add the Plural form element.
    $form['info']['plural'] = array(
      '#type' => 'textfield',
      '#title' => t('Plural'),
      '#size' => 24,
      '#default_value' => $form_state['item']->plural,
    );
  }
}
