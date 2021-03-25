
public class Calculator implements Runnable {

	private int primeNum;
	private int number;
	
	public Calculator(int number) {
		primeNum = number;
	}
	
	@Override
	public void run() {
		
		for (int i = 1; i <= primeNum; i++) {
			
			int counter = 0;
			
			for(number = i; number >= 1; number--) {
				if(i % number == 0) {
					counter++;
				}
			}
			
			if (counter == 2) {
				System.out.println(i +" is a prime number");
			}
		}
	}

}
