
public class SleepUtilities {
	
	private static final int NAP_TIME = 5;
	
	public static void nap() {
		nap(NAP_TIME);
	}
	
	public static void nap(int duration) {
		int sleeptime = (int) (duration * Math.random());
		try {
			Thread.sleep(sleeptime*1000);
		} 
		catch (InterruptedException e) {}
	}
}
