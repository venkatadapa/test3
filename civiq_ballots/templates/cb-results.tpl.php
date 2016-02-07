<div class="row">
  <div class="col-md-12"><?php echo $question['question']; ?></div>
</div>

<div class="row">
  <div class="col-md-12"><?php echo $question['description']; ?></div>
</div>

<!--How many users cast votes and what is the preference for each option-->
<h2><?php echo t('Results'); ?></h2>
<h3><?php echo t('Total number of votes for this ballot is '). count($votes); ?></h3>
<div class="row">
<table class="table-responsive table table-bordered table-hover">
<thead>
  <tr>	
    <th><?php echo t('Options'); ?></th>
    <th><?php echo t('Plurality'); ?></th>
    <th><?php echo t('Two Rounds'); ?></th>
    <th><?php echo t('Alternative'); ?></th>
    <th><?php echo t('Approval'); ?></th>    
    <th><?php echo t('MBC'); ?></th>    
  </tr>  
</thead>
<tbody>
  <?php foreach ($options as $option_id => $option) { ?>
    <tr>
	  <td data-title="<?php echo t('Option'); ?>"><?php echo $option; ?></td>
	  <td data-title="<?php echo t('Plurality'); ?>"><?php 
	    if (isset($no_times_each_preference_to_each_option[$option_id][1])) { 
          $preference_one_times = count($no_times_each_preference_to_each_option[$option_id][1]);
	    } else {
		  $preference_one_times = '-';	
		}
		echo $preference_one_times;
	   ?></td>
	  <td data-title="<?php echo t('Two Rounds'); ?>"><?php echo $preference_one_times; ?></td>
	  <td data-title="<?php echo t('Alternative'); ?>"><?php echo $preference_one_times; ?></td>
	  <td data-title="<?php echo t('Approval'); ?>"><?php echo $vote_approvals[$option_id]; ?></td>	  
	  <td data-title="<?php echo t('MBC'); ?>"><?php echo $total_points_each_option[$option_id]; ?></td>	  
    </tr>	
  <?php } ?>
</tbody>	
</table>
</div>
