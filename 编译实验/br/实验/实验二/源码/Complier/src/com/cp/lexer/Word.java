package com.cp.lexer;

public class Word extends Token {
	public String lexeme = "";
	public Word(String s,int tag) { super(tag); lexeme = s; }
	public String toString() 
	{ 
		if(tag==Tag.ID)
			return "<id,"+lexeme+">";
		else
			return "<"+lexeme+">";
		}
	public String toString(boolean flag) 
	{ 
		if(tag==Tag.ID)
			return "<id,"+lexeme+">";
		else
			return "<"+tag+" "+lexeme+">";
		}
	@Override
	public String getStr() {
		if(tag==Tag.ID)
			return "id";
		else
			return lexeme;
	}
	public static final Word
		//关系符
		le=new Word("<",Tag.LE),
		colon=new Word(";", Tag.COLON),		
		//加减乘除
		add=new Word("+",Tag.ADD),
	
	
		multiply=new Word("*", Tag.MULTIPLY),
		//赋值
		eval=new Word(":=",Tag.EVAL),
		//左右括号
		lbracke=new Word("(",Tag.LBRACKE),
		rbracke=new Word(")",Tag.RBRACKE),
		//逗号
		comma=new Word(",",Tag.COMMA),
		stop=new Word(".",Tag.STOP);
		;
}	
