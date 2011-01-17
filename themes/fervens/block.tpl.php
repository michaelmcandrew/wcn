<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block_id ?>">
  <?php if ($block->subject): ?>
    <h2 class="block-subject"><?php print $block->subject ?></h2>
  <?php endif;?>

  <div class="content">
    
    <?php
    if ($block->title == 'Resources'){
      $q = request_uri();
      
      $context = arg(2);
      //print "<h3>arg(2)</h3>";
    }
    ?>
    <?php print $block->content ?>
  </div>
</div>
