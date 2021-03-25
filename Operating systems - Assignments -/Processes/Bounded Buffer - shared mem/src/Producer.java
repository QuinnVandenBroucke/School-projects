import java.util.Date;

public class Producer implements Runnable {
	
	//instance variable mbox
	private Buffer<Date> mbox;
	
	public Producer (Buffer<Date> b) {
		mbox = b;
	}

	
	public void run() {
		Date message;
		
		while(true) {
			SleepUtilities.nap(); //sleep for a random time
			message = new Date();
			
			//send item to the mailbox (buffer)
			mbox.insert(message);
			
			System.out.println("Producer produced " + message);
		}
		
	}

}
