<?php
function mwb_helyreallitas(){
  $page_content = "<p>Ez az oldal elsősorban a fejlesztéshez készült, a bajnokság alatt <em>élesben ne használd az itt lévő gombokat</em>, mert az adatokat egy régebbi állapotukba rendezhetik!<br><em>Jelenlegi visszarendezési időpont:</em> selejtezők vége, elődöntő kezdete.</p>";
  
  $page_content .= drupal_get_form("mwb_helyreallitas_jelentkezok");
  
  $page_content .= drupal_get_form("mwb_helyreallitas_csoportok");
  
  $page_content .= drupal_get_form("mwb_helyreallitas_merkozesek");
  
  return $page_content;
}

function mwb_helyreallitas_jelentkezok(){

	$form['jelentkezok'] = array(
    '#type' => 'fieldset',
    '#title' => t('Jelentkezők bevitele az adatbázisba'),
		'#description' => 'A jelentkezés már megtörtént, ez csak az adatbázisba rendezi a dolgokat.',
  );
	$form['jelentkezok']['submit'] = array(
		'#type' => 'submit',
  	'#value' => t('Jelentkezők bevitele'),
  	'#disabled' => 'disabled',
	);
	
	return $form;
}

function mwb_helyreallitas_jelentkezok_submit($form, &$form_state){
  $uzenet = "";
  
  $uzenet .= "A jelentkezők felvitele sikeres volt.";
  
  db_query("TRUNCATE TABLE {mwb_jelentkezok}");
  
  $adatok = array(
    "147, 'nermal93', 'nermal93@freemail.hu', 'drakes', 'drake_flare', 0",
    "272, 'DigiHero', 'sipos1515@freemail.hu', 'knalgans', 'dwarvish_steelclad', 0",
    "152, 'Rangers', 'harmati.zoltan@gmail.com', 'knalgans', 'dwarvish_steelclad', 0",
    "285, 'titusz97', 'titusz97@citromail.hu', 'undead', 'dark_sorcerer', 1",
    "263, 'Prilukio', 'pastitibi@gmail.com', 'loyalists', 'white_mage', 0",
    "139, 'Napoleon', 'wellington27@freemail.hu', 'undead', 'dark_sorcerer', 1",
    "80, 'Gekko04', 'redl.balazs@freemail.hu', 'rebels', 'elvish_ranger', 1",
    "317, 'Bodri_HUN', 'bodri@fibermail.hu', 'northeners', 'orcish_crossbowman', 0",
    "105, 'pintercsabi', 'csabi.pinter@t-online.hu', 'undead', 'dark_sorcerer', 0",
    "299, 'anthelmintic', 'attila.beres@ar.hu', 'undead', 'necrophage', 0",
    "318, 'vyktor', 'viktor3628@freemail.hu', 'rebels', 'elder_wose', 0",
    "326, 'Levente96', 'halevente@gmail.com', 'rebels', 'elvish_ranger', 0",
    "315, 'pingvinpuki1', 'sipos9292@freemail.hu', 'knalgans', 'dwarvish_stalwart', 0",
    "242, 'Iker', 'lipuszbalazs@freemail.hu', 'rebels', 'elvish_marksman', 0",
    "284, 'titi99', 'szeba2006@hotmail.com', 'undead', 'deathblade', 1",
    "287, 'henckoh', 'hitem@citromail.hu', 'undead', 'dark_sorcerer', 1",
    "114, 'Berez', 'berez93@freemail.hu', 'northeners', 'troll', 0",
    "189, 'Kele', 'kelemen_zoltan@freemail.hu', 'loyalists', 'white_mage', 0",
    "269, 'szdik570', 'szdik570@freemail.hu', 'loyalists', 'red_mage', 0",
    "74, 'Lternesz', 'lternesz@citromail.hu', 'undead', 'dark_sorcerer', 0",
    "107, 'Rudanar_Firmus', 'kriszitan.kad@gmail.com', 'knalgans', 'dwarvish_steelclad', 0",
    "282, 'yanosz', 'zemenj@freemail.hu', 'rebels', 'elvish_hero', 0",
    "252, 'Alpar', 'alpar2008@gmail.com', 'rebels', 'elvish_captain', 0",
    "303, 'tordek', 'baldoghi.t@mailbox.hu', 'northeners', 'orcish_slayer', 1",
    "320, 'serzinho', 'serzinhoo@gmail.com', 'loyalists', 'javelineer', 0",
    "291, 'Konrad', 'davidlm@citromail.hu', 'northeners', 'orcish_warrior', 1",
    "298, 'gee', 'gee@motoros.eu', 'loyalists', 'white_mage', 0",
    "103, 'Horus', 'desocone@hotmail.com', 'rebels', 'red_mage', 0",
    "288, 'Aldebaran-Ghrelin', 'barthalosmarton@yahoo.com', 'northeners', 'orcish_crossbowman', 0",
    "129, 'Zmagyar', 'marci1101@freemail.hu', 'rebels', 'elvish_captain', 0",
    "266, 'domiboy', 'domoki97@freemail.hu', 'rebels', 'elvish_hero', 1",
    "314, 'adamka úr', 'varga_dam@freemail.hu', 'loyalists', 'lieutenant', 1",
    "325, 'HUN-Dragon', 'Davidb@mailbox.hu', 'rebels', 'elvish_captain', 0",
    "165, 'Udi', 'gabor.udvari@gmail.com', 'drakes', 'drake_flare', 0",
    "255, 'Zaton', 'tomanis@citromail.hu', 'knalgans', 'trapper', 0",
    "292, 'Tarp', 'szdani96@citromail.hu', 'rebels', 'elvish_hero', 1",
    "63, 'Fakivaki', 'zoobo@freemail.hu', 'drakes', 'drake_gladiator', 0",
    "102, 'Abben', 'abbenedek@citromail.hu', 'loyalists', 'lieutenant', 0",
    "204, 'Arwen', 'dorcssa@freemail.hu', 'rebels', 'elvish_druid', 0",
    "321, 'sgergely', 'surekg@freemail.hu', 'rebels', 'red_mage', 0"
  );
  db_query("INSERT INTO {mwb_jelentkezok} (`uid`, `nev`, `email`, `faj`, `vezer`, `kizarva`) VALUES (" . implode("), (", $adatok) . ")");  
  
  drupal_set_message($uzenet);
}

