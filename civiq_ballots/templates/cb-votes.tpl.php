<div class="row">
  <div class="col-md-12"><?php echo $question['question']; ?></div>
</div>

<div class="row">
  <div class="col-md-12"><?php echo $question['description']; ?></div>
</div>

<!--How many users cast votes and what is the preference for each option-->
<h2><?php echo t('vote audit'); ?></h2>
<div>
<table class="table table-responsive table-bordered table-hover">
<thead>
  <tr>	
    <th rowspan="2"><?php echo t('Preferences'); ?></th>
    <th colspan="<?php echo count($options); ?>"><?php echo t('Options'); ?></th>
    <th rowspan="2"><?php echo t('Points Excercised'); ?></th>
    <th rowspan="2"><?php echo t('Points Not Used'); ?></th>
  </tr>
  <tr>
    <?php foreach($options as $option) { ?>
		<th> <?php echo $option; ?> </th>
    <?php } ?>
  </tr>
</thead>
<tbody>	
<?php $vote_key = 1;
  $total_points = 0;
  $total_unused_points = 0;  
  foreach($votes as $vote) { ?>
	<tr>
	  <td data-title="<?php echo t('Preferences'); ?>"><?php echo $vote_key; ?></td>
	  <?php foreach ($options as $option_id => $option_value) { ?>
		<td data-title="<?php echo t('Option: '). $option_value ?>"> <?php if (isset($vote['votes'][$option_id])) {
			         echo $vote['votes'][$option_id]; 
			       } else {
			        echo '-'; 
			       } ?> 
        </td>
      <?php } ?>
	  <td data-title="<?php echo t('Points Excercised'); ?>"><?php echo $vote['total_points']; 
	    $total_points += $vote['total_points'];    
	  ?></td>
	  <td data-title="<?php echo t('Points Not Used'); ?>"><?php echo $vote['points_unused']; 
	    $total_unused_points += $vote['points_unused'];
	  ?></td>
	</tr>
<?php $vote_key++;
  } ?>
  
 <tr><td colspan="<?php echo count($options)+1;?>"><?php echo t('Total');?></td>
   <td data-title="<?php echo t('Points Excercised'); ?>"><?php echo $total_points; ?></td>
   <td data-title="<?php echo t('Points Not Used'); ?>"><?php echo $total_unused_points; ?></td>
   </tr>
</tbody>    
</table>
</div>


<!--Each preference given how many times to each option-->
<h2><?php echo t('voters profile'); ?></h2>
<div>
<table class="table-responsive table table-bordered table-hover">
<thead>
  <tr>	
    <th rowspan="2"><?php echo t('Preferences'); ?></th>
    <th colspan="<?php echo count($options); ?>"><?php echo t('Options'); ?></th>
    <th rowspan="2"><?php echo t('Totals'); ?></th>    
  </tr>  
  <tr>
    <?php foreach($options as $option) { ?>
		<th> <?php echo $option; ?> </th>
    <?php } ?>
  </tr>
</thead>
<tbody>
<?php
 $preference = 1;
 foreach($options as $option_id => $option) { ?>
  <tr>
    <td data-title="<?php echo t('Preferences'); ?>"><?php echo $preference; ?></td>
    <?php foreach($options as $option_id_inner => $option_inner) { ?>
      <td data-title="<?php echo t('Option: '). $option_inner ?>"><?php
        if (isset($no_times_each_preference_to_each_option[$option_id_inner][$preference])) { 
          echo count($no_times_each_preference_to_each_option[$option_id_inner][$preference]);
	    } else {
		  echo '-';	
	    } 
        ?>
      </td>      
    <?php } ?>
  <td data-title="<?php echo t('Totals'); ?>"><?php 
    if (isset($each_preference_no_times_voted[$preference])) { 
      echo count($each_preference_no_times_voted[$preference]);
    } else {
	  echo '0';	
    }   
    ?>
    </td>        
  </tr>	
<?php $preference++; } ?>
</tbody>	
</table>
</div>


<!--Ranking based on preferences choosen-->
<h2><?php echo t('social choice and social ranking'); ?></h2>
<div>
<table class="table-responsive table table-bordered table-hover">
<thead>
  <tr>	
    <th><?php echo t('Social choice and social ranking'); ?></th>
    <th><?php echo t('Options'); ?></th>
    <th><?php echo t('Points Received'); ?></th>    
    <th><?php echo t('Consensus Coefficient'); ?></th>    
  </tr>
</thead>
<tbody>    
    <?php
    $included_options[] = array();
    $total_points = 0;
    for ($i = 0; $i < count($total_points_each_option); $i++) { ?>
    <tr>
       <td data-title="<?php echo t('Social choice and social ranking'); ?>"><?php echo $i+1; ?></td>
       <td data-title="<?php echo t('Option'); ?>"><?php 
         if (isset($total_points_each_option[$i+1]) && $total_points_each_option[$i]['total'] == $total_points_each_option[$i+1]['total']) {
		   $option = $options[$total_points_each_option[$i]['option_id']] . ' and ' . $options[$total_points_each_option[$i+1]['option_id']];        	 
		   //$included_options[$i] = $options[$total_points_each_option[$i]['option_id']];
		   //$included_options[$i+1] = $options[$total_points_each_option[$i+1]['option_id']];
	     } else {
		   $option = $options[$total_points_each_option[$i]['option_id']];
		   //$included_options[$i] = $options[$total_points_each_option[$i+1]['option_id']];	 
		 }		 
         if (!in_array($options[$total_points_each_option[$i]['option_id']], $included_options)) {		 	 
           echo $option; 
	     } else {
		   echo '-';	 
		 }
         ?></td>
       <td data-title="<?php echo t('Points Received'); ?>"><?php echo $total_points_each_option[$i]['total']; ?></td>
       <td data-title="<?php echo t('Consensus Coefficient'); ?>"><?php $coefficient = round($total_points_each_option[$i]['total']/(count($options)*count($votes)), 2); 
         echo $coefficient;
       ?></td>
       <?php $total_points += $total_points_each_option[$i]['total']; ?>
    </tr>    		
    <?php } ?>
    <tr><td colspan="2"><?php echo t('Total'); ?></td><td data-title="<?php echo t('Points Received'); ?>"><?php echo $total_points; ?></td><td></td></tr>
</tbody>      
</table>
</div>
