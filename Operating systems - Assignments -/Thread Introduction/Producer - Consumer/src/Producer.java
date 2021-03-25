import java.util.Date;

public class Producer implements Runnable {
	
	// Create the mailbox
	private Channel mbox;
	
	//Constructor
	public Producer(Channel m) {
		mbox = m;
	}


	public void run() {
		Date message;
		
		while(true) {
			SleepUtilities.nap();
			message = new Date();
			System.out.println("Producer produced: " + message);
			
			// Add the date to the mailbox
			mbox.send(message);
		}

	}

}
