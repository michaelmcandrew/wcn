<?php

function phptemplate_body_class($left, $right) {
  if ($left != '' && $right != '') {
    $class = 'sidebars';
  }
  else {
    if ($left != '') {
      $class = 'sidebar-left';
    }
    if ($right != '') {
      $class = 'sidebar-right';
    }
  }

  if (isset($class)) {
    print ' class="'. $class .'"';
  }
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
/*
function phptemplate_breadcrumb($breadcrumb) {
	if (empty ($breadcrumb))
	{
    //$q = request_uri();
    //$listargs = split('/',$q);
    //if ($listargs[1] == 'influence-area'){
      
    //}
    //$crumb = drupa_get_breadcrumb();
		
    return '<div class="breadcrumb">' . implode(' ›› ', $breadcrumb) . '</div>';
	}
}
*/

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(& $vars) {
  //dvm($vars);
  global $user;
  //if ($user->uid == 1){
    $mycrumb = drupal_get_breadcrumb();

    //print_r($vars['title']);

    if (count($mycrumb > 1)){
      if (strstr($mycrumb[1], 'influence-area')){
        
        $q = request_uri();
        $listargs = split('/',$q);
        $final = count($listargs);
        $final -= 1;
        $newcrumb[0] = '<a href="/">Home</a>';
        $newcrumb[1] = '<a href="/influence-area/'.$listargs[$final].'">'.urldecode($listargs[$final]).'</a>';
        $vars['breadcrumb']= theme('breadcrumb', $newcrumb);       
      }
    }
  //}
  
  

}


/*
$q = request_uri();
$listargs = split('/',$q);
if (is_array($listargs)){
 if ($listargs[1] == 'influence-area'){
  $final = count($listargs);
  $final -= 1;
  if (is_numeric($listargs[$final])){
   $tid = $listargs[$final];
  }
 }
 if ($listargs[1] == 'category'){
  $final = arg(2);
  if (is_numeric($final)){
   $tid = $final;
  }
 } 
 
}


$t_object = taxonomy_get_term($tid);
$tname = $t_object->name;

$sectionhead = '<p><a class="active" href="/influence-area/'.$tid.'">'.$tname.'</a></p>';
$weblinks = '<p><a href="/influence-area/useful-links/'.$tid.'">Useful links</a></p>';
$webfiles = '<p><a href="/influence-area/resources/download/'.$tid.'">Useful reports</a></p>';
$webstories = '<p><a href="/influence-area/resources/story/'.$tid.'">General content</a></p>';
*/