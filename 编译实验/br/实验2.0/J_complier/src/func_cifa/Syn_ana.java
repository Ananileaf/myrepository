package func_cifa;

import javax.swing.JOptionPane;

import func_syn.Stack;

public class Syn_ana
{
	
	public static  Stack<String> addr = new Stack<String>();
	
	String prog,token,sum,variable="变量\n";
	char ch;
	int syn,p,m=0,n,row=1,sum2;
	String rwtab[]={"begin","if","then","while","do","end","else"};
	
	public Syn_ana(String string)
	{
		this.prog=string;
		this.m=0;
	}
	
	public static void main(String[]args)
	{
		(new Syn_ana("if (a+b>=95.76) a=3.5- -9.6;")).analys();
		
	}
	
	//扫描分析函数
	public void scaner()
	{
		if(p>=prog.length())
		{
			syn=0;
			return;
		}
		
	    token="";
	    ch=prog.charAt(p++);
	    while(ch==' '||ch=='\t')
	    {
	    	if(p>=prog.length())
			{
				syn=0;
				return;
			}
	        ch=prog.charAt(p);
	        p++;
	    }
	    if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))  //可能是标示符或者变量名 
	    {
	    	ana_word();
	    }
	    else if((ch>='0'&&ch<='9'))  //数字 
	    {
	    	
	    	ana_num(1001,1002);
	    	
	    }
	    else switch(ch)   //其他字符 
	    {
	        case'<':
	        	token="";
				token+=ch;
	            ch=prog.charAt(p++);
	            if(ch=='>')
	            {
	                syn=10021;
	                token+=ch;
	            }
	            else if(ch=='=')
	            {
	                syn=10022;
	                token+=ch;
	            }
	            else
	            {
	                syn=10023;
	                p--;
	            }
	            break;

	        case'>':
				token="";
				token+=ch;
	            ch=prog.charAt(p++);
	            if(ch=='=')
	            {
	                syn=10024;
	                token+=ch;
	            }
	            else
	            {
	                syn=10020;
	                p--;
	            }
	            break;

	        case':':
				token="";
				token+=ch;
	            ch=prog.charAt(p++);
	            if(ch=='=')
	            {
	                syn=10020;
	                token+=ch;
	            }
	            else
	            {
	                syn=10019;
	                p--;
	            }
	            break;
	        case'*':syn=10013;token=ch+"";break;
	        case'/':syn=10014;token=ch+"";break;
	        case'=':syn=10025;token=ch+"";break;
	        case';':syn=10026;token=ch+"";break;
	        case'(':syn=10027;token=ch+"";break;
	        case')':syn=10028;token=ch+"";break;
	        case'\'':syn=10028;token=ch+"";break;
	        case '\n' :syn=-2;  row++; System.out.println(row+"\nsadasd"); break;
	        
	        //字符串识别
	        case'"':
	        	boolean error=false;
	        	char s=' ';
	        	if(p<prog.length())
	        	s=prog.charAt(p++);
	        	else 
	        	{
	        		syn=-1;
	        		break;
	        	}
	        	while(s!='"')
	        	{
	        		//换行错误
	        		if(s==10)
	        		{
	        			error=true;
	        			break;
	        		}
	        		
	        		if(s=='\\'&&p<prog.length()&&prog.charAt(p)=='"')
	        		{
	        			token+='"';
	        			p++;
	        		}
	        		else if(s=='\\'&&p<prog.length()&&prog.charAt(p)=='\\')
	        		{
	        			token+='\\';
	        			p++;
	        		}
	        		else if(s=='\\')
	        		{
	        			//单独的\不作处理
	        		}
	        		else {
						token+=s+"";
						if(token.length()>255)	//长度超过要求
						{
							error=true;
							break;
						}
					}
	        		if(p<prog.length())
	        		s=prog.charAt(p++);
	        		else 
		        		break;
	        	}
	        	if(s!='"')
	        		error=true;
	        	syn=10029;
	        	if(error)
	        	syn=-3;
	        	break;
	        
	        
			//加号和减号可能是正负
			case'+':
				{
				char left=' ';
				char right=' ';
				for(int i=p-2;i>=0;i--)//获取符号左边的第一个不为空字符
				{
					if(prog.charAt(i)!=' ')
					{
						left=prog.charAt(i);
						break;
					}
				}

				for(int j=p;j<prog.length();j++)
				{
					if(prog.charAt(j)!=' ')
					{
						right=prog.charAt(j);
						break;
					}
				}

				if((left=='+'||left==' '||left=='-'||left=='*'||left=='/'||left=='>'||left=='<'||left=='=')&&right>='0'&&right<='9')//左边是运算符右边是数字
				{
					token=ch+"";
				
					ch=prog.charAt(p++);
					ana_num(10017, 10018);
				}
				else	
				{
					syn=10015;token=ch+"";
				}
				}
				break;

			case '-':
				{
				char left=' ';
				char right=' ';
				int t1=0;
				int t2=0;
				for(t1=p-2;t1>=0;t1--)//获取符号左边的第一个不为空字符
				{
					if(prog.charAt(t1)!=' ')
					{
						left=prog.charAt(t1);
						break;
					}
				}

				for(t2=p;t2<prog.length();t2++)
				{
					if(prog.charAt(t2)!=' ')
					{
						right=prog.charAt(t2);
						break;
					}
				}
				
				if(t2==p&&right=='-')	//--开头为注释。换行结束
				{
					while(p<prog.length()&&prog.charAt(p++)!=10)
					{
					}
					syn=10030;
					
				}
				
				else if((left==' '||left=='+'||left=='-'||left=='*'||left=='/'||left=='>'||left=='<'||left=='=')&&right>='0'&&right<='9')//左边是运算符-右边是数字
				{
					token=ch+"";
					ch=prog.charAt(p++);
					ana_num(10017, 10018);
					
				}
				else //(p>1&&p<prog.length()&&prog.charAt(p)!='-'&&prog.charAt(p-2)!='-')	
					{
						syn=10016;token=ch+"";
					}
				}
				break;

	        default: syn=-1;break;
	    }
	}

	//分析变量名或者关键字
	public void ana_word()
	{
		 m=0;
	        while((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
	        {
	            token+=ch;
	            if(p>=prog.length())
	    		{
	            	
	            	break;
	    		}
	            else {
	            	ch=prog.charAt(p++);
				}
	        }
	        if(!((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')))
	        	p--;
	        
	        syn=1;
	        for(n=0;n<rwtab.length;n++)  //将识别出来的字符和已定义的标示符作比较， 
	            if(token.equals(rwtab[n]))
	            {
	                syn=n+2;
	                break;
	            }
	}
	
	//取消改行的分析
	public void cancel_ana_row()
	{
		while(p<prog.length()&&prog.charAt(p++)!=10)
		{
			
			System.out.println("asdsada");
		}
		row++;
	}
	
	//分析数字
	public void ana_num(int syn1,int syn2)
	{
		boolean ox=false;
    	char c='a';
    	if(p<prog.length())
    	c=prog.charAt(p);
    	System.out.println("ox:"+c+"");
    	//十六进制检测
    	if(ch=='0'&&(c=='X'||c=='x'))
    	{
    		p+=1;
    		ch=prog.charAt(p++);
    		ox=true;
    	}
System.out.println(ox);
    		sum="";
    		while((ch>='0'&&ch<='9'||ch=='.'||ch>='a'&&ch<='f'||ch>='A'&&ch<='F'))
        	{
    			if(!ox&&(ch>='a'&&ch<='f'||ch>='A'&&ch<='F'))
    				{
System.out.println("asdas");
    					syn=-1;
    					return;
    				}
    			sum+=ch;
    			 if(p>=prog.length())
 	    		{
 	            	break;
 	    		}
 	            else {
 	            	ch=prog.charAt(p++);
 				}
        	}
    		
    		if(!ox&&(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z'))//报错
    		{
				syn=-1;
				return;
			}
    		else 
    			if(ox&&ch>='g'&&ch<='z'||ch>='G'&&ch<='Z')//无法识别报错
    		{
				syn=-1;
				return;
			}
    		else if(!(ch>='0'&&ch<='9'||ch>='a'&&ch<='f'||ch>='A'&&ch<='F'))	//(!(p==prog.length()&&ch>'9'&&ch<'0'))
    		{
    			p--;
    		}
    		
        if(ox)//进制转换
        {
        	sum2=0;
        	int i=sum.length()-1;
        	int j=i;
        	for(;i>=0;i--)
        	{
        		char s=sum.charAt(i);
        		int tempt=0;
        		if(s>='0'&&s<='9')
        		{
        			tempt=Integer.parseInt(s+"");
        			
        		}
        		else if(s>='A'&&s<='F')
        		{
					tempt=s-'A'+10;
				}
        		else if(s>='a'&&s<='f')
        		{
        			tempt=s-'a'+10;
        		}
        		sum2+=tempt*java.lang.Math.pow(16, j-i);
        	}
        	syn=syn2;
        }
        else 
        {
        	syn=syn1;
        	Float ok=0f;
        	try {
        		ok=Float.parseFloat(sum);
			} catch (Exception e) {
				syn=-1;
			}
        	
//        	if(ok>32767)
//        		syn=-1;
        }
	}
	
	public String analys()
	{
		p=0;
	    row=1;
	    String result="";
	    do
	    {
	        scaner();
	        switch(syn)
	        {
	        case 1001: result+="<"+"num"+","+sum+">"+"\n";  break;  //十进制
	        case 1002: result+="<"+"num"+","+sum2+">"+"\n";  break;	//十六进制
	        case -1: result+=("Error in row "+row+"!"+"\n"); cancel_ana_row(); break;	 //报错，并取消改行的分析	
	        case -2: row=row++;break;
	        case -3: result+=("Error in row "+row+"!"+"\n"); row=row++; break;
			case 10017: result+=("<"+"num"+","+token+sum+">"+"\n");  break; //负的十进制
			case 10018: result+=("<"+"num"+","+token+sum2+">"+"\n");  break; //负的十六进制
			case 0:break;
			case 1: result+=("<"+"id"+","+token+">"+"\n"); variable+=token+"\n"; break; 
			case 10029: result+="<"+"string"+","+token+">"+"\n"; break;
			case 10030: //result+="<"+"注释"+">"+"\n"; 
			break;
	        default: result+=("<"+token+">"+"\n"); break;
	        }
	    }
	    while (syn!=0);
	    result+="关键字\n"+"begin\n"+"if\n"+"then\n"+"while\n"+"do\n"+"end\n"+"符号表\n<\n"+">\n"+"=\n"+"+\n"+"-\n"+"*\n"+"/\n"
				+"(\n"+")\n"+"\"\n"+"\\\n";
	    result+=variable;
	    System.out.println(result);
		return result;
	}
	
	
	
	public String ana_input(Stack<String> input)//由词法错误时，反回0，和错误报告
	{
		p=0;
	    row=1;
	    String error="";
	    do
	    {
	        scaner();
	        switch(syn)
	        {
	        case 1001: input.push("num"); addr.push(sum); break;  //十进制
	        case 1002:  input.push("num"); addr.push(sum2+""); break;	//十六进制
	        case -1: error=("Error in row "+row+"!"+"\n"); cancel_ana_row(); return error; 	 //报错，并取消改行的分析	
	        case -2: row=row++;break;
	        case -3: error=("Error in row "+row+"!"+"\n"); row=row++; return error;
			case 10017:  input.push("num"); addr.push(token+sum+""); break; //负的十进制
			case 10018:   input.push("num"); addr.push(token+sum2+""); break; //负的十六进制
			case 0:break;
			case 1: if(token.equals("num")) input.push("num"); else input.push("id"); addr.push(token+""); break; 
			case 10029: input.push("string"); addr.push(token+""); break;
			case 10030: //result+="<"+"注释"+">"+"\n"; 
			break;
	        default:  input.push(token); addr.push(token+""); break;
	        }
	    }
	    while (syn!=0);
	    this.addr = addr.inverse();
	    return null;
		
	}
}