function mwb_helyreallitas_csoportok(){

	$form['csoportok'] = array(
    '#type' => 'fieldset',
    '#title' => t('A csoportok felvitele az adatbázisba'),
		'#description' => 'Az első forduló már megvolt, és a második forduló tervben van.',
  );
	$form['csoportok']['submit'] = array(
		'#type' => 'submit',
  	'#value' => t('Csoportok bevitele'),
  	'#disabled' => 'disabled',
	);
	
	return $form;
}

function mwb_helyreallitas_csoportok_submit($form, &$form_state){
  $uzenet = "";
  
  db_query("TRUNCATE TABLE {mwb_csoportok}");
  
  $adatok = array(
    array('Selejtező', 0, 'a:40:{i:147;i:0;i:272;i:0;i:152;i:0;i:285;i:0;i:263;i:0;i:139;i:0;i:80;i:0;i:317;i:0;i:105;i:0;i:299;i:0;i:318;i:0;i:326;i:0;i:315;i:0;i:242;i:0;i:284;i:0;i:287;i:0;i:114;i:0;i:189;i:0;i:269;i:0;i:74;i:0;i:107;i:0;i:282;i:0;i:252;i:0;i:303;i:0;i:320;i:0;i:291;i:0;i:298;i:0;i:103;i:0;i:288;i:0;i:129;i:0;i:266;i:0;i:314;i:0;i:325;i:0;i:165;i:0;i:255;i:0;i:292;i:0;i:63;i:0;i:102;i:0;i:204;i:0;i:321;i:0;}', '/', 11),
    array('A csoport', 4, 'a:4:{i:147;i:0;i:272;i:0;i:152;i:0;i:285;i:0;}', '/1/', 10),
    array('B csoport', 4, 'a:4:{i:263;i:0;i:139;i:0;i:80;i:0;i:317;i:0;}', '/1/', 10),
    array('C csoport', 4, 'a:4:{i:105;i:0;i:299;i:0;i:318;i:0;i:326;i:0;}', '/1/', 10),
    array('D csoport', 4, 'a:4:{i:315;i:0;i:242;i:0;i:284;i:0;i:287;i:0;}', '/1/', 10),
    array('E csoport', 4, 'a:4:{i:114;i:0;i:189;i:0;i:269;i:0;i:74;i:0;}', '/1/', 10),
    array('F csoport', 4, 'a:4:{i:107;i:0;i:282;i:0;i:252;i:0;i:303;i:0;}', '/1/', 10),
    array('G csoport', 4, 'a:4:{i:291;i:0;i:298;i:0;i:103;i:0;i:320;i:0;}', '/1/', 10),
    array('H csoport', 4, 'a:4:{i:129;i:0;i:266;i:0;i:314;i:0;i:288;i:0;}', '/1/', 10),
    array('I csoport', 4, 'a:4:{i:165;i:0;i:255;i:0;i:292;i:0;i:325;i:0;}', '/1/', 10),
    array('J csoport', 4, 'a:4:{i:63;i:0;i:102;i:0;i:204;i:0;i:321;i:0;}', '/1/', 10),
    // csid=12:
    array('Selejtező II.', 0, 'a:20:{i:147;i:0;i:272;i:0;i:263;i:0;i:317;i:0;i:105;i:0;i:326;i:0;i:315;i:0;i:242;i:0;i:114;i:0;i:189;i:0;i:107;i:0;i:282;i:0;i:103;i:0;i:320;i:0;i:288;i:0;i:129;i:0;i:325;i:0;i:255;i:0;i:63;i:0;i:102;i:0;}', '/', 10),
    array('A csoport', 5, '', '/12/', 10),
    array('B csoport', 5, '', '/12/', 10),
    array('C csoport', 5, '', '/12/', 10),
    array('D csoport', 5, '', '/12/', 10),
  );
  foreach($adatok as $ertek){
    $q_adatok = "'" . $ertek[0]."', ".$ertek[1].", '%s', '".$ertek[3]."', ".$ertek[4];
    $query = db_query("INSERT INTO {mwb_csoportok} (`nev`, `letszam`, `jatekosok`, `szulo`, `weight`) VALUES (" . $q_adatok . ")", $ertek[2]);
  }
  if($query){
    $uzenet .= "A csoportok felvitele sikeres volt.";
  }
  
  drupal_set_message($uzenet);
}

