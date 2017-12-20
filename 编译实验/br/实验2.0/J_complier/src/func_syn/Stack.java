package func_syn;

import java.util.LinkedList;

public class Stack<T> {
	
	LinkedList<T> stack = new LinkedList<T>();
	public int size()
	{
		return stack.size();
	}
	public boolean isEmpty()
	{
		return stack.size() == 0;
	}
	public T pop()
	{
		if(isEmpty())
			return null;
		T ele = stack.removeFirst();
		return ele;
	}
	public void push(T ele)
	{
	 	stack.addFirst(ele);
	}
	public T getFirst()
	{
		T t=null;

		t=stack.getFirst();
//		System.out.println(t+"--"+stack.size());
		return t;
	}
	public Stack<T> inverse()
	{
		Stack<T> inverseThis = new Stack<T>();
		for(int i = 0;i<this.stack.size();i++)
		{
			inverseThis.push(this.stack.get(i));
		}
		
		return inverseThis;
	}
	public void outStack()
	{
		System.out.print("stack content:   ");
		while(!this.isEmpty())
		{
			System.out.print(this.pop()+" ");
		}
		System.out.println();
	}
	public void clear()
	{
		stack.clear();
	}
	public T getLast()
	{
		return stack.getLast();
	}
	public void removeLast()
	{
		stack.removeLast();
	}
}
