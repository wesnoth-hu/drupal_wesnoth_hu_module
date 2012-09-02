<?php
// $Id$

/**
* Valid permissions for this module
* @return array An array of valid permissions for the onthisdate module
*/

function mwb_init(){
  //$GLOBALS['_mwb_jelentkezesi_idoszak'] = false;
  
  $GLOBALS['_mwb_alap_csoport'] = 66;

  $GLOBALS['_mwb_verseny_nev'] = 'Magyar Wesnoth Bajnokság 2011';
  
  $GLOBALS['_mwb_fajok'] = array(
    'random' => "Véletlenszerű",
    'loyalists' => "Hűségesek",
    'rebels' => "Lázadók",
    'northeners' => "Északiak",
    'undead' => "Élőholtak",
    'knalgans' => "Knalgai szövetség",
    'drakes' => "Perzsekények",
  );
  
  $GLOBALS['_mwb_vezerek'] = array(
    'random' => 'Véletlenszerű',
    'ures1' => '--',
    'lieutenant' => 'Hadnagy',
    'swordsman' => 'Kardforgató',
    'pikeman' => 'Pikás gyalogos',
    'javelineer' => 'Dárdahajító',
    'shock_trooper' => 'Darabont',
    'longbowman' => 'Hosszúíj nyilas',
    'white_mage' => 'Fehér mágus',
    'red_mage' => 'Vörös mágus',
    'ures2' => '--',
    'elvish_captain' => 'Tünde kapitány',
    'elvish_hero' => 'Tünde hős',
    'elvish_ranger' => 'Tünde vadász',
    'elvish_marksman' => 'Tünde mesterlövész',
    'elvish_druid' => 'Tünde druida',
    'elvish_sorceress' => 'Tünde boszorkány',
    'white_mage' => 'Fehér mágus',
    'red_mage' => 'Vörös mágus',
    'elder_wose' => 'Agg fapásztor',
    'ures3' => '--',
    'orcish_warrior' => 'Ork harcos',
    'troll' => 'Troll',
    'troll_rocklobber' => 'Troll kőhajító',
    'orcish_crossbowman' => 'Ork számszeríjász',
    'orcish_slayer' => 'Ork vérengző',
    'ures4' => '--',
    'dark_sorcerer' => 'Sötét varázsló',
    'revenant' => 'Bosszúálló',
    'deathblade' => 'Halálpenge',
    'bone_shooter' => 'Csontvadász',
    'necrophage' => 'Hullafaló',
    'ures5' => '--',
    'dwarvish_steelclad' => 'Törp vértes',
    'dwarvish_thunderguard' => 'Törp villámörző',
    'dwarvish_stalwart' => 'Rettenthetetlen törp',
    'rogue' => 'Haramia',
    'trapper' => 'Prémvadász',
    'ures6' => '--',
    'drake_flare' => 'Perzsekény tűzmester',
    'fire_drake' => 'Tűzperzsekény',
    'drake_trasher' => 'Perzsekény vagdalkozó',
    'drake_arbiter' => 'Perzsekény zsarnok',
    'drake_warrior' => 'Perzsekény harcos',
    'saurian_oracle' => 'Gyík jövendőmondó',
    'saurian_soothsayer' => 'Gyík kuruzsló',
  );

  /*  
  // a pályákat már egy külön funkció állítja be
  $GLOBALS['_mwb_palyak'] = array(
    'basilisk' => '2p - Caves of the Basilisk (1.4 rev1)',
    'onis' => '2p - Den of Onis (1.4 rev1)',
    'fallenstar' => '2p - Fallenstar Lake (1.4 rev1)',
    'hamlets' => '2p - Hamlets (1.4 rev1)',
    'hornshark' => '2p - Hornshark Island (1.4 rev1)',
    'howling_ghost' => '2p - Howling Ghost Badlands (1.4 new)',
    'sablestone' => '2p - Sablestone Delta (1.4 rev1)',
    'silverhead' => '2p - Silverhead Crossing (1.4 rev1)',
    'sullas_ruins' => '2p - Sullas Ruins (1.4 rev1)',
    'freelands' => '2p - The Freelands (1.4 rev1)',
    'weldyn' => '2j - Weldyn-csatorna',
  );
  
  // ezek már nem kellenek, máshogy lett megoldva
  $GLOBALS['_mwb_fordulok'] = array(
    'selejtezo' => 'Selejtező',
    'elodonto' => 'Elődöntő',
    'kozepdonto' => 'Középdöntő',
    'donto' => 'Döntő',
  );
  */
}

