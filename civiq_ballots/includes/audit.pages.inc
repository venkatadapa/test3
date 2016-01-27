<?php

/**
 * Implementation of vote audit page callback.
 * @return array
 * A render array set for theming by theme_table().
 */
function cb_options_vote_audit_page($question_id) {
  $question = cb_get_question_info($question_id);
  dsm($question);
  $options = cb_get_options($question_id);
  dsm($options);
  $votes = cb_get_votes($question_id);
  dsm($votes);
  return 'In Progress';
}
