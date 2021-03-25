
public class Driver {

	public static void main(String[] args) {
		if (args.length != 1) {
			System.err.println("Must enter an int as argument");
			System.exit(0);
		}
		
		
		MutableInteger sumObj = new MutableInteger();
		int upper = Integer.parseInt(args[0]);
		
		// Create a thread
		Thread worker = new Thread(new Summation(upper, sumObj));
		
		// Start the tread
		worker.start();
		
		try {
			//Wait for the thread to complete
			worker.join();
		} 
		catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("The value of " + upper + " is " + sumObj.getVal());
		
	}

}