function _mwb_palyak_tomb($csoport){
  if(_mwb_csoport_resze($csoport, 33)){
    $tomb = Array(
    'basilisk' => '2j - A sárkánygyík barlangja',
    'onis' => '2j - Az onik odúja',
    'fallenstar' => '2j - Hullócsillag tó',
    'hamlets' => '2j - Falvacskák',
    'hornshark' => '2j - Pörölycápa sziget',
    'howling_ghost' => '2j - Szellemüvöltés puszta',
    'sablestone' => '2j - Gyászos kövek deltavidéke',
    'silverhead' => '2j - Ezüstfő útkereszteződés',
    'sullas_ruins' => '2j - Sulla romjai',
    'freelands' => '2j - Szabadfölde',
    'weldyn' => '2j - Weldyn-csatorna',
    );
  }else if(_mwb_csoport_resze($csoport, 35)){
    // Szövetségesek csatája
    $tomb = Array(
      'kekvizu' => '4j - Kékvízű vidék',
      'varfoglalos' => '4j - Várfoglalós sziget',
      'osszecsapas' => '4j - Összecsapás',
      'falvacskak' => '4j - Falvacskák',
      'isar' => '4j - Isar keresztje',
      'loris' => '4j - Loris-folyó',
      'morituri' => '4j - Morituri',
      'torokutja' => '4j - A tőrök útja',
      'alvilag' => '4j - Alvilág',
      'xanthe' => '4j - Xanthe káosz',
    );
  }else if(_mwb_csoport_resze($csoport, 36)){
    // Bajnokság 2010
    $tomb = Array(
      'random' => 'Véletlenszerű',
      // alap térképek
      'basilisk' => '2j - A sárkánygyík barlangja',
      'onis' => '2j - Az onik odúja',
      'fallenstar' => '2j - Hullócsillag tó',
      'hamlets' => '2j - Falvacskák',
      'hornshark' => '2j - Pörölycápa sziget',
      'howling_ghost' => '2j - Szellemüvöltés puszta',
      'sablestone' => '2j - Gyászos kövek deltavidéke',
      'silverhead' => '2j - Ezüstfő útkereszteződés',
      'sullas_ruins' => '2j - Sulla romjai',
      'freelands' => '2j - Szabadfölde',
      'weldyn' => '2j - Weldyn-csatorna',
      // új pályák
      'arcaneclave' => '2p - Arcaneclave Citadel',
      'astralport' => '2p - Astral Port',
      'crescent' => '2p - Crescent Lake',
      'elensefar' => '2p - Elensefar Courtyard',
      'madness' => '2p - Fast to Madness',
      'serpentford' => '2p - Serpent Ford',
      'scarred' => '2p - Scarred Foothills',
      'unfolding' => '2p - Unfolding Space',
    );
  }else{
    // III. Torna, 2011-es bajnokság
    $tomb = Array(
      'random' => 'Véletlenszerű',
      // alap térképek
      'basilisk' => '2j - A sárkánygyík barlangja',
      'cynsaun' => '2j - Cynsaun csatamezeje',
      'onis' => '2j - Az onik odúja',
      'elensefar_kertje' => '2j - Elensefar kertje',
      'fallenstar' => '2j - Hullócsillag tó',
      'hamlets' => '2j - Falvacskák',
      'hornshark' => '2j - Pörölycápa sziget',
      'howling_ghost' => '2j - Szellemüvöltés puszta',
      'sablestone' => '2j - Gyászos kövek deltavidéke',
      'silverhead' => '2j - Ezüstfő útkereszteződés',
      'sullas_ruins' => '2j - Sulla romjai',
      'freelands' => '2j - Szabadfölde',
      'weldyn' => '2j - Weldyn-csatorna',
      // új pályák
      'astralport' => '2p - Astral Port',
      'crescent' => '2p - Crescent Lake',
      'elensefar' => '2p - Elensefar Courtyard',
      'serpentford' => '2p - Serpent Ford',
      'unfolding' => '2p - Unfolding Space',
    );
  }
  return $tomb;
}

