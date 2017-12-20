package com.cp.sys;

public class Parase
{
	String input;
	String result="";
	Stack<String> inputStack=new Stack<String>();
	Stack<Integer>stateStack=new Stack<Integer>();
	Stack<String>symbolStack=new Stack<String>();
	ItemSetCluster itemSet = new ItemSetCluster();

	Produce[] produce = new Produce[21];
	

	private void setProduce()
	{
		
		produce[1] = new Produce("S","programid(id_lists);compound_stmt.");
		produce[2] = new Produce("id_lists","id");
		produce[3] = new Produce("id_lists","id_lists,id");
		produce[4] = new Produce("compound_stmt","beginoptional_stmtsend");
		produce[5] = new Produce("optional_stmts","stmts");
		produce[6] = new Produce("stmts","stmt");
		produce[7] = new Produce("stmts","stmts;stmt");
		produce[8] = new Produce("optional_stmts","ε");
		produce[9] = new Produce("stmt","compound_stmt");
		produce[10] = new Produce("stmt","id:=expr");
		produce[11] = new Produce("stmt","ifboolthenstmt");
		produce[12] = new Produce("stmt","ifboolthenstmtelsestmt");
		produce[13] = new Produce("stmt","whilebooldostmt");
		produce[14] = new Produce("bool","expr<expr");
		produce[15] = new Produce("expr","expr+term");
		produce[16] = new Produce("expr","term");
		produce[17] = new Produce("term","term*factor");
		produce[18] = new Produce("term","factor");
		produce[19] = new Produce("factor","id");
		produce[20] = new Produce("factor","num");	
	}
	
	/**
	 * 
	 * @param in
	 * 初始化语法分析器
	 */
	public Parase(Stack<String> in)
	{
		setProduce();
		this.inputStack=in;
		stateStack.push(0);
		symbolStack.push("$");
		inputStack.push("$");
	}
	
	public Parase()
	{}
	
	/**
	 * 
	 * @return
	 * 打印状态表
	 */
	public String printstateform()
	{
		//打印状态表
		String res="state\tprogram\t id\t num\t if\t else\t while\t begin\t end\t.\t "
				+ ":=\t <\t +\t  *\t  ;\t (\t )\t $\t "
				+ "id_lists\t compound_stmt\t optional_stmts\t stmts\t stmt\t expr\t bool\t term\t factor\t"
				+ "\r\n";
		ItemSetCluster itemSet = new ItemSetCluster();
		State tmp[] = itemSet.state;
		
		String[] terminal={"program","id","num","if","else","while","begin","end",".",
				":=","<","+","*",";","(",")","$"};
		String[] nonTerminal={"id_lists","compound_stmt","optional_stmts","stmts","stmt","expr",
				"bool","term","factor"};
		
		for(int i = 0;i<tmp.length;i++)
		{
			res+=tmp[i].stateNumber+"\t";
			
			for(int j = 0;j<terminal.length;j++)
			{
				if(tmp[i].act.action.get(terminal[j]) == null)
				{
					res+="\t";
				}
				else
					res+=tmp[i].act.action.get(terminal[j]).toString()+"\t";
			}
			for(int j = 0;j<nonTerminal.length;j++)
			{
				if(tmp[i].go_to._goto.get(nonTerminal[j]) == null)
				{
					res+="\t";
				}
				else
					res+=tmp[i].go_to._goto.get(nonTerminal[j])+"\t";
			}	
			res+="\n";
		}
		
		return res;
	}
	
	
	public String syntax_any()
	{
		String currentinput;//当前输入
		Integer currentstate;//当前状态
		result="";//结果
		//输入栈压入$
		while(inputStack.size()!=0)
		{
			currentinput=inputStack.getLast();
			currentstate=stateStack.getFirst();
			System.out.println("当前输入: "+currentinput);
			System.out.println("当前状态:"+currentstate);
			 result+="当前输入: "+currentinput+"\n";
			 result+="当前状态:"+currentstate+"\n";
			//输出双栈状态
			
			outStateStack(this.stateStack.inverse());
			outSymbolStack(this.symbolStack.inverse());
			outInput(this.inputStack.inverse());
			
			//获取当前操作
			Pair act=itemSet.state[currentstate].act.action.get(currentinput);
			 if(act==null)
			 {//如果无操作，则报错
				
				 System.out.println("出现语法错误\nerror near："+currentinput);
				 result+="出现语法错误\nerror near"+currentinput;
				 return result;
			 }
			 if(act.actionType=='r')//进行规约
			 {
				
					if(act.n == 1)
					{
						//第一个状态 接受状态
						System.out.println("[按照第"+1+"条规则规约:"+produce[1].head+"->"+produce[1].produce+"]");
						result+="[按照第"+1+"条规则规约: "+produce[1].head+"->"+produce[1].produce+"]\n";
						result+="[acc]\n语法分析成功!\n";
						System.out.println("语法分析成功!");
						break ;
					}
					//进行规约，使用第n个规则
					reduction(act.n);
			 }
			 else if(act.actionType=='s')//进行移入
			 {
				 //转移到状态n
				 shift(act.n);
			 }
		}
		return result;
	}
	private void shift(int n)
	{
		//压入状态栈
		stateStack.push(n);
		System.out.println("[转移至状态 ："+n+"]");
		result+="[转移至状态 ："+n+"]\n";
		
		
		
		//获取输入栈最后一个并删除
		String tmp = inputStack.getLast();
		inputStack.removeLast();
		//System.out.println(testUnit);
		//压入符号栈
		symbolStack.push(tmp);
		
	}

