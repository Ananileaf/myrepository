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
int const MAXN = 5;
char buf[MAXN+2];
int p = -1;

char rollback;
bool mistake = false;

map<string,bool>KEYWORD;

bool isspace(char &now)//是不是空白符 
{
	return now == '\n' || now == ' ' || now == '\t';
}

bool iskeyword(char *str)
{
	return KEYWORD[str] == true; 
}


bool isdigit(char ch)
{
	return (ch>='0'&&ch<='9');
}


bool isletter(char ch)
{
	return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z');
}

bool isword(char ch,bool f)
{
	if(f) return isletter(ch)|| (ch == '_'); //首字母f=true 
	else return isletter(ch) || isdigit(ch) || ch == '_';
}

bool isoperator(char ch)
{
	return (ch == '+')||(ch == '-')||(ch == '*')||(ch == '/') || (ch == '%')
		 ||(ch == '>')||(ch == '<')||(ch == '=')
		 ||(ch == '^') || (ch == '|') || (ch == '&')
		 ||(ch == '!');
		 
}

bool isariop(char ch)
{
	return (ch == '+')||(ch == '-')||(ch == '*')||(ch == '/') || (ch == '%');
}


bool isrelop(char ch)
{
	return (ch == '>')||(ch == '<')||(ch == '=')
		 ||(ch == '^') || (ch == '|') || (ch == '&')
		 ||(ch == '!');
}

//输出 
void Print(char *str1,char *str2)
{
	if(mistake)
	{
		mistake = false;
		 return;
	}
	
	printf("<%s,%s>\n",str1,str2);
}

void fail(char *str,char &now,int i);
int get_other(char &now)
{
	char str[200] = "\0";
	int i = 0;
	str[i++] = now;
	if(now == ')'||now=='('||now == ']' || now == '['||now == ';'||now=='.'||now==','||now==':') Print(str,(char*)"");
	else if(now == '{'||now=='}') Print(str,(char*)"边界");
	else fail(str,now,i);
	
	return 0;
}



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
		 str[i++] = now;
		 now = nextchar();
	}
	printf("error:undefine %s \n",str);
	mistake = true;
}

void fail(char &now)
{
	char str[200] = {"\0"};
	int i = 0;
	str[i++] = now;
	now = nextchar();
	while(!isspace(now)&&now != eof)
	{
		 str[i++] = now;
		 now = nextchar();
	}
	printf("error:undefine %s !\n",str);
	mistake = true;
}

//获取逻辑运算符 
int get_relop(char &pre)
{
	char now = nextchar();
	char str[4] = {"\0"};
	
	if(pre=='<')
	{
		if(now == '=') strcpy(str,"<=");//"<="
		else if(now == '<') strcpy(str,"<<");//"<<"
		else if(now == '>') strcpy(str,"<>");//"<>"
		else rollback = now,strcpy(str,"<");//"<", rollback
		
	}
	else if(pre=='=')
	{
		if(now=='=') strcpy(str,"==");//"=="
		else rollback = now,strcpy(str,"=");//"=" , rollback 
	}
	else if(pre=='>')
	{
		if(now=='=') strcpy(str,">=");//">="
		else if(now == '>') strcpy(str,">>");//">>"
		else rollback = now,strcpy(str,">");//">", rollback
	}
	else if(pre == '|')
	{
		if(now=='|') strcpy(str,"||");//"||"
		else rollback = now,strcpy(str,"|");//"|", rollback
	}
	else if(pre == '^')
	{
		rollback = now,strcpy(str,"^");//"^", rollback
	}
	else if(pre == '&')
	{
		if(now=='&') strcpy(str,"&&");//"&&"
		else rollback = now,strcpy(str,"&");//"&", rollback
	}
	else if(pre == ':')
	{
		if(now==':') strcpy(str,"::");//"&&"
		else rollback = now,strcpy(str,":");//"&", rollback
	}else if(pre == '!')
	{
		if(now=='!') strcpy(str,"!!");//"!!"
		if(now=='=') 
		{
			strcpy(str,"!=");//"!="
			Print(str,(char*)"op");
		}
		else rollback = now,strcpy(str,"!");//"!", rollback
	}
	
	//print
	Print(str,(char*)"relop");
	return 0;
}

//获取算数运算符 
int get_ariop(char &pre)
{
	char now = nextchar();
	char str[4] = {"\0"};
	
	if(pre=='+')
	{
		if(now == '=') strcpy(str,"+=");//"+="
		else if(now == '+') strcpy(str,"++");//"++"
		else rollback = now,strcpy(str,"+");//"+", rollback
	}
	else if(pre=='-')
	{
		if(now=='-') strcpy(str,"--");//"--"
		if(now=='-') strcpy(str,"-=");//"--"
		if(now=='>')
		{
			 strcpy(str,"->");//"->"
			 Print(str,(char*)"relop");
			 return 0;
		}
		else rollback = now,strcpy(str,"-");//"-" , rollback 
	}
	else if(pre=='*')
	{
		if(now=='=') strcpy(str,"*=");//">="
		else if(now == '/')
		{
			strcpy(str,"*/");//"*/"
			int i = 2;
			fail(str,now,i);
			return 0; 
		}
		else rollback = now,strcpy(str,"*");//"*", rollback
	}
	else if(pre=='/')
	{
		if(now=='=') strcpy(str,"/=");//">="
		else if(now == '/'||now == '*')//注释/* 
		{
			str[0] = pre;str[1] = now;str[2] = '\0';
			rollback = now;
			//Print(str,(char*)"注释");
			return zhushi; 
		} 
		else rollback = now,strcpy(str,"/");//"/", rollback
	}else if(pre=='%')
	{
		if(now=='=') strcpy(str,"%=");//"%="
		else rollback = now,strcpy(str,"%");//"%", rollback
	}
	//print
	Print(str,(char*)"op");
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
			else rollback = now;
			
			break;
		}
	}
	if(flag&&!mistake)//获取小数 
	{	
		while(true)
		{
			now = nextchar();
			if(isdigit(now)) str[i++] = now;
			else 
			{
				rollback = now;
				break;
			}
		}
	}
	
	Print(str,(char*)"num");
	
	return 0;
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
	
	if(iskeyword(str)) Print(str,(char*)"key");
	else Print(str,(char*)"id");
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
	else if(ch=='\'') return CHAR; //获取关键字或者标识符  
	else if(ch=='\"') return STRING; //获取关键字或者标识符 
	else if(ch==eof) return eof;
	else return OTHER;
}



