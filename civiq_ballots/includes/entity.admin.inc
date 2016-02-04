<?php
/**
 * @file
 * The file for admin forms and functionality for the questions entity.
 */

/*=====================Questions Related Code=============================*/

/**
 * Implements entityname_form().
 *
 * Entity API will call this form for crud operations.
 */
function cb_questions_form($form, &$form_state, $entity = NULL) {
  $form = array();

  $form['question'] = array(
    '#title' => t('Question'),
    '#type' => 'textfield',
    '#default_value' => isset($entity->question) ? $entity->question : '',
    '#description' => t('Question'),
    '#required' => TRUE,    
  );
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => isset($entity->description) ? $entity->description : '',
    '#description' => t('Description'),
    '#required' => TRUE,    
  );
  field_attach_form('cb_questions', $entity, $form, $form_state);
  
  // Adding options to collect for this question start here
  $existing_options = array();    
  if ($form_state['op'] == 'edit') {
    $results = db_select('cb_options', 'o')
      ->fields('o', array('id', 'cb_option'))
      ->condition('cb_question_id', $entity->id, '=')
      ->execute();
    while($record = $results->fetchAssoc()) {
      $existing_options[] = array(
         'id' => $record['id'],
         'cb_option' => $record['cb_option'],
      );
    }    
  }  
  $default_options = 3;
  if (count($existing_options) > 1) {
    $default_options = count($existing_options);
  }
  $form_state['storage']['options'] =
    isset($form_state['storage']['options']) ? $form_state['storage']['options'] : $default_options;  
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
    '#tree' => TRUE,
    '#prefix' => '<div id="options-container">',
    '#suffix' => '</div>',
  );
  if ($form_state['storage']['options']) {
    for ($i = 0; $i < $form_state['storage']['options']; $i++) {
	  $default_value = '';
	  $index = $i+1;
	  $attributes = array();	
	  if (array_key_exists($i, $existing_options)) {
	    $default_value = $existing_options[$i]['cb_option'];
	    $attributes = array('cb_id' => $existing_options[$i]['id']);	  
	  }	      	
      $form['options'][$i] = array(
        '#title' => t('Option') . ' ' . $index,
        '#type' => 'textfield',
        '#default_value' => $default_value,
        '#attributes' => $attributes,
      );      
    }
  }
  $form['add_option'] = array(
    '#type' => 'button',
    '#value' => t('Add an option'),
    '#href' => '',
    '#ajax' => array(
      'callback' => 'civiq_ballots_ajax_add_more_options',
      'wrapper' => 'options-container',
     ),
  );
 // Adding options to collect for this question ends here

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => isset($entity->id) ? t('Update') : t('Save'),
    ),
  );

  $form_state['storage']['options']++;
  return $form;
}

/**
 * Implements hook_form_validate().
 */
function cb_questions_form_validate($form, &$form_state) {
  $values = (object) $form_state['values'];
  entity_form_field_validate('cb_questions', $form, $form_state);  
}

/**
 * Implements hook_form_submit().
 */
function cb_questions_form_submit($form, &$form_state) {
  // Add author id as logged in user.
  global $user;
  $form_state['values']['uid'] = $user->uid;
  //$form_state['values']['status'] = 0;  
  $entity = entity_ui_form_submit_build_entity($form, $form_state);
  $entity->save();
  $question_id = $entity->id;     
  if ($form_state['op'] == 'add') {    
    $query = db_insert('cb_options')->fields(
      array(
        'uid',
        'cb_option',
        'cb_question_id',
        'created'       
      )
    );
   foreach($form_state['values']['options'] as $value) {
	 if (empty($value)) {
	   continue;	 
	 }     
	  $query->values(array(
	    'uid' => $user->uid,
	    'cb_option' => $value,
	    'cb_question_id' => $question_id,
	    'created' => REQUEST_TIME,	  
	  ));      
    }
    $query->execute();
  } else if ($form_state['op'] == 'edit') {
	
	$insert = db_insert('cb_options')->fields(
      array(
        'uid',
        'cb_option',
        'cb_question_id',
        'created'       
      )
    );
    foreach($form_state['values']['options'] as $key => $value) {
	  if (array_key_exists('cb_id', $form['options'][$key]['#attributes'])) {
		// Update existing option
		$option_id = $form['options'][$key]['#attributes']['cb_id'];
		if (!empty($value)) {
		  db_update('cb_options')
		  ->fields(array(
		    'cb_option' => $value,
		    'changed' => REQUEST_TIME,
		  ))
		  ->condition('id', $option_id, '=')
		  ->execute();
	    } 
	    else {
		  // If value empty, remove it		  
		  // First remove the option votes from cb_votes table  
		  $votes = db_select('cb_votes', 'v')
		    ->fields('v', array('id', 'votes'))
		    ->condition('cb_question_id', $question_id)
		    ->execute();
		  foreach ($votes as $row) {
			$votes_array = drupal_json_decode($row->votes);
			unset($votes_array[$option_id]);
			$votes_updated = drupal_json_encode($votes_array);
		    db_update('cb_votes')
		      ->fields(array(
		        'votes' => $votes_updated 
		      ))
		      ->condition('id', $row->id)
		      ->execute(); 	  
		  }
		  
		  // Delete option from options table	
		  db_delete('cb_options')
		  ->condition('id', $option_id)
          ->execute();	
		} 		
	    continue;
	  }
	  // If value empty, don't insert the option
	  if (empty($value)) {
	    continue;	 
	  } 
	  	  
	  $insert->values(array(
	    'uid' => $user->uid,
	    'cb_option' => $value,
	    'cb_question_id' => $question_id,
	    'created' => REQUEST_TIME,	  
	  ));      
    }
    $insert->execute();
  }	  
  drupal_set_message(t('Ballot Question @question has been saved.',
    array('@question' => $entity->question)));
  $form_state['redirect'] = CB_QUESTIONS_ADMIN_PATH;
}

