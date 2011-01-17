<?php
/**
 * Defines administration form
 *
 * @return array
 */
function montharchive_settings_form() {
  $output['montharchive_all'] = array(
    
    '#tree' => FALSE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
    '#title' => t('Global block node types'), 
    'montharchive_include_node_type' => array(
      
      '#type' => 'checkboxes', 
      '#multiple' => TRUE, 
      '#default_value' => variable_get('montharchive_include_node_type', array_keys(node_get_types('names'))), 
      '#options' => node_get_types('names'), 
      '#description' => t('Selected node types will be included in the global block and archive pages.')
    )
  );
  $output['montharchive_block_type'] = array(    
    '#tree' => FALSE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
    '#title' => t('Blocks by node type'), 
    'montharchive_block_node_type' => array(
      '#type' => 'checkboxes', 
      '#multiple' => TRUE, 
      '#default_value' => variable_get('montharchive_block_node_type', array()), 
      '#options' => node_get_types('names'), 
      '#description' => t('Blocks and archive pages for the selected node types will be created.')
    ),
  );
  
  $output['montharchive_author'] = array(    
    '#tree' => FALSE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
    '#title' => t('Author blocks by node type'), 
    'montharchive_block_node_type_by_user' => array(
      '#type' => 'checkboxes', 
      '#multiple' => TRUE, 
      '#default_value' => variable_get('montharchive_block_node_type_by_user', array()), 
      '#options' => node_get_types('names'), 
      '#description' => t('Blocks and archive pages for the selected node types created by the author of the current node will be created.')
    )
  );
  
  $output['montharchive_block_link_max'] = array(
    
    '#type' => 'textfield', 
    '#title' => t('Maximum month links in block'), 
    '#default_value' => variable_get('montharchive_block_link_max', 12), 
    '#size' => 5, 
    '#maxlength' => 5, 
    '#description' => t('Enter a number to limit the number of months linked in the block, blank or "0" to list all months.')
  );
  
  $output['montharchive_rev_linksort'] = array(
    
    '#type' => 'checkbox', 
    '#title' => t('Sort links in chronological order'), 
    '#return_value' => 1, 
    '#default_value' => variable_get('montharchive_rev_linksort', 0), 
    '#description' => t('If checked, the list of archive links will be sorted from oldest to newest. Otherwise it will be sorted from newest to oldest')
  );
  
  $output['montharchive_show_linkcount'] = array(
    '#type' => 'checkbox', 
    '#title' => t('Show link count'), 
    '#return_value' => 1, 
    '#default_value' => variable_get('montharchive_show_linkcount', 1), 
    '#description' => t('If checked, the link to each monthly archive page in blocks will show the number of nodes in that month ')
  );
  
  $output['montharchive_rev_pagesort'] = array(
    
    '#type' => 'checkbox', 
    '#title' => t('Sort archive page in chronological order'), 
    '#return_value' => 1, 
    '#default_value' => variable_get('montharchive_rev_pagesort', 0), 
    '#description' => t('If checked, the list of archive links will be sorted from oldest to newest. Otherwise it will be sorted from newest to oldest')
  );
  
  $output['montharchive_paginate'] = array(
    
    '#type' => 'checkbox', 
    '#title' => t('Paginate archive page'), 
    '#return_value' => 1, 
    '#default_value' => variable_get('montharchive_paginate', 0), 
    '#description' => t('If checked the output will be split into pages. The number of posts will respect the global nodes per page setting.')
  );
  $form = system_settings_form($output);
  $form['#submit'] = array(
    'montharchive_settings_form_submit'
  );
  $output['#validate'][] = 'montharchive_settings_form_validate';
  return $form;
}

/**
 * montharchive_settings_form reset function
 *
 */
function montharchive_settings_form_reset() {
  variable_del('montharchive_include_node_type');
  variable_del('montharchive_block_node_type');
  variable_del('montharchive_block_node_type_by_user');
  
  variable_del('montharchive_block_link_max');
  variable_del('montharchive_rev_linksort');
  variable_del('montharchive_show_linkcount');
  variable_del('montharchive_rev_pagesort');
  variable_del('montharchive_paginate');
  montharchive_settings_type_path_form_reset();
}

/**
 * montharchive_settings_form submit function
 *
 * @param array $form
 * @param array $form_state
 */