function _mwb_jatekosok_tomb(){
  $query = db_query("SELECT * FROM {mwb_jelentkezok}");
  $a = array();
  while($r = db_fetch_array($query)){
    $a[] = $r;
  }
  return $a;
}

function _mwb_suly_tomb(){
  $a = array();
  for($i=-10; $i<=10; $i++){
    $a[] = $i;
  }
  return $a;
}

function _mwb_csoportok_tomb($csid=0){
  $query = db_query("SELECT * FROM {mwb_csoportok} ORDER BY `weight`");
  $a = array();
  while($r = db_fetch_array($query)){
    if($csid > 0){
      if(_mwb_csoport_resze($r['csid'], $csid)){
        $a[] = $r;
      }
    }else{
      $a[] = $r;
    }
  }
  
  $tomb_szulok = array();
  foreach($a as $e){
    $tomb_szulok[] = $e['szulo'];
  }
  sort($tomb_szulok);
  $tomb_szulok = array_unique($tomb_szulok);
  
  $ra = array(); // return array
  $a = array_reverse($a);
  foreach($tomb_szulok as $k=>$e){
    for($j=0; $j<count($a); $j++){
      if($a[$j]['szulo'] == $e){
        // egyezik a szülővel, keresd meg a megfelelő helyét
        $hely = 0;
        for($i=0; $i<count($a); $i++){
          $sz = $ra[$i]['szulo'].$ra[$i]['csid'].'/';
          if($sz == $a[$j]['szulo']){
            // megtaláltad a szülőt
            $hely = $i;
          }
        }
        array_splice($ra, $hely, 0, array($a[$j]));
      }
    }
  }
  $ra = array_reverse($ra);
  
  return $ra;
}

function _mwb_uid2nick($id){
  $s = "";
	if(empty($id)){
		return false;
	}
	$query = db_query("SELECT `nev`, `kizarva` FROM {mwb_jelentkezok} WHERE `uid`=".$id." LIMIT 1");
	$r = db_fetch_array($query);
	$s .= "<a href=\"" . url("user/".$id) . "\"";
	if(is_array($r)){
		if($r['kizarva']) $s .= " class=\"mwb-kizarva\" ";
		$s .= ">".$r['nev']."</a>";
	}else{
		$u = user_load($id);
		$s .= ">".$u->name."</a>";
	}
	return $s;
}

function _mwb_pontszam_frissit($cs){
  // játékosok tömbjének generálása
  $query = db_query("SELECT `jatekos1`, `jatekos2` FROM {mwb_merkozesek} WHERE `csoport`=%d", $cs);
  $jatekosok_tomb = array();
  while($r = db_fetch_array($query)){
    $jatekosok_tomb[] = $r['jatekos1'];
    $jatekosok_tomb[] = $r['jatekos2'];
  }
  $jatekosok_tomb = array_unique($jatekosok_tomb);
  //drupal_set_message("játékosok: " . implode(", ", $jatekosok_tomb));
  foreach($jatekosok_tomb as $kj=>$ej){
    $jatekosok[$ej] = 0;
  }
  $query = db_query("SELECT `jatekos1`, `jatekos2`, `gyoztes` FROM {mwb_merkozesek} WHERE `csoport`=%d", $cs);
  while($r = db_fetch_array($query)){
	// csoportok szerint kiválasztjuk a pontszámítási módszert
    //if(_mwb_csoport_resze($cs, 33) || _mwb_csoport_resze($cs, 35)){
    if(_mwb_csoport_resze($cs, 65)){
      if($r['gyoztes'] > 1){
        $jatekosok[$r['gyoztes']] = $jatekosok[$r['gyoztes']]+2;
      }else if($r['gyoztes'] == 1){
        $jatekosok[$r['jatekos1']]++;
        $jatekosok[$r['jatekos2']]++;
      }
    }else if(_mwb_csoport_resze($cs, 66)){
      // 2011-es MWB-n 3 pont jár a győzelemért, döntetlenért 1
      if($r['gyoztes'] > 1){
        $jatekosok[$r['gyoztes']] = $jatekosok[$r['gyoztes']]+3;
      }else if($r['gyoztes'] == 1){
        $jatekosok[$r['jatekos1']]++;
        $jatekosok[$r['jatekos2']]++;
      }
    }else{
      // tornákon általában 1 pont a győzelem
      if($r['gyoztes'] != 0) $jatekosok[$r['gyoztes']]++;
    }
  }
  $s = serialize($jatekosok);
  //drupal_set_message($s);
  $query = db_query("UPDATE {mwb_csoportok} SET `jatekosok`='%s' WHERE `csid`=%d", $s, $cs);
  return $query;
}

