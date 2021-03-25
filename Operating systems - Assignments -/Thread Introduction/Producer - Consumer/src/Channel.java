
public interface Channel {
	
	// Abstract method to send data
	public abstract void send(Object item);
	
	// Abstract method to receive data
	public abstract Object receive();
	
}
