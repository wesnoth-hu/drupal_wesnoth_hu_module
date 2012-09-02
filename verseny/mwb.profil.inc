<?php

function mwb_profil($u){
  $GLOBALS['user_id'] = $u;
  $query = db_query("SELECT `name` FROM {users} WHERE `uid`=" . $u . " LIMIT 1");
  $user_name = db_result($query);
  $display_text = '<div class="profile">';
  $display_text .= "<h3>Wesnoth adatok - " . $user_name . "</h3>";
 
  if(user_access('administer mwb')){
    // ha van adminisztrációs jog, akkor mutass űrlapot
    $display_text .= drupal_get_form('mwb_profil_form');
  }else{
  	// ha nincs adminisztrációs jog, akkor csak mutasd az adatokat
	$rang = 0;
    $helyezesek = '';
    $query = db_query('SELECT * FROM {profile_values} WHERE (`fid`=13 OR `fid`=14) AND `uid`=%d LIMIT 2', $GLOBALS['user_id']);
    while($r = db_fetch_array($query)){
		if($r['fid'] == 14) $rang = $r['value'];
		if($r['fid'] == 13) $helyezesek = $r['value'];
	}
	if(strlen($helyezesek) > 0){
      $display_text .= '<dl>';
      $display_text .= '<dt>Ranglista helyezés: </dt><dd>'.$rang.'. hely</dd>';
      $helyezesek_tomb = json_decode($helyezesek);
      foreach($helyezesek_tomb as $e){
        $display_text .= $e[0].': '.$e[1].'. hely<br />';
      }
      $display_text .= '</dl>';
	}else{
      $display_text .= '<p>A játékos még nem szerzett pontot a portálon szerzett versenyeken.</p>';
    }
  }
  $display_text .= '</div>';
  return $display_text;
}

function mwb_profil_form($form_state){
  $helyezesek = '';
  $query = db_query('SELECT * FROM {profile_values} WHERE `fid`=13 AND `uid`=%d LIMIT 1', $GLOBALS['user_id']);
  while($r = db_fetch_array($query)){
    if($r['fid'] == 13) $helyezesek = $r['value'];
  }
  $helyezesek_tomb = json_decode($helyezesek, true);
  $champ_count = count($helyezesek_tomb);

  // Add a wrapper for the choices and more button.
  $form['champ_wrapper'] = array(
      '#tree' => FALSE,
      '#weight' => 0,
      '#prefix' => '<div class="clear-block">',
      '#suffix' => '</div>',
      );
  
  $form['champ_wrapper']['champ'] = array(
      '#tree' => FALSE,
      '#weight' => 0,
      '#prefix' => '<div class="clear-block">',
      '#suffix' => '</div>',
      );
  
  // if the form is being generated from an ahah callback, $form_state['quicktabs'] will
  // contain the posted values of the form - if it's an edit form, the contents of 
  // $quicktabs will be coming from the database
  if (isset($form_state['previous'])) {
  	foreach($form_state['previous'] as $i=>$details){
      $form['champ_wrapper']['champ'][$i] = _mwb_champ_form($i, $details);
	}
  }else{
    if(count($helyezesek_tomb) > 0){
    	foreach($helyezesek_tomb as $i=>$details){
         $form['champ_wrapper']['champ'][$i] = _mwb_champ_form($i, $details);
      }
    }else{
      $form['champ_wrapper']['champ'][0] = _mwb_champ_form(0);
    }
  }
 
  $form['champ_wrapper']['champ_more'] = array(
      '#type' => 'submit',
      '#value' => 'Több helyezés hozzáadása',
      '#weight' => 1,
      '#submit' => array('mwb_profil_ujhelyezes_submit'), // If no javascript action.
      /*
      '#ahah' => array(
        'path' => 'poll/js',
        'wrapper' => 'champ-choices',
        'method' => 'replace',
        'effect' => 'fade',
        ),
        */
      );
  
  $form['champ_wrapper']['champ_submit'] = array(
      '#type' => 'submit',
      '#value' => 'Eredmények felvitele',
      '#weight' => 2,
      '#submit' => array('mwb_profil_form_submit'), // If no javascript action.
    );
	
	return $form;
}