function montharchive_settings_form_submit($form, &$form_state) {
  $edit = $form_state['values'];
  if ($form_state['clicked_button']['#value'] == 'Reset to defaults') {
    montharchive_settings_form_reset();
    drupal_set_message('The configuration options have been reset to their default values.');
  }
  else {
    variable_set('montharchive_include_node_type', $edit['montharchive_include_node_type']);
    variable_set('montharchive_block_node_type', $edit['montharchive_block_node_type']);
    variable_set('montharchive_block_node_type_by_user', $edit['montharchive_block_node_type_by_user']);
    
    variable_set('montharchive_block_link_max', $edit['montharchive_block_link_max']);
    variable_set('montharchive_rev_linksort', $edit['montharchive_rev_linksort']);
    variable_set('montharchive_show_linkcount', $edit['montharchive_show_linkcount']);
    variable_set('montharchive_rev_pagesort', $edit['montharchive_rev_pagesort']);
    variable_set('montharchive_paginate', $edit['montharchive_paginate']);
    drupal_set_message('The configuration options have been saved.');
  }
  menu_rebuild();
}

/**
 * montharchive_settings_form validation function
 *
 * @param array $form
 * @param array $form_state
 */
function montharchive_settings_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['montharchive_block_link_max'])) {
    form_set_error('montharchive_block_link_max', 'Maximum number of links must be numeric.');
  }
}

