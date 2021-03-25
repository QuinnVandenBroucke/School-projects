
public class Start {

	public static void main(String[] args) {
		
		Thread calcWorker = new Thread(new Calculator(Integer.parseInt(args[0])));
		Thread isPrimeWorker = new Thread(new IsPrime(Integer.parseInt(args[0])));
		
		System.out.println("Your number was: " + args[0]);
		
		calcWorker.start();
		try {
			calcWorker.join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		isPrimeWorker.start();
		
	}

}
