public class Writer implements Runnable {

	private RWLock db;
	private String name;
	
	public Writer(RWLock db, String name) {
		this.db = db;
		this.name = name;
	}
	
	@Override
	public void run() {
		while(true) {

			// Sleep for a random time
			SleepUtilities.nap();
			
			// Try to acquire the writing lock
			db.acquireWriteLock(name);

			// Sleep for a random time
			SleepUtilities.nap();

			// Release the writing lock, so others can read or write
			db.releaseWriteLock(name);		
		}
	}
}
