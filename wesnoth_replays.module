<?php
// $Id$

function wesnoth_replays_init(){
  // változók definiálása
  $GLOBALS['_wreplays_tipus'] = array(
    'egyeb' => 'Egyéb',
    'bajnoksag' => 'Bajnokság',
  );

  $GLOBALS['_wreplays_bajnoksagmappa'] = '2011_mwb';
  
  $GLOBALS['_wreplays_csoportok'] = array();
  $query = db_query("SELECT `csid`, `nev` FROM {mwb_csoportok}");
  while($r = db_fetch_array($query)){
    $GLOBALS['_wreplays_csoportok'][$r['csid']] = $r['nev'];
  }
}

function wesnoth_replays_node_info() {
  return array(
    'wesnoth_replays' => array(
      'name' => 'Wesnoth visszajátszás',
      'module' => 'wesnoth_replays',
      'description' => "A wesnoth visszajátszásokat lehet feltenni vele.",
    )
  );
}

function wesnoth_replays_perm() {
  return array('access wesnoth replays', 'administer wesnoth replays', 'edit any wesnoth replays', 'edit own wesnoth replays');
}

function wesnoth_replays_access($op, $node, $account){
  // hozzáférések meghatározása

  // adatok lekérdezése
  $query = db_query("SELECT `jatekos1`, `jatekos2` FROM {mwb_merkozesek} WHERE `mid`=%d LIMIT 1", $node->mid);
  $adatok = db_fetch_array($query);
  
  if($op == 'create'){
    // ellenőrizd, hogy bajnokság, vagy sima mérkőzést akar-e feltölteni
    return user_access('edit own wesnoth replays');
  }
  
  if($op == 'update'){
    if($GLOBALS['user']->uid == $adatok['jatekos1'] || $GLOBALS['user']->uid == $adatok['jatekos2']){
      return user_access('edit own wesnoth replays');
    }else{
      return user_access('edit any wesnoth replays');
    }
  }
 
  if($op == 'delete'){
    return FALSE;
  }

  if($op == 'view'){
    return user_access('access wesnoth replays');
  }
}

function _wreplays_uid2nick($id){
  $s = "";
	if(empty($id)){
		return false;
	}
	$query = db_query("SELECT `nev`, `kizarva` FROM {mwb_jelentkezok} WHERE `uid`=".$id." LIMIT 1");
	$r = db_fetch_array($query);
	if(is_array($r)){
		$s .= $r['nev'];
	}else{
		$u = user_load($id);
		$s .= $u->name;
	}
	return $s;
}

function wesnoth_replays_merkozeshez($mid){
  $node = new stdClass();
  $node->type = 'wesnoth_replays';
  $node->title = 'Wesnoth visszajátszás';
  $node->body = '';
  $node->uid = 0;
  $node->status = 1;
  $node->mid = $mid;
  $node->comment = 2; // legyen írható, olvasható
  $node->tipus = 'bajnoksag';

  node_save($node);
}

