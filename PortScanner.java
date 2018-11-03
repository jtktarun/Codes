import java.net.*;
public class PortScanner{
	public static void main(String[] args) {
		int i;
		for(i=1;i<65535;i++){
			try{
				Socket socket = new Socket();
				socket.connect(new InetSocketAddress("localhost",i),1000);
				socket.close();
				System.out.println( i + " is open");
			}
			catch (Exception e) {
				
			}
		}	
	}
}