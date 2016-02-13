<?php $total_votes_count = count($votes);
  $options_count = count($options);
  $total_points_each_option_count = count($total_points_each_option);
 ?>
<p class="well"><?php echo $question['question']; ?></p>
<p class="well"><?php echo $question['description']; ?></p>
<!--How many users cast votes and what is the preference for each option-->
<h2><?php echo t('vote audit'); ?></h2>
<div>
<table class="table-responsive table table-bordered table-hover">
<thead>
  <tr>	
    <th rowspan="2" width="15%"><?php echo t('Preferences'); ?></th>
    <th colspan="<?php echo $options_count; ?>" class="text-center" width="55%"><?php echo t('Options'); ?></th>
    <th rowspan="2" width="15%"><?php echo t('Points Excercised'); ?></th>
    <th rowspan="2" width="15%"><?php echo t('Points Not Used'); ?></th>
  </tr>
  <tr>
    <?php foreach($options as $option) { ?>
		<th class="sub"> <?php echo $option; ?> </th>
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
  
 <tr><td colspan="<?php echo $options_count+1;?>"><?php echo t('Total');?></td>
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
    <th rowspan="2" width="15%"><?php echo t('Preferences'); ?></th>
    <th colspan="<?php echo $options_count; ?>" class="text-center" width="55%"><?php echo t('Options'); ?></th>
    <th rowspan="2" width="15%"><?php echo t('Total Number Used'); ?></th>
    <th rowspan="2" width="15%"><?php echo t('Total Number Unused'); ?></th>        
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
    <td data-title="<?php echo t('Total number Unused'); ?>"><?php 
    if (isset($each_preference_no_times_voted[$preference])) { 
	  $unused = (int) $total_votes_count - count($each_preference_no_times_voted[$preference]); 	
      echo $unused;
    } else {
	  echo count($votes);	
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
    for ($i = 0; $i < $total_points_each_option_count; $i++) { ?>
    <tr>
       <td data-title="<?php echo t('Social choice and social ranking'); ?>"><?php echo cb_ordinal_suffix($i+1); ?></td>
       <td data-title="<?php echo t('Option'); ?>">
       <?php
        if (in_array($total_points_each_option[$i]['option_id'], $included_options)) {
		  $to_print = '-';
	    } else {
		  $to_print = $options[$total_points_each_option[$i]['option_id']];
		  $included_options[] = $total_points_each_option[$i]['option_id']; 		
		  for ($j = $i+1; $j < count($total_points_each_option); $j++) {
	        if ($total_points_each_option[$i]['total'] == $total_points_each_option[$j]['total']) {		
		      $to_print .= ' & ' . $options[$total_points_each_option[$j]['option_id']];
		      $included_options[] = $total_points_each_option[$j]['option_id'];
	        }
		  }
	    }
	    echo $to_print;	    
         ?></td>
       <td data-title="<?php echo t('Points Received'); ?>">
       <?php
         if ($to_print != '-') { 
           echo $total_points_each_option[$i]['total'];
	     } else {
		   echo '-';	 
	     }
       ?></td>
       <td data-title="<?php echo t('Consensus Coefficient'); ?>">
       <?php
         if ($to_print != '-') {  
           $coefficient = round($total_points_each_option[$i]['total']/($options_count*$total_votes_count), 2); 
           echo $coefficient;
	     } else {
		   echo '-';	 
		 }
       ?></td>
       <?php $total_points += $total_points_each_option[$i]['total']; ?>
    </tr>    		
    <?php } ?>
    <tr><td colspan="2"><?php echo t('Total'); ?></td><td data-title="<?php echo t('Points Received'); ?>"><?php echo $total_points; ?></td><td></td></tr>
</tbody>      
</table>
</div>
<div class='row-fluid'><span class='pull-right'>
  <?php echo l(t('Show all ballots'), 'questions'); ?>
</span></div>
