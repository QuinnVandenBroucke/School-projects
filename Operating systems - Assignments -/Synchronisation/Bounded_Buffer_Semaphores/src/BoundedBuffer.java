import java.util.concurrent.Semaphore;

public class BoundedBuffer implements Buffer {

	// Variables
	private static final int BUFFER_SIZE = 5;
	private Object[] buffer;
	private int in, out;
	private Semaphore mutex;
	private Semaphore empty;
	private Semaphore full;
	
	// Constructor
	public BoundedBuffer() {
		// Buffer is initially empty
		in = 0;
		out = 0;
		buffer = new Object[BUFFER_SIZE];
		
		mutex = new Semaphore(1);
		empty = new Semaphore(BUFFER_SIZE);
		full = new Semaphore(0);
	}
	
	@Override
	public void insert(Object item) {
		try {
			empty.acquire();
			mutex.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		
		// Add item to the buffer
		buffer[in] = item;
		in = (in + 1) % BUFFER_SIZE;
		
		mutex.release();
		full.release();
	}

	@Override
	public Object remove() {
		try {
			full.acquire();
			mutex.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		
		// Remove item from buffer
		Object item = buffer[out];
		out = (out + 1) % BUFFER_SIZE;
		
		mutex.release();
		empty.release();
		
		return item;
	}

}
