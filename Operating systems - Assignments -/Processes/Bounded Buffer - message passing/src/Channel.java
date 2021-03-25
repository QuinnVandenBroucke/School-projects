public interface Channel<E> {

	//abstract classes => no implementation and must be overwritten in sub classes
	
	//sends message
	public abstract void send (E item);
	
	//receive message
	public abstract E receive();
}