function montharchive_settings_type_path_form() {
  $token_user = module_load_include('inc', 'token', 'token_user');
  $tokens = montharchive_token_list('montharchive');
  foreach ($tokens['montharchive'] as $key => $value) {
    $token_help[] = "<strong>$key</strong>: $value";
  }
  $tokens = user_token_list('user');
  foreach ($tokens['user'] as $key => $value) {
    $user_token_help[] = "<strong>$key</strong>: $value";
  }
  $archive_path = variable_get('montharchive_path', 'archive');  
  $output['global'] = array(
    '#tree' => FALSE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
    '#title' => t('Link text'),     
    'montharchive_link_text' => array(
      '#type' => 'textfield', 
      '#default_value' => variable_get('montharchive_link_text', '[month] [yyyy]'), 
      '#description' => t('Define how the block link text is constructed. This pattern will be used in all generated blocks.')
    ),
    'help' => array(
      '#tree' => FALSE, 
      '#type' => 'fieldset', 
      '#collapsible' => TRUE, 
      '#collapsed' => TRUE, 
      '#title' => t('Replacement patterns'), 
      'output' => array(
        '#type' => 'markup', 
        '#value' => theme('item_list', $token_help), 
        '#prefix' => '<div>', 
        '#sufffix' => '</div>'
      )
    )
  );

  $output['archive_paths'] = array(
    '#tree' => FALSE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
    '#title' => t('Archive paths'),     
    'montharchive_path' => array(
      '#type' => 'textfield', 
      '#required' => TRUE,
      '#title' => t('Global archive root'), 
      '#default_value' => $archive_path, 
      '#description' => t('Enter the path to use as the archive path. Please use only letters, numbers and underscores (_). No token substitution will be done on this variable. The global archive path
      will be "archive_path/year/month".'),
    )
  );
    
  $output['archive_paths']['montharchive_path_order'] = array(   
    '#type' => 'radios', 
    '#title' => t('Node type archive path'), 
    '#options' => array(
      ARCHIVEROOTBEFORETYPE => $archive_path . '/node_path', 
      TYPEBEFOREARCHIVEROOT => 'node_path/' . $archive_path
    ), 
    '#default_value' => variable_get('montharchive_path_order', ARCHIVEROOTBEFORETYPE), 
    '#description' => 'Select the order in which the parts of node specific archive appear in the path to the archive page. The node type archive paths will be
    archive_path/node_type/year/month or node_type/archive_path/year/month.',
  );
  
  $output['archive_paths']['node_type'] = array(
    '#tree' => TRUE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
  	'#title' => t('Archive by type paths'),
  	'#description' => t("Enter the path to use as the %node_type archive path. Please use only letters, numbers and underscores (_). No token substitution will be done on this variable. ", array('%nodetyep =>$node_type')),
  );
  
  $node_types = variable_get('montharchive_block_node_type', array());
  foreach ($node_types as $key => $node_type) {
    if ($node_type) {
      $output['archive_paths']['node_type']['path'][$node_type] = array(      
        '#type' => 'textfield', 
        '#required' => TRUE,
        '#title' => node_get_types('name', $node_type) . t(' archive path'), 
        '#default_value' => variable_get('montharchive_' . $node_type . '_path', $node_type),				
      );
    }
  }  
  
  $author_path = variable_get('montharchive_author_path', 'author');  
  $output['archive_paths']['montharchive_author_path'] = array(
    '#type' => 'textfield', 
  	'#required' => TRUE,
    '#title' => t('Author archive root'), 
    '#default_value' => $author_path, 
    '#description' => t('Enter the path to use as the author archive path. Please use only letters, numbers and underscores (_). No token substitution will be done on this variable. '),
    '#prefix' => '<hr />',
  );  
  $output['archive_paths']['montharchive_author_uid_or_name'] = array(   
    '#type' => 'radios', 
    '#title' => t('Author path'), 
    '#options' => array(
      'uid' => $author_path . '/uid', 
      'user-name' => $author_path . '/user-name',
    ), 
    '#default_value' => variable_get('montharchive_author_uid_or_name', 'uid'), 
    '#description' => 'Set the author archive paths to use the user id (author_path/uid) or the user name (author_path/user-name). Spaces will be converted to hyphens.'
  );
  
  $output['archive_paths']['montharchive_author_path_order'] = array(   
    '#type' => 'radios', 
    '#title' => t('Author archive path'), 
    '#options' => array(
      ARCHIVEROOTBEFORETYPE => $author_path . '/node_path', 
      TYPEBEFOREARCHIVEROOT => 'node_path/' . $author_path
    ), 
    '#default_value' => variable_get('montharchive_author_path_order', ARCHIVEROOTBEFORETYPE), 
    '#description' => 'Select the order in which the parts of node specific archive appear in the path to the archive page. <br />
    The node type archive paths will be author_path/user/node_type/year/month or node_type/author_path/user/year/month.'
  );
  $output['archive_paths']['author'] = array(
    '#tree' => TRUE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
  	'#title' => t('Author archive by type paths'),
		'#description' => t('Enter the path to use as the %node_type archive path. Please use only letters, numbers and underscores (_). '),
  );
  $node_types = variable_get('montharchive_block_node_type_by_user', array());
  foreach ($node_types as $key => $node_type) {
    if ($node_type) {
      $output['archive_paths']['author']['path'][$node_type] = array(
        '#type' => 'textfield', 
      	'#required' => TRUE,
        '#title' => node_get_types('name', $node_type) . t(' archive path'), 
        '#default_value' => variable_get('montharchive_path_by_user_' . $node_type, $node_type),
      );
    }
  }
    
  $output['titles'] = array(
    '#tree' => FALSE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
  	'#title' => t('Archive page titles'),
    'montharchive_title' => array(
      '#type' => 'textfield', 
      '#title' => t('Global archive title'), 
      '#default_value' => variable_get('montharchive_title', 'Monthly archive [month] [yyyy]'), 
      '#description' => t('Enter the base title to use for the archive pages.')
    ), 
  );
  $output['titles']['node_type'] = array(
    '#tree' => TRUE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
  	'#title' => t('Archive by type page titles'),
  );
  
  $node_types = variable_get('montharchive_block_node_type', array());
  foreach ($node_types as $key => $node_type) {
    if ($node_type) {
      $output['titles']['node_type']['title'][$node_type] = array(      
        '#type' => 'textfield', 
        '#title' => node_get_types('name', $node_type) . t(' archive title'), 
        '#default_value' => variable_get('montharchive_' . $node_type . '_title', '[type_name] [month] [yyyy]')
      );
    }
  }  
  $output['titles']['node_type']['title']['help'] = array(
    '#tree' => FALSE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
    '#title' => t('Replacement patterns'), 
    'output' => array(
      '#type' => 'markup', 
      '#value' => theme('item_list', $token_help), 
      '#prefix' => '<div>', 
      '#sufffix' => '</div>'
    )
  );
  
  $output['titles']['author'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
  	'#title' => t('Author archive by type page titles')
  );
  $node_types = variable_get('montharchive_block_node_type_by_user', array());
  foreach ($node_types as $key => $node_type) {
    if ($node_type) {
      $output['titles']['author']['title'][$node_type] = array(
        '#type' => 'textfield', 
        '#title' => node_get_types('name', $node_type) . t(' archive title'), 
        '#default_value' => variable_get('montharchive_title_by_user_'. $node_type , '[user]\'s [type_name] archive [month] [yyyy]'),
      );
    }
  }
  $output['titles']['author']['title']['help'] = array(
    '#tree' => FALSE, 
    '#type' => 'fieldset', 
    '#collapsible' => TRUE, 
    '#collapsed' => TRUE, 
    '#title' => t('Replacement patterns'), 
    'output' => array(
      '#type' => 'markup', 
      '#value' => theme('item_list', array_merge($token_help, $user_token_help)), 
      '#prefix' => '<div>', 
      '#sufffix' => '</div>',
    )
  );
  
  $output = system_settings_form($output);
  $output['#submit'] = array(
    'montharchive_settings_type_path_submit'
  );
  $output['#validate'][] = 'montharchive_settings_type_path_validate';
  return $output;
}

/**
 * montharchive_settings_type_path_form reset function
 */
function montharchive_settings_type_path_form_reset() {
  variable_del('montharchive_link_text');
  variable_del('montharchive_path');
  variable_del('montharchive_title');
  variable_del('montharchive_path_order');
  variable_del('montharchive_author_path');  
  variable_del('montharchive_author_path_order');
  variable_del('montharchive_author_uid_or_name');
  $node_types = node_get_types('names');
  foreach ($node_types as $key => $node_type) {
    if ($node_type) {
      variable_del('montharchive_' . $key . '_path');
      variable_del('montharchive_' . $key . '_title');
      variable_del('montharchive_title_by_user_'. $key);
      variable_del('montharchive_path_by_user_'. $key);
    }
  }
}

/**
 * montharchive_settings_type_path_form submit function
 * @param $form
 * @param $form_state
 */
function montharchive_settings_type_path_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == 'Reset to defaults') {
    montharchive_settings_type_path_form_reset();
    drupal_set_message('The path and title configuration options have been reset to their default values.');
  }
  else {
    $edit = $form_state['values'];
    variable_set('montharchive_link_text', $edit['montharchive_link_text']);
    variable_set('montharchive_path', $edit['montharchive_path']);
    variable_set('montharchive_title', $edit['montharchive_title']);
    variable_set('montharchive_path_order', $edit['montharchive_path_order']);
    variable_set('montharchive_author_path', $edit['montharchive_author_path']);    
    variable_set('montharchive_author_path_order', $edit['montharchive_author_path_order']);
    variable_set('montharchive_author_uid_or_name', $edit['montharchive_author_uid_or_name']);
    $edit = $form_state['values']['node_type']['path'];
    foreach ($edit as $key => $value) {
      variable_set('montharchive_' . $key . '_path', $value);
    }
    $edit = $form_state['values']['node_type']['title'];
    foreach ($edit as $key => $value) {
      variable_set('montharchive_' . $key . '_title', $value);
    }
    $edit = $form_state['values']['author']['path'];
    foreach ($edit as $key => $value) {
      variable_set('montharchive_path_by_user_'. $key, $value);
    }
    $edit = $form_state['values']['author']['title'];
    foreach ($edit as $key => $value) {
      variable_set('montharchive_title_by_user_'. $key, $value);
    }
    drupal_set_message('The path and title configuration options have been saved.');
  }
  menu_rebuild();
}

