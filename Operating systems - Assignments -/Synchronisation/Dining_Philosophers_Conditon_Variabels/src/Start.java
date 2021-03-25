public class Start {

	public static void main(String[] args) {
		
		Thread[] philo = new Thread[5];
		/// Ze zitten allemaal aan een gemeenschappelijke tafel! Dus meegeven
		DiningPhilosophers table = new DiningPhilosophers();
		
		
		for(int i = 0; i < 5; i++) {
			philo[i] = new Thread(new Philosopher(i, table));
		}
		
		
		for(int i = 0; i < 5; i++) {
			philo[i].start();
		}		
	}
}
