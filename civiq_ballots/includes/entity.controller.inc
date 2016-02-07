<?php
/**
 * @file
 * Controller file for all entity related classes.
 */

/*=====================Questions Related Code=============================*/

/**
 * CB Questions entity class.
 */
class CbQuestionsEntity extends Entity {
  /**
   * Override defaultUri().
   */
  protected function defaultUri() {
    return array('path' => CB_QUESTIONS_VIEW_PATH . '/' . $this->identifier());
  }
}

/**
 * Custom controller for the CB Questions.
 */
class CbQuestionsEntityAPIController extends EntityAPIController {

  /**
   * Override the save method.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }    
    $entity->changed = REQUEST_TIME;
    //$entity->status = 0;
    return parent::save($entity, $transaction);
  }

}

/**
 * Custom controller for the administrator UI.
 */
class CbQuestionsEntityDefaultUIController extends EntityDefaultUIController {
  /**
   * Generates the table headers for the overview table.
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
	//add additional headers
    $additional_header = array('Voting Status');
	//call the parent table to do its thing
	$header =  parent::overviewTableHeaders($conditions, $rows, $additional_header );
	return $header;
  }

  /**
	* Generates the row for the passed entity and may be overridden in order to
	* customize the rows.
	*
	* @param $additional_cols
	*   Additional columns to be added after the entity label column.
	*/
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    //add additional rows to the table
    $additional_cols[] = array('data' => array(
	  '#theme' => 'entity_ui_overview_item',
	  '#label' => ($entity->enable_voting) ? t('Open') : t('Closed'),
	  '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
	  '#url' => '',
	  '#entity_type' => $this->entityType),
    );	 
    //call the parent method to do its thing
    return parent::overviewTableRow($conditions, $id, $entity, $additional_cols);
  }
}  

/*=====================Options Related Code=============================*/

/**
 * CB Options entity class.
 */
class CbOptionsEntity extends Entity {
  /**
   * Override defaultUri().
   */
  protected function defaultUri() {
    return array('path' => CB_OPTIONS_VIEW_PATH . '/' . $this->identifier());
  }
}

/**
 * Custom controller for the CB Options entity.
 */
class CbOptionsEntityAPIController extends EntityAPIController {

  /**
   * Override the save method.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }    
    $entity->changed = REQUEST_TIME;
    //$entity->status = 0;
    return parent::save($entity, $transaction);
  }

}

/**
 * Custom controller for the administrator UI.
 */
class CbOptionsEntityDefaultUIController extends EntityDefaultUIController {
  /**
   * Generates the table headers for the overview table.
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
	//add additional headers
    $additional_header = array('Question');
	//call the parent table to do its thing
	$header =  parent::overviewTableHeaders($conditions, $rows, $additional_header);
	return $header;
  }

  /**
	* Generates the row for the passed entity and may be overridden in order to
	* customize the rows.
	*
	* @param $additional_cols
	*   Additional columns to be added after the entity label column.
	*/
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
	$question = cb_get_question_info($entity->cb_question_id);  	  
    //add additional rows to the table
    $additional_cols[] = array('data' => array(
	  '#theme' => 'entity_ui_overview_item',
	  '#label' => $question['question'],
	  '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
	  '#url' => '',
	  '#entity_type' => $this->entityType),
    );	 
    //call the parent method to do its thing
    return parent::overviewTableRow($conditions, $id, $entity, $additional_cols);
  }
}  

/*=====================Votes Related Code=============================*/

/**
 * CB Votes entity class.
 */
class CbVotesEntity extends Entity {
  /**
   * Override defaultUri().
   */
  protected function defaultUri() {
    return array('path' => CB_VOTES_VIEW_PATH . '/' . $this->identifier());
  }
}

/**
 * Custom controller for the CB Votes entity.
 */
class CbVotesEntityAPIController extends EntityAPIController {

  /**
   * Override the save method.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }    
    $entity->changed = REQUEST_TIME;
    //$entity->status = 0;
    return parent::save($entity, $transaction);
  }

}

/**
 * Custom controller for the administrator UI.
 */
class CbVotesEntityDefaultUIController extends EntityDefaultUIController {
  
}  