function wesnoth_replays_form(&$node, &$form_state){
  $uj = false;
  if($node->fid == 0){
    $uj = true;
  }
  $mid = $node->mid;
  $type = node_get_types('type', $node);
  
  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $node->rid,
  );
  
  $form['mid'] = array(
    '#type' => 'hidden',
    '#value' => $node->mid,
  );
  
  $form['tipus'] = array(
    '#type' => 'hidden',
  );
  if(isset($mid)){
    $form['tipus']['#value'] = 'bajnoksag';
  }else{
    $form['tipus']['#value'] = 'egyeb';
    $form['info'] = array(
      '#value' => '<div class="messages"><strong>Jelenleg az egyéb mérkőzések űrlapot használod.</strong> Ha verseny mérkőzéshez szeretnél visszajátszást feltölteni, kérlek használd a mérkőzések oldalon lévő <strong>"Visszajátszás feltöltése"</strong> linket!</div>',
      '#weight' => -10,
    );
  }
  
  // We need to define form elements for the node's title and body.
  $form['title'] = array(
    '#type' => 'hidden',
    '#value' => $node->title,
  );
  if($uj) $form['title']['#value'] = 'Wesnoth visszajátszás '.$rid;

  if(isset($mid)){
    // információ gyűjtés
    $query = db_query("SELECT `jatekos1`, `jatekos2`, `gyoztes`, `palya` FROM {mwb_merkozesek} WHERE `mid`=%d LIMIT 1", $mid);
    $merkozes = db_fetch_array($query);
  }

  // első játékos mező 
  $form['jatekos1'] = array(
    '#type' => 'textfield',
    '#title' => 'Játékos 1',
    '#default_value' => $node->jatekos1,
    '#weight' => -10,
  );
  if(isset($mid)) $form['jatekos1']['#default_value'] = _wreplays_uid2nick($merkozes['jatekos1']);
  $form['jatekos2'] = array(
    '#type' => 'textfield',
    '#title' => 'Játékos 2',
    '#default_value' => $node->jatekos2,
    '#weight' => -9,
  );
  if(isset($mid)) $form['jatekos2']['#default_value'] = _wreplays_uid2nick($merkozes['jatekos2']);

  // pálya mező
  if(isset($mid)){
    $form['palya'] = array(
      '#title' => 'Pálya',
      '#type' => 'select',
      '#options' => _mwb_palyak_tomb($GLOBALS['_mwb_alap_csoport']),
      '#default_value' => $merkozes['palya'],
      '#weight' => -7,
    );
  }else{
    $form['palya'] = array(
      '#title' => 'Pálya',
      '#type' => 'textfield',
      '#default_value' => $node->palya,
      '#weight' => -7,
    );
  }
  if(isset($mid)){ 
    $form['gyoztes'] = array(
      '#type' => 'textfield',
      '#title' => 'Mérkőzés győztese',
      '#description' => 'Add meg a mérkőzés győztesének nevét! A bajnokság alatt használt név kell (fentről puskázhatsz) vagy "döntetlen".',
      '#default_value' => $node->gyoztes,
      '#weight' => -8,
    );
  }
  
  $form['body'] = array(
    '#type' => 'textarea',
    '#title' => 'Megjegyzés',
    '#description' => 'A mérkőzés rövid leírása, fajok, taktikák stb.',
    '#required' => 'required',
    '#default_value' => $node->body,
    '#size' => 20,
    '#weight' => -5,
  );
  
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['visszajatszas'] = array(
    '#type' => 'file',
    '#title' => 'Visszajátszás',
    '#description' => 'A visszajátszás. Kizárólag a gz kiterjesztésű visszajátszást töltsed fel! Amennyiben a visszajátszás több részletben van meg, tömörítsd őket zip fájlba! A megengedett fájlméret: ' . round(file_upload_max_size()/1024, 0) . 'kb.',
    '#weight' => -4,
  );
  if($node->fid){
    $query = db_query("SELECT `filename`, `filepath` FROM {files} WHERE `fid`=%d LIMIT 1", $node->fid);
    while($r = db_fetch_array($query)){
      $form['visszajatszas']['#prefix'] = 'Korábban feltöltött visszajátszás: <a href="'.file_create_url($r['filepath']).'">' . $r['filename'] . '</a>';
    }
    $form['korabbi-visszajatszas'] = array(
      '#type' => 'hidden',
      '#value' => $node->fid,
    );
  }
  
  $form['verzio'] = array(
    '#type' => 'select',
    '#title' => 'Visszajátszás verziója',
    '#description' => 'Kérlek add meg, hogy a játék melyik verziójával készült a visszajátszás!',
    '#options' => array(
      '1-0' => '1.0',
      '1-2' => '1.2',
      '1-4' => '1.4',
      '1-6' => '1.6',
      '1-8' => '1.8',
      '1-10' => '1.10',
    ),
    '#default_value' => $node->verzio,
    '#weight' => -3,
  );
  if($uj) $form['verzio']['#default_value'] = '1-8';
  
  $form['#validate'] = array('wesnoth_replays_form_validate');

  return $form;
}

function wesnoth_replays_form_alter(&$form, $form_state, $form_id){
  switch ($form_id) {
    case 'wesnoth_replays_node_form':
      unset($form['buttons']['delete']);
      break;
  }
}

