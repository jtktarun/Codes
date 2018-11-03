import java.net.*;

class mac{
	public static void main(String[] args){
		InetAddress ip;
		try{
			ip = InetAddress.getByName("10.10.0.40");
			NetworkInterface ne = NetworkInterface.getByInetAddress(ip);
			System.out.println(ne.getHardwareAddress());
		}
		catch(Exception e){

		}
	}
}