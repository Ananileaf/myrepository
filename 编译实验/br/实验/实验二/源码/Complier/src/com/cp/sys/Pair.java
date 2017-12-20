package com.cp.sys;

public class Pair {
	char actionType;//action类型。r为规约，s为移入
	int n;
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
