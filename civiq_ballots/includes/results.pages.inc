<?php

/**
 * Implementation of vote results page callback.
 * @return array
 * A render array set for theming by theme_table().
 */
function cb_options_vote_results_page($question_id) {
  drupal_add_css(drupal_get_path('module', 'civiq_ballots') . '/css/responsive_tables.css');	
  $question = cb_get_question_info($question_id);
  if (empty($question)) {
	drupal_set_title('');  
	drupal_set_message(t('Invalid url'), 'error');  
	return '';
  }
  $options = cb_get_options($question_id);  
  $votes = cb_get_votes($question_id);
  
  $vote_approvals = array();
  foreach ($votes['no_times_each_preference_to_each_option'] as $option_id => $total_votes) {    
    $count = 0;
    foreach ($total_votes as $vote) {
	  $count += count($vote);	
	}
	$vote_approvals[$option_id] = $count;	  
  }  
  
  $data = array(
    'question' => $question,
    'options' => $options,
    'votes' => $votes['votes'],
    'no_times_each_preference_to_each_option' => $votes['no_times_each_preference_to_each_option'],
    'each_preference_no_times_voted' => $votes['each_preference_no_times_voted'],
    'total_points_each_option' => $votes['total_points_each_option'], 
    'vote_approvals' => $vote_approvals,
  );
  
  if (count($votes['votes']) > 0) {
    return theme('cb_results_page', $data);
  }
  
  $output = t('No votes found') . ' ' . l('Click here to vote and be the first person', 'vote/' . arg(1));
  return $output;
}
