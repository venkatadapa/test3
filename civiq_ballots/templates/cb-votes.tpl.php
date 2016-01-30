<div class="row">
  <div class="col-md-12"><?php echo $question['question']; ?></div>
</div>

<div class="row">
  <div class="col-md-12"><?php echo $question['description']; ?></div>
</div>

<!--How many users cast votes and what is the preference for each option-->
<h2><?php echo t('vote audit'); ?></h2>
<table>
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
<?php $vote_key = 1;
  $total_points = 0;
  $total_unused_points = 0; 
  foreach($votes as $vote) { ?>
	<tr>
	  <td><?php echo $vote_key; ?></td>
	  <?php for ($key=1; $key <= count($options); $key++) { ?>
		<td> <?php if (isset($vote['votes'][$key])) {
			         echo $vote['votes'][$key]; 
			       } else {
			        echo '-'; 
			       } ?> 
        </td>
      <?php } ?>
	  <td><?php echo $vote['total_points']; 
	    $total_points += $vote['total_points'];    
	  ?></td>
	  <td><?php echo $vote['points_unused']; 
	    $total_unused_points += $vote['points_unused'];
	  ?></td>
	</tr>
<?php $vote_key++;
  } ?>
  
 <tr><td colspan="<?php echo count($options)+1;?>"><?php echo t('Total');?></td>
   <td><?php echo $total_points; ?></td>
   <td><?php echo $total_unused_points; ?></td>
   </tr> 
</table>


<!--Each preference given how many times to each option-->
<h2><?php echo t('voters profile'); ?></h2>
<table>
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
<?php
 $preference = 1;
 foreach($options as $option_id => $option) { ?>
  <tr>
    <td><?php echo $preference; ?></td>
    <?php foreach($options as $option_id_inner => $option_inner) { ?>
      <td><?php
        if (isset($no_times_each_preference_to_each_option[$option_id_inner][$preference])) { 
          echo count($no_times_each_preference_to_each_option[$option_id_inner][$preference]);
	    } else {
		  echo '-';	
	    } 
        ?>
      </td>      
    <?php } ?>
  <td><?php echo count($each_preference_no_times_voted[$preference]); ?></td>        
  </tr>	
<?php $preference++; } ?>
</table>


<!--Ranking based on preferences choosen-->
<h2><?php echo t('social choice and social ranking'); ?></h2>
<table>
<thead>
  <tr>	
    <th><?php echo t('Social choice and social ranking'); ?></th>
    <th><?php echo t('Options'); ?></th>
    <th><?php echo t('Points Received'); ?></th>    
    <th><?php echo t('Consensus Coefficient'); ?></th>    
  </tr>
</thead>
<tbody>    
    <?php $index = 1;
    foreach($options as $option_id => $option) { ?>
    <tr>
       <td><?php echo $index; ?></td>
       <td><?php echo $option; ?></td>
       <td><?php echo array_sum($each_preference_no_times_voted[$option_id]); ?></td>
    </tr>		
    <?php $index++; 
    } ?>
</tbody>      
</table>
