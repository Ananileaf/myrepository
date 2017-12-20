package func_syn;

import java.io.FileWriter;
import java.io.IOException;
import threeAddressCode.Attribute;
import threeAddressCode.SemanticAction;

public class Parase
{
	String input;
	
	public static Stack<String> addr = new Stack<String>();
	public static String currentInputAddr = "";
	Stack<Attribute> attributeStack = new Stack<Attribute>();
	
	String result="";
	Stack<String> inputStack;
	Stack<Integer>stateStack=new Stack<Integer>();
	Stack<String>symbolStack=new Stack<String>();
	ItemSetCluster itemSet = new ItemSetCluster();//状态表创建
	/**存产生式**/
	Produce[] produce = new Produce[21];
	
	/**存入产生式**/
	private void setProduce()
	{
		produce[1] = new Produce("S","program");
		produce[2] = new Produce("program","stmts");
		produce[3] = new Produce("stmts","stmtsstmt");
		produce[4] = new Produce("stmts","ε");
		produce[5] = new Produce("stmt","id:=expr;");
		produce[6] = new Produce("stmt","if(bool)stmt");
		produce[7] = new Produce("stmt","if(bool)stmtNelsestmt");
		produce[8] = new Produce("stmt","while(bool)stmt");
		produce[9] = new Produce("stmt","beginstmtsend");
		produce[10] = new Produce("bool","expr<=expr");
		produce[11] = new Produce("bool","expr>expr");
		produce[12] = new Produce("expr","expr+expr");
		produce[13] = new Produce("expr","expr-expr");
		produce[14] = new Produce("expr","term");
		produce[15] = new Produce("term","term*factor");
		produce[16] = new Produce("term","term/factor");
		produce[17] = new Produce("term","factor");
		produce[18] = new Produce("factor","id");

		produce[19] = new Produce("factor","num");
		produce[20] = new Produce("N","ε");
	}
	
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
	
	
	public String printstateform()
	{
		String res="state\t id\t num\t if\t else\t while\t begin\t end\t "
				+ ":=\t <=\t >\t +\t -\t *\t /\t ;\t (\t )\t $\t "
				+ "program\t stmts\t stmt\t expr\t bool\t term\t factor\t"
				+ "\r\n";
		ItemSetCluster itemSet = new ItemSetCluster();
		State tmp[] = itemSet.state;
		
		String[] terminal={"id","num","if","else","while","begin","end",
				":=","<=",">","+","-","*","/",";","(",")","$"};
		String[] nonTerminal={"program","stmts","stmt","expr",
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
	
	
	public String ana_yufa()
	{
		String currentinput;
		Integer currentstate;
		result="";
		while(inputStack.size()!=0)
		{
			currentinput=inputStack.getLast();
			currentstate=stateStack.getFirst();
			
			outStateStack(this.stateStack.inverse());
			outSymbolStack(this.symbolStack.inverse());
			outInput(this.inputStack.inverse());
			
			Pair act=itemSet.state[currentstate].act.action.get(currentinput);//根据状态表获取当前状态与输入对应的操作
			 if(act==null)
			 {
				 System.out.print("error");
				 result+="→error near 【"+currentinput+"】←";
				 return result;
			 }
			 if(act.actionType=='r')//归约
			 {
				 /*act.n==1代表用第一张规则归约，即结束**/
					if(act.n == 1)
					{
						System.out.println("【归约：program'->program】");
						System.out.println("【0】\t【$ S】\t【$】 \t【acc】");
						result+="【归约：program'->program】\n";
						result+="【0】\t【$ program'】\t【$】 \t【acc】\n";
						updateAttributeStackAfterReduction(1,1);
						break ;
					}
					reduction(act.n);
			 }
			 else if(act.actionType=='s')//状态跳转
			 {
				 shift(act.n);
				 currentInputAddr = addr.pop();
				 updateAttributeStackAfterShift(currentInputAddr);
			 }
		}
		return result;
	}
	private void shift(int n)
	{
		/**执行移入操作，将状态移入状态栈**/
		stateStack.push(n);
		
		System.out.println("【shift to state "+n+"】");
		result+="【shift to state "+n+"】\n";
		
		/**从输入中取出下一个终结符移入符号栈中，输入串也作相应修改**/
		String testUnit = inputStack.getLast();
		inputStack.removeLast();
		//System.out.println(testUnit);
		symbolStack.push(testUnit);
		
	}
	private void updateAttributeStackAfterShift(String testUnit)
	{
		Attribute a = new Attribute();
		a.addr = this.currentInputAddr;
		attributeStack.push(a);
		
	}
	private void reduction(int n)
	{
		System.out.println("【归约："+produce[n].head+"->"+produce[n].produce+"】");
		result+="【归约："+produce[n].head+"->"+produce[n].produce+"】\n";
		
		String produce,head;
		head = this.produce[n].head;
		produce = this.produce[n].produce;
		
		/**count是符号栈弹出的符号数目**/
		int count = changeSymbolStack(head,produce);
		
		updateAttributeStackAfterReduction(count,n);
		
		changeStateStack(head,count);
		
	}
	private void updateAttributeStackAfterReduction(int count,int n)
	{
		SemanticAction.doSemanticAction(n,attributeStack);
	}
	private void changeStateStack(String head,int count)
	{
System.out.print(count+" ");
		for(int i=0;i<count;i++)
			stateStack.pop();
System.out.print(stateStack.size());		
		int currentState = stateStack.getFirst();
	
		if(null != itemSet.state[currentState].go_to._goto.get(head))
		{
			int newState = itemSet.state[currentState].go_to._goto.get(head);
			stateStack.push(newState);
		}
		else
		{
			System.out.println("归约错误");
		}
		
		
		
	}
	private int changeSymbolStack(String head,String produce)
	{
		/**例如A->ε
		 * 则此时直接将产生式头部移入符号栈中
		 * **/
		if(produce.equals("ε"))
		{
			this.symbolStack.push(head);
			
			return 0;
		//	System.out.print("getfirst: "+symbolStack.getFirst());
			
		}
		else
		{
			int count = 0;
			int produceLength = produce.length();
			int len = 0;
			while(len < produceLength)
			{
				len += symbolStack.getFirst().length();
				System.out.print(len+" **");
				count ++;
				if(len <= produceLength)
				{
					symbolStack.pop();
				}
			}
		//	System.out.print(symbolStack.size());
			/**存入符号栈，如果产生式有空格则要分割开***/
			symbolStack.push(head);
			return count;
		}
	}
	private void outStateStack(Stack<Integer> s)
	{
		System.out.print("【");
		result+="【";
		while(!s.isEmpty())
		{
			int tmp = s.pop();
			System.out.print(tmp+" ");
			result+=tmp+" ";
		}
				
		System.out.print("】\t");
		result+="】\t";
	}
	private void outSymbolStack(Stack<String> s)
	{
		System.out.print("【");
		result+="【";
		while(!s.isEmpty())
		{
			String tmp = s.pop();
			System.out.print(tmp+" ");
			result+=tmp+" ";
		}
		System.out.print("】\t");
		result+="】\t";

	}
	private void outInput(Stack<String> input)
	{
		result+="【";
		System.out.print("【");
		while(!input.isEmpty())
		{
			String tmp = input.pop();
			System.out.print(tmp+"");
			result+=tmp+"";
		}
		System.out.print("】\t");
		result+="】\t";
	}
	
}
