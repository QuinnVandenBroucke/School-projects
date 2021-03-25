import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DiningPhilosophers {

	// Variables
	enum State {
		THINKING, HUNGRY, EATING
	};

	State[] state = new State[5];
	Condition[] self = new Condition[5];
	Lock lock = new ReentrantLock();

	// Constructor
	public DiningPhilosophers() {
		for (int i = 0; i < state.length; i++) {
			state[i] = State.THINKING;
			self[i] = lock.newCondition();
		}
	}

	// Check the position itself & the neighbours
	private void testIfFree(int position) {

		/*
		 * We need to check if the user at position is hungry, AND the fork to the left
		 * AND right is free
		 */
		if ((state[(position + 4) % 5] != State.EATING) && (state[position] == State.HUNGRY)
				&& (state[(position + 1) % 5] != State.EATING)) {
		
			
			int leftfork = position + 1;
			int rightfork = (position + 4) % 5 + 1;
			
			System.out.println(String.format("Philosopher %d takes fork %d and %d", position + 1, leftfork, rightfork));
			
			state[position] = State.EATING;
			self[position].signal();
		}
	}

	// Take the forks
	public void takeForks(int position) {
		
		 lock.lock(); 
		 try {		 
			state[position] = State.HUNGRY;
			testIfFree(position);
	
			// This means that the fork(s) are not available
			if (state[position] != State.EATING) {
				// Needs to be in TRY-CATCH
				try {
					self[position].await();	
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		 } 
		 finally { 
			 lock.unlock(); 
		 }
		 

	}

	// Put back the forks
	public void returnForks(int position) {

		
	  lock.lock(); 
	  try {
		state[position] = State.THINKING;
		
		int leftfork = position + 1;
		int rightfork = (position + 4) % 5 + 1;
		
		System.out.println(String.format("--Philosopher %d puts fork %d and %d down", position + 1, leftfork, rightfork));
		
		testIfFree((position + 4) % 5);
		testIfFree((position + 1) % 5);
	 } 
	  finally { 
		 lock.unlock(); 
	  }
	}
}