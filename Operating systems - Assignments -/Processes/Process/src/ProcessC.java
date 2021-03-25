

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

public class ProcessC {

	public static void main(String[] args) {
		
		
		System.out.println("\nProcess B started process C\nNow pinging google with 4 packets");

		
		// cmd => Through command prompt, /c => exit after completion, ping google.com => command
		ProcessBuilder ping = new ProcessBuilder("cmd.exe", "/c", "ping google.com");

		try {
			//start the process
			Process process = ping.start();
			
			//Inputstream returns bytes
			InputStream is = process.getInputStream();
			
			//InputstreamReader converts the bytes to chars
			InputStreamReader isr = new InputStreamReader(is);
			
			//BufferedReader reads text form chars
			BufferedReader br = new BufferedReader(isr);
			
			String line;
			//readLine reads until a \n, \r,...
			while ((line = br.readLine()) != null) {
				System.out.println(line);
			}		
			
			//Show user that process C is finished
			System.out.println("\nProcess C finished");

		} catch (Exception e) {
			System.out.println("Error: " + e);
		}

	}
}
