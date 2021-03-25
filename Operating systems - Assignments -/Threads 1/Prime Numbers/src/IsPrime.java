
public class IsPrime implements Runnable {

	private int primeNumber;
	private boolean isPrime;
	
	public IsPrime(int number) {
		primeNumber = number;
	}
	
	@Override
	public void run() {
		
		for(int i = 2; i < primeNumber; i++) {
			
			if(primeNumber % i == 0) {
				isPrime = false;
				break;
			}
			else {
				isPrime = true;
			}
		}
		
		if(isPrime) {
			System.out.println(primeNumber + " is a prime number itself");
		}
		else {
			System.out.println(primeNumber + " is NOT a prime number itself");
		}

	}

}
