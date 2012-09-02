<?php

function mwb_merkozesek(){  
  $page_content = "";
  
  if($GLOBALS['user']->uid == 165){
    $q = db_query('SELECT * FROM {wesnoth_replays}');
    while($r = db_fetch_array($q)){
      $vid = db_result(db_query('SELECT `vid` FROM {node} WHERE `nid`=%d LIMIT 1', $r['nid']));
      $filename = db_result(db_query('SELECT `filename` FROM {files} WHERE `fid`=%d LIMIT 1', $r['fid']));
      //$page_content .= "INSERT INTO `drupal_upload` (`fid`, `nid`, `vid`, `description`, `list`) VALUES ('".$r['fid']."', '".$r['nid']."', '".$vid."', '".$filename."', 1);<br />";
    }
  }
	
	$page_content .= "<h3>Jelmagyarázat:</h3>";
	$page_content .= "<ul><li><span class=\"mwb-gyoztes\">Játékos neve félkövéren</span>: a mérkőzés győztese.</li>";
	$page_content .= "<li><span class=\"mwb-fiktiv\">Mérkőzés kékkel</span>: a mérkőzés nem került lejátszásra.</li>";
	$page_content .= "<li><span class=\"mwb-kizarva\">Játékos neve kékkel</span>: a bajnokságról kizárt és szégyenfalra került játékos.</li>";
	$page_content .= "<li><span class=\"mwb-ellenorizendo\">Visszajátszás zölddel</span>: a visszajátszást még nem ellenőrizte le bíró.</li></ul>";
	
  $csid = $GLOBALS['_mwb_alap_csoport'];
  $cs = _mwb_csoportok_tomb($csid);
  $ellenorzo_gomb = false;
  if(empty($cs)){
    $page_content .= "\n<p>Még nincsenek csoportok meghatározva.</p>";
  }else{
    foreach($cs as $e){
      $szint = substr_count($e['szulo'], "/");
      if($szint == 1){
        $page_content .= "<hr />";
      }
      $page_content .= "\n\n<h" . ($szint+2) . " style=\"text-align: center\">" . $e['nev'] . "</h" . ($szint+2) . ">";
      
      // meccsek adatainak lekérdezése
      $query = db_query("SELECT * FROM {mwb_merkozesek} WHERE `csoport`=".$e['csid']." ORDER BY `mid`");
      $mt = array();
      while($r = db_fetch_array($query)){
        $mt[] = $r;
      }
      
      // összes visszajátszás lekérdezése és rid szerint tömbbe rendezése
      $query = db_query('SELECT `rid`, `mid`, `nid`, `fid` FROM {wesnoth_replays}');
      $r_tomb = array();
      while($r = db_fetch_array($query)){
        $r_tomb[$r['mid']] = $r;
      }
      // összes fájlméret lekérdezése és fid szerint tömbbe rendezése
      $query = db_query('SELECT `fid`, `filename`, `filepath`, `filesize` FROM {files}');
      $fajl_tomb = array();
      while($r = db_fetch_array($query)){
        $fajl_tomb[$r['fid']] = $r;
      }
      // összes fájl letöltés lekérdezése és név szerint tömbbe rendezése
      $query = db_query("SELECT `filename`, `count` FROM {file_downloads}");
      $letoltesek_tomb = array();
      while($r = db_fetch_array($query)){
        $letoltesek_tomb[$r['filename']] = $r['count'];
      }
      // összes visszajátszás node lekérdezése
      $query = db_query("SELECT * FROM {node} WHERE `type`='wesnoth_replays'");
      $node_tomb = array();
      while($r = db_fetch_object($query)){
        $node_tomb[$r->nid] = $r;
      }
      
      if(empty($mt) && $e['letszam'] > 0){
        $page_content .= "<p>Még nincs mérkőzés kiírva a csoportban.</p>";
      }else{
        $page_content .= "\n<ul class=\"mwb\">";

        foreach($mt as $mk => $me){

          // adatok meghatározása
          $mid = $me['mid'];
          $rid = $r_tomb[$mid]['rid'];
          $nid = $r_tomb[$mid]['nid'];
          $fid = $r_tomb[$mid]['fid'];

          // bajnoksághoz rendezés
          /*
          $j1 = $me['jatekos1'];
          $j2 = $me['jatekos2'];
          $ej1 = $mt[$mk-1]['jatekos1'];
          $ej2 = $mt[$mk-1]['jatekos2'];
          $uj_meccs = true;
          //if($mk > 1){
            if(($j1 == $ej1 && $j2 == $ej2) || ($j1 == $ej2 && $j2 == $ej1)){
              $uj_meccs = false;
            }
          //}
          if($uj_meccs){
            if($mk > 1) $page_content .= "</ul>";
            $page_content .= "\n<ul class=\"mwb\">";
          }
          */
          // szövetségesek csatájához rendezés
          if($ej != $me['jatekos1']) $page_content .= "</ul>\n<ul class=\"mwb\">";
          $ej = $me['jatekos1'];
          
          $page_content .= "<li";
          if($me['fiktiv']) $page_content .= " class=\"mwb-fiktiv\" ";
          $page_content .= ">";
          if($me['gyoztes'] == $me['jatekos1']){
            $page_content .= "<span class=\"mwb-gyoztes\">"._mwb_uid2nick($me['jatekos1'])."</span>";
          }else{
             $page_content .= _mwb_uid2nick($me['jatekos1']);
          }
          $page_content .= " vs. ";
          if($me['gyoztes'] == $me['jatekos2']){
            $page_content .= "<span class=\"mwb-gyoztes\">"._mwb_uid2nick($me['jatekos2'])."</span>";
          }else{
             $page_content .= _mwb_uid2nick($me['jatekos2']);
          }
          $palya = _mwb_palyak_tomb($e['csid']);
          $page_content .= " - " . $palya[$me['palya']].'<br />';

          // mérkőzés szerkesztése
          if(user_access('administer mwb')) $page_content .= '<a href="'. url('mwb_szervezo/merkozesek/'.$mid) .'" class="mwb-meta">Mérkőzés szerkesztése</a><br />';

          if($GLOBALS['user']->uid == 165) $page_content .= '<span class="mwb-meta">(hibaelhárításhoz - mid: '. $mid. ', rid: '. $rid .', nid: ' . $nid .')</span><br />';
         
          if($fid > 0){
            // ha már van visszajátszás feltöltve
            $dfilename = str_replace('sites/default/files/', '', $fajl_tomb[$fid]['filepath']);
            $letoltve = $letoltesek_tomb[$dfilename];
            //$node = db_fetch_object(db_query('SELECT * FROM {node} WHERE `nid`=%d LIMIT 1', $r_tomb['nid']));
            $l = "<table style=\"width: 40%; margin: 0 auto 0.5em 0; float: left;\"><tr>";
            $l .= "<td style=\"width: 34px\"><a href=\"".file_create_url($fajl_tomb[$fid]['filepath']) . "\"><img src=\"/kepek/ikon-merkozes-letoltes.gif\" title=\"Letöltés: ".$fajl_tomb[$fid]['filename']."\" alt=\"Letöltés: ".$fajl_tomb['filename']."\" /></a></td>";
            if($letoltve <= 0){
              $letoltve_szoveg = "A visszajátszást még nem töltötte le senki.";
            }else{
              $letoltve_szoveg = "A visszajátszást $letoltve alkalommal töltötték le.";
            }
            $l .= "<td>Fájlméret: ".round($fajl_tomb[$fid]['filesize']/1024, 1)."kB<br />$letoltve_szoveg</td>";
            $l .= "</tr></table>";
            //$l .= "<div style=\"float: left;\">".fivestar_widget_form($node_tomb[$nid])."</div>";
            $l .= "<div style=\"clear: both;\"></div>";
            if($me['ellenorizve'] == 0){
              $page_content .= "<br /><span class=\"mwb-ellenorizendo\">".$l."</span>";
              /*if(user_access('administer mwb')){
                $page_content .= drupal_get_form('mwb_jovahagyas_form', $me['mid'], $ellenorzo_gomb);
                $ellenorzo_gomb = true;
              }*/
            }else{
              $page_content .= "<br />".$l;
            }

            // visszajátszás szerkesztő gomb
            if($GLOBALS['user']->uid == $me['jatekos1'] || $GLOBALS['user']->uid == $me['jatekos2']){
              if(user_access('edit own wesnoth replays')) $page_content .= "<a href=\"". url('node/'.$nid.'/edit') ."\" class=\"mwb-meta\">Visszajátszás szerkesztése</a> <br />";
            }else{
              if(user_access('edit any wesnoth replays')) $page_content .= "<a href=\"". url('node/'.$nid.'/edit') ."\" class=\"mwb-meta\">Visszajátszás szerkesztése</a> <br />";
            }

            // hozzászólások link
            $kommentek = db_result(db_query('SELECT `comment_count` FROM {node_comment_statistics} WHERE `nid`=%d', $nid));
            $page_content .= "<a href=\"". url('node/'.$nid) ."\" class=\"mwb-meta\">Megjegyzés megtekintése</a> - ".$kommentek . " hozzászólás <br />";
          }else{
            // még nincs visszajátszás feltöltve
            if($me['fiktiv'] == 0){
              if(user_access('edit any wesnoth replays') || ($GLOBALS['user']->uid == $me['jatekos1'] || $GLOBALS['user']->uid == $me['jatekos2'])){
                $page_content .= "<a href=\"". url('node/'.$nid.'/edit') ."\" class=\"mwb-meta\">Visszajátszás feltöltése</a> <br />";
              }
            }
          }
          $page_content .= "</li>";
        }
        $page_content .= "</ul>";
      }
    }
  }

  return $page_content;
}

