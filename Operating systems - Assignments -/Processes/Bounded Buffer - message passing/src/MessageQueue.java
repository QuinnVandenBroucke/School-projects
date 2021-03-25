import java.util.Vector;

public class MessageQueue<E> implements Channel<E> {

	
	private Vector<E> queue;
	
	//constructor
	public MessageQueue(){
		queue = new Vector<E>();
	}
	
	
	//non blocking send
	public void send(E item) {
		queue.add(item);

	}

	//non blocking receive
	public E receive() {
		if (queue.size() == 0) {
			return null;	
		}
		else {
			return queue.remove(0);
		}
	}

}
