package com.cp.main;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;
import javax.swing.UIManager;

import com.cp.lexer.Lexer;
import com.cp.sys.Parase;
import com.cp.sys.Stack;

public class Ui extends JFrame
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JButton Button[];
	private JScrollPane Pane[ ];
	private JTextArea TextArea[];
	JToolBar jtb;
	private Stack<String> input=new Stack<>();
	public Ui()
	{
		super();
		setTitle("我是一个Pascal编译器");
		setBounds(100,100,750,750);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		initTools();
		initPanel();
		setLayout(new BorderLayout());
		add(jtb,BorderLayout.NORTH);
		JPanel panel=new JPanel();
		panel.setLayout(new GridLayout(1,2));
		panel.add(Pane[0]);
		panel.add(Pane[1]);
		add(panel);
		setVisible(true);
	}
	public void initTools()
	{
		jtb=new JToolBar();
		jtb.setFloatable(false);
		this.Button=new JButton[3];
		Button[0]=new JButton("打开文件");
		
		Button[0].setFont(new Font("华体新巍",Font.PLAIN,15));
		
		Button[0].addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				JFileChooser fileChooser = new JFileChooser();
				
				int j = fileChooser.showOpenDialog(getContentPane());
				if(j == JFileChooser.APPROVE_OPTION)
				{
					try
					{
						File selectedFile = fileChooser.getSelectedFile();
						BufferedReader in = new BufferedReader(new FileReader(selectedFile));
						String str = in.readLine();
						while(str != null)
						{
							TextArea[0].append(str+"\n");
							str = in.readLine();
						}
					}catch (Exception e1){
						e1.printStackTrace();
					}
				}
			}
		});
		jtb.add(Button[0]);
		Button[1]=new JButton("词法分析");
		Button[1].setFont(new Font("华体新巍",Font.PLAIN,15));
		Button[1].addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				TextArea[1].setText("");
				//读取this.TextArea[0]的内容，调用getText()函数什么的读入文件内容
				//调用此法分析函数
				//把结果输出到this.TextArea[1]上...
				String str=TextArea[0].getText();
				str+="\n";
				Lexer lexer=new Lexer(str);
				lexer.line=1;
				try {
					lexer.scanner();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				TextArea[1].append(lexer.result+lexer.err+lexer.warning);
				TextArea[1].append("符号表:\n");
				boolean flag=true;
				for(int i=0;i<lexer.arr.size();i++)
				{
					TextArea[1].append((lexer.arr.get(i)).toString(flag)+"\n");
				}
				input=lexer.input;
				
			}
		}
		);
		jtb.add(Button[1]);
		
		Button[2]=new JButton("语法分析");
		Button[2].setFont(new Font("华体新巍",Font.PLAIN,15));
		Button[2].addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				TextArea[1].setText("");
				//读取this.TextArea[0]的内容，调用getText()函数什么的读入文件内容
				//调用此法分析函数
				//把结果输出到this.TextArea[1]上...

				System.out.println("测试");
				Parase test=new Parase(input);
				TextArea[1].append(test.printstateform());
				TextArea[1].append(test.syntax_any());			
			}
		}
		);
		jtb.add(Button[2]);
		
		Container ct=this.getContentPane();
		jtb.setBounds(0, 0, 900, 30);
		ct.add(jtb);
	}

	public void initPanel()
	{
		this.Pane = new JScrollPane[2];
		this.TextArea = new JTextArea[2];
		for(int i=0;i<2;i++)
		{
			this.TextArea[i] = new JTextArea();
			this.Pane[i] = new JScrollPane(TextArea[i]);
			if(i == 0)
			{
				this.TextArea[i].addKeyListener(new KeyListener()
						{
							public void keyPressed(KeyEvent e)
							{
								if((e.getKeyCode() == KeyEvent.VK_S) && e.isControlDown())
								{
									final String text = TextArea[0].getText();
									JFileChooser fileChooser = new JFileChooser();
									int j = fileChooser.showSaveDialog(null);
									if(j == fileChooser.APPROVE_OPTION)
									{
										File file = fileChooser.getSelectedFile();
										try
										{
											if(file.exists() == false)
											{
												file.createNewFile();
											}
											FileWriter writer = new FileWriter(file);
											char[] array = text.toCharArray();
											writer.write(array);
											writer.flush();
											writer.close();
										}catch(IOException e3){}
									}
								}
							}
							@Override
							public void keyReleased(KeyEvent arg0) {
								// TODO Auto-generated method stub
								
							}
							@Override
							public void keyTyped(KeyEvent arg0) {
								// TODO Auto-generated method stub
								
							}
						}
						);
			}
		}
	}
	

	
	public static void main(String args[])
	{
		try
		{
			String lookAndFeel =
					UIManager.getSystemLookAndFeelClassName();
			UIManager.setLookAndFeel(lookAndFeel);
		}catch(Exception e2){}
		
		Ui frame = new Ui();
	}
}