/**
 * montharchive_settings_type_path_form validation function
 * @param $form
 * @param $form_state
 */
function montharchive_settings_type_path_validate($form, &$form_state) {
  $found = preg_match('%^[a-z|0-9|_]+$%', $form_state['values']['montharchive_path']);
  if (!$found) {
    form_set_error('global', 'Archive path must be all lowercase, and begin with an alphabetic character or underscore. The remainder must be all alphanumerics.', TRUE);
  }  
  
  $edit = $form_state['values']['node_type']['path'];
  foreach ($edit as $value) {
    $found = preg_match('%^[a-z|0-9|_]+$%', $value['path']);
    if (!$found) {
      form_set_error("node_type][path][$type", 'Archive path must be all lowercase, and begin with an alphabetic character or underscore. The remainder must be all alphanumerics.', TRUE);
    }
  }
  $unique_edit = array_unique($edit);
  $diff_edit = array_diff_assoc($edit, $unique_edit);
  if(count($diff_edit) > 0) {
    foreach ($diff_edit as $type => $path) {
      form_set_error("node_type][path][$type", 'Archive path by node type must be unique.', TRUE);
    }
  }
  
  $edit = $form_state['values']['author']['path'];
  foreach ($edit as $value) {
    $found = preg_match('%^[a-z|0-9|_]+$%', $value['path']);
    if (!$found) {
      form_set_error("author][path][$type", 'Author archive path must be all lowercase, and begin with an alphabetic character or underscore. The remainder must be all alphanumerics.', TRUE);
    }
  }
  $unique_edit = array_unique($edit);
  $diff_edit = array_diff_assoc($edit, $unique_edit);
  if(count($diff_edit) > 0) {
    foreach ($diff_edit as $type => $path) {
      form_set_error("author][path][$type", 'Author archive path by node type must be unique.', TRUE);
    }
  }
}