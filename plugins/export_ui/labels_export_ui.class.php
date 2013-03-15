<?php

class labels_export_ui extends ctools_export_ui {

  // Alter the edit form to add a form element for our plural string, as well as
  // a "Save and translate" button if we're doing translations.
  function edit_form(&$form, &$form_state) {
    parent::edit_form($form, $form_state);

    $form['info']['singular']['#title'] = t('Singular');

    // Add the Plural form element.
    $form['info']['plural'] = array(
      '#type' => 'textfield',
      '#title' => t('Plural'),
      '#description' => t('This will be the plural version of the label.'),
      '#size' => 24,
      '#default_value' => $form_state['item']->plural,
    );
  }

  // Altering edit form submission to update translation strings in case we're
  // doing translations.
  function edit_form_submit(&$form, &$form_state) {
    parent::edit_form_submit($form, $form_state);

    if (labels_translatable()) {
      i18n_string_object_update('label', $form_state['item']);
    }
  }

  // If we're doing translations, make sure that we're removing i18n strings
  // from deleted objects.
  function delete_form_submit(&$form_state) {
    parent::delete_form_submit($form_state);
    if (labels_translatable() && $form_state['op'] == 'delete') {
      i18n_string_object_remove('label', $form_state['item']);
    }
  }
}
