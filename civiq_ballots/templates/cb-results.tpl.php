<div class="row">
  <div class="col-md-12"><?php echo $question['question']; ?></div>
</div>

<div class="row">
  <div class="col-md-12"><?php echo $question['description']; ?></div>
</div>

<!--How many users cast votes and what is the preference for each option-->
<h2><?php echo t('Results'); ?></h2>
<h3><?php echo t('Total number of votes for this ballot is '); ?></h3>
<table>
<thead>
  <tr>	
    <th><?php echo t('Options'); ?></th>
    <th><?php echo t('Plurality'); ?></th>
    <th><?php echo t('Two Rounds'); ?></th>
    <th><?php echo t('Alternative'); ?></th>
    <th><?php echo t('Approval'); ?></th>
    <th><?php echo t('Borda count'); ?></th>
    <th><?php echo t('MBC'); ?></th>
    <th><?php echo t('Serial'); ?></th>
  </tr>  
</thead>
<tbody>
  <?php foreach ($options as $option_id => $option) { ?>
    <tr>
	  <td><?php echo $option; ?></td>
	  <td><?php 
	    if (isset($no_times_each_preference_to_each_option[$option_id][1])) { 
          $preference_one_times = count($no_times_each_preference_to_each_option[$option_id][1]);
	    } else {
		  $preference_one_times = '-';	
		}
		echo $preference_one_times;
	   ?></td>
	  <td><?php echo $preference_one_times; ?></td>
	  <td><?php echo $preference_one_times; ?></td>
	  <td><?php echo $vote_approvals[$option_id]; ?></td>
	  <td><?php echo '-'; ?></td>
	  <td><?php echo $total_points_each_option[$option_id]; ?></td>
	  <td><?php echo '-'; ?></td>
    </tr>	
  <?php } ?>
</tbody>	
</table>
