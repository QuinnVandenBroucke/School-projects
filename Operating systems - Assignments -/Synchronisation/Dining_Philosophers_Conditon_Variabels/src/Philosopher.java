
public class Philosopher implements Runnable {

	// Variables
	int position;
	DiningPhilosophers philo;
	
	
	public Philosopher(int position, DiningPhilosophers philo) {
		this.position = position;
		this.philo = philo;
	}
	
	
	@Override
	public void run() {
		

		
		
		while (true) {
			
			SleepUtilities.nap();
			philo.takeForks(position);


			
			SleepUtilities.nap();
			philo.returnForks(position);
		}
	}
}
