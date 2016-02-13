<?php

/**
 * Implementation of questions page callback.
 * @return array
 * A render array set for theming by theme_table().
 */
function cb_questions_page() {
  drupal_add_css(drupal_get_path('module', 'civiq_ballots') . '/css/responsive_tables.css');	
  // We are going to output the results in a table with a nice header.
  $header = array(
    // The header gives the table the information it needs in order to make
    // the query calls for ordering. TableSort uses the field information
    // to know what database column to sort by.
    'question' => array(
      'data' => t('Question'), 
      'field' => 'q.question',      
    ),
    'desc' => array(
      'data' => t('Description')),
    'created' => array(
      'data' => t('Created'),
      'class' => 'numeric',       
    ),
    'updated' => array(
      'data' => t('Updated'), 
      'class' => 'numeric',      
    ),
    'actions' => array('data' => t('Actions')),
  );

  // Using the TableSort Extender is what tells the the query object that we
  // are sorting.
  $query = db_select('cb_questions', 'q')
    ->extend('PagerDefault')
    ->extend('TableSort');
  $query->fields('q');

  // Don't forget to tell the query object how to find the header information.
  $result = $query
    ->limit(10)
    ->orderByHeader($header)
    ->execute();

  $rows = array();
  foreach ($result as $row) {	
	$vote_link = t('Voting Closed');
	if ($row->enable_voting) {
	  $vote_link = l(t('Vote') , 'vote/' . $row->id);
	}	
    $content = array(      
      'question' => array(
        'data' => $row->question,
        'data-title' => t('Question'),
      ),  
      'description' => array(
        'data' => $row->description,
        'data-title' => t('Description'),
      ),  
      'created' => array(
        'data' => date('d/m/Y h:m:s', $row->created),
        'class' => 'numeric',
      ),
      'changed' => array(
        'data' => date('d/m/Y h:m:s', $row->changed),
        'class' => 'numeric',
      ),
      'actions' => array(
        'data' => $vote_link . '&nbsp;|&nbsp;' .
        l(t('Audit') , 'vote-audit/' . $row->id) . '&nbsp;|&nbsp;' .
        l(t('Results') , 'vote-results/' . $row->id),
        'data-title' => t('Actions'),
      ),  
    );
    // Normally we would add some nice formatting to our rows
    // but for our purpose we are simply going to add our row
    // to the array.
    $rows[] = array('data' => $content);
  }

  // Build the table for the nice output.
  $build['tablesort_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There is no data exists in db'),
    '#attributes' => array(
      'class' => array('cb-questions-table'),      
    ),
  );

  // Attach the pager theme.
  $build['pager_pager'] = array('#theme' => 'pager');

  return $build;
}
