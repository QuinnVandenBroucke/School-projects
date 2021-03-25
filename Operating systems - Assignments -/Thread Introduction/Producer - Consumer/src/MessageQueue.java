import java.util.Vector;

public class MessageQueue implements Channel {
	
	private Vector<Object> queue;

	// Constructor
	public MessageQueue() {
		queue = new Vector<Object>();
	}
	
	// Non blocking send
	public void send(Object item) {
		queue.addElement(item);
	}

	// Non blocking receive
	public Object receive() {
		if (queue.size() == 0) {
			return null;
		}
		else {
			return queue.remove(0);
		}
	}

}
