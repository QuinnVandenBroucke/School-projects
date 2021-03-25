

import java.rmi.*;

public class RMIClient 
{  
	public static final String server = "127.0.0.1";

   	public static void main(String args[]) { 
    		try {
      		String host = "rmi://" + server + "/DateServer";
      		RemoteDate dateServer = (RemoteDate)Naming.lookup(host);
      		System.out.println(dateServer.getDate());
    		}
    		catch (Exception e) {
        		System.err.println(e);
    		}
   	}
}

