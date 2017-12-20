package threeAddressCode;

import java.util.ArrayList;
import java.util.List;

import func_syn.*;

public class SemanticAction {
	public static ThreeAddressCode threeAddrCode = new ThreeAddressCode();
    /***
     * 根据归约用的产生式序号来选择执行相应的语义动作
     * @param n
     */
	public static void doSemanticAction(int n,Stack<Attribute> attributeStack) 
	{
	//	System.out.println(n);
		switch(n)
		{
		case 1:
			SemanticAction.actionOfProduce1(attributeStack);
			break;
		case 2:
			SemanticAction.actionOfProduce2(attributeStack);
			break;
		case 3:
			SemanticAction.actionOfProduce3(attributeStack);
			break;
		case 4:
			SemanticAction.actionOfProduce4(attributeStack);
			break;
		case 5:
			SemanticAction.actionOfProduce5(attributeStack);
			break;
		case 6:
			SemanticAction.actionOfProduce6(attributeStack);
			break;
		case 7:
			SemanticAction.actionOfProduce7(attributeStack);
			break;
		case 8:
			SemanticAction.actionOfProduce8(attributeStack);
			break;
		case 9:
			SemanticAction.actionOfProduce9(attributeStack);
			break;
		case 10:
			SemanticAction.actionOfProduce10(attributeStack);
			break;
		case 11:
			SemanticAction.actionOfProduce11(attributeStack);
			break;
		case 12:
			SemanticAction.actionOfProduce12(attributeStack);
			break;
		case 13:
			SemanticAction.actionOfProduce13(attributeStack);
			break;
		case 14:
			SemanticAction.actionOfProduce14(attributeStack);
			break;
		case 15:
			SemanticAction.actionOfProduce15(attributeStack);
			break;
		case 16:
			SemanticAction.actionOfProduce16(attributeStack);
			break;
		case 17:
			SemanticAction.actionOfProduce17(attributeStack);
			break;
		case 18:
			SemanticAction.actionOfProduce18(attributeStack);
			break;
		case 19:
			SemanticAction.actionOfProduce19(attributeStack);
			break;
		case 20:
			SemanticAction.actionOfProduce20(attributeStack);
			break;
		default:
			System.out.println("选择语义动作有误！");
			break;
		}
	}
	
