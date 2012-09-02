<?php

require_once 'verseny.inc';

function mwb_jelentkezes($u){
  $GLOBALS['user_id'] = $u;
  $query = db_query("SELECT `name` FROM {users} WHERE `uid`=" . $u . " LIMIT 1");
  $user_name = db_result($query);
  $display_text = '<h3>'.$GLOBALS['_mwb_verseny_nev'] . ' jelentkezés - ' . $user_name . "</h3>";
  
  $display_text .= drupal_get_form("mwb_jelentkezes_form");
  return $display_text;
}

function mwb_jelentkezes_form(){
  global $user_id, $fajok;
  
  $query = db_query("SELECT * FROM {mwb_jelentkezok} WHERE `uid`=" . $GLOBALS['user_id'] ." LIMIT 1");
  $jelentkezo = db_fetch_array($query);

  // ranglista adatok
  $query = db_query('SELECT `value` FROM {profile_values} WHERE `fid`=14 AND `uid`='.$GLOBALS['user_id'].' LIMIT 1');
  $ranglista = db_result($query);
  
  $form['jelentkezek']= array(
		'#type' => 'checkbox',
  	'#title' => 'Jelentkezek',
  	'#description' => 'Ezt a versenyre való jelentkezéshez <strong>be kell jelölnöd</strong>! Ezzel kinyílvánítod, hogy a jelentkezés előtt elolvastad és elfogadtad a szabályzatot, a jelentkezést megfontoltad, és tudomásul vetted, hogy a le nem játszott mérkőzéseknek a fórumrang elvesztése vagy egyéb következménye lehet.',
  	'#default_value' => '1',
  	'#size' => 50,
  	'#maxlength' => 50,
	);
  
  $form['nev']= array(
		'#type' => 'textfield',
  	'#title' => 'Verseny alatt használt név',
  	'#description' => 'A kiszolgálón, a meccsek alatt használt neved. <strong>Kizárólag az angol ABC betűit és számokat tartalmazhat!</strong>',
  	'#default_value' => $jelentkezo['nev'],
  	'#required' => 'required',
  	'#size' => 50,
  	'#maxlength' => 50,
	);
	
	$form['email']= array(
		'#type' => 'textfield',
  	'#title' => 'A verseny alatt használt e-mail cím',
  	'#description' => 'A verseny alatt ezen az e-mail címen értesítünk téged, ezért fontos, hogy létező és gyakran ellenőrzőtt e-mail fiókot adj meg! Ezt az e-mail nem lesz publikusan elérhető!',
  	'#default_value' => $jelentkezo['email'],
  	'#required' => 'required',
  	'#size' => 50,
  	'#maxlength' => 50,
	);

    /*
    // Pick Your Recruithoz
	$form['csapat'] = array(
		'#type' => 'textfield',
		'#title' => 'A versenyen használt csapatod neve',
		'#required' => 'required',
  		'#size' => 50,
  		'#default_value' => $jelentkezo['csapat'],
	);
    */

    // Bajnoksághoz:	
    $form['faj']= array(
      '#type' => 'select',
      '#title' => 'Faj',
      '#description' => 'A versenyen alatt használt nemzetség. A bajnokság indulása után ennek módosítására nincs lehetőség!',
      '#default_value' => $jelentkezo['faj'],
      '#required' => 'required',
      '#options' => $GLOBALS['_mwb_fajok'],
	);
	
    // Bajnoksgához:
    $form['vezer']= array(
      '#type' => 'select',
      '#title' => 'Vezér',
      '#default_value' => $jelentkezo['vezer'],
      '#required' => 'required',
      '#options' => $GLOBALS['_mwb_vezerek'],
	);

    // Szövetségesek csatájához:	
    /*$form['faj2']= array(
      '#type' => 'select',
      '#title' => 'Faj 2',
      '#description' => 'A verseny alatt használt második nemzetséged. A bajnokság indulása után ennek módosítására nincs lehetőség!',
      '#default_value' => $jelentkezo['faj2'],
      '#required' => 'required',
      '#options' => $GLOBALS['_mwb_fajok'],
	);

    // Szövetségesek csatájához:
    $form['vezer2']= array(
      '#type' => 'select',
      '#title' => 'Vezér 2',
      '#default_value' => $jelentkezo['vezer2'],
      '#required' => 'required',
      '#options' => $GLOBALS['_mwb_vezerek'],
	);
	*/

    // kiemeléshez
    if(!empty($ranglista)){
    $form['kiemeles']= array(
      '#type' => 'checkbox',
      '#title' => 'Kiemelésről lemondok',
      '#description' => 'Jelöld ezt be, ha le szeretnél mondani a kiemelésedről!',
      '#default_value' => $jelentkezo['kiemeles'],
    );
    }

    // verseny adminisztrátori funkciók
    if(user_access('administer mwb')){
	
      $form['mwb-admin']= array(
      '#type' => 'fieldset',
      '#title' => 'Versenyszervezői funkciók',
	);
	
	$form['mwb-admin']['kizarva']= array(
      '#type' => 'checkbox',
      '#title' => 'Kizárva',
      '#description' => 'Jelöld ezt be, ha a játékos mulasztás, vagy egyéb szabálysértés miatt <em>ki lett zárva</em> és szégyenfalra kerül.',
      '#default_value' => $jelentkezo['kizarva'],
	);
	
	$form['mwb-admin']['fiktiv-merkozesek']= array(
      '#type' => 'radios',
      '#title' => 'Fiktív mérkőzések',
      '#description' => 'Jelöld be azt a lehetőséget, amit a le nem játszott mérkőzéseivel szeretnél tenni.',
      '#options' => array(
        'semmi' => 'Ne változtass semmit a játékos mérkőzésein',
        'bevitel' => 'A le nem játszott mérkőzéseit jelöld fiktívként és őt vesztesként',
        'visszavonas' => 'A fiktívként jelölt elvesztett mérkőzéseit jelöld normálisnak és lejátszatlannak',
      ),
      '#default_value' => 'semmi',
	);
    }
	
  if(empty($jelentkezo)){
	  $form['uj'] = array(
	    '#type' => 'hidden',
	    '#value' => 'uj',
    );
  }
	
	$form['submit'] = array(
	  '#type' => 'submit',
	  '#value' => 'Mentés',
	);
	
	return $form;
}

