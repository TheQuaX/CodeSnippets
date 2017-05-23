<?php
    echo ' <!DOCTYPE html>
<html>
    <head>
        <title>Output Tag</title>
    </head>
    <body> <h3> Change The number to see Output in action</h3>
        <form oninput="sumresult.value=parseInt(z2.value)+parseInt(z3.value)"><input type="number" name="z2" value="20"/> + <input type="number" name="z3" value="40"/> <br/> The output is : <output name="sumresult"></output></form>
    </body>
</html> ';
?>