<?php

/**
* Implementation of hook_block().
* @param string $op one of "list", "view", "save" and "configure"
* @param integer $delta code to identify the block
* @param array $edit only for "save" operation
*/
function wesnoth_hu_block($op = 'list', $delta = 0, $edit = array()) { 

  // set up an empty array which will contain the blocks
  $blocks = array();
 
  switch ($op) {
    case 'list':
      $block['forum_comments'] = array(
        'info' => 'wesnoth.hu: Friss fórum hozzászólások',
        'status' => TRUE, 
        'weight' => 0, 
        'visibility' => 1, 
        'pages' => '<front>',
      );
      return $block;
      break;
   
    case 'view':
      switch ($delta) {
        case 'forum_comments':
          // Setup the block (block['content'])
          $block['subject'] = "Friss fórum hozzászólások";
          $block['content'] = _wesnoth_hu_forum_comments_block_content();
          break;
      } // switch vége
      break; // view vége

    case "save":
      break;

    case "configure":
      break;
  }

  return $block;
}

function _wesnoth_hu_forum_comments_block_content(){
  $content = '';

  $content .= '<table><tbody>';

  $sql = 'SELECT c.nid, c.cid, c.subject, c.timestamp, s.comment_count, td.tid, td.name AS topic, c.uid, u.name AS username
    FROM {comments} AS c
      INNER JOIN {node} AS n ON c.nid = n.nid
      INNER JOIN {node_comment_statistics} AS s ON s.nid = c.nid
      INNER JOIN {term_node} AS tn ON tn.nid = c.nid
      INNER JOIN {term_data} AS td ON td.tid = tn.tid
      INNER JOIN {users} AS u ON u.uid = c.uid
    WHERE n.type = "forum"
    ORDER BY timestamp DESC
    LIMIT 10
  ';
  $result = db_query($sql);
  $i = 0;
  while($row = db_fetch_array($result)){
    if($i%2 != 0){
      $content .= '<tr class="odd">';
    }else{
      $content .= '<tr class="even">';
    }
    $page = round($row['comment_count']/variable_get('forum_per_page', 25) );
    $comment_link = url('node/'.$row['nid'], array(
      'query'=>array('page'=>$page),
      'fragment'=>'comment-'.$row['cid'])
    );
    $topic_link = url('forum/'.$row['tid']);
    $user_link = $row['username'];
    if(user_access('access user profiles')) $user_link = '<a href="'.url('user/'.$row['uid']).'">'.$row['username'].'</a>';

    $content .= '<td><a href="'.$comment_link.'">'.$row['subject'].'</a><br><span class="meta"><a href="'.$topic_link.'">'.$row['topic'].'</a></span></td>';
    $content .= '<td style="width: 250px">'.$user_link.'<br><span class="meta">'.date('Y. m. d. H.i', $row['timestamp']).'</span></td>';
    $content .= '</tr>';
    $i++;
  }

  $content .= '</tbody></table>';

  return $content;
}