function wesnoth_replays_form_validate($form, &$form_state){
  $adatok = $form_state['values'];
  $fnev = $_FILES['files']['name']['visszajatszas'];
  $frissites = false;
  if(!empty($fnev)){
    $validators = array(
      'file_validate_extensions' => array('gz zip'),
      'file_validate_size' => array(file_upload_max_size()),
    );
    if($adatok['tipus'] == 'bajnoksag'){
      $mappa = file_directory_path().'/visszajatszasok/'.$GLOBALS['_wreplays_bajnoksagmappa'].'/';
    }else{
      $mappa = file_directory_path().'/visszajatszasok';
    }
    $file = file_save_upload('visszajatszas', $validators, $mappa, FILE_EXISTS_RENAME);
    if (!$file) {
      form_set_error('visszajatszas', 'Érvényes fájlt töltsél fel!');
    } else {
      $form_state['values']['fajl'] = $file;
      $frissites = true;
    }
  }else{
    if(empty($adatok['korabbi-visszajatszas'])){
      form_set_error('visszajatszas', 'Tallózz egy visszajátszást!');
    }else{
      $frissites = true;
    }
  }

  // adatok frissítése a mérkőzések táblában
  if($adatok['tipus'] == 'bajnoksag' && $frissites){
    $query = db_query("SELECT `jatekos1`, `jatekos2`, `palya`, `csoport` FROM {mwb_merkozesek} WHERE `mid`=%d LIMIT 1", $adatok['mid']);
    while($r = db_fetch_array($query)){
      $merkozes_adatok = $r;
      $form_state['values']['jatekos1'] = _wreplays_uid2nick($r['jatekos1']);
      $form_state['values']['jatekos2'] = _wreplays_uid2nick($r['jatekos2']);
    }
    if($adatok['gyoztes'] != _wreplays_uid2nick($merkozes_adatok['jatekos1']) && $adatok['gyoztes'] != _wreplays_uid2nick($merkozes_adatok['jatekos2']) && $adatok['gyoztes'] != 'döntetlen'){
      // a győztes neve nem egyezik meg egyikkel sem, ez gond
      form_set_error('gyoztes', 'A győztes neve nem stimmel a játékosok nevével! Győztesnek valamelyik fél bajnokságban használt nevét kell beírnod vagy azt, hogy "döntetlen"!');
    }else{
      // a győztes neve megfelelő, vidd be a bajnokságba
      if($adatok['gyoztes'] == _wreplays_uid2nick($merkozes_adatok['jatekos1'])){
        $gyoztes = $merkozes_adatok['jatekos1'];
      }else if($adatok['gyoztes'] == _wreplays_uid2nick($merkozes_adatok['jatekos2'])){
        $gyoztes = $merkozes_adatok['jatekos2'];
      }else{
	  	$gyoztes = 1;
	  }
      db_query('UPDATE {mwb_merkozesek} SET `gyoztes`=%d, `palya`=\'%s\', `ellenorizve`=0 WHERE `mid`=%d LIMIT 1', $gyoztes, $adatok['palya'], $adatok['mid']); // mérkőzések felírása
      _mwb_pontszam_frissit($merkozes_adatok['csoport']); //pontszámok frissítése

      // pálya teljes nevét adjuk tovább
      $ptomb = _mwb_palyak_tomb($GLOBALS['_mwb_alap_csoport']);
      $form_state['values']['palya'] = $ptomb[$adatok['palya']];
    }
  }
}

function wesnoth_replays_load($node){
  $additions = db_fetch_object(db_query('SELECT * FROM {wesnoth_replays} WHERE `nid`=%d', $node->nid));
  $additions->gyoztes = _wreplays_uid2nick(db_result(db_query('SELECT `gyoztes` FROM {mwb_merkozesek} WHERE `mid`=%d', $additions->mid)));
  return $additions;
}

