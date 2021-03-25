
public class Reader implements Runnable {

	// Variables
	private RWLock db;
	private String name;
	
	// Constructor
	public Reader(RWLock db, String name) {
		this.db = db;
		this.name = name;
	}
	
	@Override
	public void run() {
		while(true) {
			
			// Sleep for a random time
			SleepUtilities.nap();

			// Makes sure the writers can't write
			db.acquireReadLock(name);
			
			// Sleep for a random time
			SleepUtilities.nap();
			
			// Release the lock so writers can write (if there are no more readers)
			db.releaseReadLock(name);

		}
	}

}
