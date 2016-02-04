<?php

/**
 * Implementation of page callback for vote. 
 */
function cb_options_vote_form($form, &$form_state, $question_id) {
  $form = array(); 
  $question = cb_get_question_info($question_id);
  if (empty($question)) {
	drupal_set_title('');  
	drupal_set_message(t('Invalid url'), 'error');  
	return '';
  }    
  $form['question'] = array(    
    '#markup' => '<div class="row"><div class="col-md-12">'.
      $question['question'].'</div></div>',
  );
  $form['description'] = array(    
    '#markup' => '<div class="row"><div class="col-md-12">'.
      $question['description'].'</div></div>',
  ); 
  $vote_preferences = array('' => t('Select'));
  $options = array();
  $options_query = db_select('cb_options', 'o')
    ->fields('o', array('id', 'cb_option'))
    ->condition('cb_question_id', $question_id, '=')
    ->execute();
  $total_options = $options_query->rowCount();    
  for($i = 1; $i <= $total_options; $i++) {
    $vote_preferences[$i] = $i;
  }
  $form['options'] = array(
    '#type' => 'container',    
    '#tree' => TRUE,
    '#prefix' => '<div id="options-container">',
    '#suffix' => '</div>',
  );      
  while($record = $options_query->fetchAssoc()) {      
    $form['options'][$record['id']] = array(
      '#type' => 'select',
      '#options' => $vote_preferences,
      '#title' => $record['cb_option']
    );    
  }  
  $form['question_id'] = array(
    '#type' => 'hidden',
    '#value' => $question_id,
  );
  $form['actions'] = array(
    '#type' => 'submit',
    '#value' => t('Vote')
  );
  
  return $form;     
} 

/**
 * Form validation 
 **/
function cb_options_vote_form_validate($form, &$form_state) {
  $option_preferences = $form_state['values']['options'];
  $casted_votes = array();
  foreach($option_preferences as $key => $preference) {
    if (!empty($preference)) {
      $casted_votes[$key] = $preference;      
    }
  }
  sort($casted_votes); 
  $invalid_sequence = FALSE;
  if (isset($casted_votes[0]) and $casted_votes[0] != 1){
    $invalid_sequence = TRUE;	  
  }
  
  for($i=0; $i < count($casted_votes); $i++) {
	  //dsm($casted_votes);
	if (isset($casted_votes[$i+1])) {  
      if (($casted_votes[$i+1] - $casted_votes[$i]) > 1) {
	    $invalid_sequence = TRUE;
	  }
    }
  }
  if ($invalid_sequence) {
    form_set_error('options', t('Invalid sequence found, Please vote in sequential order'));
  }
  
  // Show error if same preference given for multiple options
  if(count(array_unique($casted_votes)) < count($casted_votes)) {
    form_set_error('options', t('Invalid voting found, Please remove duplicates'));
  }
  
  if (count($casted_votes) == 0) {
    form_set_error('optios', t('Please cast votes before submit')); 
  }
}

function cb_options_vote_form_submit($form, $form_state) {
  global $user;
  $option_preferences = $form_state['values']['options'];
  $casted_votes = array();
  $question_id = $form_state['values']['question_id'];
  foreach($option_preferences as $key => $preference) {
    if (!empty($preference)) {
      $casted_votes[$key] = $preference;      
    }
  }
  if (count($casted_votes) > 0) {  
	  $votes = drupal_json_encode($casted_votes);
	  db_insert('cb_votes')
		->fields(array(
		'uid' => $user->uid,
		'cb_question_id' => $question_id,
		'votes' => $votes,
		'created' => REQUEST_TIME,
	  ))
	  ->execute();
	  drupal_set_message(t('Thanks for voting'));
  }
  $form_state['redirect'] = 'questions';
}
