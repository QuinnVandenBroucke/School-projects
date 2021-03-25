
public class Factory {
	
	public static void main(String[] args) {
		Buffer buffer = new BoundedBuffer();
		
		// Create threads
		Thread producer = new Thread(new Producer(buffer));
		Thread consumer = new Thread(new Consumer(buffer));
		
		// Start threads
		producer.start();
		consumer.start();
	}

}
