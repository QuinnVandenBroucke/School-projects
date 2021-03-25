import java.util.Date;

public class Consumer implements Runnable {
	
	// Create the mailbox
		private Channel mbox;
		
		//Constructor
		public Consumer(Channel m) {
			mbox = m;
		}

	public void run() {
		Date message;
		
		while (true) {
			SleepUtilities.nap();	
			message = new Date();
			System.out.println("-Consumer wants to consume");
			message = (Date) mbox.receive();
			if (message != null) {
				System.out.println("--Consumer consumed " + message);
			}
		}
		
		

	}

}
