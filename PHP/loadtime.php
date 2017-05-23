<?php
function get_time() {
    $time = microtime();
    $time = explode(' ', $time);
    $time = $time[1] + $time[0];
    
    return $time;
}
$start = get_time();
?>

<h1>A Sample HTML Page</h1>
<p>A paragraph of text</p>

<?php
//a sample dummy loop
for($i=0;$i<100000;$i++) { }
?>

<?php
$finish = get_time();
$total_time = round(($finish - $start), 4);
echo 'Page generated in '.$total_time.' seconds.';
?>