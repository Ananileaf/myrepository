package com.cp.slr;

public class Pair {
	char actionType;//r规则，s状态
	int n;//规则和状态标记
	Pair(char actionType,int n)
	{
		this.actionType = actionType;
		this.n = n;
	}
	
	public String toString()
	{
		if(actionType == 'r')
		{
			return "r"+Integer.toString(n);
		}
		else
			return "s"+Integer.toString(n);
	}
}
