import java.io.IOException;
import java.io.File;

import java.util.Scanner;

public class LineCount {
	public static void main(String args[]) throws IOException {
		File dir = new File(".");
		
		File files[] = dir.listFiles();
		
		int lineCount = 0;
		
		for(File f : files) {
			if(f.getName().contains(".cpp") || f.getName().contains(".hpp") || f.getName().contains(".tpp") || f.getName().contains(".java")) {
				Scanner r = new Scanner(f);
				
				while(r.hasNextLine()) {
					String s = r.nextLine();
					s = s.trim();
					if(s.equals("")) {
						
					} else lineCount++;
				}
				
				r.close();
			}
		}
		
		System.out.println(lineCount);
	}
}