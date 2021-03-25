public class SleepUtilities {

	private static final int NAP_TIME = 5;
	
	//we call this one
	public static void nap() {
		nap(NAP_TIME); //calls the other nap method
	}
	
	public static void nap(int duration) {
		
		 //typecast int truncates the value
		int sleeptime = (int) (duration * Math.random());
		
		try {
			//let the thread sleep for a random time (in ms)
			Thread.sleep(sleeptime*1000); 
		} 
		catch (Exception e) {
			System.out.println(e);
		}
	}
	
	
}
