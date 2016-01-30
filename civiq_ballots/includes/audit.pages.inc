<?php

/**
 * Implementation of vote audit page callback.
 * @return array
 * A render array set for theming by theme_table().
 */
function cb_options_vote_audit_page($question_id) {
  $question = cb_get_question_info($question_id);
  //dsm($question);
  $options = cb_get_options($question_id);
  //dsm($options);
  $votes = cb_get_votes($question_id);
  //dsm($votes);
  $data = array(
    'question' => $question,
    'options' => $options,
    'votes' => $votes['votes'],
    'no_times_each_preference_to_each_option' => $votes['no_times_each_preference_to_each_option'],
    'each_preference_no_times_voted' => $votes['each_preference_no_times_voted'], 
  );
  
  return theme('cb_audit_page', $data);
}
