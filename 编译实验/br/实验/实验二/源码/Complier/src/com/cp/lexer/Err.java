package com.cp.lexer;

public class Err extends Token {

	String errInfo;
	public Err(int t,String errInfo) {
		super(t);
		this.errInfo=errInfo;
	}
	public String toString() {
		return errInfo+"\n";	
	}

}
