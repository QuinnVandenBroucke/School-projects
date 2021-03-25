import java.io.*;

public class ProcessB {

	public static void main(String[] args) {
		
		//pathstring needed for processbuilder
		String pathString = System.getProperty("user.dir");
		
		
		System.out.println("Process A started process B");
		
		
		//Create a file called CreatedByB
		File createdByBFile = new File("CreatedByB.txt");
		System.out.println("\nTrying to create a file");
		try {
			if(createdByBFile.createNewFile()) {
				System.out.println("--File succesfully created: " + createdByBFile.getName());
			}
			else {
				System.out.println("--File already exists.");
			}
		} 
		catch (IOException e1) {
			System.err.println(e1);
		}

		
		// Builds a new Java process: pb
		ProcessBuilder pb = new ProcessBuilder("Java.exe", "-cp", pathString, "ProcessC");
		try {
			Process process = pb.start();

			// Inputstream returns bytes
			InputStream is = process.getInputStream();

			// InputstreamReader converts the bytes to chars
			InputStreamReader isr = new InputStreamReader(is);

			// BufferedReader reads text form chars
			BufferedReader br = new BufferedReader(isr);

			String line;
			// readLine reads until a \n, \r,...
			while ((line = br.readLine()) != null) {
				System.out.println(line);
			}

			br.close();

		} catch (Exception e) {
			System.err.println(e);
		}

		System.out.println("Process B finished");

	}

}
