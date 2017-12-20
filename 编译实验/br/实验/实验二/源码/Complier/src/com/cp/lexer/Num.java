package com.cp.lexer;

public class Num extends Token {
	public final int value;
	public final static int MAX_INT=16777216;
	public Num(int v) { super(Tag.NUM); value = v; }
	public String toString() { return "<num," +value+">"; }
	@Override
	public String getStr() {
		// TODO Auto-generated method stub
		return "num";
	}
}