/*
function mwb_jovahagyas_form($form_state, $mid, $eg){
  $form['mid'] = array(
    '#type' => 'hidden',
    '#value' => $mid,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Ellenőriztem',
  );
  if($eg) $form['submit']['#disabled'] = 'disabled';
  
  return $form;
}

function mwb_jovahagyas_form_submit($form, &$form_state){
  $query = db_query('UPDATE {mwb_merkozesek} SET `ellenorizve`=1 WHERE `mid`=%d', $form_state['values']['mid']);
  if($query){
    drupal_set_message('A visszajátszás jóváhagyva: '.$form_state['values']['mid']);
  }
}
*/

function mwb_admin_merkozesek(){
  // csoportok létrehozása
  
  $display_text = "<h3>Mérkőzések hozzáadása</h3>";
  
  $display_text .= "<p>Ezen az oldalon tudod létrehozni az új mérkőzéseket.";
  $display_text .= "<br />A csoportok változásait rögtön figyelemmel is kísérheted a <a href=\"" . url("bajnoksag/merkozesek") . "\">". url("bajnoksag/merkozesek") . "</a> oldalon.</p>";
  
  $display_text .= "<p><a href=\"" . $base_url . url('mwb_szervezo/merkozesek/uj') . "\">Új mérkőzés hozzáadása</a></p>";
  
  return $display_text;
}

