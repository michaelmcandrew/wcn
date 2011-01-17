<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?> clear-block">
  <?php print $picture ?>

  <?php if (!$page): ?>
    <h2 class="title"><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
  <?php endif; ?>

  <?php if ($submitted): ?>
    <div class="submitted"><?php print $submitted ?></div>
  <?php endif; ?>

  <div class="content">
    <?php print $content ?>
  </div>

  <?php if (!empty($links) || !empty($terms)): ?>
    <div class="node-links" class="clear-block">
      <?php print $links; ?>

      <?php if ($terms): ?>
        <div class="terms terms-inline clear-block"><?php print $terms ?></div>
      <?php endif;?>
    </div>
  <?php endif; ?>
</div>
