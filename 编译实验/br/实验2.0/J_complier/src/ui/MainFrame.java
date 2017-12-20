package ui;

import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;

import threeAddressCode.SemanticAction;

import func_cifa.Syn_ana;
import func_syn.Parase;
import func_syn.Stack;

public class MainFrame extends JFrame
{
	JMenuBar jmb;
	JMenu jm[]=new JMenu[10];
	JMenuItem jmi[]=new JMenuItem[10];
	JTextArea jta1,jta2;
	JButton jb1,jb2,jt1,jt2,jt3,jt4,jt5;
	JScrollPane jsp,jsp2;
	JToolBar jtb;
	Stack<String> inputStack=new Stack<String>();
	
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		new MainFrame();
	}

	public MainFrame()
	{
		//�˵���ʼ��
		initmenu();
		
		//��������ʼ��
		inittools();
		
		//������ʼ��
		initboard();
		
		this.setSize(900, 700);
		this.setTitle("���ױ�����");
		this.setIconImage((new ImageIcon("images/1.png")).getImage());
		int width = Toolkit.getDefaultToolkit().getScreenSize().width;
		int height = Toolkit.getDefaultToolkit().getScreenSize().height;
		this.setLocation((width - 800) / 2, (height - 600) / 2-100);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setResizable(false);
		this.setVisible(true);
	}
	
	//��������ʼ��
	public void inittools()
	{
		jtb=new JToolBar();
		jtb.setFloatable(false);
		
		jt1=new JButton("��");
		jt1.setFont(new Font("������κ",Font.PLAIN,15));
		jt1.addActionListener(new toollistener());
		jtb.add(jt1);
		jt2=new JButton("����");
		jt2.setFont(new Font("������κ",Font.PLAIN,15));
		jt2.addActionListener(new toollistener());
		jtb.add(jt2);
		jt3=new JButton("�ʷ�����");
		jt3.setFont(new Font("������κ",Font.PLAIN,15));
		jt3.addActionListener(new toollistener());
		jtb.add(jt3);
		jt4=new JButton("�﷨����");
		jt4.setFont(new Font("������κ",Font.PLAIN,15));
		jt4.addActionListener(new toollistener());
		jtb.add(jt4);
		jt5=new JButton("�������");
		jt5.setFont(new Font("������κ",Font.PLAIN,15));
		jt5.addActionListener(new toollistener());
		jtb.add(jt5);
		
		
		Container ct=this.getContentPane();	//���ϵ���ӷ��������ܸ����ȶ�
		jtb.setBounds(0, 0, 900, 30);
		ct.add(jtb);
	}
	
	//����������
	class toollistener implements ActionListener
	{
		@Override
		public void actionPerformed(ActionEvent arg0)
		{
			if(arg0.getSource()==jt3)
			{
				jmi[3].doClick();
			}
			else if(arg0.getSource()==jt4)
			{
				String in="";
				String string=jta1.getText().toString();
				inputStack.clear();//�������ջ
				if(string.equals(""))
				{
					JOptionPane.showMessageDialog(null, "��������Ҫ���������");
				}
				else
				{
					Syn_ana saAna=new Syn_ana(string);
					saAna.addr.clear();
					String error=saAna.ana_input(inputStack);

					if(error==null)
					{
						Parase parase=new Parase(inputStack);
						Parase.addr=saAna.addr;
						jta2.setText(parase.ana_yufa());
						
						SemanticAction.threeAddrCode.outThreeAddrCode();
						System.out.println(SemanticAction.threeAddrCode.currentLabel+":");
					}
					else {
						jta2.setText(error);	//�ʷ��������
						
					}

				}
			}
			else if(arg0.getSource()==jt5)
				{
					String in="";
					String string1=jta1.getText().toString();
					inputStack.clear();//�������ջ
					if(string1.equals(""))
					{
						JOptionPane.showMessageDialog(null, "��������Ҫ���������");
					}
					else
					{
						Syn_ana saAna=new Syn_ana(string1);
						saAna.addr.clear();
						String error=saAna.ana_input(inputStack);

						if(error==null)
						{
							Parase parase=new Parase(inputStack);
							Parase.addr=saAna.addr;
							parase.ana_yufa();
							
							String s=SemanticAction.threeAddrCode.outThreeAddrCode();
							System.out.println(SemanticAction.threeAddrCode.currentLabel+":");
							s=s+SemanticAction.threeAddrCode.currentLabel+":";
							
							jta2.setText(s);
						}
						else {
							jta2.setText(error);	//�ʷ��������
							
						}

					}
			}
		}
		
	}
	
	private void initboard()
	{
		this.setLayout(null);
		jta1=new JTextArea();
		jta1.setFont(new Font("������κ",Font.PLAIN,15));
		jsp=new JScrollPane(jta1);
		jsp.setBounds(10, 30, 875, 300);
		this.add(jsp);
		
		JLabel jlb1=new JLabel("�������:");
		jlb1.setBounds(10, 340, 300, 20);
		jlb1.setFont(new Font("������κ",Font.PLAIN,15));
		this.add(jlb1);
		
		jb1=new JButton("��ա�");
		jb1.setBounds(560, 340, 80, 20);
		jb1.setFont(new Font("������κ",Font.PLAIN,15));
		jb1.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				jta1.setText("");
			}
		});
		this.add(jb1);
		
		jb2=new JButton("��ա�");
		jb2.setBounds(660, 340, 80, 20);
		jb2.setFont(new Font("������κ",Font.PLAIN,15));
		jb2.addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				jta2.setText("");
			}
		});
		this.add(jb2);
		
		jta2=new JTextArea();
		jsp2=new JScrollPane(jta2);
		jta2.setFont(new Font("������κ",Font.PLAIN,15));
		jta2.setForeground(Color.BLACK);
		jta2.setEditable(false);
		jsp2.setBounds(10, 365, 875, 270);
		this.add(jsp2,"South");

	}

	public void initmenu()
	{
		jmb=new JMenuBar();
		jm[0]=new JMenu("�ļ�");
		jm[0].setFont(new Font("������κ",Font.PLAIN,15));
		jmi[0]=new JMenuItem("�½�");
		jmi[0].setFont(new Font("������κ",Font.PLAIN,15));
		jm[0].add(jmi[0]);
		jmi[1]=new JMenuItem("��");
		jmi[1].setFont(new Font("������κ",Font.PLAIN,15));
		jm[0].add(jmi[1]);
		jmi[2]=new JMenuItem("����");
		jmi[2].setFont(new Font("������κ",Font.PLAIN,15));
		jm[0].add(jmi[2]);
		jmi[3]=new JMenuItem("�ʷ�����");
		jmi[3].setFont(new Font("������κ",Font.PLAIN,15));
		jm[0].add(jmi[3]);
		
		jm[1]=new JMenu("�﷨");
		jm[1].setFont(new Font("������κ",Font.PLAIN,15));
		jmi[4]=new JMenuItem("SLR������");
		jmi[4].setFont(new Font("������κ",Font.PLAIN,15));
		jm[1].add(jmi[4]);
		
		jmb.add(jm[0]);
		jmb.add(jm[1]);
		jmi[4].addActionListener(new ActionListener()
		{
			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				Parase aParase=new Parase();
				String s=aParase.printstateform();
				jta2.setText(s);
			}
		});
		
		
		jmi[3].addActionListener(new ActionListener()
		{
			
			@Override
			public void actionPerformed(ActionEvent arg0)
			{
				String string=jta1.getText().toString();
				if(string.equals(""))
				{
					JOptionPane.showMessageDialog(null, "��������Ҫ���������");
				}
				else
				{
					Syn_ana saAna=new Syn_ana(string);
					String s=saAna.analys();
					
					jta2.setText(s);
				}
				
			}
		});
		this.setJMenuBar(jmb);
	}
}
