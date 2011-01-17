<div id="comment-<?php print $comment->cid ?>" class="comment<?php print ($comment->new) ? ' comment-new' : ''; print ' '. $status ?> clear-block">
  <div class="comment-tl">
    <div class="comment-tr">
      <div class="comment-br">
        <div class="comment-bl">
          <?php print $picture ?>

          <h3><?php print $id ?>.&nbsp;<?php print $title ?></h3>

          <div class="submitted">
            <?php print $submitted ?>
          </div>

          <div class="content">
            <?php print $content ?>
            <?php if ($signature): ?>
              <div class="user-signature clear-block">
                <?php print $signature ?>
              </div>
            <?php endif; ?>
          </div>

          <?php print $links ?>
        </div>
      </div>
    </div>
  </div>
</div>
