package com.cp.slr;

import java.awt.List;
import java.util.ArrayList;
import java.util.HashSet;

public class ItemCluster {
	public ArrayList<State> state=new ArrayList<State>();
	public ArrayList<Produce> G=new ArrayList<Produce>();
	public HashSet<Produce> set=new HashSet<>();
	
	public int[] core;
	public ItemCluster(int len) {
		core=new int[len];//等于核心的长度
	}
	public ArrayList<Produce> closure(ArrayList<Produce> I)
	{
		
		ArrayList<Produce> J=I;
		boolean flag=true;
		Produce tmp;
		int old;
		do{
			old=J.size();
		for(int i=0;i<J.size();i++)
			{	
				int index=J.get(i).index;
				String B=J.get(i).produce.get(index);
				for(int j=0;j<G.size();j++)
				{
					if(G.get(j).head.equals(B))
					{
						tmp=G.get(j);
						if(!J.contains(tmp))
						{
							Produce add=tmp;
							add.index=0;
							J.add(add);
						}
					}
				}
			}
		}while(J.size()==old);
		return J;
	}
	/*public void items()
	{
		Produce first=new Produce("S'","S" );
		first.index=0;
		ArrayList<Produce> f=new ArrayList<>();
		f.add(first);
		//用队列做
	
		ArrayList<ArrayList<Produce>> C=new ArrayList<>();
		C.add(f);
		int s=0,old;
		do
		{
			old=C.size();
		
			for(int i=0;i<C.size();i++)
			{
				ArrayList<Produce> list=C.get(i);
				for(int j=0;j<list.size();j++)
				{
					
					
				}
			}
		
		}
		while(true);
		
	}
*/

}
