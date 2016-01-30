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
	  <td><?php echo $vote['total_points']; ?></td>
	  <td><?php echo $vote['points_unused']; ?></td>
	</tr>
<?php $vote_key++;
  } ?>
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
  foreach($options as $option) { 
	
  }
?>
</table>


<!--Ranking based on preferences choosen-->
<h2><?php echo t('social choice and social ranking'); ?></h2>
