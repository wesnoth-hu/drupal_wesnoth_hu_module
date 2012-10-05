<?php

require_once 'verseny.inc';

function mwb_csoportok(){
  // csoportok mutatása
  $page_content = "";
	
  $page_content .= "<h3>Jelmagyarázat:</h3>";
  $page_content .= "<ul><li><span class=\"mwb-kizarva\">Játékos neve kékkel</span>: a bajnokságról kizárt játékos.</li></ul>";

  $csid = $GLOBALS['_mwb_alap_csoport'];
  //$csid = 66;
  $cs = _mwb_csoportok_tomb($csid);
  if(empty($cs)){
    $page_content .= "\n<p>Még nincsenek csoportok meghatározva.</p>";
  }else{
    // bajnokságon szereplő játékosok
    $jelentkezok = array();
    $query = db_query("SELECT * FROM {mwb_jelentkezok}");
    while($r = db_fetch_array($query)){
      $jelentkezok[$r['uid']] = $r;
    }
          
    foreach($cs as $e){
      $szint = substr_count($e['szulo'], "/");
      if($szint == 1) $page_content .= "<hr style=\"border: 1px #300 solid\"/>";
      $page_content .= "\n\n<h" . ($szint+2) . " style=\"text-align: center\">" . $e['nev'] . "</h" . ($szint+2) . ">";
      
      if($e['letszam'] > 0){
        // ha nem fordulóról, hanem csoportról van szó
        if(empty($e['jatekosok']) || !is_array(unserialize($e['jatekosok']))){
          $page_content .= "<p>Még nincsenek játékosok sorsolva ebbe a csoportba.</p>";
        }else{
          // csoportban lévő lejátszatlan mérkőzések
          $max_merkozesek = 0;
          $lejatszatlan_merkozesek = 0;
          $jatszott_meccsek = array();
          $query = db_query('SELECT `jatekos1`, `jatekos2`, `gyoztes`, `fiktiv` FROM {mwb_merkozesek} WHERE `csoport`=%d', $e['csid']);
          while($sor = db_fetch_array($query)){
            $max_merkozesek++;
            if($sor['gyoztes'] == 0 && $sor['fiktiv'] == 0){
              $lejatszatlan_merkozesek++;
              if(!isset($jatszott_meccsek[$sor['jatekos1']])) $jatszott_meccsek[$sor['jatekos1']] = 0;
              if(!isset($jatszott_meccsek[$sor['jatekos2']])) $jatszott_meccsek[$sor['jatekos2']] = 0;
            }else{
              if(!isset($jatszott_meccsek[$sor['jatekos1']])){
			    $jatszott_meccsek[$sor['jatekos1']] = 1;
              }else{
			    $jatszott_meccsek[$sor['jatekos1']]++;
              }
              if(!isset($jatszott_meccsek[$sor['jatekos2']])){
			    $jatszott_meccsek[$sor['jatekos2']] = 1;
              }else{
			    $jatszott_meccsek[$sor['jatekos2']]++;
              }
            }
          }
          array_unique($jatszott_meccsek);

          if($lejatszatlan_merkozesek > 0) $page_content .= '<p>A csoportban még <em>' . $lejatszatlan_merkozesek . ' mérkőzés nincs lejátszva</em>.</p>';
          
          // csoportokban szereplő játékosok
          $jt = unserialize($e['jatekosok']);

          // oszlopok létrehozása rendezéshez
          $pontok = array();
          foreach ($jt as $k => $e) {
            $pontok[$k] = $e;
            $jt[$k] = $k;
          }
          $rendezo_pontok = $pontok;
          @array_multisort($rendezo_pontok, SORT_DESC, $jatszott_meccsek, SORT_ASC, $jt);

          //arsort($jt);
          // Bajnoksághoz kell
          if(array_key_exists($GLOBALS['user']->uid, $jelentkezok)) {
            // ha a bejelentkezett ember is részt vesz a bajnokságon, akkor mutass e-mail címet is
            $page_content .= "<table><thead><tr><th style=\"width: 20%\">Név</th><th>E-mail</th><th style=\"width: 25%\">Faj, vezér</th><th style=\"width: 10%\">Játszott meccsek</th><th style=\"width: 10%\">Pontok</th></tr></thead><tbody>";
          }else{
            $page_content .= "<table><thead><tr><th style=\"width: 20%\">Név</th><th style=\"width: 25%\">Faj, vezér</th><th style=\"width: 10%\">Játszott meccsek</th><th style=\"width: 10%\">Pontok</th></tr></thead><tbody>";
          }

          // Tornához kell
          //$page_content .= "<table class=\"mwb-tablazat\"><thead><tr><th style=\"width: 20%\">Név</th><th style=\"width: 10%\">Játszott meccsek</th><th style=\"width: 10%\">Pontok</th></tr></thead><tbody>";

          // Pick Your Recruithoz kell
          //$page_content .= "<table class=\"mwb-tablazat\"><thead><tr><th style=\"width: 20%\">Név</th><th>E-mail</th><th style=\"width: 15%\">Csapat</th><th style=\"width: 10%\">Játszott meccsek</th><th style=\"width: 10%\">Pontok</th></tr></thead><tbody>";
          // Szövetségesek csatájához kell
          //$page_content .= "<table class=\"mwb-tablazat\"><thead><tr><th style=\"width: 15%\">Név</th><th>E-mail</th><th style=\"width: 25%\">Első faj</th><th style=\"width: 25%\">Második faj</th><th style=\"width: 10%\">Játszott meccsek</th><th style=\"width: 5%\">Pontok</th></tr></thead><tbody>";
          // csoportok szerint végigmegyünk
          $r = 0; // páros, páratlan
          foreach($jt as $jk => $je){
            // $jk => uid, $jelentkezok => tomb minden adattal
            $j = $jelentkezok[$je];
            // páros, páratlan osztály
            $row_class = 'odd';
            if($r%2 == 0) $row_class = 'even';
            $r++;
            // Bajnoksághoz kell
            //$page_content .= "<tr><td>" . _mwb_uid2nick($jk) . "</td><td>" . $jelentkezok[$jk]['email'] . "</td><td>" . $GLOBALS['_mwb_fajok'][$jelentkezok[$jk]['faj']] . "</td><td>" . $GLOBALS['_mwb_vezerek'][$jelentkezok[$jk]['vezer']] . "</td><td class=\"mwb-tablazat-pontok\">".$je."</td></tr>";
            // Pick Your Recruithoz kell
            //$page_content .= "<tr><td>" . _mwb_uid2nick($jk) . "</td><td>" . $jelentkezok[$jk]['email'] . "</td><td>" . $jelentkezok[$jk]['csapat'] . "</td><td style=\"text-align: center;\">".$jatszott_meccsek[$jk]."</td><td class=\"mwb-tablazat-pontok\">".$je."</td></tr>";

            // Szövetségesek csatája táblázat
            //$page_content .= "<tr><td>" . _mwb_uid2nick($jk) . "</td><td>" . $j['email'] . "</td><td>" . $GLOBALS['_mwb_fajok'][$j['faj']] . " - ".$GLOBALS['_mwb_vezerek'][$j['vezer']] . "</td><td>" . $GLOBALS['_mwb_fajok'][$j['faj2']] ." - ". $GLOBALS['_mwb_vezerek'][$jelentkezok[$jk]['vezer2']] . "</td><td style=\"text-align: center\">".$jatszott_meccsek[$jk]."</td><td class=\"mwb-tablazat-pontok\">".$je."</td></tr>";

            // Bajnokság táblázat
            if(array_key_exists($GLOBALS['user']->uid, $jelentkezok)) {
              $page_content .= '<tr class="'.$row_class.'"><td>' . _mwb_uid2nick($j['uid']) . '</td><td>'. $j['email'] .'</td><td>' . $GLOBALS['_mwb_fajok'][$j['faj']] . " - ".$GLOBALS['_mwb_vezerek'][$j['vezer']] . "</td><td style=\"text-align: center\">".$jatszott_meccsek[$jk]."</td><td class=\"mwb-tablazat-pontok\">".$pontok[$je]."</td></tr>";
            }else{
              $page_content .= '<tr class="'.$row_class.'"><td>' . _mwb_uid2nick($j['uid']) . "</td><td>" . $GLOBALS['_mwb_fajok'][$j['faj']] . " - ".$GLOBALS['_mwb_vezerek'][$j['vezer']] . "</td><td style=\"text-align: center\">".$jatszott_meccsek[$jk]."</td><td class=\"mwb-tablazat-pontok\">".$pontok[$je]."</td></tr>";
            }

            // Torna táblázat
            //$page_content .= "<tr><td>" . _mwb_uid2nick($j['uid']) . "</td><td style=\"text-align: center\">".$jatszott_meccsek[$jk]."</td><td class=\"mwb-tablazat-pontok\">".$pontok[$je]."</td></tr>";
          }
          $page_content .= "</tbody></table>";
        }
      }
    }
  }
  
  return $page_content;
}

