import java.util.Date;

public class Producer implements Runnable {

	private Buffer buffer;
	
	public Producer(Buffer buffer) {
		this.buffer = buffer;
	}
	
	@Override
	public void run() {
		Date message;
		
		while(true) {
			// Nap for a bit
			SleepUtilities.nap();
			
			
			// Produce new item and insert it
			message = new Date();
			System.out.println("Producer produced: " + message);
			buffer.insert(message);
		}
	}

}
