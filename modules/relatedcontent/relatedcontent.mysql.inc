<?php // $Id: relatedcontent.mysql.inc,v 1.1.2.5.2.1 2009/06/07 13:28:46 peterboeren Exp $

/* relatedcontent.mysql.inc,v 1.1.2.5 2008/01/27 22:22:21 tbarregren Exp $
 *
 * Copyright (C) 2008 Thomas Barregren.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


/**
 * @file
 * MySQL queries for RelatedContent – a Drupal module that Allows privileged
 * users to associate a node with related nodes that can be displayed along
 * with the node.
 *
 * Each function below must return a string that can be passed into db_query()
 * as the query argument. The additional arguments that will be passed into
 * db_query() are passed in an array to the function. The function may use
 * these arguments to build the query, or alter them.
 *
 * Author:
 *   Thomas Barregren <http://drupal.org/user/16678>.
 *
 * Ported to drupal 6.x by Peter Boeren
 */


/******************************************************************************
 * MYSQL QUERIES
 ******************************************************************************/

function _relatedcontent_db_content_type_query() {
  return <<<SQL
SELECT type FROM {node} WHERE nid = %d
SQL;
}

function _relatedcontent_db_enabled_views_query() {
    return <<<SQL
SELECT * from {relatedcontent_view} r WHERE r.enabled = %d
ORDER BY weight, title
SQL;
}

function _relatedcontent_db_get_views_for_type_query() {
    return <<<SQL
SELECT * FROM {relatedcontent_view} where type = '%s'
SQL;
}

function _relatedcontent_db_get_enabled_views_for_type_query() {
    return <<<SQL
SELECT * FROM {relatedcontent_view} where type = '%s' and enabled = %d
SQL;
}

function _relatedcontent_db_set_view_update_query() {
  return <<<SQL
UPDATE {relatedcontent_view} SET enabled = %d, title='%s', weight = %d WHERE vid = '%s' AND type = '%s'
SQL;
}

function _relatedcontent_db_set_view_insert_query() {
  return <<<SQL
INSERT INTO {relatedcontent_view} (type, vid, title, weight, enabled) VALUES ('%s', '%s', '%s', %d, %d)
SQL;
}

function _relatedcontent_db_load_query() {
  return <<<SQL
SELECT r.nid, r.vid, r.include_nid FROM {relatedcontent} r
  INNER JOIN {relatedcontent_view} v ON r.vid = v.vid AND r.nid = %d
ORDER BY v.weight, r.ordinal_number
SQL;
}

function _relatedcontent_db_insert_query(&$values) {

  foreach ($values as $value) {
    $value[1] = "'$value[1]'";
    $str .= '('. implode(',', $value) .'),';
  }
  $str = drupal_substr($str, 0, -1);
  $values = array();
  return <<<SQL
INSERT INTO {relatedcontent} (nid, vid, include_nid, ordinal_number) VALUES $str
SQL;
}

function _relatedcontent_db_delete_query($args) {
  $and_vid = $args[1] ? "AND vid = '%s'" : '';
  return <<<SQL
DELETE FROM {relatedcontent} WHERE nid = %d $and_vid
SQL;
}

// load the title of a node
function _relatedcontent_db_load_title_query($args) {
  return <<<SQL
  SELECT title FROM {node} WHERE nid = $args[0]
SQL;
}

// load the type of a node
function _relatedcontent_db_load_type_query($args) {
  return <<<SQL
  SELECT type FROM {node} WHERE nid = $args[0]
SQL;
}