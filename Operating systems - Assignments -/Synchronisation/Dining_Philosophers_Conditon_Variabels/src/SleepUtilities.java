
public class SleepUtilities {
	
	//Variables
	private static final int NAP_DURATION = 5;
	
	static void nap() {
		nap(NAP_DURATION);
	}
	
	static void nap(int duration) {
		int sleeptime = (int) (NAP_DURATION * Math.random());
		
		try {
			Thread.sleep(sleeptime * 1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
