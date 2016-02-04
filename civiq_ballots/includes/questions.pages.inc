<?php

/**
 * Implementation of questions page callback.
 * @return array
 * A render array set for theming by theme_table().
 */
function cb_questions_page() {
  // We are going to output the results in a table with a nice header.
  $header = array(
    // The header gives the table the information it needs in order to make
    // the query calls for ordering. TableSort uses the field information
    // to know what database column to sort by.
    array('data' => t('Question'), 'field' => 'q.question'),
    array('data' => t('Description')),
    array('data' => t('Created'), 'field' => 'q.created'),
    array('data' => t('Updated'), 'field' => 'q.changed'),
    array('data' => t('Actions')),
  );

  // Using the TableSort Extender is what tells the the query object that we
  // are sorting.
  $query = db_select('cb_questions', 'q')
    ->extend('PagerDefault')
    ->extend('TableSort');
  $query->fields('q');

  // Don't forget to tell the query object how to find the header information.
  $result = $query
    ->limit(20)
    ->orderByHeader($header)
    ->execute();

  $rows = array();
  foreach ($result as $row) {
    $content = array(      
      'question' => $row->question,
      'description' => $row->description,
      'created' => date('d/m/Y h:m:s', $row->created),
      'changed' => date('d/m/Y h:m:s', $row->changed),
      'actions' => l(t('Vote') , 'vote/' . $row->id,
        array('query' => drupal_get_destination())) . ' ' .
        l(t('Audit') , 'vote-audit/' . $row->id) . ' ' .
        l(t('Results') , 'vote-results/' . $row->id),
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
    '#attributes' => array('class' => array('table-responsive')),
  );

  // Attach the pager theme.
  $build['pager_pager'] = array('#theme' => 'pager');

  return $build;
}
