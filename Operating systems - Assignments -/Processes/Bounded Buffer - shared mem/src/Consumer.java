import java.util.Date;

public class Consumer implements Runnable{

	//instance variable mbox
	private Buffer<Date> mbox;
	
	
	//Constructor
	public Consumer(Buffer<Date> m) {
		mbox = m;
	}

	//implement the run method from Runnable
	public void run() {
		Date message;
		
		while(true) {
			//lets the Consumer sleep for a random time
			SleepUtilities.nap();
			
			//consume an item from the mailbox
			System.out.println("--Consumer wants to consume");
			message = mbox.remove();//removes item from mailbox and returns it
			if (message != null) {
				System.out.println("--Consumer consumed " + message);
			}
		}
		
	}

}
