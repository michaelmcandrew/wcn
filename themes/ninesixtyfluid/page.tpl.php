<?php
// $Id:

$mainwidth =$right?8:12;

?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>



    <?php print $scripts; ?>
    <style type="text/css">
    /* for 16 subdivisions: 960 + 60 (1 grid unit) */
    .plus-1 .container_16 {
      width: 1020px;
    }
    </style>
  </head>
	<body class="plus1">
		<div class="container_16">
			<div class="grid_16">
			  <?php if ($site_name): ?>
				<h1 id="branding">
					<?php if ($linked_logo_img): ?>
            <span id="logo" ><?php print $linked_logo_img; ?></span>
          <?php endif; ?>
          <?php echo $site_name; ?>
				</h1>
				<?php endif; ?>
				<?php if ($site_slogan): ?>
          <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
        <?php endif; ?>
			</div>
			<div class="clear"></div>
			
		  <?php if ($primary_links || $secondary_links): ?>
        <div id="site-menu" class="grid_16">
          <?php if (isset($primary_links)) { ?>
            <?php print theme('links', $primary_links, array('class' =>'nav menu', 'id' => 'navlist')) ?>
          <?php } ?>
          <?php if (isset($secondary_links)) { ?>
            <?php print theme('links', $secondary_links, array('class' =>'nav menu', 'id' => 'subnavlist')) ?>
          <?php } ?>
        </div>
      <?php endif; ?>
      <div class="clear"></div>
			<div class="grid_16">
			  <?php if ($title): ?>
				<h2 id="page-heading"><?php print $title; ?></h2>
				<?php print $breadcrumb; ?>
				<?php else: ?>
				<p>&nbsp;</p>
				<?php endif; ?>
				
			</div>
			<div class="clear"></div>
			<div class="grid_16">
			  
			</div>
			<div id="sidebar-left" class="column sidebar grid_4">
			  <?php print $left; ?>
			</div>
			<div class="grid_<?php print $mainwidth; ?>">
			  <?php if ($tabs): ?>
          <div class="tabs"><?php print $tabs; ?></div>
        <?php endif; ?>
        <?php print $messages; ?>
        <?php print $help; ?>
        <div id="main-content" class="box clear-block">
          <?php print $content; ?>
        </div>
        <?php print $feed_icons; ?>
			</div>
			<?php if ($right): ?>
			<div id="sidebar-right" class="grid_4 omega">
			  <?php if ($search_box): ?>
          <div id="search-box" class="grid_6 prefix_10"><?php print $search_box; ?></div>
        <?php endif; ?>
			  <?php print $right; ?>
      </div>
      <?php endif; ?>
			<div class="clear"></div>
			<div class="grid_16" id="footer">
        <?php if ($footer): ?>
          <div id="footer-region" class="region grid_16 clear-block">
            <?php print $footer; ?>
          </div>
        <?php endif; ?>

        <?php if ($footer_message): ?>
          <div id="footer-message" class="grid_16">
            <?php print $footer_message; ?>
          </div>
        <?php endif; ?>
			</div>
			<div class="clear"></div>
		</div>
        <?php print $closure; ?>
	</body>
</html>




