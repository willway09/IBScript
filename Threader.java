import javax.swing.JTextArea;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.concurrent.atomic.AtomicBoolean;

public class Threader implements Runnable {

	volatile boolean stop = false;
	JTextArea area;
	BufferedReader in;
	BufferedReader err;
	public Threader(JTextArea area, BufferedReader in, BufferedReader err) {
		this.area = area;
		this.in = in;
		this.err = err;
	}
	
	public void run() {
		
		
		while(!stop) {
			try {
				String s = in.readLine();
				
				if(s != null) {
					area.append(s + "\n");
				}
				
				String se = err.readLine();
				if(se != null) {
					area.append(se + "\n");
				}
				
				Thread.sleep(1);
				
			} catch(IOException e) {
				
			} catch(InterruptedException e) {
				
			}
		}
	}
	
	public void stopThreader() {
		stop = true;
	}
}