function mwb_admin_csoportok(){
  // csoportok létrehozása
  
  $link_uj = "<p><a href=\"" . $base_url . url('admin/wesnoth/verseny/csoportok/uj') . "\">Új csoport hozzáadása</a></p>";

  $display_text = "<h3>A bajnokság csoportjai</h3>";
  
  $display_text .= "<p>Ezen az oldalon tudod létrehozni a bajnokság fordulóit, csoportjait esetleg alcsoportjait.";
  //$display_text .= "<br />A csoportok változásait rögtön figyelemmel is kísérheted a <a href=\"" . $base_path . url("torna/merkozesek") . "\">". $base_path . url("torna/merkozesek") . "</a> oldalon.</p>";
  $display_text .= "<br />A csoportok változásait rögtön figyelemmel is kísérheted a <a href=\"" . $base_path . url("bajnoksag/allas") . "\">". $base_path . url("bajnoksag/allas") . "</a> oldalon.</p>";
  
  $display_text .= "\n<h4>Eddigi csoportok</h4>";
  
  $display_text .= $link_uj;
  
  $cs = _mwb_csoportok_tomb(0);
  if(empty($cs)){
    $display_text .= "\n<p>Még nincsenek csoportok meghatározva.</p>";
  }else{
    $prev_sz = 0;
    foreach($cs as $e){
      //$szint = ceil(strlen($e['szulo'])/2);
      $szint = substr_count($e['szulo'], "/");
      if($szint > $prev_sz){
        $display_text .= "<ul>";
      }
      while($prev_sz > $szint){
        $display_text .= "</ul>"; 
        $prev_sz--;
      }
      $display_text .= "<li><a href=\"". $base_url . url('admin/wesnoth/verseny/csoportok/'.$e['csid']) ."\">" . $e['nev'] . "</a></li>";
      $prev_sz = $szint;
    }
    while($prev_sz > 0){
      $display_text .= "</ul>"; 
      $prev_sz--;
    }
  }
  
  $display_text .= $link_uj;
  
  return $display_text;
}

