import java.net.*;
import java.io.*;
import java.util.*;

public class GroupChat{
	private static final String TERMINATE = "exit";
	static String name;
	static volatile boolean finished = false;

	public static void main(String[] args){
		if(args.length != 2)
			System.out.println("err");
		else{
			try{
				InetAddress group = InetAddress.getByName(args[0]);
				int port = Integer.parseInt(args[1]);
				Scanner sc = new Scanner(System.in);
				System.out.println("Name");
				name = sc.nextLine();
				MulticastSocket socket = new MulticastSocket(port);
				socket.setTimeToLive(0);
				socket.joinGroup(group);
				Thread t = new Thread (new ReadThread(socket,group,port));
				t.start();
				while(true){
					String message;
					message = sc.nextLine();
					if(message.equalsIgnoreCase(GroupChat.TERMINATE)){
						finished = true;
						socket.leaveGroup(group);
						socket.close();
						break;
					}
					message = name + " : " + message;
					byte[] buffer = message.getBytes();
					DatagramPacket dg = new DatagramPacket(buffer,buffer.length,group,port);
					socket.send(dg);
				}
			}
			catch(SocketException se){
				System.out.println("err");
			}
			catch(IOException io){
				System.out.println("err");
			}
		}
	}
}
class ReadThread implements Runnable{
	private MulticastSocket socket;
	private InetAddress group;
	private int port;
	private static final int MAX_LEN = 1000;
	ReadThread(MulticastSocket socket, InetAddress group, int port){
		this.socket = socket;
		this.group = group;
		this.port = port;
	}

	@Override
	public void run(){
		while(!GroupChat.finished){
			byte[] buffer = new byte[MAX_LEN];
			DatagramPacket dg = new DatagramPacket(buffer,buffer.length,group,port);
			try{
				socket.receive(dg);
				String message = new String(buffer,0,dg.getLength(),"UTF-8");
				if(!message.startsWith(GroupChat.name))
					System.out.println(message);
			}
			catch(IOException io){
				System.out.println("err");
			}
		}
	}
}