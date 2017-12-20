package com.cp.sys;

public class State {
	int stateNumber;
	Goto go_to = new Goto();
	Action act = new Action();
	public State(int num)
	{
		this.stateNumber = num;
	}
}