function mwb_admin_csoportok_form(&$form_state){
  // admin/wesnoth/verseny/csoportok/[uj|%]
  $arg = arg(4);
  if($arg == 'uj') $cs_uj = true;
  if(!$cs_uj){
    $query = db_query("SELECT * FROM {mwb_csoportok} WHERE `csid`=" . $arg);
    $a = db_fetch_array($query);
  }
  
  $form['intro'] = array(
    '#type' => 'markup',
    '#value' => '<p>Ezen az oldalon tudsz új csoportokat létrehozni, illetve a korábbiakat szerkeszteszni. Kérlek olvasd el alaposan az egyes mezők leírásait, hogy helyesen tudd beállítani a csoportokat!</p>',
  );
  
  $form['nev'] = array(
    '#type' => 'textfield',
    '#title' => 'Csoport neve',
    '#description' => 'A csoport neve, ahogyan az egyes összegző lapokon szeretnéd látni. Több csoportnak is lehet ugyanaz a neve, csak majd ügyelj, hogy különböző szülők alá helyezd!',
  	'#default_value' => '',
  	'#required' => 'required',
  	'#size' => 50,
  	'#maxlength' => 50,
  );
  if(!$cs_uj) $form['nev']['#default_value'] = $a['nev'];
  
  $form['letszam'] = array(
    '#type' => 'textfield',
    '#title' => 'Létszám',
    '#description' => 'A csoport sorsoláskor figyelembe vett létszáma. A 0 létszámú csoportokba sorsolás alapján nem kerülhet ember, azonban a lenti felsorolásból így is belerakhatsz embereket (általában a fordulóknál).',
  	'#default_value' => '0',
  	'#size' => 20,
  	'#maxlength' => 20,
  );
  if(!$cs_uj) $form['letszam']['#default_value'] = $a['letszam'];
  
  // játékosok tömb létrehozása
  $t = _mwb_jatekosok_tomb();
  $jt = array();
  foreach($t as $e){
    $jt[$e['uid']] = $e['nev'];
  }
  
  $form['jatekosok'] = array(
    '#type' => 'select',
    '#title' => 'Játékosok',
    '#description' => 'A csoportban résztvevő játékosok. Amennyiben a csoportba sorsolás útján akarod a játékosokat berakni, ne jelölj be egyet sem, hanem egy létszámot határozz meg!',
    '#default_value' => '',
    '#options' => $jt,
    '#multiple' => 'multiple',
    '#size' => '10',
  );
  if(!$cs_uj){
    $t = unserialize($a['jatekosok']);
    $ot = array();
    foreach($t as $k=>$e){
      $ot[] = $k;
    }
    $form['jatekosok']['#default_value'] = $ot;
  }
  
  // szülők tömb létrehozása
  $sz = array('/' => 'Gyökér');
  $t = _mwb_csoportok_tomb();
  foreach($t as $e){
    $prefix = str_repeat('--', substr_count($e['szulo'], "/"));
    $k = $e['szulo'] . $e['csid'] . '/';
    $sz[$k] = $prefix . " " . $e['nev'];
  }
  
  $form['szulo'] = array(
    '#type' => 'select',
    '#title' => 'Szülő',
    '#description' => 'A csoport szülője. Forduló esetén nincs szülője a csoportnak, azonban a fordulón belüli csoportnak a megfelelő forduló legyen!',
    '#default_value' => '/',
    '#options' => $sz,
  );
  if(!$cs_uj) $form['szulo']['#default_value'] = $a['szulo'];
  
  $form['weight'] = array(
    '#type' => 'select',
    '#title' => 'Súly',
    '#description' => 'A megjelenítési sorrendet határozza meg. A nehezebb elemek lesüllyednek a lap aljára. Ha több elemnek ugyanaz a súlya, akkor névsorrendben kerülnek kilistázásra.',
    '#default_value' => 10,
    '#options' => _mwb_suly_tomb(),
  );
  if(!$cs_uj) $form['weight']['#default_value'] = $a['weight'];
  
  $form['tipus'] = array(
    '#type' => 'hidden',
    '#value' => 'uj',
  );
  if(!$cs_uj) $form['tipus']['#value'] = $a['csid'];
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Hozzáadás',
  );
	
  $form['#redirect'] = 'admin/wesnoth/verseny/csoportok';
	
  if(!$cs_uj) $form['submit']['#value'] = 'Mentés';
  
  if(!$cs_uj){
    $form['torol'] = array(
      '#type' => 'submit',
      '#value' => 'Törlés',
    );
  }

  return $form;
}

