
/**
 * @author quinn
 *
 */
public class Summation implements Runnable {
	
	private int upper;
	private MutableInteger sumValue;
	
	// Constructor
	public Summation(int upper, MutableInteger sumValue) {
		if (upper < 0) {
			throw new IllegalArgumentException();
		}
		this.upper = upper;
		this.sumValue = sumValue;
	}

	@Override
	public void run() {
		int sum = 0;
		for (int i = 0; i <= upper; i++) {
			sum =+ i;
			sumValue.setVal(sum);
		}

	}

}
