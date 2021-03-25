import java.util.Date;

public class Factory {

	// constructor
	public Factory() {
		
		//We need to define mailbox here, bcs it is shared btwn cons & prod
		Buffer<Date> mailbox = new BoundedBuffer<Date>();

		//produce the threads
		Thread producerThread = new Thread(new Producer(mailbox));
		Thread consumerThread = new Thread(new Consumer(mailbox));

		// give the threads a name
		producerThread.setName("Producer");
		consumerThread.setName("Consumer");

		// start the threads
		producerThread.start();
		consumerThread.start();

	}
	
	
	public static void main(String args[]) {
		Factory server = new Factory(); // initilize the factory
	}
}