function mwb_admin_csoportok_form_submit($form, &$form_state){
  $adatok = $form_state['values'];
  
  $tj = array();
  foreach($adatok['jatekosok'] as $k=>$e){
    $tj[$k] = 0;
  }
  $s_jatekosok = serialize($tj);

  if($adatok['tipus'] == 'uj'){
    $query = db_query("INSERT INTO {mwb_csoportok} (`nev`, `letszam`, `jatekosok`, `szulo`, `weight`) VALUES ('" . $adatok['nev'] . "', ". $adatok['letszam'] .", '%s', '". $adatok['szulo'] ."', ".$adatok['weight'].")", $s_jatekosok);
    if($query){
      drupal_set_message("Új csoport sikeresen hozzáadva!");
    }else{
      drupal_set_message("Új csoportot nem lehetett hozzáadni!", 'error');
    }
  }else{
    if($adatok['op'] == t('Delete')){
      $query = db_query("DELETE FROM {mwb_csoportok} WHERE `csid`=".$adatok['tipus']);
      if($query){
        drupal_set_message("Csoport sikeresen törölve!");
      }
    }else{
      $query = db_query("UPDATE {mwb_csoportok} SET `nev`='".$adatok['nev']."', `letszam`=".$adatok['letszam'].", `jatekosok`='%s', `szulo`='".$adatok['szulo']."', `weight`=".$adatok['weight']." WHERE `csid`=".$adatok['tipus'], $s_jatekosok);
      if($query){
        drupal_set_message("Csoport sikeresen frissítve!");
      }
    }
  }
}
