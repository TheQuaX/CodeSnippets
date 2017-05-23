import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

//translate bytes of request to string
String data = new Scanner(in,"UTF-8").useDelimiter("\\r\\n\\r\\n").next();

Matcher get = Pattern.compile("^GET").matcher(data);

if (get.find()) {
    Matcher match = Pattern.compile("Sec-WebSocket-Key: (.*)").matcher(data);
    match.find();
    byte[] response = ("HTTP/1.1 101 Switching Protocols\r\n"
            + "Connection: Upgrade\r\n"
            + "Upgrade: websocket\r\n"
            + "Sec-WebSocket-Accept: "
            + DatatypeConverter
            .printBase64Binary(
                    MessageDigest
                    .getInstance("SHA-1")
                    .digest((match.group(1) + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11")
                            .getBytes("UTF-8")))
            + "\r\n\r\n")
            .getBytes("UTF-8");

    out.write(response, 0, response.length);
}