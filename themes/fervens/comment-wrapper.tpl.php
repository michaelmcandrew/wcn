<div id="comments">
  <div class="comment-count">
    <?php if ($node->comment == 1 || $node->comment == 2): ?>
      <?php if ($node->comment_count == 0): ?>
        <h3><?php print t('There are no comments for') . ' "' . $node->title . '".'; ?></h3>
      <?php elseif ($node->comment_count == 1): ?>
        <h3><?php print t('1 comment for') . ' "' . $node->title . '".'; ?></h3>
      <?php else: ?>
        <h3><?php print $node->comment_count . ' ' . t('comments for') . ' "' . $node->title . '".'; ?></h3>
      <?php endif; ?>
    <?php endif; ?>
  </div>

  <?php print $content; ?>
</div>
