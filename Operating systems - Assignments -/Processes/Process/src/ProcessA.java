import java.io.*;

public class ProcessA {
	public static void main(String[] args) throws IOException {

		//pathstring needed for processbuilder
		String pathString = System.getProperty("user.dir");		


		// Builds a new Java process: pb
		ProcessBuilder pb = new ProcessBuilder("Java.exe", "-cp", pathString, "ProcessB");

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

		System.out.println("Process A finished");
	}
}
