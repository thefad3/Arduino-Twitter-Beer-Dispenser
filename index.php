<?php

require "vendor/abraham/twitteroauth/autoload.php";

use Abraham\TwitterOAuth\TwitterOAuth;

define('CONSUMER_KEY', 'swWztv5btayRyo7NPYvE7zbRb');
define('CONSUMER_SECRET', 'lOoCLcjckuN95OJDpKWBdLOwz7KM8ZiKV9fV69fDS8al474rfr');
define('ACCESS_TOKEN', '2351957653-Tz01PNAtXDyyidbLTatFiF50WUDZUye04RhwL04');
define('ACCESS_TOKEN_SECRET', 'qTHSB4P6CipjwDoH6RqWo9MiZoWnydKNdSnQdRDKTVbI6');

$toa = new TwitterOAuth(CONSUMER_KEY, CONSUMER_SECRET, ACCESS_TOKEN, ACCESS_TOKEN_SECRET);

$query = array(
  "q" => "#brewcrewfs",
  "result_type" => "recent"
);

$results = $toa->get('search/tweets', $query);
$currentTime = strtotime("-1 minute");
$data = strtotime($results->statuses[0]->created_at);

if($data > $currentTime){
        echo 'y';
}else{
        echo 'n';
}

?>