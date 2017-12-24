#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
#define eof -1
#define RELOP 1
#define DIGIT 2
#define ARIOP 3
#define WORD  4
#define OTHER 5
#define STRING 6
#define CHAR 7
#define zhushi 8
int const MAXN = 200;
char buf[MAXN+2];//定义缓冲区大小 
int p = -1;

char rollback;	//存放需要回退一步的字符 
bool mistake = false;//判断当前是否出错,出错则输出错误信息,不输出词法单元 

map<string,bool>KEYWORD;

bool isspace(char &now)//是不是空白符 
{
	return now == '\n' || now == ' ' || now == '\t';
}

bool iskeyword(char *str)//判断是不是关键字 
{
	return KEYWORD[str] == true; 
}


bool isdigit(char ch)	//	判断是不是数字 
{
	return (ch>='0'&&ch<='9');
}


bool isletter(char ch)	//判断是不是字母 
{
	return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z');
}

bool isword(char ch,bool f)	//判断是不是单词,true:首字母 
{
	if(f) return isletter(ch)|| (ch == '_'); //首字母f=true 
	else return isletter(ch) || isdigit(ch) || ch == '_';
}


bool isariop(char ch)	//判断是不是逻辑运算符 
{
	return (ch == '+')||(ch == '-')||(ch == '*')||(ch == '/');
}


bool isrelop(char ch)	//判断是不是算数运算符 
{
	return (ch == '>')||(ch == '<')||(ch == '=');
}
bool isoperator(char ch)//判断是不是运算符 
{
	return isariop(ch) || isrelop(ch);
}


//输出 
void Print(char *str1,char *str2)
{
	if(mistake)
	{
		mistake = false;
		 return;
	}
	
	printf("< %s , %s >\n",str1,str2);
}

//获取下一个字符,模拟缓冲区 
char nextchar()
{
	if(rollback!=eof) //是不是需要回退一次 
	{
		char ch = rollback;
		rollback = eof;
		return ch;
	}
	
	//缓冲区 
	if(buf[p] == eof)//eof 
	{
		if(p>=MAXN)//缓冲区尾部,继续读入 
		{
			int i = 0;p = 0;
			while((i<MAXN)&&(~scanf("%c",&buf[i]))) ++i; 
			buf[i] = buf[i+1] = eof;//缓冲区尾部给eof 
		}
		else ; 
	} 
	
	return buf[p++];
}


//错误信息 
void fail(char *str,char &now,int i)
{
	now = nextchar();
	while(!isspace(now)&&now != eof)
	{
		if(now==')'||now==';'||now=='/')
		{
			rollback = now;
			break;
		}
		 str[i++] = now;
		 now = nextchar();
	}
	printf("error:undefine %s \n",str);
	mistake = true;
}

//获取其他合法符号，如: () 
int get_other(char &now)
{
	char str[200] = "\0";
	int i = 0;
	str[i++] = now;
	if(now == ')'||now=='('||now == ';'||now==','||now=='.') Print(str,(char*)"NULL");
	else if(now == ':')//:=
	{
		char pre = now;
		now = nextchar();
		if(now == '=') Print((char*)":=",(char*)"NULL");
		else rollback=now,Print(str,(char*)"NULL");
	} 
	else if(now=='{')
	{
		rollback=now; 
		return zhushi;
	}
	else fail(str,now,i);
	
	return 0;
}


//获取算数运算符 
int get_ariop(char &pre)
{
	char now = nextchar();
	char str[4] = {"\0"};
	str[0] = pre;
	
	if(pre=='+'||pre=='-')
	{
		Print(str,(char*)"adding-operator");
		
	}
	else if(pre=='*'||pre=='/')
	{
		if(now == '/') return zhushi;
		Print(str,(char*)"multiplying-operator");
	}
	rollback=now;
	return 0;
}