function _mwb_csoport_resze($csid, $feltetel){
  if(!isset($csid)) $csid = 1;
  $szulo = db_result(db_query("SELECT `szulo` FROM {mwb_csoportok} WHERE `csid`=".$csid." LIMIT 1"));
  if($csid == $feltetel || preg_match("/\/".$feltetel."\//", $szulo)){
    return true;
  }else{
    return false;
  }
}

/*
function mwb_sorsolas_csoportok(){
  $form['sorsolas'] = array(
    '#type' => 'fieldset',
    '#title' => 'Sorsolás',
    '#description' => 'Játékosok sorsolása egy adott csoportban, és a mérkőzéseik generálása. A csoportbeosztások ellenőrzéséhez nézd meg a <a href="'.url('torna/allas').'">csoportok</a> oldalt, a mérkőzések ellenőrzéséhez pedig a <a href="'.url('torna/merkozesek').'">mérkőzések</a> oldalt!',
  );
  
  // szülők tömb létrehozása
  $sz = array();
  $t = _mwb_csoportok_tomb();
  foreach($t as $e){
    $prefix = str_repeat('--', substr_count($e['szulo'], "/")-1);
    $szam_jatekosok = 0;
    if(is_array(unserialize($e['jatekosok']))) $szam_jatekosok = count(unserialize($e['jatekosok']));
    $letszam = "";
    if($e['letszam'] > 0){
      $letszam = "/".$e['letszam'];
    }
    $k = $e['csid'];
    
    $sz[$k] = $prefix . " " . $e['nev']." (".$szam_jatekosok.$letszam." fő)";
  }
  
  $form['sorsolas']['csoport'] = array(
    '#type' => 'select',
    '#title' => 'Csoport',
    '#description' => 'Válaszd ki, hogy melyik csoportban szeretnél sorsolni. Csak abban az esetben lehetséges a sorsolás, ha a kiválasztott csoportban már vannak játékosok, de annak a gyermek csoportjában még nincsenek.',
    '#options' => $sz,
  );
  
  $form['sorsolas']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Sorsolás',
    '#disabled' => 'disabled',
  );
  
  return $form;
}

function mwb_sorsolas_csoportok_submit($form, &$form_state){
  // játékosok sorsolása a csoportokba  
  $adatok = $form_state['values'];
  
  $csoportok = array();
  $query = db_query("SELECT * FROM {mwb_csoportok}");
  while($r = db_fetch_array($query)){
    $csoportok[$r['csid']] = $r;
  }
	
	$jatekosok = array();
	$kiv_csoport = $csoportok[$adatok['csoport']];
	
  $u = unserialize($kiv_csoport['jatekosok']);
  if(is_array($u)){
    $jatekosok = $u;
  }
  foreach($jatekosok as $jk => $je){
    $jatekosok_kulcs[] = $jk;
  }
  
  if(empty($jatekosok)){
    // nincs játékos amiből választhatunk
    form_set_error("sorsolas", "Olyan csoportot válassz, amiben vannak játékosok!");
  }else{
    // megvannak a játékosok, gyermekcsoportok megkeresése
    $csoport_letszamok = array();
    $csoport_jatekosok = array();
    $szam_letszamok = 0;
    
    $szulo = $kiv_csoport['szulo'];
    $csid = $kiv_csoport['csid'];
    foreach($csoportok as $csk => $cse){
      if($cse['szulo'] == $szulo.$csid."/"){
        $j = array();
        if(is_array(unserialize($cse['jatekosok']))) $j = unserialize($cse['jatekosok']);
        $csoport_letszamok[$cse['csid']] = $cse['letszam']-count($j);
        $szam_letszamok += $cse['letszam']-count($j);
        if($csoport_letszamok[$cse['csid']] < 0) $csoport_letszamok[$cse['csid']] = 0;
      }
    }
    if($szam_letszamok == 0){
      form_set_error("sorsolas", "Ennek a csoportnak nincsenek üres alcsoportjai!");
    }else{
      // sorsolás megkezdése
      foreach($csoport_letszamok as $csk => $cse){
        while($cse > 0){
          $vszam = rand(0, count($jatekosok));
          if(!empty($jatekosok_kulcs[$vszam])){
            $csoport_jatekosok[$csk][$jatekosok_kulcs[$vszam]] = 0;
            $cse--;
            unset($jatekosok_kulcs[$vszam]);
          }
        }
      }
      
      // mérkőzések sorsolása
      foreach($csoport_jatekosok as $csk => $cse){
        $j = array();
        foreach($cse as $kcse => $ecse){
          $j[] = $kcse;
        }
        _mwb_sorsolas_merkozesek($j, $csk);
        _mwb_pontszam_frissit($csk);
      }
      
      drupal_set_message("A csoportok sorsolása sikeres volt.");
    }
  }
}

function _mwb_sorsolas_merkozesek($jatekosok, $csoport) {
  $uzenet = "";
  
  // ebbe a tömbbe érkeznek a mérkőzések
  $merkozesek = array();
  
	for($i=0; $i<count($jatekosok); $i++){	  
		$jatekos = $jatekosok[$i];
		
		// ellenfelek tömbbe rendezése
		$ellenfelek = array();
		
		for($j=0; $j<count($jatekosok); $j++){
			$ellenfel = $jatekosok[$j];
			if($i != $j){
				$ellenfelek[] = $ellenfel;
			}
		}
		// mérkőzések kiírása ellenfél szerint
		for($j=0; $j<count($ellenfelek); $j++){
			$merkozes1 = array($jatekos, $ellenfelek[ $j]);
			$merkozes2 = array($ellenfelek[ $j], $jatekos);
			if(!in_array($merkozes1, $merkozesek, true) && !in_array($merkozes2, $merkozesek, true)){
				$merkozesek[] = $merkozes1;
			}
		}
	}
  
  // pályák érkeznek ide: 0=>jatekos1, 1=>jatekos2, 2=>palya
  $palyak = array();
  
  $tp = array();
  foreach($GLOBALS['_mwb_palyak'] as $k=>$p){
    $tp[] = $k;
  }
  $maxp = count($tp)-1;
	
	for($i=0; $i<count($merkozesek); $i++){
    // mérkőzés pályák elrendezése
		$merkozes_palyak = array();
    $kedvezmeny = rand(0, 1);
		for($j = 0; $j<3; $j++){
			$veletlen_palya = rand(0, $maxp);
			while(in_array($veletlen_palya, $merkozes_palyak)){
				$veletlen_palya = rand(0, $maxp);
			}
      $merkozes_palyak[$j] = $veletlen_palya;
			if($kedvezmeny == 1){
			  if($j % 2 > 0){
          $palyak[] = array($merkozesek[$i][0], $merkozesek[$i][1], $tp[$veletlen_palya]);
        }else{
          $palyak[] = array($merkozesek[$i][1], $merkozesek[$i][0], $tp[$veletlen_palya]);
        }
      }else{
        if($j % 2 > 0){
          $palyak[] = array($merkozesek[$i][1], $merkozesek[$i][0], $tp[$veletlen_palya]);
        }else{
          $palyak[] = array($merkozesek[$i][0], $merkozesek[$i][1], $tp[$veletlen_palya]);
        }
      }
		}
	}
	foreach($palyak as $palya){
	  drupal_set_message("INSERT INTO {mwb_merkozesek} (`jatekos1`, `jatekos2`, `palya`, `csoport`) VALUES (".$palya[0].", ".$palya[1].", '".$palya[2]."', ".$csoport.")");
	  //$query = db_query("INSERT INTO {mwb_merkozesek} (`jatekos1`, `jatekos2`, `palya`, `csoport`) VALUES (".$palya[0].", ".$palya[1].", '".$palya[2]."', ".$csoport.")");
  }
	
	drupal_set_message('A mérkőzések sikerrel generálva lettek.');
}
*/

