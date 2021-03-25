import java.util.Date;

public class Consumer implements Runnable {

	private Buffer buffer;
	
	public Consumer(Buffer buffer) {
		this.buffer = buffer;
	}
	
	@Override
	public void run() {
		Date message;
		
		while (true) {
			// Nap for a bit
			SleepUtilities.nap();
			
			System.out.println("Consumer wants to consume");
			
			// Consume an item
			message = (Date) buffer.remove();
			System.out.println("Consumer consumed: " + message);

		}

	}

}
