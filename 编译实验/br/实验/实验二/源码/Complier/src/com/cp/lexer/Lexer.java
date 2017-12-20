package com.cp.lexer;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Hashtable;

import com.cp.sys.Stack;

public class Lexer {
	public static int line = 1;
	char peek = ' ';
	char[] tmp=new char[1];
	public Hashtable words = new Hashtable();
	public ArrayList<Token> arr=new ArrayList<Token>();
	public char[] in=null;
	public int next=0;
	boolean flag;
	public String result="输出：\n";
	public String err="错误：\n";
	public String warning="警告：\n";
	public ArrayList<Err> errList=new ArrayList<Err>();
	public ArrayList<Warning> warnList=new ArrayList<Warning>();
	void reserve(Word w) { words.put(w.lexeme, w); }
	public Stack<String> input=new Stack<>();
	public Lexer(String in) {
		/**
		 * 将关键字存入hash表
		 */
		reserve( new Word("program",    Tag.PROGRAM)    );
		arr.add(new  Word("do",   Tag.PROGRAM) );
		reserve(new  Word("end",   Tag.END)   );
		arr.add(new  Word("end",   Tag.END) );
		reserve(new  Word("begin", Tag.BEGIN) );
		arr.add(new  Word("begin",   Tag.BEGIN) );
		reserve( new Word("if",    Tag.IF)    );
		arr.add(new  Word("if",   Tag.IF) );
		reserve( new Word("then",  Tag.THEN)  );
		arr.add(new  Word("then",   Tag.THEN) );
		reserve( new Word("while", Tag.WHILE) );
		arr.add(new  Word("while",   Tag.WHILE) );
		reserve( new Word("do",    Tag.DO)    );
		arr.add(new  Word("do",   Tag.DO) );
		reserve( new Word("else",    Tag.ELSE)    );
		arr.add(new  Word("else",   Tag.ELSE) );
		this.in=in.toCharArray();
		flag=true;
	}
	/**
	 * 
	 * @throws IOException
	 * 读取一个字符
	 */
	void readch() throws IOException {
		if(next>in.length-1)
			{
			//System.out.println(in.length);
			flag=false;
			//System.out.println(flag+"f");
			}
		else
		{
			peek =Character.toLowerCase(in[next]);
		//	System.out.println(peek);
			next++;
		}
	}
	boolean readch(char c) throws IOException {
		readch();
		if( peek != c ) return false;
		peek = ' ';
		return true;
	}
	public void scanner() throws IOException
	{
		Token tmp;
		while(flag)
		{

			if((tmp=scan())!=null&&tmp.tag!=10)
				{
				result+=tmp.toString()+"\n";
				if(tmp.getStr()!=null)
				{input.push(tmp.getStr());
				System.out.println("栈输出："+tmp.getStr());
				}
				}
				//System.out.println(result);					
		}
		for(int i=0;i<errList.size();i++)
			err+=errList.get(i);
		for(int i=0;i<warnList.size();i++)
			warning+=warnList.get(i);
		
	}
	public Token scan() throws IOException {
		
		for(;;readch())
		{
			/**
			 *处理空格和换行
			 */
	
			if(next==in.length)
			{
				flag=false;break;
			}
			if( peek == ' ' || peek == '\t' ) continue;
			else if( peek == '\n' ) line = line + 1;
			else break;
		}
		/**
		 * 关系符和运算符
		 */
		switch( peek ) {
		case '<':
			readch();
			return Word.le;
		case ':':
			if(readch('=')) return Word.eval;
			else return null;//返回错误
		case '(':
			readch();
			return Word.lbracke;
		case ')':
			readch();
			return Word.rbracke;
		case '+':
			readch();
			return Word.add;
		case '*':
			readch();
			return Word.multiply;
		case ',':
			readch();
			return Word.comma;
		case '.':
			readch();
			return Word.stop;
		case ';':
			readch();
			return Word.colon;
		default:break;		
		}
		/**
		 * 整数
		 */
		if( Character.isDigit(peek) ) {
			int v = 0;
			int tmp=0;
			do {
				v = 10 * v + Character.digit(peek, 10);
				if(v>Num.MAX_INT)
				{

					do readch();
					while(peek!='\n');
					errList.add(new Err(Tag.ERROR,"错误行数:"+line+"  错误类型：整数越界"));
					return null;
				}
				readch();
			} while( Character.isDigit(peek) );
			
			/**
			 *判断三十六进制
			 */
			if(peek=='x'&&v==0)
			{	
				readch();
				do
				{
					if(Character.isDigit(peek))
						tmp=Character.digit(peek,10);
					else 
						tmp=(int)peek-87;
					//System.out.println(tmp);
					v=36*v+tmp;
					if(v>Num.MAX_INT)
					{
						do readch();
						while(peek!='\n');
						errList.add( new Err(Tag.ERROR,"错误行数:"+line+"  错误类型：整数越界"));
						return null;
					}
					readch();
				}while(Character.isLetterOrDigit(peek));
			}
			else if(peek=='.')
				{float x = v; float d = 10;
			   for( ; ; ) {
				readch();
				if( !Character.isDigit(peek) ) break;
				x = x + Character.digit(peek, 10) / d; d = d * 10;
			  }
			  return new Real(x);
				}
			return new Num(v);

			/*
			if( peek != '.' ) return new Num(v);
			float x = v; float d = 10;
			for( ; ; ) {
				readch();
				if( !Character.isDigit(peek) ) break;
				x = x + Character.digit(peek, 10) / d; d = d * 10;
			}
			return new Real(x);*/
		}
		/**
		 * 标识符
		 */
		if( Character.isLetter(peek)) {
			StringBuffer b = new StringBuffer();
			do {
				b.append(peek); readch();
				//包括下划线
			} while( Character.isLetterOrDigit(peek)||peek=='_');
			String s = b.toString();

			if(s.length()>32)
			{
				errList.add( new Err(Tag.ERROR,"错误行数:"+line+"  错误类型：标识符长度超过32"));
				return null;
			}
			else if(s.length()>8)
			{	
				warnList.add(new Warning(Tag.WARNING,"警告行数:"+line+"  警告类型：标识符超过8"));
				s=s.substring(0, 7);
				//warning
			}				
			/**
			 * 是否是保留字
			 */
			Word w = (Word)words.get(s);
			
			if( w != null ) return w;			
			w = new Word(s, Tag.ID);
			/**
			 * 放入符号表中
			 */
			words.put(s, w);
			arr.add(w);
			return w;
		}
		Token tok = new Token(peek);
		readch();
		return tok;
	}
}