int get_char(char &now)
{
	char str[5] = {"\0"};
	int i = 0;
	
	// 'x'
	str[i++] = now;
	now = nextchar();
	str[i++] = now;
	if(now=='\\')
	{
		now = nextchar();
		str[i++] = now;
	}
	now = nextchar();
	str[i++] = now;
	
	
	if(now!='\'') fail(str,now,i);
	else Print(str,(char*)"char");
	
	return 0;
} 
int get_string(char &now)
{
	char str[200] = {"\0"};
	int i = 0;
	
	// 'x'
	str[i++] = now;
	
	now = nextchar();
	while(now!=eof&&now!='"'&&now!='\n') 
	{
		str[i++] = now;
		now = nextchar();
	}
	if(now!='"') fail(str,now,i);
	else 
	{
		str[i++] = now;
		Print(str,(char*)"string");
	}
	return 0;
}

int get_zhushi(char &now)
{
	now = nextchar();
	if(now == '/')// "//"
	{
		now = nextchar();
		while(now!='\n'&&now!=eof)  now = nextchar();
	}
	else
	{
		char str[200] = {"/*"};
		int i = 2;
		while(!(str[i-2]=='*'&&str[i-1]=='/') && now!=eof)
		{
			now = nextchar();
			str[i++] = now;
		}
		if(now == eof) fail(str,now,i);

	}
	
	return 0;
}

void solve()
{
	int state = 0;
	char now,pre = eof;
	while(true)
	{
		switch(state)
		{
			case  0   : state = get_state(now); break;//除去空白 
			case RELOP:	state = get_relop(now); break;//获取逻辑运算符 
			case ARIOP:	state = get_ariop(now); break;//获取算数运算符 
			case DIGIT:	state = get_digit(now); break;//获取数字 
			case WORD :	state = get_word(now);  break;//获取关键字或者标识符
			case CHAR :	state = get_char(now);  break;//获取单个字符
			case STRING :state = get_string(now);  break;//获取字符串 
			case zhushi :state = get_zhushi(now);  break;//获取字符串 
			case OTHER:	state = get_other(now);  break;//获取其他
			/*case      :						;break;
			case  :						;break;
			case  :						;break;*/
			case eof : return; //eof 退出 
			
		}
	//	printf("now = %c\n",now);
		//pre = now;
	}
}

void init()
{
	p = MAXN;
	buf[p] = eof;
	rollback = eof;
	KEYWORD.clear();
	
	//来源:https://www.cnblogs.com/jirglt/archive/2012/06/08/2542303.html 
	KEYWORD["break"] = KEYWORD["case"] = KEYWORD["catch"] = KEYWORD["char"] = KEYWORD["continue"] = KEYWORD["do"] = 
	KEYWORD["double"] = KEYWORD["else"] = KEYWORD["final"] = KEYWORD["finally"] = KEYWORD["float"] = KEYWORD["for"] = 
	KEYWORD["if"] = KEYWORD["import"] = KEYWORD["instanceof"] = KEYWORD["int"] = KEYWORD["class"] = KEYWORD["long"] = 
	KEYWORD["private"] = KEYWORD["protected"] = KEYWORD["public"] = KEYWORD["return"] = KEYWORD["short"] = KEYWORD["static"] = 
	KEYWORD["this"] = KEYWORD["throw"] = KEYWORD["throws"] = KEYWORD["transient"] = KEYWORD["try"] = KEYWORD["void"] = 
	KEYWORD["while"] = KEYWORD["const"] = KEYWORD["package"] = KEYWORD["abstract"] = KEYWORD["swtich"] = KEYWORD[""] = 
	KEYWORD["new"] = KEYWORD["null"] = KEYWORD["true"] = KEYWORD["false"] = KEYWORD["do"] = KEYWORD[""] = 
	KEYWORD["implements"] = KEYWORD["private"] = KEYWORD["Boolean"] = KEYWORD["double"] = KEYWORD[" import "] = KEYWORD[""] = 
	KEYWORD["extends"] = KEYWORD["goto"] = KEYWORD["if"] = KEYWORD["switch"] = KEYWORD[""] = KEYWORD[""] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = true;
	 
}
int main()
{
	freopen("input.txt","r",stdin);
	init();
	solve();

	return 0;
}

