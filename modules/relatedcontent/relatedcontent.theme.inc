<?php // $Id: relatedcontent.theme.inc,v 1.1.2.2 2009/12/09 12:45:19 peterboeren Exp $

/**
 * @file
 * RelatedContent – a Drupal module that Allows privileged users to associate
 * a node with related nodes that can be displayed along with the node.
 *
 * Author:
 *   Thomas Barregren <http://drupal.org/user/16678>.
 *
 * Ported to drupal 6.x by Peter Boeren
 *
 * Sponsors:
 *   Spoon Media <http://www.spoon.com.au/>,
 *   GMCVO <http://www.gmcvo.org.uk/>, and
 *   Webbredaktören <http://www.webbredaktoren.se/>.
 */


/**
 * Themeable function for the related content.
 *
 * @ingroup themeable
 * @param $output
 *   An associative array, whose keys are the names by which the output
 *   should be grouped, i.e. the names of content types, the names of the
 *   authors, the names of the views from which the node were selected, or
 *   'all' if grouping is disabled. Each output buffer is an ordinary array
 *   with already themed nodes which should be outputted in index order as they
 *   are.
 * @param $grouped
 *   The string 'type' if the related content should be grouped by their
 *   content types, the string 'author' if it should be grouped by their
 *   authors, the string 'view' if it should be grouped by their authors, and
 *   false if it should not be grouped at all.
 * @param $node_type
 *   The content type of the node whose related content is themed.
 * @param $teaser
 *   true or false depending on whether the node, whose related content is
 *   themed, will be displayed as a teaser or in full, respectively.
 * @param $page
 *   true or false depending on whether the node, whose related content is
 *   themed, will be displayed as a page itself or embedded into another page,
 *   respectively.
 * @return
 *   The default theming described in the help text.
 */
function theme_relatedcontent($output, $grouped = NULL, $node_type = NULL, $teaser = NULL, $page = NULL) {
  global $theme_engine;
  global $base_url;

  // Add CSS-file.
  $base = drupal_get_path('module', 'relatedcontent');
  drupal_add_css("$base/relatedcontent.css");

  // If the current theme engine is PHPTemplate and the current theme has a
  // RelatedContent template file, process the provided template file, and
  // return the resulting output. Otherwise, return the default theming.
  foreach ($output as $group => $contents) {
    $out .= "<div class=\"relatedcontent-nodes $group\">";
    if ($grouped) {
      $out .= '<h3>'. relatedcontent_group_title($group, $grouped, $node_type) .'</h3>';
    }
    // replace the internal urls by absolute urls for usage in a newsletter.
    if (_relatedcontent_variable("relatedcontent_links_absolute_$node_type")) {
      $contents = str_replace(base_path(), $base_url.'/', $contents);
    }

    $out .= implode('', $contents);
    $out .= '</div>';
  }

  return $out;

}

/**
 * Themeable function for displaying the overview table.
 *
 * @ingroup themeable
 * @param $form
 *   An array where:
 *     - $form['intro'] is a introductory text,
 *     - $form['nodes'][<nid>] is the form element for a checkbox,
 *     - $form['title'][<nid>] is the form element for a title,
 *     - $form['name'][<nid>] is the form element for a content type,
 *     - $form['created'][<nid>] is the form element for a create time,
 *     - $form['username'][<nid>] is the form element for an author,
 *   with <nid> being the identity number (nid) of the node in question.
 * @returns
 *   The themed table of nodes to select from.
 */
function theme_relatedcontent_form($form) {
  // Two global variables needed by the pager.
  // Taken from pager_query() in pager.inc
  global $pager_page_array, $pager_total, $pager_items_per_page;

  // Table header.
  $header = array(theme('table_select_header_cell'), t('Title'), t('Type'), t('Author'), t('Created'));

  // Build the table.
  $type = $form['#parameters'][1]->type;
  if (isset($form['nodes']) && is_array($form['nodes'])) {
    foreach (element_children($form['nodes']) as $vid) {

      // Add a row with the title of the view.
      $rows[] = array(array(
        'data' => '<strong>'. relatedcontent_view_title($vid, $type) .'</strong>',
        'colspan' => count($header),
      ));

      // Add rows of nodes with related content.
      foreach (element_children($form['nodes'][$vid]) as $nid) {
        $row = array();
        $row[] = drupal_render($form['nodes'][$vid][$nid]);
        $row[] = drupal_render($form['title'][$vid][$nid]);
        $row[] = drupal_render($form['name'][$vid][$nid]);
        $row[] = drupal_render($form['username'][$vid][$nid]);
        $row[] = drupal_render($form['created'][$vid][$nid]);
        $rows[] = $row;
      }

    }
  }
  else {
    $rows[] = array(array(
      'data' => t('No nodes are selected or a view does not have nodes as result directly such as the default \'archive\' view'),
      'colspan' => count($header),
    ));
  }

  // Render the form.
  $output .= drupal_render($form['intro']);
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($form);
  $output .= theme('pager', NULL, $pager_items_per_page, 0);


  return $output;

}

/**
 * Themeable function for displaying the table with the views that can be
 * used as sources.
 *
 * @ingroup themeable
 * @param $form
 *   is an array where:
 *     - $form['enabled'][<vid>] is the form element for a checkbox,
 *     - $form['name'][<vid>] is the form element for a name,
 *     - $form['description'][<vid>] is the form element for a description,
 *     - $form['title'][<vid>] is the form element for a display name,
 *     - $form['weight'][<vid>] is the form element for a weight,
 *   with <vid> being the identity number (vid) of the view in question.
 * @returns
 *   The themed table of views.
 */
function theme_relatedcontent_form_alter_node_type_views($form) {
  // Prepare the table for rendering.
  $header = array(theme('table_select_header_cell'), t('View'), t('Description'), t('Display name (optional)'));
  if (isset($form['enabled']) && is_array($form['enabled'])) {
    foreach (element_children($form['enabled']) as $vid) {
      $row = array();
      $row[] = drupal_render($form['enabled'][$vid]);
      $row[] = drupal_render($form['name'][$vid]);
      $row[] = drupal_render($form['description'][$vid]);
      $row[] = drupal_render($form['title'][$vid]);
      $row[] = drupal_render($form['weight'][$vid]);
      $rows[] = $row;
    }
  }
  else  {
    $rows[] = array(array(
      'data' => t('No views available.'),
      'colspan' => count($header)
    ));
  }

  // Render the form.
  $output .= theme('table', $header, $rows);
  $output .= drupal_render($form);

  return $output;
}