	private void reduction(int n)
	{
		System.out.println("[按照第"+n+"条规则规约:"+produce[n].head+"->"+produce[n].produce+"]");
		result+="[按照第"+n+"条规则规约: "+produce[n].head+"->"+produce[n].produce+"]\n";
		
		String produce,head;
		head = this.produce[n].head;
		produce = this.produce[n].produce;
		
		
		int count = changeSymbolStack(head,produce);
		//System.out.println("count"+count);
		changeStateStack(head,count);
		
	}

	private void changeStateStack(String head,int count)
	{
 System.out.print(count+" ");
 //符号栈减少个数等于栈减少个数
 	for(int i=0;i<count;i++)
			stateStack.pop();
//System.out.print(stateStack.size());		
		int currentState = stateStack.getFirst();
	
		if(null != itemSet.state[currentState].go_to._goto.get(head))
		{
			int newState = itemSet.state[currentState].go_to._goto.get(head);
			stateStack.push(newState);
		}
		else
		{
			System.out.println("规约错误");
		}
		
		
	
	}
	private int changeSymbolStack(String head,String produce)
	{
		//将规约的后件删除
		if(produce.equals("ε"))
		{
			this.symbolStack.push(head);
			return 0;
		//	System.out.print("getfirst: "+symbolStack.getFirst());
			
		}
		else
		{
			//判断应该删除多少个项
			int count = 0;
			int produceLength = produce.length();
			//System.out.println("len: "+produceLength);
			int len = 0;
			while(len < produceLength)
			{
				len += symbolStack.getFirst().length();
				//System.out.print(len+" **");
				count ++;
				if(len <= produceLength)
				{
					symbolStack.pop();
				}
			}
		//	System.out.print(symbolStack.size());
			//将规约的规则前件加入符号栈
			symbolStack.push(head);
			return count;
		}
	}
	private void outStateStack(Stack<Integer> s)
	{
		
		System.out.print("状态栈：\n[");
		result+="状态栈：\n[";
		while(!s.isEmpty())
		{
			int tmp = s.pop();
			System.out.print(tmp+" ");
			result+=tmp+" ";
		}
				
		System.out.print("]\t\n");
		result+="]\t\n";
	}
	private void outSymbolStack(Stack<String> s)
	{
		System.out.print("符号栈：\n[");
		result+="符号栈：\n[";
		while(!s.isEmpty())
		{
			String tmp = s.pop();
			System.out.print(tmp+" ");
			result+=tmp+" ";
		}
		System.out.print("]\t\n");
		result+="]\t\n";

	}
	private void outInput(Stack<String> input)
	{
		result+="输入栈：\n[";
		System.out.print("输入栈：\n[");
		while(!input.isEmpty())
		{
			String tmp = input.pop();
			System.out.print(tmp+" ");
			result+=tmp+"";
		}
		System.out.print("]\t\n");
		result+="]\t\n";
	}
	public static void main(String[] args) {
		Parase test=new Parase();
		test.inputStack.push("12");
		test.inputStack.push("+");
		test.inputStack.push("13");
		test.setProduce();
		test.syntax_any();
	}
}
/*
  program test(a,b);
  begin
  a:=19;
  end
  
 */