function mwb_jelentkezes_form_submit($form, &$form_state){
  $uzenet = "";
  
  $adatok = $form_state['values'];
  if(!$adatok['kizarva']){
    $adatok['kizarva'] = 0;
  }
  if(empty($adatok['kiemeles'])){
    $adatok['kiemeles'] = 0;
  }
  
  if(isset($adatok['fiktiv-merkozesek'])){
    if($adatok['fiktiv-merkozesek'] == 'bevitel'){
      $query = db_query('SELECT `mid`, `jatekos1`, `jatekos2` FROM {mwb_merkozesek} WHERE (`jatekos1`='.$GLOBALS['user_id'].' OR `jatekos2`=' . $GLOBALS['user_id'] . ') AND `gyoztes`=0');
      while($r = db_fetch_array($query)){
        if($r['jatekos1'] == $GLOBALS['user_id']){
          $gyoztes = $r['jatekos2'];
        }else{
          $gyoztes = $r['jatekos1'];
        }
        //drupal_set_message('győztes: '.$gyoztes.', mérkőzés:'.$r['mid']);
        db_query('UPDATE {mwb_merkozesek} SET `gyoztes`=%d, `fiktiv`=1 WHERE `mid`=%d LIMIT 1', $gyoztes, $r['mid']);
      }
      
    }else if($adatok['fiktiv-merkozesek'] == 'visszavonas'){
      $query = db_query('SELECT `mid`, `gyoztes` FROM {mwb_merkozesek} WHERE (`jatekos1`='.$GLOBALS['user_id'].' OR `jatekos2`=' . $GLOBALS['user_id'] . ') AND `fiktiv`=1');
      while($r = db_fetch_array($query)){
        //drupal_set_message('mérkőzés:'.$r['mid']);
        if($r['gyoztes'] != $GLOBALS['user_id']){
          // csak ott vond vissza a fiktív státuszt, ahol vesztesként van felírva a játékos
          db_query('UPDATE {mwb_merkozesek} SET `gyoztes`=0, `fiktiv`=0 WHERE `mid`=%d LIMIT 1', $r['mid']);
        }
      }
    }
  }
  
  if($adatok['uj'] == 'uj'){
    if($adatok['jelentkezek']){
      $uzenet .= "Új jelentkezés felvitele: ";
      // Pick Your Recruithoz:
      //$query = db_query("INSERT INTO {mwb_jelentkezok} (`uid`, `nev`, `email`, `csapat`, `kizarva`) VALUES (".$GLOBALS['user_id'].", '" . $adatok['nev'] . "', '" . $adatok['email'] . "', '" .$adatok['csapat'] . "', " . $adatok['kizarva'].")");
      // Bajnoksághoz:
      $query = db_query("INSERT INTO {mwb_jelentkezok} (`uid`, `nev`, `email`, `faj`, `vezer`, `kizarva`, `kiemeles`) VALUES (".$GLOBALS['user_id'].", '" . $adatok['nev'] . "', '" . $adatok['email'] . "', '" .$adatok['faj'] . "', '" . $adatok['vezer'] . "', " . $adatok['kizarva'].", ". $adatok['kiemeles'] .")");
      // Szövetségesek csatájához:
      // $query = db_query("INSERT INTO {mwb_jelentkezok} (`uid`, `nev`, `email`, `faj`, `vezer`, `faj2`, `vezer2`, `kizarva`, `kiemeles`) VALUES (".$GLOBALS['user_id'].", '" . $adatok['nev'] . "', '" . $adatok['email'] . "', '" .$adatok['faj'] . "', '" . $adatok['vezer'] . "', '". $adatok['faj2'] ."', '". $adatok['vezer2'] ."', " . $adatok['kizarva'] .", ". $adatok['kiemeles'] .")");
      if($query == true){
        $uzenet .= "sikeres.";
      }else{
        $uzenet .= "sikertelen.";
      }
    }
  }else{
    if($adatok['jelentkezek']){
      $uzenet .= "Korábbi jelentkezés frissítése: ";
      // Pick Your Recruithoz:
      //$query = db_query("UPDATE {mwb_jelentkezok} SET `nev`='" . $adatok['nev'] . "', `email`='" . $adatok['email'] . "', `csapat`='" . $adatok['csapat'] . "', `kizarva`=".$adatok['kizarva']." WHERE `uid`=".$GLOBALS['user_id']." LIMIT 1");
      // Bajnoksághoz:
      $query = db_query("UPDATE {mwb_jelentkezok} SET `nev`='" . $adatok['nev'] . "', `email`='" . $adatok['email'] . "', `faj`='" . $adatok['faj'] . "', `vezer`='". $adatok['vezer'] ."', `kizarva`=".$adatok['kizarva'].", `kiemeles`=". $adatok['kiemeles'] ." WHERE `uid`=".$GLOBALS['user_id']." LIMIT 1");
      // Szövetségesek csatájához:
      //$query = db_query("UPDATE {mwb_jelentkezok} SET `nev`='" . $adatok['nev'] . "', `email`='" . $adatok['email'] . "', `faj`='" . $adatok['faj'] . "', `vezer`='". $adatok['vezer'] ."', `faj2`='". $adatok['faj2'] ."', `vezer2`='". $adatok['vezer2'] ."', `kizarva`=".$adatok['kizarva'].", `kiemeles`=". $adatok['kiemeles'] ." WHERE `uid`=".$GLOBALS['user_id']." LIMIT 1");
      if($query == true && db_affected_rows($query) == 1){
        $uzenet .= "sikeres.";
      }else{
        $uzenet .= "sikertelen.";
      }
    }else{
      $uzenet .= "Korábbi jelentkezés törlése.";
      $query = db_query("DELETE FROM {mwb_jelentkezok} WHERE `uid`=".$GLOBALS['user_id']." LIMIT 1");
    }
  }
  
  drupal_set_message($uzenet);
}

