
public interface RWLock {

	/// Add the names to make it more clear
	public abstract void acquireReadLock(String Name);
	public abstract void acquireWriteLock(String Name);
	public abstract void releaseReadLock(String Name);
	public abstract void releaseWriteLock(String Name);

	
}
