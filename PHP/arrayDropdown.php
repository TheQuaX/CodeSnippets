<?php
$arr = array(
    1=>"PHP",
    2=>"C++",
    3=>"Java",
    4=>"C#",
    5=>"Python"
    );
?>
Topic: <select name="topic">
    <?php
    foreach($arr as $key=>$val) {
        echo '<option value="'.$key.'">'.$val.'</option>';
    }
    ?>
</select>