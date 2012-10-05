<?php

/**
* Implementation of hook_block().
* @param string $op one of "list", "view", "save" and "configure"
* @param integer $delta code to identify the block
* @param array $edit only for "save" operation
*/
function wesnoth_hu_block($op = 'list', $delta = 0, $edit = array()) { 
  // set up an empty array which will contain the blocks
  $block = array();
 
  switch ($op) {
    case 'list':
      $block['forum_comments'] = array(
        'info' => 'wesnoth.hu: Friss fórum hozzászólások',
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
  $maxlimit = 10;

  $content .= '<table><tbody>';

  $nodes = array();
  $sql = 'SELECT n.nid, n.title AS subject, n.timestamp, td.tid, td.name AS topic, n.uid, u.name AS username
    FROM {node_revisions} AS n
      INNER JOIN {node} AS no ON no.nid = n.nid
      INNER JOIN {term_node} AS tn ON tn.nid = n.nid
      INNER JOIN {term_data} AS td ON td.tid = tn.tid
      INNER JOIN {users} AS u ON u.uid = n.uid
    WHERE no.type = "forum"
    ORDER BY timestamp DESC
    LIMIT '.$maxlimit.'
  ';
  $result = db_query($sql);
  while($row = db_fetch_array($result)){
    $link = '';
    $nodes[$row['timestamp']] = array(
      'subject'=>$row['subject'],
      'link'=>url('forum/tema/'.$row['nid'] ),
      'topic'=>$row['topic'],
      'topic_link'=>url('forum/'.$row['tid']),
      'username'=>$row['username'], 
      'uid'=>$row['uid'],
    );
  }

  $comments = array();
  $sql = 'SELECT c.nid, c.cid, c.subject, c.timestamp, s.comment_count, td.tid, td.name AS topic, c.uid, u.name AS username
    FROM {comments} AS c
      INNER JOIN {node} AS n ON c.nid = n.nid
      INNER JOIN {node_comment_statistics} AS s ON s.nid = c.nid
      INNER JOIN {term_node} AS tn ON tn.nid = c.nid
      INNER JOIN {term_data} AS td ON td.tid = tn.tid
      INNER JOIN {users} AS u ON u.uid = c.uid
    WHERE n.type = "forum"
    ORDER BY timestamp DESC
    LIMIT '.$maxlimit.'
  ';
  $result = db_query($sql);
  while($row = db_fetch_array($result)){
    $page = round($row['comment_count']/variable_get('forum_per_page', 25) );
    $comment_link = url('node/'.$row['nid'], array(
      'query'=>array('page'=>$page),
      'fragment'=>'comment-'.$row['cid'])
    );
    $topic_link = url('forum/'.$row['tid']);
    $comments[$row['timestamp']] = array(
      'subject'=>$row['subject'],
      'link'=>$comment_link,
      'topic'=>$row['topic'],
      'topic_link'=>$topic_link,
      'username'=>$row['username'],
      'uid'=>$row['uid'],
    );
  }

  $merged = $nodes + $comments;
  ksort($merged);
  $merged = array_reverse($merged, true);

  // az összevont dologból mutatjuk meg a legfrissebb 10-et
  $i = 0;
  foreach($merged as $k=>$m ){
    if($i%2 != 0){
      $content .= '<tr class="odd">';
    }else{
      $content .= '<tr class="even">';
    }
    $i++;
    $user_link = $m['username'];
    if(user_access('access user profiles')) $user_link = '<a href="'.url('user/'.$m['uid']).'">'.$m['username'].'</a>';

    $content .= '<td><a href="'.$m['link'].'">'.$m['subject'].'</a><br><span class="meta"><a href="'.$m['topic_link'].'">'.$m['topic'].'</a></span></td>';
    $content .= '<td style="width: 250px">'.$user_link.'<br><span class="meta">'.date('Y. m. d. H.i', $k).'</span></td>';
    $content .= '</tr>';

    // limitáld 
    if($i >= $maxlimit) break;
  }

  $content .= '</tbody></table>';

  return $content;
}