function mwb_admin_merkozesek_form(&$form_state){
  $cs_uj = false;
  if(arg(2) == 'uj' || $form_state['values']['uj'] == true) $cs_uj = true;
  $a = array();

  if(!$cs_uj){
    $query = db_query("SELECT * FROM {mwb_merkozesek} WHERE `mid`=" . arg(2) . " LIMIT 1");
    $a = db_fetch_array($query);
  }
  
  $form['intro'] = array(
    '#type' => 'markup',
    '#value' => '<p>Ezen az oldalon tudsz új mérkőzéseket létrehozni, illetve a korábbiakat szerkeszteni. A <a href="/torna/merkozesek">torna/merkozesek</a> oldalon tudod ellenőrizni őket.</p>',
  );
  
  // játékosok tömb létrehozása
  $t = _mwb_jatekosok_tomb();
  $jt = array();
  foreach($t as $e){
    $jt[$e['uid']] = $e['nev'];
  }
  
  $form['jatekos1'] = array(
    '#type' => 'select',
    '#title' => 'Játékos 1',
    '#description' => 'A kezdő játékos',
  	'#default_value' => '',
  	'#options' => $jt,
  	'#size' => '1',
	'#required' => 'required',
  );
  if(!$cs_uj) $form['jatekos1']['#default_value'] = $a['jatekos1'];

  $form['jatekos2'] = array(
    '#type' => 'select',
    '#title' => 'Játékos 2',
    '#description' => 'A másik játékos',
  	'#default_value' => '',
  	'#options' => $jt,
  	'#size' => '1',
	'#required' => 'required',
  );
  if(!$cs_uj) $form['jatekos2']['#default_value'] = $a['jatekos2'];

	$gyt = Array('0'=>'Nincs', '1'=>'Döntetlen');
	$gyt = $gyt + $jt;
  $form['gyoztes'] = array(
    '#type' => 'select',
    '#title' => 'Győztes',
    '#description' => 'A mérkőzés győztese',
  	'#default_value' => '',
  	'#options' => $gyt,
  	'#size' => '1',
  );
  if(!$cs_uj) $form['gyoztes']['#default_value'] = $a['gyoztes'];
  
  // pályák tömb létrehozása
  $p = _mwb_palyak_tomb($GLOBALS['_mwb_alap_csoport']);
  $form['palya'] = array(
    '#type' => 'select',
    '#title' => 'Pálya',
    '#description' => 'A mérkőzés pályája',
  	'#default_value' => '',
  	'#options' => $p,
  	'#size' => '1',
  );
  if(!$cs_uj) $form['palya']['#default_value'] = $a['palya'];
  
  // csoportok tömb létrehozása
  $t = _mwb_csoportok_tomb(0);
  foreach($t as $e){
    $prefix = str_repeat('--', substr_count($e['szulo'], "/")-1);
    $k = $e['csid'];
    $sz[$k] = $prefix . " " . $e['nev'];
  }

  $form['csoport'] = array(
    '#type' => 'select',
    '#title' => 'Csoport',
    '#description' => 'A mérkőzés csoportja',
  	'#default_value' => $GLOBALS['_mwb_alap_csoport'],
  	'#options' => $sz,
  );
  if(!$cs_uj) $form['csoport']['#default_value'] = $a['csoport'];

  $form['fiktiv'] = array(
    '#type' => 'checkbox',
    '#title' => 'Fiktív',
    '#description' => 'A mérkőzés nem került lejátszásra, az eredmény a szabályzat alapján került kihírdetésre',
  	'#default_value' => '0',
  );
  if(!$cs_uj) $form['fiktiv']['#default_value'] = $a['fiktiv'];
  
  $form['ellenorizve'] = array(
    '#type' => 'checkbox',
    '#title' => 'Ellenőrizve',
    '#description' => 'A mérkőzés visszajátszását és a győztes kilétét ellenőrizte egy bíró',
  	'#default_value' => '0',
  );
  if(!$cs_uj) $form['ellenorizve']['#default_value'] = $a['ellenorizve'];
  
  $form['tipus'] = array(
    '#type' => 'hidden',
    '#value' => 'uj',
  );
  if(!$cs_uj) $form['tipus']['#value'] = $a['mid'];
  
  $form['submit'] = array(
		'#type' => 'submit',
  	'#value' => 'Hozzáadás',
	);
	if(!$cs_uj) $form['submit']['#value'] = 'Mentés';
	
  $form['#redirect'] = 'mwb_szervezo/merkozesek';
 
	if(!$cs_uj){
		$form['torol'] = array(
			'#type' => 'submit',
		  	'#value' => 'Törlés',
		);
	}
  
  return $form;
}