function mwb_jelentkezes_access($op, $node, $account){
    if($GLOBALS['user']->uid == arg(1)){
      return user_access('edit own profile content', $account);
    }else{
      return user_access('edit any profile content', $account);
    }
  /*
  if (user_access('edit own profile content', $account)) {
    if($GLOBALS['user']->uid == arg(1)){
      return true;
    }else{
      return false;
    }
  }
  if (user_access('edit any profile content', $account)) {
    return true;
  }
  */
}

function mwb_jelentkezok(){
  // adatok lekérdezése
  // jelentkezés adatok
	$jelentkezok = Array();
  $query = db_query("SELECT * FROM {mwb_jelentkezok}");
  while($r = db_fetch_array($query)){
    $jelentkezok[$r['uid']] = $r;
  }
  // ranglista adatok
  $query = db_query("SELECT * FROM {profile_values} WHERE `fid`=14");
  while($r = db_fetch_array($query)){
    $ranglista[$r['uid']] = $r['value'];
  }


  $page_content = "<p>Eddigi jelentkezők száma: <b>" . count($jelentkezok) . "</b> fő.</p>";

  // Tornához kell
  //$page_content .= "<table class=\"mwb-tablazat\"><thead><tr><th style=\"width: 20%\">Név</th><th style=\"width: 10%\">Rangl. hely</th></tr></thead><tbody>";

  // Bajnoksághoz kell
  $page_content .= "<table><thead><tr><th style=\"width: 20%\">Név</th><th style=\"width: 10%\">Rangl. hely</th><th style=\"width: 10%\">Kiem. lemond</th><th style=\"width: 10%\">Faj</th><th style=\"width: 10%\">Vezér</th></tr></thead><tbody>";

  $i = 0; 
  foreach($jelentkezok as $jk => $je){
    // $jk => uid, $jelentkezok => tomb minden adattal
    $j = $jelentkezok[$jk];
    $ranglistahely = $ranglista[$j['uid']];
    $kiemeles = "";
    if(!empty($ranglistahely)){
      if($j['kiemeles'] == 0){
        $kiemeles = 'nem';
      }else{
        $kiemeles = '<strong>igen</strong>';
      }
    }

    // Torna táblázat
    // $page_content .= "<tr><td>" . _mwb_uid2nick($jk) . "</td><td style=\"text-align: center\">". $ranglistahely ."</td></td></tr>";
    if($i%2 != 0) {
      $page_content .= '<tr class="odd">';
    }else{
      $page_content .= '<tr class="even">';
    }
    $i++;

    // Bajnokság táblázat
    $page_content .= '<td>' . _mwb_uid2nick($jk) . "</td><td style=\"text-align: center\">". $ranglistahely ."</td><td>" . $kiemeles . "</td><td>". $GLOBALS['_mwb_fajok'][$j['faj']] . "</td><td>".$GLOBALS['_mwb_vezerek'][$j['vezer']] . "</td></tr>";

  }
  $page_content .= "</tbody></table>";
  return $page_content;
}
