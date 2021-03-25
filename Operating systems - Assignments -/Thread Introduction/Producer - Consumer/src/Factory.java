
public class Factory {
	
	// Constructor
	public Factory() {
		Channel mailbox = new MessageQueue();
	
	// Producer thread
	Thread producerThread = new Thread(new Producer(mailbox));
	
	// Consumer thread
	Thread consumerThread = new Thread(new Consumer(mailbox));
	
	//Set the names of the Threads
	producerThread.setName("Producer");
	consumerThread.setName("Consumer");
	
	// Start the threads
	producerThread.start();
	consumerThread.start();
	}
	
	
	public static void main (String args[]) {
		Factory server = new Factory();
	}

}
