import java.net.ServerSocket;
import java.net.Socket;

public class Server{
    public static void main(String[] args){
        ServerSocket server = new ServerSocket(80);

        System.out.println("Server started on 127.0.0.1:80.\r\nWaiting for a connection...");

        Socket client = server.accept();

        System.out.println("A client connected.");
    }
}