//获取数字 
int get_digit(char &now)
{
	char str[200] = {'\0'};
	int i = 0;
	

		
	bool flag = false;
	str[i++] = now;
	while(true)
	{
		now = nextchar();
		if(isdigit(now)) str[i++] = now;
		else 
		{
			if(now == '.') 
			{
				str[i++] = now;
				flag = true;
				
			}
			else if(isspace(now)||now==';'||now==')'||isoperator(now))
			{
				rollback = now;
			}
			else 
			{
				str[i++] = now;
				fail(str,now,i);
			}
			
			break;
		}
	}
	if(flag&&!mistake)//获取小数 
	{	
		while(true)
		{
			now = nextchar();
			if(isdigit(now)) str[i++] = now;
			else if(isspace(now)||now==';'||now==')'||isoperator(now))
			{
				rollback = now;
				break;
			}
			else 
			{
				str[i++] = now;
				fail(str,now,i);
				break;
			}
		}
	}

	Print(str,(char*)"number");
	
	return 0;
}


//获取逻辑运算符   = | <> | < | > | <= | >=
int get_relop(char &pre)
{
	char now = nextchar();
	char str[4] = {"\0"};
	
	if(pre=='<')
	{
		if(now == '=') strcpy(str,"<=");//"<="
		else if(now == '>') strcpy(str,"<>");//"<>"
		else rollback = now,strcpy(str,"<");//"<", rollback
		
	}
	else if(pre=='=')
	{
		rollback = now,strcpy(str,"=");//"=" , rollback 
	}
	else if(pre=='>')
	{
		if(now=='=') strcpy(str,">=");//">="
		else rollback = now,strcpy(str,">");//">", rollback
	}
	
	Print(str,(char*)"relation");
	return 0;
}

//获取注释 
int get_zhushi(char &now)
{
	now = nextchar();
	char str[200] = {'\0'};
	int i = 0;
	str[i++] = now;
	if(now == '/')// //
	{
		while(now!='\n'&&now!=eof)  now = nextchar();
	}
	else //{ 
	{
		while(now!='}'&&now!=eof)
		{
			now = nextchar();
			str[i++] = now;	
		}
		if(now==eof) 
		{
			fail(str,now,i);
			return eof;
		} 
	}
	
	
	return 0;
}

int get_state(char &ch)
{
	ch = nextchar(); 
	if(isspace(ch)) return 0;//忽略回车和空格分隔符 	  
	else if(isariop(ch)) return ARIOP; //获取算数运算符   
	else if(isrelop(ch)) return RELOP; //获取逻辑运算符
	else if(isdigit(ch)) return DIGIT;//获取数字常数 
	else if(isword(ch,true)) return WORD; //获取关键字或者标识符 
	else if(ch==eof) return eof;
	else return OTHER;
}

//获取关键字和标识符 
int get_word(char &now)
{
	char str[200] = {"\0"};
	int i = 0;
	str[i++] = now;
	now = nextchar();
	while(isword(now,false))
	{
		str[i++] = now;
		now = nextchar();
	}
	
	rollback = now;
	
	if(iskeyword(str)) Print(str,(char*)"keyword");
	else Print(str,(char*)"ident");
	return 0;
}


void solve()
{
	int state = 0;
	char now;
	while(true)
	{
		switch(state)
		{
			case  0   : state = get_state(now); break;//除去空白 		      
			case ARIOP:	state = get_ariop(now); break;//获取算数运算符 	       
			case RELOP:	state = get_relop(now); break;//获取逻辑运算符 		   
			case DIGIT:	state = get_digit(now); break;//获取数字               
			case WORD :	state = get_word(now);  break;//获取关键字或者标识符   
			case zhushi :state = get_zhushi(now);  break;//获取注释 
			case OTHER:	state = get_other(now);  break;//获取其他	
			case eof : return; //eof 退出 
			
		}
	}
}

void init()
{
	p = MAXN;
	buf[p] = eof;
	rollback = eof;
	KEYWORD.clear();
	
	//map来存放的关键字 
	KEYWORD["const"] = KEYWORD["var"] = KEYWORD["call"] = KEYWORD["begin"] = KEYWORD["end"] = KEYWORD["if"] = 
	KEYWORD["then"] = KEYWORD["while"] = KEYWORD["do"] = KEYWORD["odd"] = KEYWORD["procedure"] = KEYWORD["to"] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = true;
	 
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	init();
	solve();
	return 0;
}

