
public class Factory {
	public static void main(String[] args) {
		
		// Variables
		RWLock db = new Lock();
		Thread[] readers = new Thread[3];
		Thread[] writers = new Thread[2];
		
		// Create Writers & readers
		for(int i = 0; i < 2; i++) {
			writers[i] = new Thread(new Writer(db, new Integer(i).toString()));
		}
		for(int i = 0; i < 3; i++) {
			readers[i] = new Thread(new Reader(db, new Integer(i).toString()));
		}
		
		// Start Writers & readers
		for(int i = 0; i < 2; i++) {
			writers[i].start();
		}
		for(int i = 0; i < 3; i++) {
			readers[i].start();
		}
		
	}
}