/**
 * Function to add more options
 * */
function civiq_ballots_ajax_add_more_options($form, $form_state) {
  return $form['options'];
}

/*=====================Options Related Code=============================*/

/**
 * Implements entityname_form().
 *
 * Entity API will call this form for crud operations.
 */
function cb_options_form($form, &$form_state, $entity = NULL) {
  $form = array();
  $questions = array();
  $results = db_select('cb_questions', 'q')
    ->fields('q', array('id', 'question'))
    ->execute()
    ->fetchAll();
  foreach($results as $row) {
    $questions[$row->id] = $row->question;   
  }  
  $form['cb_question_id'] = array(
    '#title' => t('Select Question'),
    '#type' => 'select',
    '#options' => $questions,
    '#default_value' => isset($entity->cb_question_id) ? $entity->cb_question_id : '',
    '#description' => t('Choose Question to which this option belongs to'),
    '#required' => TRUE,    
  );
  $form['cb_option'] = array(
    '#title' => t('Option'),
    '#type' => 'textfield',
    '#default_value' => isset($entity->cb_option) ? $entity->cb_option : '',
    '#description' => t('Option'),
    '#required' => TRUE,    
  );
  field_attach_form('cb_options', $entity, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => isset($entity->id) ? t('Update') : t('Save'),
    ),
  );

  return $form;
}

/**
 * Implements hook_form_validate().
 */
function cb_options_form_validate($form, &$form_state) {
  $values = (object) $form_state['values'];
  entity_form_field_validate('cb_options', $form, $form_state);  
}

/**
 * Implements hook_form_submit().
 */
function cb_options_form_submit($form, &$form_state) {
  // Add author id as from logged in user.
  global $user;
  $form_state['values']['uid'] = $user->uid;
  //$form_state['values']['status'] = 0;  
  $entity = entity_ui_form_submit_build_entity($form, $form_state);
  $entity->save();
  drupal_set_message(t('Ballot Option @option has been saved.',
    array('@option' => $entity->cb_option)));
  $form_state['redirect'] = CB_OPTIONS_ADMIN_PATH;
}


/*=====================Votes Related Code=============================*/

/**
 * Implements entityname_form().
 *
 * Entity API will call this form for crud operations.
 */
function cb_votes_form($form, &$form_state, $entity = NULL) {  	
  $form = array();
  $options = array();
  $results = db_select('cb_options', 'o')
    ->fields('o', array('id', 'cb_option'))
    ->execute()
    ->fetchAll();
  foreach($results as $row) {
    $options[$row->id] = $row->cb_option;   
  }
  $form['cb_option_id'] = array(
    '#title' => t('Select Option'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => isset($entity->cb_option_id) ? $entity->cb_option_id : '',
    '#description' => t('Choose option to which this vote casts to'),
    '#required' => TRUE,    
  );
  $form['vote'] = array(
    '#title' => t('Preference'),
    '#type' => 'textfield',
    '#default_value' => isset($entity->vote) ? $entity->vote : '',
    '#description' => t('Preference'),
    '#required' => TRUE,    
  );
  field_attach_form('cb_votes', $entity, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => isset($entity->id) ? t('Update') : t('Save'),
    ),
  );

  return $form;
}

/**
 * Implements hook_form_validate().
 */
function cb_votes_form_validate($form, &$form_state) {
  $values = (object) $form_state['values'];
  entity_form_field_validate('cb_votes', $form, $form_state);  
}

/**
 * Implements hook_form_submit().
 */
function cb_votes_form_submit($form, &$form_state) {
  // Add author id as from logged in user.
  global $user;
  $form_state['values']['uid'] = $user->uid;
  //$form_state['values']['status'] = 0;  
  $entity = entity_ui_form_submit_build_entity($form, $form_state);
  $entity->save();
  drupal_set_message(t('Ballot Vote @vote has been saved.',
    array('@vote' => $entity->vote)));
  $form_state['redirect'] = CB_VOTES_ADMIN_PATH;
}
