

import java.util.Date;
import java.rmi.*;

public interface RemoteDate extends Remote
{
	public Date getDate() throws RemoteException;
}