function mwb_admin_merkozesek_form_submit($form, &$form_state){
  $adatok = $form_state['values'];
  $adatok['idopont'] = '0000-00-00 00:00:00';
  
  if($adatok['tipus'] == 'uj'){
    $query = db_query("INSERT INTO {mwb_merkozesek} (`jatekos1`, `jatekos2`, `gyoztes`, `palya`, `idopont`, `csoport`, `fiktiv`, `ellenorizve`) VALUES (" . $adatok['jatekos1'] . ", ". $adatok['jatekos2'] .", ". $adatok['gyoztes'] .", '".$adatok['palya']."', '" . $adatok['idopont'] . "', '". $adatok['csoport'] ."', ". $adatok['fiktiv'] .", ". $adatok['ellenorizve'] .")");
    if($query){
      // a mérkőzések csoportba sikeresen felvettük, készítsük el rögtön a visszajátszást is
      $query = db_query("SELECT LAST_INSERT_ID()");
      $mid = db_result($query);
      wesnoth_replays_merkozeshez($mid);
      drupal_set_message("Új mérkőzés sikeresen hozzáadva!");
    }
  }else{
    if($adatok['op'] == t('Delete')){
      $query = db_query("DELETE FROM {mwb_merkozesek} WHERE `mid`=".$adatok['tipus']);
      if($query){
        drupal_set_message("Mérkőzés sikeresen törölve!");
      }
    }else{
      // meglévő mérkőzés frissítése
      $query = db_query("UPDATE {mwb_merkozesek} SET `jatekos1`='".$adatok['jatekos1']."', `jatekos2`=".$adatok['jatekos2'].", `gyoztes`='". $adatok['gyoztes'] ."', `palya`='".$adatok['palya']."', `idopont`='".$adatok['idopont']."', `csoport`='" .$adatok['csoport']. "', `fiktiv`='". $adatok['fiktiv'] ."', `ellenorizve`='". $adatok['ellenorizve'] ."' WHERE `mid`=".$adatok['tipus']);
      if($query){
        drupal_set_message("Mérkőzés sikeresen frissítve!");
      }
    }
  }
}
