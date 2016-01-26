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

