
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;

public class RemoteDateImpl extends UnicastRemoteObject implements RemoteDate
{
    public RemoteDateImpl() throws RemoteException {  }
    
    public  Date getDate() throws RemoteException {
        return new Date();
    }
    
   public static void main(String[] args)  {
        try {
         RemoteDate dateServer = new RemoteDateImpl();

         // Bind this object instance to the name "RMIDateObject"
         Naming.rebind("DateServer", dateServer);

         System.out.println("DateServer bounded");
        }
        catch (Exception e) {
            System.err.println(e);
        }
    }
  
   
   
}