function wesnoth_replays_insert(&$node){
  db_query("INSERT INTO {wesnoth_replays} (`nid`, `fid`, `jatekos1`, `jatekos2`, `palya`, `verzio`, `tipus`, `mid`) VALUES (%d, %d, '%s', '%s', '%s', '%s', '%s', %d)", $node->nid, $fid, $node->jatekos1, $node->jatekos2, $node->palya, $node->verzio, $node->tipus, $node->mid);
  if ($node->fajl) {
    // Do something useful with the uploaded file
    file_set_status($node->fajl, FILE_STATUS_PERMANENT);
    $fid = db_result(db_query("SELECT `fid` FROM {files} WHERE `filepath`='%s'", $node->fajl->filepath));
    db_query("UPDATE {wesnoth_replays} SET `fid`=%d WHERE `nid`=%d", $fid, $node->nid);
    db_query("INSERT INTO {upload} (`fid`, `nid`, `vid`, `description`, `list`) VALUES (%d, %d, %d, '%s', %d)", $fid, $node->nid, $node->vid, $node->fajl->filepath);
  }
}

function wesnoth_replays_update(&$node){
  db_query("UPDATE {wesnoth_replays} SET `nid`=%d, `jatekos1`='%s', `jatekos2`='%s', `palya`='%s', `verzio`='%s', `tipus`='%s', `mid`=%d WHERE `nid`=%d", $node->nid, $node->jatekos1, $node->jatekos2, $node->palya, $node->verzio, $node->tipus, $node->mid, $node->nid);
  if ($node->fajl) {
    // ellenőrizd, hogy volt-e már csatolva hozzá fájl, ha igen, akkor azt tedd törölhetővé
    $rfid = db_result(db_query("SELECT `fid` FROM {wesnoth_replays} WHERE `nid`=%d", $node->nid));
    if(!empty($rfid)){
      db_query("UPDATE {files} SET `status`=0 WHERE `fid`=%d LIMIT 1", $rfid);
      db_query("DELETE FROM {upload} WHERE `fid`=%d LIMIT 1", $rfid); // töröld a régi feltöltést a csatolmányok közül
    }
    // Do something useful with the uploaded file
    file_set_status($node->fajl, FILE_STATUS_PERMANENT);
    $fid = db_result(db_query("SELECT `fid` FROM {files} WHERE `filepath`='%s'", $node->fajl->filepath));
    db_query("UPDATE {wesnoth_replays} SET `fid`=%d WHERE `nid`=%d", $fid, $node->nid);
    db_query("INSERT INTO {upload} (`fid`, `nid`, `vid`, `description`, `list`) VALUES (%d, %d, %d, '%s', %d)", $fid, $node->nid, $node->vid, $node->fajl->filepath);
  }
}

/*
function wesnoth_replays_delete(&$node){
  db_query("DELETE FROM {node} WHERE `nid`=%d", $node->nid);
  db_query("DELETE FROM {node_revisions} WHERE `nid`=%d", $node->nid);
  if(module_exists('comment')){
    db_query("DELETE FROM {node_comment_statistics} WHERE `nid`=%d", $node->nid);
    db_query("DELETE FROM {comments} WHERE `nid`=%d", $node->nid);
  }
  db_query("DELETE FROM {wesnoth_replays} WHERE `nid`=%d", $node->nid);
  db_query("DELETE FROM {files} WHERE `fid`=%d", $node->fid);
}
*/

function wesnoth_replays_theme() {
  return array(
    'wreplays_mutasd' => array(
      'arguments' => array('node'),
    ),
  );
}

function theme_wreplays_mutasd($node){
  $display_text = "<p>";
  $display_text .= "<br />".$node->jatekos1 . " vs. ".$node->jatekos2;
  $display_text .= "<br />Pálya: ".$node->palya;
  $display_text .= "<br />".$GLOBALS['_wreplays_tipus'][$node->tipus]." mérkőzés";
  $display_text .= "</p>";
  $display_text .= "<p>" . $node->body . "</p>";
  $display_text .= $node->visszajatszas;
  $fpath = db_result(db_query("SELECT `filepath` FROM {files} WHERE `fid`=%d", $node->fid));
  $u = file_create_url($fpath);
  $fname = substr($fpath, strrpos($fpath, "/")+1);
  $display_text .= "<p><a href=\"" . $u . "\">" . $fname . "</a></p>";
  return $display_text;
}

function wesnoth_replays_view($node, $teaser = FALSE, $page = FALSE){
  $node->content['tartalom'] = array(
    '#value' => theme('wreplays_mutasd', $node),
    '#weight' => 1,
  );
  return $node;
}
