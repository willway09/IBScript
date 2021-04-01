import java.io.IOException;
import java.io.File;

import java.util.Scanner;
import java.io.PrintWriter;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

public class GenerateHeaders {
	public static void main(String args[]) throws IOException {
		File dir = new File(".");
		
		File files[] = dir.listFiles();
		
		for(File f : files) {
			if(f.getName().contains(".h") && !f.getName().contains(".hpp")) {
				PrintWriter pw = new PrintWriter(f);
				
				pw.println("#include \"" + f.getName() + "pp\"");
				
				pw.close();
			}
		}
	}
}