/**
 * Submit handler to add more choices to a poll form. This handler is used when
 * javascript is not available. It makes changes to the form state and the
 * entire form is rebuilt during the page reload.
 */
function mwb_profil_ujhelyezes_submit($form, &$form_state) {
  unset($form_state['submit_handlers']);
  //form_execute_handlers('submit', $form, $form_state);
  $form_state['rebuild'] = TRUE;
  
  $maxi = count($form_state['values']['champ']);

  // ha hozzáadunk
  if ($form_state['values']['op'] == 'Több helyezés hozzáadása') {
	$form_state['values']['champ'][] = Array('chgroup'=>'', 'chrank'=>'');
  }
  
  // ha elveszünk
  for($i=0; $i<$maxi; $i++){
    if($form_state['values']['op'] == ($i+1).'. eredmény törlése'){
      unset($form_state['values']['champ'][$i]);
    }
  }


  $form_state['previous'] = $form_state['values']['champ'];

  print_r($form_state['values']);

  return $form_state;
}

function _mwb_champ_form($delta, $details=Array('chgroup'=>'', 'chrank'=>'')) {
  $form = array(
    '#tree' => TRUE,
  );

  // We'll manually set the #parents property of these fields so that
  // their values appear in the $form_state['values']['choice'] array.
  $t = Array();
  $query = db_query('SELECT `csid`, `nev` FROM {mwb_csoportok} WHERE `szulo`=\'%s\' ORDER BY `csid`', '/');
  while($r = db_fetch_array($query)){
    $t[$r['csid']] = $r['nev'];
  }

  $form['chentry'] = array(
    '#type' => 'fieldset',
    '#title' => ($delta+1).'. verseny',
  );

  $form['chentry']['chgroup'] = array(
    '#type' => 'select',
    '#title' => ($delta+1).'. verseny',
    '#default_value' => $details['chgroup'],
    '#parents' => array('champ', $delta, 'chgroup'),
    '#options' => $t,
  );
  $form['chentry']['chrank'] = array(
    '#type' => 'textfield',
    '#title' => ($delta+1).'. versenyen elért helyezés',
    '#default_value' => $details['chrank'],
    '#size' => 5,
    '#maxlength' => 3,
    '#parents' => array('champ', $delta, 'chrank'),
  );
  $form['chentry']['chdelete_'.$delta] = array(
      '#type' => 'submit',
      '#value' => ($delta+1).'. eredmény törlése',
      '#weight' => 1,
      '#submit' => array('mwb_profil_ujhelyezes_submit'), // If no javascript action.
  );

  return $form;
}

function mwb_profil_form_submit($form, &$form_state) {
  $tomb = Array();
  foreach($form_state['values']['champ'] as $e){
    $tomb[] = Array('chgroup'=>$e['chgroup'], 'chrank'=>$e['chrank']);
  }
  $valtozo = json_encode($tomb);

  if($form_state['values']['op'] == 'Eredmények felvitele'){
    $query = db_query('SELECT `fid` FROM {profile_values} WHERE `fid`=13 AND `uid`=%d LIMIT 1', $GLOBALS['user_id']);
    if(db_result($query)){
      // ha van már ilyen mező, frissítsd
      $q = db_query('UPDATE {profile_values} SET `value`=\'%s\' WHERE `fid`=13 AND `uid`=%d LIMIT 1', $valtozo, $GLOBALS['user_id']);
      if($q) drupal_set_message("Eredmények felvitele megtörtént!");
    }else{
      // ha még nincs ilyen mező, írd bele
      $q = db_query('INSERT INTO {profile_values} (`fid`, `uid`, `value`) VALUES (13, %d, \'%s\')', $GLOBALS['user_id'], $valtozo);
          if($q) drupal_set_message("Eredmények felvitele megtörtént!");
          }
  }

  return $form_state;
}