function mwb_admin_merkozesek_kiirasa_form(){
  $form['merkozesek-kiirasa'] = array(
    '#type' => 'fieldset',
    '#title' => 'Mérkőzések kiírása',
    '#description' => 'Egyszerű módszer az egyes csoportokban lévő összes mérkőzés kiírására. Mindenki két játékot játszik egymással, egyszer az egyik kezd, máskor a másik. <strong>Ügyelj arra, hogy csak egyszer írj ki mérkőzéseket a csoportban!</strong> Ellenőrzéshez: <a href="' . url('bajnoksag/merkozesek') . '">bajnoksag/merkozesek</a>.',
  );

  // csoportok tömb létrehozása
  $sz = array();
  $t = _mwb_csoportok_tomb();
  foreach($t as $e){
    $prefix = str_repeat('--', substr_count($e['szulo'], "/"));
    $k = $e['csid'];
    $sz[$k] = $prefix . " " . $e['nev'];
  }

  $form['merkozesek-kiirasa']['csoport'] = array(
    '#type' => 'select',
    '#title' => 'Kiírandó csoport',
    '#description' => 'Jelöld ki azt a csoportot, amelyikben ki akarod írni a mérkőzéseket. A mérkőzések kiírása csak az adott csoportban történik, ezért ne a szülőt jelöld ki!',
    '#options' => $sz,
  );

  $form['merkozesek-kiirasa']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Mérkőzések kiírása',
  );

  return $form;
}