function mwb_helyreallitas_merkozesek(){

	$form['merkozesek'] = array(
    '#type' => 'fieldset',
    '#title' => t('A mérkőzések felvitele az adatbázisba'),
		'#description' => 'Az első forduló már megvolt, és a második forduló tervben van.',
  );
	$form['merkozesek']['submit'] = array(
		'#type' => 'submit',
  	'#value' => t('Mérkőzések bevitele'),
  	'#disabled' => 'disabled',
	);
	
	return $form;
}

function mwb_helyreallitas_merkozesek_submit($form, &$form_state){
  $uzenet = "";
  
  db_query("TRUNCATE TABLE {mwb_merkozesek}");
  
  $adatok = array(
    // A csoport
    array(152, 147, 147, 'basilisk', 2, 0),
    array(147, 152, 147, 'fallenstar', 2, 0),
    array(152, 147, 147, 'hornshark', 2, 0),
    
    array(272, 152, 272, 'onis', 2, 0),
    array(152, 272, 272, 'hamlets', 2, 0),
    array(272, 152, 272, 'howling_ghost', 2, 0),
    
    array(285, 152, 152, 'basilisk', 2, 1),
    array(152, 285, 152, 'howling_ghost', 2, 1),
    array(285, 152, 152, 'silverhead', 2, 1),
    
    array(147, 272, 147, 'basilisk', 2, 0),
    array(272, 147, 147, 'hamlets', 2, 0),
    array(147, 272, 147, 'silverhead', 2, 0),
    
    array(285, 147, 147, 'fallenstar', 2, 1),
    array(147, 285, 147, 'hornshark', 2, 1),
    array(285, 147, 147, 'sullas_ruins', 2, 1),
    
    array(285, 272, 272, 'fallenstar', 2, 1),
    array(272, 285, 272, 'sullas_ruins', 2, 1),
    array(285, 272, 272, 'weldyn', 2, 1),
    
    // B csoport
    array(263, 139, 263, 'basilisk', 3, 1),
    array(139, 263, 263, 'onis', 3, 1),
    array(263, 139, 263, 'freelands', 3, 1),
    
    array(263, 80, 263, 'howling_ghost', 3, 1),
    array(80, 263, 263, 'silverhead', 3, 1),
    array(263, 80, 263, 'freelands', 3, 1),
    
    array(317, 263, 263, 'basilisk', 3, 0),
    array(263, 317, 317, 'sablestone', 3, 0),
    array(317, 263, 263, 'freelands', 3, 0),
    
    array(80, 139, 80, 'fallenstar', 3, 1),
    array(139, 80, 80, 'hamlets', 3, 1),
    array(80, 139, 80, 'sablestone', 3, 1),
    
    array(317, 139, 317, 'onis', 3, 1),
    array(139, 317, 317, 'fallenstar', 3, 1),
    array(317, 139, 317, 'sablestone', 3, 1),
    
    array(317, 80, 317, 'fallenstar', 3, 1),
    array(80, 317, 317, 'hornshark', 3, 1),
    array(317, 80, 317, 'weldyn', 3, 1),
    
    // C csoport
    array(105, 299, 105, 'hornshark', 4, 0),
    array(299, 105, 105, 'silverhead', 4, 0),
    array(105, 299, 105, 'weldyn', 4, 0),
    
    array(318, 105, 105, 'hamlets', 4, 0),
    array(105, 318, 318, 'howling_ghost', 4, 0),
    array(318, 105, 318, 'sablestone', 4, 0),
    
    array(105, 326, 326, 'hornshark', 4, 0),
    array(326, 105, 326, 'freelands', 4, 0),
    array(105, 326, 105, 'weldyn', 4, 0),
    
    array(318, 326, 326, 'hornshark', 4, 0),
    array(326, 318, 326, 'sablestone', 4, 0),
    array(318, 326, 318, 'freelands', 4, 0),
    
    array(318, 299, 299, 'hamlets', 4, 0),
    array(299, 318, 318, 'sablestone', 4, 0),
    array(318, 299, 299, 'freelands', 4, 0),
    
    array(299, 326, 299, 'fallenstar', 4, 0),
    array(326, 299, 326, 'howling_ghost', 4, 0),
    array(299, 326, 299, 'silverhead', 4, 0),
    
    // D csoport
    array(284, 242, 242, 'basilisk', 5, 1),
    array(242, 284, 242, 'sablestone', 5, 1),
    array(284, 242, 242, 'sullas_ruins', 5, 1),
    
    array(242, 287, 242, 'basilisk', 5, 1),
    array(287, 242, 242, 'hornshark', 5, 1),
    array(242, 287, 242, 'sablestone', 5, 1),
    
    array(315, 242, 315, 'fallenstar', 5, 0),
    array(242, 315, 315, 'hornshark', 5, 0),
    array(315, 242, 315, 'weldyn', 5, 0),
    
    array(287, 284, 287, 'fallenstar', 5, 1),
    array(284, 287, 287, 'hamlets', 5, 1),
    array(287, 284, 287, 'hornshark', 5, 1),
    
    array(315, 284, 315, 'basilisk', 5, 1),
    array(284, 315, 315, 'hamlets', 5, 1),
    array(315, 284, 315, 'sablestone', 5, 1),
    
    array(287, 315, 315, 'basilisk', 5, 1),
    array(315, 287, 315, 'onis', 5, 1),
    array(287, 315, 315, 'weldyn', 5, 1),
    
    // E csoport
    array(189, 74, 189, 'onis', 6, 1),
    array(74, 189, 189, 'hornshark', 6, 1),
    array(189, 74, 189, 'howling_ghost', 6, 1),
    
    array(74, 269, 269, 'basilisk', 6, 1),
    array(269, 74, 269, 'onis', 6, 1),
    array(74, 269, 269, 'hornshark', 6, 1),
    
    array(269, 189, 189, 'sablestone', 6, 0),
    array(189, 269, 189, 'silverhead', 6, 0),
    array(269, 189, 189, 'sullas_ruins', 6, 0),
    
    array(189, 114, 114, 'onis', 6, 0),
    array(114, 189, 189, 'basilisk', 6, 0),
    array(189, 114, 114, 'howling_ghost', 6, 0),
    
    array(114, 269, 114, 'silverhead', 6, 0),
    array(269, 114, 114, 'sullas_ruins', 6, 0),
    array(114, 269, 114, 'weldyn', 6, 0),
    
    array(74, 114, 114, 'basilisk', 6, 1),
    array(114, 74, 114, 'howling_ghost', 6, 1),
    array(74, 114, 114, 'sablestone', 6, 1),
    
    // F csoport
    array(282, 107, 107, 'hamlets', 7, 0),
    array(107, 282, 107, 'hornshark', 7, 0),
    array(282, 107, 107, 'howling_ghost', 7, 0),
    
    array(252, 107, 107, 'basilisk', 7, 0),
    array(107, 252, 107, 'howling_ghost', 7, 0),
    array(252, 107, 107, 'sablestone', 7, 0),
    
    array(303, 107, 107, 'hamlets', 7, 0),
    array(107, 303, 107, 'howling_ghost', 7, 1),
    array(303, 107, 107, 'freelands', 7, 1),
    
    array(252, 282, 282, 'basilisk', 7, 0),
    array(282, 252, 282, 'fallenstar', 7, 0),
    array(252, 282, 282, 'weldyn', 7, 0),
    
    array(282, 303, 282, 'basilisk', 7, 1),
    array(303, 282, 282, 'sullas_ruins', 7, 1),
    array(282, 303, 282, 'weldyn', 7, 1),
    
    array(252, 303, 252, 'basilisk', 7, 1),
    array(303, 252, 252, 'howling_ghost', 7, 1),
    array(252, 303, 252, 'silverhead', 7, 1),
    
    // G csoport
    array(298, 291, 298, 'onis', 8, 1),
    array(291, 298, 298, 'silverhead', 8, 1),
    array(298, 291, 298, 'weldyn', 8, 1),
    
    array(291, 103, 103, 'onis', 8, 1),
    array(103, 291, 103, 'hamlets', 8, 1),
    array(291, 103, 103, 'hornshark', 8, 1),
    
    array(320, 291, 320, 'onis', 8, 1),
    array(291, 320, 320, 'fallenstar', 8, 1),
    array(320, 291, 320, 'freelands', 8, 1),
    
    array(298, 103, 103, 'basilisk', 8, 0),
    array(103, 298, 103, 'howling_ghost', 8, 0),
    array(298, 103, 103, 'sullas_ruins', 8, 0),
    
    array(298, 320, 320, 'basilisk', 8, 0),
    array(320, 298, 320, 'silverhead', 8, 0),
    array(298, 320, 320, 'sullas_ruins', 8, 0),
    
    array(320, 103, 320, 'fallenstar', 8, 0),
    array(103, 320, 103, 'hamlets', 8, 0),
    array(320, 103, 103, 'silverhead', 8, 0),
    
    // H csoport
    array(266, 129, 129, 'fallenstar', 9, 1),
    array(129, 266, 129, 'hornshark', 9, 1),
    array(266, 129, 129, 'sullas_ruins', 9, 1),
    
    array(314, 129, 129, 'fallenstar', 9, 1),
    array(129, 314, 129, 'sablestone', 9, 1),
    array(314, 129, 129, 'sullas_ruins', 9, 1),
    
    array(129, 288, 129, 'onis', 9, 0),
    array(288, 129, 288, 'hamlets', 9, 0),
    array(129, 288, 288, 'hornshark', 9, 0),
    
    array(314, 266, 314, 'onis', 9, 1),
    array(266, 314, 314, 'fallenstar', 9, 1),
    array(314, 266, 314, 'silverhead', 9, 1),
    
    array(266, 288, 288, 'howling_ghost', 9, 1),
    array(288, 266, 288, 'sullas_ruins', 9, 1),
    array(266, 288, 288, 'freelands', 9, 1),
    
    array(288, 314, 288, 'onis', 9, 1),
    array(314, 288, 288, 'howling_ghost', 9, 1),
    array(288, 314, 288, 'silverhead', 9, 1),
    
    // I csoport
    array(255, 165, 255, 'hamlets', 10, 0),
    array(165, 255, 255, 'howling_ghost', 10, 0),
    array(255, 165, 255, 'sullas_ruins', 10, 0),
    
    array(165, 292, 165, 'hornshark', 10, 1),
    array(292, 165, 165, 'sablestone', 10, 1),
    array(165, 292, 165, 'weldyn', 10, 1),
    
    array(325, 165, 165, 'basilisk', 10, 0),
    array(165, 325, 325, 'sablestone', 10, 0),
    array(325, 165, 325, 'weldyn', 10, 0),
    
    array(255, 292, 255, 'sullas_ruins', 10, 1),
    array(292, 255, 255, 'freelands', 10, 1),
    array(255, 292, 255, 'weldyn', 10, 1),
    
    array(255, 325, 325, 'fallenstar', 10, 0),
    array(325, 255, 325, 'silverhead', 10, 0),
    array(255, 325, 325, 'sullas_ruins', 10, 0),
    
    array(325, 292, 325, 'onis', 10, 1),
    array(292, 325, 325, 'fallenstar', 10, 1),
    array(325, 292, 325, 'weldyn', 10, 1),
    
    // J csoport
    array(63, 204, 63, 'basilisk', 11, 0),
    array(204, 63, 63, 'hornshark', 11, 0),
    array(63, 204, 63, 'sullas_ruins', 11, 0),
    
    array(204, 102, 102, 'basilisk', 11, 0),
    array(102, 204, 204, 'hornshark', 11, 0),
    array(204, 102, 204, 'howling_ghost', 11, 0),
    
    array(321, 204, 204, 'basilisk', 11, 0),
    array(204, 321, 204, 'sablestone', 11, 0),
    array(321, 204, 204, 'freelands', 11, 0),
    
    array(102, 63, 102, 'fallenstar', 11, 0),
    array(63, 102, 102, 'sullas_ruins', 11, 0),
    array(102, 63, 63, 'weldyn', 11, 0),
    
    array(63, 321, 63, 'fallenstar', 11, 0),
    array(321, 63, 63, 'howling_ghost', 11, 0),
    array(63, 321, 63, 'sullas_ruins', 11, 0),
    
    array(321, 102, 102, 'fallenstar', 11, 0),
    array(102, 321, 102, 'silverhead', 11, 0),
    array(321, 102, 102, 'freelands', 11, 0),
  );
  foreach($adatok as $ertek){
    $q_adatok = $ertek[0] . ", " . $ertek[1] .", ". $ertek[2] .", '".$ertek[3]."', ".$ertek[4].", ".$ertek[5];
    $query = db_query("INSERT INTO {mwb_merkozesek} (`jatekos1`, `jatekos2`, `gyoztes`, `palya`, `csoport`, `fiktiv`) VALUES (" . $q_adatok . ")");
  }
  if($query){
    $uzenet .= "A mérkőzések felvitele sikeres volt.";
  }
  
  drupal_set_message($uzenet);
}
