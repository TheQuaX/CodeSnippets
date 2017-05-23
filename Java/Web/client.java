package websocket.client;
import java.net.URI;
import javax.websocket.*;
@ClientEndpoint
public class WSClient  {
    private static Object waitLock = new Object();
@OnMessage
    public void onMessage(String message) {
//the new USD rate arrives from the websocket server side.
       System.out.println("Received msg: "+message);        
    }
 private static void  wait4TerminateSignal()
 {
  synchronized(waitLock)
  {try {
    waitLock.wait();
   } catch (InterruptedException e) {    
   }}}
public static void main(String[] args) {
WebSocketContainer container=null;//
     Session session=null;
  try{

   container = ContainerProvider.getWebSocketContainer(); 
//ratesrv is the  path given in the ServerEndPoint annotation on server implementation
session=container.connectToServer(WSClient.class, URI.create("ws://localhost:8080/test/")); 
   wait4TerminateSignal();
  } catch (Exception e) {
   e.printStackTrace();
  }
  finally{
   if(session!=null){
    try {
 session.close();
    } catch (Exception e) {     
     e.printStackTrace();
    }
   }         
  } 
 }
}