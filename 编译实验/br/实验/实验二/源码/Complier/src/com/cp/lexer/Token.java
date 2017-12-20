package com.cp.lexer;

public class Token {
	public final int tag;
	public Token(int t) { 
		System.out.println(t);
		tag = t; }
	public String toString() { return "<" + (char)tag+">"; }
	public String toString(boolean flag){return null;}
	public String getStr(){return null;};
}
