package com.cp.lexer;

public class Warning extends Token {

	int tag;
	String warning;
	public Warning(int t,String warnInfo) {
		super(t);
		// TODO Auto-generated constructor stub
		tag=t;
		warning=warnInfo;
	}
	public String toString() {
		return warning+"\n";	
	}

}
