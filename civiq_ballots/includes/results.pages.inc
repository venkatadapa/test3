<?php

/**
 * Implementation of vote results page callback.
 * @return array
 * A render array set for theming by theme_table().
 */
function cb_options_vote_results_page($question_id) {
  $question = cb_get_question_info($question_id);
  //dsm($question);
  $options = cb_get_options($question_id);
  //dsm($options);
  $votes = cb_get_votes($question_id);
  
  $vote_approvals = array();
  foreach ($votes['no_times_each_preference_to_each_option'] as $option_id => $total_votes) {    
    $count = 0;
    foreach ($total_votes as $vote) {
	  $count += count($vote);	
	}
	$vote_approvals[$option_id] = $count;	  
  }
  
  //dsm($votes);
  $data = array(
    'question' => $question,
    'options' => $options,
    'votes' => $votes['votes'],
    'no_times_each_preference_to_each_option' => $votes['no_times_each_preference_to_each_option'],
    'each_preference_no_times_voted' => $votes['each_preference_no_times_voted'],
    'total_points_each_option' => $votes['total_points_each_option'], 
    'vote_approvals' => $vote_approvals,
  );
  
  return theme('cb_results_page', $data);
}
