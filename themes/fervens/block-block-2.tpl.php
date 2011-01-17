<?php
/**
 * use menu tree to find name of parent and use it for the block title
 *  
 */ 
$tree = menu_tree_page_data("primary-links");
$parent = "Section link";
foreach($tree as $link_data){
      if($link_data['link']['in_active_trail']){
      //can use parent to show current menu item 
      $parent = ($link_data['link']['link_title']); 
      }
    }
?>
<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block_id ?>">
  <?php if ($parent): ?>
    <h2 class="block-subject"><?php print $parent ?></h2>
  <?php endif;?>

  <div class="content">
    <?php print $block->content ?>
  </div>
</div>
