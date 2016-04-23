<?php

$plaka = $_POST['input'];

$plakalar = file('plakalar.txt');

echo plaka_ara($plaka, $plakalar);

function plaka_ara($plaka, $plakalar) {
  foreach($plakalar as $p) {
    if (strpos($p, $plaka) !== FALSE)
      return $p;
  }

  return "Kayıt bulunamadı";
}
