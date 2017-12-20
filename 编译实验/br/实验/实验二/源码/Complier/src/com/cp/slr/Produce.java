package com.cp.slr;

import java.util.ArrayList;

import javax.swing.plaf.SliderUI;

/**
 * 
 * @author qdl
 * 表达式
 *
 */
public class Produce {
	public String head;
	public ArrayList<String> produce=new ArrayList<String>();//分割字符
	public int index;//点的索引
	public Produce(String head,String pro,int index)
	{
		this.head = head;
		String[] tmp=pro.split(" ");
		for(int i=0;i<tmp.length;i++)
		{
			produce.add(tmp[i]);	
			
		}
		this.index=index;
	}
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		if(this.head.equals(((Produce)obj).head)&&this.produce.equals(((Produce)obj).produce))
		return true;
		else 
			return false;
	}
}
