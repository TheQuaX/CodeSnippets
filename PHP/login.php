<?php

    $_SESSION['authorized'] = false;
    
    # set your username and password here
    $username = 'test';
    $password = 'pwd';
    
    # if user clicks logout link then remove session and refresh page
    if(isset($_GET['logout'])){
       session_unset();
       header('Location:' . $_SERVER["SCRIPT_NAME"]);
    }

    #show an error if user enters wrong username and password
    if(isset($_GET['error'])){
       echo '<ul><li>Wrong username - password combination. Try again.</li></ul>';
    }
    
    #check if user is not logged in yet
    if($_SESSION['authorized'] == false){
    
        #check if user submitted form
        if(isset($_POST['submit'])){
        
            #check if user entered right username and password
            if($_POST['username'] == $username && $_POST['password'] == $password){
                
                #finally set a session to determine if user signed in or not, refresh page
                $_SESSION['authorized'] = true;
                header('Location:' . $_SERVER["SCRIPT_NAME"]);
            } else {
                header('Location:' . $_SERVER["SCRIPT_NAME"] . '?error');

            }
        } 
        
        #user did not logged in. Show login form
?>
        
        <html>
            <form action="" method="post">
                Username: <input type="text" name="username"></br>
                Password: <input type="password" name="password"></br>
                <input type="submit" name="submit" value="Login">
            </form>
        </html>
              
<?php       
    } else {   
    
    #show content to logged in user!
?>

<html>
    <head>
        <title>Login</title>
        <meta charset="utf-8">
        <style>
            nav{ 
                position: fixed;
                top:0px;
                left:0px;
                width:100%;
                background: rgba(100,100,100,0.6);
                line-height: 1.5;
                padding: 5px;
            }
            nav a{
               float: right;
               margin-right: 10px;
            }
            body{
               min-height: 1000px;
               padding: 5px;
            }
            section{
               background: rgba(190,220,190,0.7);
               margin: 20px 2px 2px 2px;
               padding: 5px;
               text-align: center;
               border-radius: 10px;
            }         
        </style>
    </head>
    <body>
        <nav> Hello <?php echo $username; ?>! <a href="?logout" alt="Click to logout"> Logout </a> </nav> 
        <section>
            <h1>Login</h1>
            <p>´This is just for testing issues.</p>
        </section>   
    </body>
</html>
<?php } ?>