import java.util.concurrent.Semaphore;

public class Lock implements RWLock {

	// Variables
	private Semaphore mutex;
	private Semaphore wrt_db;
	private int readCount;
	
	
	// Constructor
	public Lock() {
		mutex = new Semaphore(1);
		wrt_db = new Semaphore(1);
		readCount = 0;
	}
		
	
	@Override
	public void acquireReadLock(String name) {
		System.out.println(String.format("Reader %s wants to read", name));
		
		// Must be in a TRY-CATCH
		try {
			mutex.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		
		++readCount;
		// First reader tells the others that the db is being read (Can't write anymore)
		if (readCount == 1) {
			// Must be in a TRY-CATCH
			try {
				wrt_db.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		/// Acquired the lock so can read. 
		System.out.println(String.format("Reader %s is reading. Reader count = %d", name, readCount));
		mutex.release();
	}

	@Override
	public void acquireWriteLock(String name) {
		System.out.println(String.format("--Writer %s wants to write", name));
		
		// Must be in a TRY-CATCH
		try {
			wrt_db.acquire();
			/// Acquired the write lock, so can write
			System.out.println(String.format("--Writer %s is writing", name));
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		

	}

	@Override
	public void releaseReadLock(String name) {
		
		// Must be in a TRY-CATCH
		try {
			mutex.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		--readCount;
		System.out.println(String.format("Reader %s is done reading. Reader count = %d", name, readCount));
		// Last readers tells the others that everyone is done, writers can write.
		if(readCount == 0) {
			wrt_db.release();
		}
		mutex.release();
	}

	@Override
	public void releaseWriteLock(String name) {
		// Done writing, release the lock
		System.out.println(String.format("--Writer %s is done writing", name));
		wrt_db.release();

	}

}