function mwb_admin_merkozesek_kiirasa_form_submit($form, &$form_state){
  $szamlalo = 0;
  $adatok = $form_state['values'];
  $csid = $adatok['csoport'];
  $jatekosok = db_result(db_query('SELECT `jatekosok` FROM {mwb_csoportok} WHERE `csid`=%d LIMIT 1', $csid));

  $j_tomb = unserialize($jatekosok);
  if(!is_array($j_tomb) || count($j_tomb) < 1){
    form_set_error('merkozesek-kiirasa', 'A kiválasztott csoportban nincs elég játékos! A csoportok szerkesztésénél jelölj ki játékosokat a csoportba!');
  }else{
    foreach($j_tomb as $j1=>$e1){
      foreach($j_tomb as $j2=>$e2){
        if($j1 != $j2){
          $s .= $j1." vs. ".$j2."<br />";

          // új mérkőzés kiírása
          $form_state = array();
          $form_state['values']['uj'] = true;
          $form_state['values']['jatekos1'] = $j1;
          $form_state['values']['jatekos2'] = $j2;
          $form_state['values']['gyoztes'] = 0;
          // a pálya 2010 óta véletlenszerű, majd a játék eldönti
          $form_state['values']['palya'] = 'random';
          $form_state['values']['csoport'] = $csid;
          module_load_include('inc', 'mwb', 'mwb.merkozesek');
          drupal_execute('mwb_admin_merkozesek_form', $form_state);

          $szamlalo++;
        }
      }
    }
  }

  //drupal_set_message(print_r($j_tomb, true) . "<br />" . $s);
  if(!is_array(form_get_errors())) drupal_set_message($szamlalo . " mérkőzések lett kiírva, csid: ". $csid . ".");
}

function mwb_admin_pontszamok_form(){
  $form['pontszamok'] = array(
    '#type' => 'fieldset',
    '#title' => 'Pontszámok szinkronizációja',
    '#description' => 'A pontszámokat a rendszer automatikusan módosítja mikor egy mérkőzésnél győztest jelölünk be. Azonban előfordulhatnak hibák, ilyenkor használd ezt a gombot a pontszámok szinkronizálásához. Az ellenőrzéshez nézd meg a <a href="'.url('bajnoksag/allas').'">bajnokság állása</a> oldalt.',
  );
  
  $form['pontszamok']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Szinkronizálás',
  );
  
  return $form;
}

