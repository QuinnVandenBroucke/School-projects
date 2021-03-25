import java.util.concurrent.atomic.AtomicInteger;

public class BoundedBuffer<E> implements Buffer<E> {

	private static final int BUFFER_SIZE = 5; // sets the size of the buffer
	private E[] buffer; // initilize a buffer

	// number of items in the buffer
	private int count;

	// points to the free position
	private int in;

	// points to the full position
	private int out;
	//private AtomicInteger count;
	
	// constructor
	public BoundedBuffer() {
		in = 0;
		out = 0;
		count = 0; // new AtomicInteger(0); // = 0;
		
		//initilize the buffer object
		buffer = (E[]) new Object[BUFFER_SIZE];
	}
	
	

	// implement the insert method
	public void insert(E item) {
		while (count  == BUFFER_SIZE) {
			// do nothing => no free space
		}

		// add items to the buffer
		buffer[in] = item;
		in = (in + 1) % BUFFER_SIZE;
		count++;
	}

	// implement the remove method
	public E remove() {
		E item = null;
		while (count == 0) {
			//needed bcs we don't use AtomicInteger, otherwise it gets stuck.
			return null;
			// do nothing => no items in the buffer
			
		}

		item = buffer[out];
		out = (out + 1) % BUFFER_SIZE;
		count--;
		
		return item;
	}

}
