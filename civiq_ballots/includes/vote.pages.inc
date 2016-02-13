<?php

/**
 * Implementation of page callback for vote. 
 */
function cb_options_vote_form($form, &$form_state, $question_id) {
  $form = array(); 
  $question = cb_get_question_info($question_id);
  if (!$question['enable_voting']) {
	drupal_set_title('');  
	drupal_set_message(t('Voting Closed for this question'), 'error');  
	return ''; 
  }
  if (empty($question)) {
	drupal_set_title('');  
	drupal_set_message(t('Invalid url'), 'error');  
	return '';
  }
  global $user;
  $is_voted = cb_is_user_voted($question_id, $user->uid);  
  if ($is_voted) {
	drupal_set_title('');  
	drupal_set_message(t('You have already voted on this ballot'), 'warning');  
	return '';  
  }
      
  $form['question'] = array(    
    '#markup' => '<p class="well">'.
      $question['question'].'</p>',
  );
  $form['description'] = array(    
    '#markup' => '<p class="well">'.
      $question['description'].'</p>',
  ); 
  $vote_preferences = array('' => t('Select Preference'));
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
  $form['back_link'] = array(
    '#markup' => "<div class='row-fluid'><span class='pull-right'>".l(t('Show all ballots'), 'questions')."</span></div>",
    '#weight' => 30, 
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
  
  $casted_votes_count = count($casted_votes);
  for($i=0; $i < $casted_votes_count; $i++) {	  
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
  if(count(array_unique($casted_votes)) < $casted_votes_count) {
    form_set_error('options', t('Invalid voting found, Please remove duplicates'));
  }
  
  if ($casted_votes_count == 0) {
    form_set_error('optios', t('Please cast votes before submit')); 
  }
}

function cb_options_vote_form_submit($form, &$form_state) {
  global $user;
  $option_preferences = $form_state['values']['options'];
  $casted_votes = array();
  $question_id = $form_state['values']['question_id'];
  foreach($option_preferences as $key => $preference) {
    if (!empty($preference)) {
      $casted_votes[$key] = $preference;      
    }
  }
  $casted_votes_count = count($casted_votes);
  if ($casted_votes_count > 0) {  
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