function mwb_admin_pontszamok_form_submit($form, &$form_state){
  $csoportok = _mwb_csoportok_tomb();
  
  foreach($csoportok as $e){
    _mwb_pontszam_frissit($e['csid']);
  }
  
  drupal_set_message("Pontszámok szinkronizációja sikeres!");
}

function mwb_all(){
	// content variable that will be returned for display
  $page_content = '<p>Ez a mindenkori magyar Wesnoth bajnokságok és tornák rendezését segítő vezérlőpult. Igyekszem minél hamarabb befejezni az összes funkciót. Ha nagyon hiányzik valami, szóljatok Udinak!</p>';
	
	//$page_content .= drupal_get_form("mwb_sorsolas_csoportok");
	
	//$page_content .= drupal_get_form("mwb_merkozesek");
	
	$page_content .= drupal_get_form("mwb_admin_pontszamok_form");
	
        $page_content .= drupal_get_form("mwb_admin_merkozesek_kiirasa_form");
	
	return $page_content;
} 

function mwb_perm() {
  return array('administer mwb', 'access mwb', 'edit jelentkezesek');
}

function mwb_menu() {
  $items = array();

  $items['mwb_szervezo'] = array(
    'title' => 'Bajnokság szervező',
    'description' => 'A bajnokság és tornák szervezését segítő oldal',
    'page callback' => 'mwb_all',
    'access arguments' => array('administer mwb'),
  );
  
  $items['mwb_szervezo/attekintes'] = array(
    'title' => 'Általános feladatok',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );
  
  $items['mwb_szervezo/merkozesek'] = array(
    'title' => 'Mérkőzések szerkesztése',
    'description' => 'Mérkőzéseket tudsz létrehozni.',
    'page callback' => 'mwb_admin_merkozesek',
    'file' => 'mwb.merkozesek.inc',
    'access arguments' => array('administer mwb'),
    'weight' => 2,
    'type' => MENU_LOCAL_TASK,
  );

  $items['mwb_szervezo/merkozesek/%'] = array(
    'title' => 'Mérkőzések szerkesztése',
    'description' => 'Mérkőzéseket tudsz létrehozni.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('mwb_admin_merkozesek_form'),
    'file' => 'mwb.merkozesek.inc',
    'access arguments' => array('administer mwb'),
    'weight' => 2,
    'type' => MENU_CALLBACK,
  );

  $items['mwb_szervezo/csoportok'] = array(
    'title' => 'Csoportok szerkesztése',
    'description' => 'Csoportokat tudsz létrehozni fordulóként maximum létszámmal.',
    'page callback' => 'mwb_admin_csoportok',
    'file' => 'mwb.csoportok.inc',
    'access arguments' => array('administer mwb'),
    'weight' => 2,
    'type' => MENU_LOCAL_TASK,
  );

  $items['mwb_szervezo/csoportok/%'] = array(
    'title' => 'Csoportok szerkesztése',
    'description' => 'Csoportokat tudsz létrehozni fordulóként maximum létszámmal.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('mwb_admin_csoportok_form'),
    'file' => 'mwb.csoportok.inc',
    'access arguments' => array('administer mwb'),
    'weight' => 2,
    'type' => MENU_CALLBACK,
  );

  /*  
  $items['mwb_szervezo/helyreallitas'] = array(
    'title' => 'Helyreállítás',
    'description' => 'Főként a modul fejlesztése során volt hasznos, azonban az adatok elvesztésekor létfontosságú lehet.',
    'page callback' => 'mwb_helyreallitas',
    'file' => 'mwb.helyreallitas.inc',
    'access arguments' => array('administer mwb'),
    'weight' => 3,
    'type' => MENU_LOCAL_TASK,
  );
  */

  /*
  // TORNA - jelentkezés
  $items['user/%/edit/torna_jelentkezes'] = array(
    'title' => 'Torna jelentkezés',
    'description' => 'Ezen az oldalon lehet jelentkezni a tornára',
    'page callback' => 'mwb_jelentkezes',
    'page arguments' => array(1),
    'file' => 'mwb.jelentkezes.inc',
    'access arguments' => array('edit jelentkezesek'),
    'type' => MENU_LOCAL_TASK,
    'weight' => 5,
  );
  */
 
  // BAJNOKSÁG - jelentkezés 
  $items['user/%/edit/mwb_jelentkezes'] = array(
    'title' => 'Bajnokság jelentkezés',
    'description' => 'Ezen az oldalon lehet jelentkezni a bajnokságra',
    'page callback' => 'mwb_jelentkezes',
    'page arguments' => array(1),
    'file' => 'mwb.jelentkezes.inc',
    'access arguments' => array('edit jelentkezesek'),
    'type' => MENU_LOCAL_TASK,
    'weight' => 5,
  );

  // TORNA - jelentkezők
  $items['torna/jelentkezok'] = array(
    'title' => $GLOBALS['_mwb_verseny_nev']. ' - Jelentkezők',
    'description' => 'A bajnokságra jelentkezettek.',
    'page callback' => 'mwb_jelentkezok',
    'file' => 'mwb.jelentkezes.inc',
    'access arguments' => array('access mwb'),
    'weight' => 2,
    'type' => MENU_SUGGESTED_ITEM,
  );
  
  // BAJNOKSÁG - jelentkezők
  $items['bajnoksag/jelentkezok'] = array(
    'title' => $GLOBALS['_mwb_verseny_nev']. ' - Jelentkezők',
    'description' => 'A bajnokságra jelentkezettek.',
    'page callback' => 'mwb_jelentkezok',
    'file' => 'mwb.jelentkezes.inc',
    'access arguments' => array('access mwb'),
    'weight' => 2,
    'type' => MENU_SUGGESTED_ITEM,
  );


  // TORNA - pontszámok
  $items['torna/allas'] = array(
    'title' => 'Torna állása',
    'description' => 'A torna résztvevőinek pontszámai.',
    'page callback' => 'mwb_csoportok',
    'file' => 'mwb.csoportok.inc',
    'access arguments' => array('access mwb'),
    'weight' => 2,
    'type' => MENU_SUGGESTED_ITEM,
  );

  // BAJNOKSÁG - pontszámok
  $items['bajnoksag/allas'] = array(
    'title' => 'Bajnokság állása',
    'description' => 'A bajnokság résztvevőinek pontszámai.',
    'page callback' => 'mwb_csoportok',
    'file' => 'mwb.csoportok.inc',
    'access arguments' => array('access mwb'),
    'weight' => 2,
    'type' => MENU_SUGGESTED_ITEM,
  );

  // TORNA - mérkőzések
  $items['torna/merkozesek'] = array(
    'title' => 'Torna mérkőzései',
    'description' => 'Ezen az oldalon találod a torna mérkőzéseit a csoportok és fordulók szerint.',
    'page callback' => 'mwb_merkozesek',
    'file' => 'mwb.merkozesek.inc',
    'access arguments' => array('access mwb'),
    'type' => MENU_SUGGESTED_ITEM,
  );
  
  // BAJNOKSÁG - mérkőzések
  $items['bajnoksag/merkozesek'] = array(
    'title' => 'Bajnokság mérkőzései',
    'description' => 'Ezen az oldalon találod a bajnokság mérkőzéseit a csoportok és fordulók szerint.',
    'page callback' => 'mwb_merkozesek',
    'file' => 'mwb.merkozesek.inc',
    'access arguments' => array('access mwb'),
    'type' => MENU_SUGGESTED_ITEM,
  );
 
  // Az eddigi versenyeken szerzett pontok stb. 
  $items['user/%/wesnoth'] = array(
    'title' => 'Wesnoth',
    'description' => 'A játékkal kapcsolatos adataid',
    'page callback' => 'mwb_profil',
    'page arguments' => array(1),
    'file' => 'mwb.profil.inc',
    'access arguments' => array('edit jelentkezesek'),
    'type' => MENU_LOCAL_TASK,
    'weight' => 5,
  );

  return $items;
}
