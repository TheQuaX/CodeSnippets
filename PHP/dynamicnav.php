<style>
    #menu {
        display block;
        background-color:#272822;
        padding:10px;
    }
    #menu a {
        background-color:#17a68a;
        color:#ffffff;
        font-weight:bold;
        padding:5px;
        text-decoration:none;
        margin-right:5px;
    }
    #menu a:hover {
        background-color:#1abc9c;
    }
</style>

<?php
$pages = array(
    'index.php' => 'Home',
    'about.php' => 'About',
    'contact.php' => 'Contact'
);
?>
<nav id="menu">
    <?php
    foreach($pages as $link => $title) {
        echo '<a href="'.$link.'">'.$title.'</a>';
     }
    ?>
</nav>