	public static void actionOfProduce1(Stack<Attribute> attributeStack)
	{
		Attribute top = attributeStack.getFirst();
			threeAddrCode.backPatch(top.nextList, ThreeAddressCode.currentLabel);
	}
	public static void actionOfProduce2(Stack<Attribute> attributeStack)
	{
		//do nothing
		
	}
	public static void actionOfProduce3(Stack<Attribute> attributeStack)
	{
		Attribute t0 = attributeStack.pop();
		System.out.println("----"+t0+"--"+attributeStack.size());
		
		Attribute top = attributeStack.getFirst();
		System.out.println("----"+top+"--"+attributeStack.size());
		
		threeAddrCode.backPatch(top.nextList, t0.first);
		System.out.println("----"+top+"--"+attributeStack.size());
		
		if(top.first == -1)
			top.first = t0.first;
		top.nextList = t0.nextList;
		System.out.println("asd"+attributeStack.size());
		
	}
	public static void actionOfProduce4(Stack<Attribute> attributeStack)
	{
		attributeStack.push(new Attribute());
	}
	public static void actionOfProduce5(Stack<Attribute> attributeStack)
	{
		Attribute t0,t1,t2,top;
		t0 = attributeStack.pop();
		t1 = attributeStack.pop();
		t2 = attributeStack.pop();
		top = attributeStack.getFirst();
System.out.println("----"+t0+t1+t2+top+"--"+attributeStack.size());
		top.first = t1.first;//ThreeAddressCode.currentLabel;
		top.nextList = t1.nextList;
		
		threeAddrCode.addNewThreeAddrCode(top.addr+"="+t1.addr);
	}
	public static void actionOfProduce6(Stack<Attribute> attributeStack)
	{
		//stmt -> if(bool) stmt
		
		Attribute bool,stmt,top;
		
		stmt = attributeStack.pop();
		attributeStack.pop();
		bool = attributeStack.pop();
		attributeStack.pop();
		top = attributeStack.getFirst();
		
		threeAddrCode.backPatch(bool.trueEntry, stmt.first);
		top.nextList = merge(bool.falseEntry,stmt.nextList);
		top.first = bool.first;
	}
	public static void actionOfProduce7(Stack<Attribute> attributeStack)
	{
		//stmt -> if(bool) stmt1 N else stmt2
		Attribute N,stmt1,stmt2,top,bool;
		stmt2 = attributeStack.pop();
		attributeStack.pop();
		N = attributeStack.pop();
		stmt1 = attributeStack.pop();
		attributeStack.pop();
		bool = attributeStack.pop();
		attributeStack.pop();
		top = attributeStack.getFirst();
System.out.println("----"+N+stmt1+stmt2+top+bool+"--"+attributeStack.size());
		top.first = bool.first;
		threeAddrCode.backPatch(bool.trueEntry, stmt1.first);
		threeAddrCode.backPatch(bool.falseEntry, stmt2.first);
		top.nextList = merge(stmt1.nextList,stmt2.nextList);
		top.nextList = merge(top.nextList,N.nextList);
	}
	public static void actionOfProduce8(Stack<Attribute> attributeStack)
	{
		//stmt ->while (bool) stmt1
		Attribute bool,stmt1,stmt;
		
		stmt1 = attributeStack.pop();
		attributeStack.pop();
		bool = attributeStack.pop();
		attributeStack.pop();
		stmt = attributeStack.getFirst();
		
		threeAddrCode.backPatch(stmt1.nextList, bool.first);
		threeAddrCode.backPatch(bool.trueEntry, stmt1.first);
		
		stmt.nextList = merge(-1,bool.falseEntry);
		//if(stmt.nextList != null)
		//System.out.println("aaaaaaaaaaaaaa+ "+stmt.nextList.get(0));
		threeAddrCode.addNewThreeAddrCode("goto "+bool.first);
		stmt.first  = bool.first;
		
		
	}
	public static void actionOfProduce9(Stack<Attribute> attributeStack)
	{
		//stmt ->begin stmts end;
		Attribute stmt,stmts;
		attributeStack.pop();
		stmts = attributeStack.pop();
		
		stmt = attributeStack.getFirst();
System.out.println("----"+stmt+stmts+"--"+attributeStack.size());
		stmt.first = stmts.first;
		stmt.nextList = stmts.nextList;
	}
	public static void actionOfProduce10(Stack<Attribute> attributeStack)
	{
		//bool->expr1<=expr2;
		Attribute bool,expr1,expr2;
		expr2 = attributeStack.pop();
		attributeStack.pop();
		expr1 = bool = attributeStack.getFirst();
		
		bool.trueEntry = ThreeAddressCode.currentLabel;
		bool.falseEntry = ThreeAddressCode.nextLabel;
		
		threeAddrCode.addNewThreeAddrCode("if "+expr1.addr+"<="+expr2.addr+" goto ");
		threeAddrCode.addNewThreeAddrCode("goto ");
		
	}
	public static void actionOfProduce11(Stack<Attribute> attributeStack)
	{
		//bool->expr1>expr2;
		Attribute bool,expr1,expr2;
		expr2 = attributeStack.pop();
		attributeStack.pop();
		expr1 = bool = attributeStack.getFirst();
		
		bool.trueEntry = ThreeAddressCode.currentLabel;
		bool.falseEntry = ThreeAddressCode.nextLabel;
		
		threeAddrCode.addNewThreeAddrCode("if "+expr1.addr+">"+expr2.addr+" goto ");
		threeAddrCode.addNewThreeAddrCode("goto ");
	}
	public static void actionOfProduce12(Stack<Attribute> attributeStack)
	{
		//expr ->expr1+term;
		Attribute expr,expr1,term;
		term = attributeStack.pop();
		attributeStack.pop();
		expr = expr1 = attributeStack.getFirst();
		
		//expr.nextList = term.nextList;
		String tmp = expr1.addr;
		expr.addr = TempVarGenerator.newTemp();
		threeAddrCode.addNewThreeAddrCode(expr.addr+"="+tmp+"+"+term.addr);
		
	}
	public static void actionOfProduce13(Stack<Attribute> attributeStack)
	{
		//expr ->expr1-term;
		Attribute expr,expr1,term;
		term = attributeStack.pop();
		attributeStack.pop();
		expr = expr1 = attributeStack.getFirst();
				
		//expr.nextList = term.nextList;
		String tmp = expr1.addr;
		expr.addr = TempVarGenerator.newTemp();
		threeAddrCode.addNewThreeAddrCode(expr.addr+"="+tmp+"-"+term.addr);
				
	}
	public static void actionOfProduce14(Stack<Attribute> attributeStack)
	{
		//expr ->term 
		//do nothing
	}
	public static void actionOfProduce15(Stack<Attribute> attributeStack)
	{
		//term->term1*factor;
		Attribute factor,term1,term;
		factor = attributeStack.pop();
		attributeStack.pop();
		term = term1 = attributeStack.getFirst();
System.out.println("----"+factor+term1+term+"--"+attributeStack.size());
		String tmp = term1.addr;
		term.addr = TempVarGenerator.newTemp();
		threeAddrCode.addNewThreeAddrCode(term.addr+"="+tmp+"*"+factor.addr);
	}
	public static void actionOfProduce16(Stack<Attribute> attributeStack)
	{
		//term->term/factor
		Attribute factor,term1,term;
		factor = attributeStack.pop();
		attributeStack.pop();
		term = term1 = attributeStack.getFirst();
		
		String tmp = term1.addr;
		term.addr = TempVarGenerator.newTemp();
		threeAddrCode.addNewThreeAddrCode(term.addr+"="+tmp+"/"+factor.addr);
	
	}
	public static void actionOfProduce17(Stack<Attribute> attributeStack)
	{
		//term->factor
		attributeStack.getFirst().first = ThreeAddressCode.currentLabel;
	}
	public static void actionOfProduce18(Stack<Attribute> attributeStack)
	{
		//factor->id
		attributeStack.getFirst().addr = Parase.currentInputAddr;
	}
	public static void actionOfProduce19(Stack<Attribute> attributeStack)
	{
		//factor->num
		attributeStack.getFirst().addr = Parase.currentInputAddr;
	}
	public static void actionOfProduce20(Stack<Attribute> attributeStack)
	{
		//N->null
		List<Integer> tmp = new ArrayList<Integer>();
		tmp.add(ThreeAddressCode.currentLabel);
		attributeStack.push(new Attribute());
		attributeStack.getFirst().nextList = tmp;
		threeAddrCode.addNewThreeAddrCode("goto ");
		
	}
	private static List<Integer> merge(List<Integer> l1,List<Integer> l2)
	{
		if(l1 == null)
			return l2;
		if(l2 == null)
			return l1;
		
		l1.addAll(l2);
		return l1;
	}
	private static List<Integer> merge(int l1,List<Integer> l2)
	{
	    if(l1 == -1)
	    	return l2;
	    if(l2 == null)
	    	l2 = new ArrayList<Integer>();

		
	    l2.add(l1);
	    return l2;   
	}
	private static List<Integer> merge(List<Integer> l2,int l1)
	{
	    if(l1 == -1)
	    	return l2;
	    if(l2 == null)
	    	l2 = new ArrayList<Integer>();
	
	    l2.add(l1);
	    return l2;
	}
	private static List<Integer> merge(int l1,int l2)
	{
	  if(l1 == -1 && l2 == -1)
		  return null;
      List<Integer> l = new ArrayList<Integer>();
      if(l1 != -1)
    	  l.add(l1);
      if(l2 != -1)
    	  l.add(l2);
      
      return l;
	  
	}
}
