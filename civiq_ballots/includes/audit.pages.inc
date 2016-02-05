<?php

/**
 * Implementation of vote audit page callback.
 * @return array
 * A render array set for theming by theme_table().
 */
function cb_options_vote_audit_page($question_id) {
  $question = cb_get_question_info($question_id);
  
  // If user enters invalid question id  manullay through error.
  if (empty($question)) {
	drupal_set_title('');  
	drupal_set_message(t('Invalid url'), 'error');  
	return '';
  }
    
  $options = cb_get_options($question_id);  
  $votes = cb_get_votes($question_id);  
  $data = array(
    'question' => $question,
    'options' => $options,
    'votes' => $votes['votes'],
    'no_times_each_preference_to_each_option' => $votes['no_times_each_preference_to_each_option'],
    'each_preference_no_times_voted' => $votes['each_preference_no_times_voted'], 
    'total_points_each_option' => $votes['total_points_each_option'],
  );
  if (count($votes['votes']) > 0) {
    return theme('cb_audit_page', $data);
  }
  
  $output = t('No votes found') . ' ' . l('Click here to vote and be the first person', 'vote/' . arg(1));
  return $output;
}
