import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JButton;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JOptionPane;

import javax.swing.filechooser.FileFilter;
import javax.swing.JFileChooser;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;


import java.io.PrintWriter;
import java.io.IOException;
import java.io.File;

import java.awt.BorderLayout;
import javax.swing.JToolBar;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import java.util.Scanner;
import java.util.StringTokenizer;

import java.util.HashMap;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

public class GUI {
	
	JTextArea ta;
	JTextArea initializationTa;
	//JButton open;
	JButton save;
	JButton run;
	JButton open;
	JButton export;
	JButton view;
	JFrame window;
	
	String assignmentText = null;
	
	File file = null;
	
	public GUI(String filename) {
		this();
		load(filename);
	}
	
	public GUI() {
		window = new JFrame();
		window.setTitle("IBScript");
		
		window.setSize(500,500);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		window.setLayout(new BorderLayout());
		
		ta = new JTextArea();
		ta.setTabSize(2);
		initializationTa = new JTextArea();
		
		
		JTabbedPane tabbedPane = new JTabbedPane();
		tabbedPane.addTab("Code", new JScrollPane(ta));
		tabbedPane.addTab("Initialization", new JScrollPane(initializationTa));
		window.add(tabbedPane, BorderLayout.CENTER);
		
		
		JToolBar tb = new JToolBar();
		
		open = new JButton("Open");
		
		open.addActionListener(
			new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					
								
						if(file != null) save();
						JFileChooser selector = new JFileChooser();
						
						selector.setFileFilter(

							new FileFilter() {
								
								public boolean accept(File file) {
									if(file.getName().endsWith(".ib") || file.getName().endsWith(".ibasg") || file.isDirectory()) {
										return true;
									} else {
										return false;
									}
								}
								
								public String getDescription() {
									return "IBScript files";
								}
							}
						);
						selector.setCurrentDirectory(new File("."));
						
						int fileRtn = selector.showOpenDialog(window);
						
						if(fileRtn == JFileChooser.APPROVE_OPTION) {
							file = selector.getSelectedFile();
						}
						
						load();
					
					
					
				}
				
				
			}
		);
		
		save = new JButton("Save");
		
		save.addActionListener(
			new ActionListener() {
				public void actionPerformed(ActionEvent e) {						
					save();
				}
			}
		);
		
		run = new JButton("Run");
		
		run.addActionListener(
			new ActionListener() {
				public void actionPerformed(ActionEvent e) {

					save();
					run();
				}
			}
		);
		
		export = new JButton("Export as Assignment");
		
		export.addActionListener(
			new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					File oldFile = file;
					
					
					saveAs(".ibasg");
					
					file = oldFile;
				}
			}
		);
		
		view = new JButton("View Assignment Details");
		view.addActionListener(
			new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if(assignmentText != null) {
						JOptionPane.showMessageDialog(window, assignmentText);
					}
				}
			}
		);
		
		
		tb.add(open);
		tb.add(save);
		tb.add(run);
		tb.add(export);
		tb.add(view);
		
		window.add(tb, BorderLayout.NORTH);
		
		
		window.setVisible(true);
	}
	
	public static void main(String args[]) {
		
		if(args.length < 1) {
			new GUI();
		} else {
			new GUI(args[0]);
		}
	}
	
	int evaluate(String ss, HashMap<String, Integer> variables) {
		String s = ss.trim();
		try {
			int a = Integer.parseInt(s);
			System.out.println(a);
			return a;
		} catch(NumberFormatException e) {
			//return variables.get(s);
			System.out.println(variables);
			return 1;
		}
	}
	
	public void run() {
		
		JFrame f = new JFrame();
		f.setSize(500,500);
		f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		
		JTextArea out = new JTextArea();
		out.setTabSize(2);
		out.setEditable(false);
		
		String s = ta.getText();
		
		StringTokenizer stk = new StringTokenizer(s, "\n");
		String execs[] = new String[stk.countTokens()];
		
		
		f.add(new JScrollPane(out));
		
		f.setVisible(true);
		
		try {
			Process proc = Runtime.getRuntime().exec("ibscript.exe " + file.getCanonicalPath());
			BufferedReader in = new BufferedReader(new InputStreamReader(proc.getInputStream()));
			BufferedReader err = new BufferedReader(new InputStreamReader(proc.getErrorStream()));
			
			String str = null;
			Threader threader = new Threader(out, in, err);
			(new Thread(threader)).start();
			
			f.addWindowListener(
				new WindowAdapter() {
					public void windowClosed(WindowEvent e) {
						threader.stopThreader();
					}
				}
			);
			
		} catch(IOException e) {
			
		}
		
		
	}
	
	public void load(String filename) {
		file = new File(filename);
		load();
	}
	
	private void load() {
		

		ta.setText("");
		
		window.setTitle(file.getName());
		
		if(file.getName().contains(".ibasg")) {
			
			try {
				Scanner r = new Scanner(file);
				
				while(r.hasNextLine()) {
					String s = r.nextLine();
					
					if(s.equals("//END ASSIGNMENT")) {
						
						
						assignmentText = initializationTa.getText();
						initializationTa.setText("");
					} else {
						initializationTa.append(s + "\n");
					}
				}
				ta.setText("");
				r.close();
				
				file = new File(file.getName().replace(".ibasg", ".ib"));
			} catch(IOException e) {
				
			}
		} else {
			try {
				
				Scanner r = new Scanner(file);
				
				while(r.hasNextLine()) {
					String s = r.nextLine();
					
					if(s.equals("//END INITIALIZATION")) {
						
						initializationTa.setText(ta.getText());
						
						ta.setText("");
					} else {
						ta.append(s + "\n");
					}
				}
				assignmentText = null;
				r.close();
			} catch(IOException e) {
				JOptionPane.showMessageDialog(window, "Invalid IBScript file", "Error", JOptionPane.ERROR_MESSAGE);
			}
		}

	}
	
	public void saveAs(String extension) {
		JFileChooser selector = new JFileChooser();
		
		selector.setFileFilter(

			new FileFilter() {
				
				public boolean accept(File file) {
					if(file.getName().endsWith(extension) || file.isDirectory()) {
						return true;
					} else {
						return false;
					}
				}
				
				public String getDescription() {
					return "IBScript files";
				}
			}
		);
		selector.setCurrentDirectory(new File("."));
		
		int fileRtn = selector.showSaveDialog(window);
		
		if(fileRtn == JFileChooser.APPROVE_OPTION) {
			file = selector.getSelectedFile();
			save();
		}
	}

	public void save() {		
		if(file == null) {
			saveAs(".ib");
			return;
		}
		
		if(file.getName().contains(".ibasg")) {
			try {
				PrintWriter pw = new PrintWriter(file);
				
				String description = JOptionPane.showInputDialog(window, "Describe the assignment");
				
				pw.println(description);
				pw.println("//END ASSIGNMENT");
				
				String s = initializationTa.getText();
				pw.println(s);
				pw.close();
				
			} catch(IOException exc) {
				
			}
		} else {
			try {
				PrintWriter pw = new PrintWriter(file);
				
				
				String s = initializationTa.getText();
				pw.println(s);
				pw.println("//END INITIALIZATION");
				s = ta.getText();
				pw.println(s);
				pw.close();
				
			} catch(IOException exc) {
				
			}
		}
	}
}