
import java.util.Date;

public class Run {

	public static void main(String[] args) {

		Channel<Date> mailBox = new MessageQueue<Date>();

		Date addDate = new Date();
		mailBox.send(addDate);
		System.out.println("New date added to the mailbox: " + addDate);

		Date rightNow = mailBox.receive();
		System.out.println("--Date removed from the mailbox: " + rightNow);

	}
}
