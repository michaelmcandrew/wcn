<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <!--[if lte IE 6]>
    <style type="text/css">body { behavior: url(<?php print $base_path ?><?php print path_to_theme() ?>/whateverhover.htc); }</style>
  <![endif]-->
  <?php print $scripts; ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyled Content in IE */ ?></script>
</head>
<body<?php print phptemplate_body_class($left, $right); ?>>
  <div id="page">
    <div id="header">
      <?php if (!empty($site_name)): ?>
        <div id="site-name">
          <h1><a href="<?php print $front_page ?>"><span><img src="<?php print $base_path ?><?php print path_to_theme() ?>/images/banner-a.png" title="<?php print t('Home'); ?> for <?php print $site_name; ?>" alt="<?php print $site_name; ?> - the voice for Westminster's voluntary sector - calls us on 020 7535 0493" height="105" width="960" /></span></a></h1>
        </div> <!-- /#site-name -->
      <?php endif; ?>

      <?php if (!empty($header)): ?>
        <div id="header-region">
          <?php print $header; ?>
        </div> <!-- /#header-region -->
      <?php endif; ?>
    </div> <!-- /#header -->

    <div id="primary" class="clear-block">
      <?php print theme('links', $primary_links, array('class' => 'links primary-links')); ?>
    </div>

    <div id="main-and-sidebars" class="clear-block">
      <div id="main" class="main-tl">
        <div class="main-tr">
          <div class="main-br">
            <div class="main-bl">
              <?php if (!empty($breadcrumb)): ?><div id="breadcrumb"><?php print $breadcrumb; ?></div><?php endif; ?>
              <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
              <?php if (!empty($title)): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
              <?php if (!empty($tabs)): ?><div class="tabs"><?php print $tabs; ?></div><?php endif; ?>
              <?php if (!empty($messages) || !empty($help)): ?><div class="clear-block">
              <?php if (!empty($messages)): print $messages; endif; ?>
              <?php if (!empty($help)): print $help; endif; ?>
              </div><?php endif; ?>
              <div id="content" class="clear-block">
                
                <?php print $content; ?>
              </div> <!-- /#content -->
              <?php print $feed_icons; ?>
            </div> <!-- /.main-bl -->
          </div> <!-- /.main-br -->
        </div> <!-- /.main-tr -->
      </div> <!-- /#main.tl -->

      <div id="sidebars">
        <div id="sidebar-left">
          <?php print $left; ?>
        </div> <!-- /#sidebar-left -->

        <div id="sidebar-right">
          <?php print $right; ?>
        </div> <!-- /#sidebar-right -->
      </div> <!-- /#sidebars -->
    </div> <!-- /#main-and-sidebars -->

    <div id="footer" class="clear-block">
      <!--<a href="http://smashingmagazine.com/" id="i-love-sm"><img src="<?php print $base_path ?><?php print path_to_theme() ?>/images/i-love-sm.png" title="<?php print t('I love') . ' Smashing Magazine.'; ?>" /></a>-->
      <?php print $footer_message; ?>
      <!--<div id="footer-credits"><?php print '<a href="http://drupal.org/project/fervens" title="' . t('Download') . ' Fervens Drupal ' . t('theme') . '.">Fervens</a> Drupal ' . t('theme by') . ' ' . '<a href="http://kahthong.com/" title="' . t('Visit') . ' Leow Kah Thong\'s website.">Leow Kah Thong</a>. ' . 'Designed by' . ' ' . '<a href="http://designdisease.com/" title="' . t('Visit') . ' Design Disease.">Design Disease</a> ' . t('and brought to you by') . ' <a href="http://smashingmagazine.com/" title="' . t('Visit') . ' Smashing Magazine.">Smashing Magazine</a>.'; ?></div>--> <!-- /#theme-credits -->
    </div> <!-- /#footer -->
  </div> <!-- /#page -->

  <?php print $closure; ?>
</body>
</html>
