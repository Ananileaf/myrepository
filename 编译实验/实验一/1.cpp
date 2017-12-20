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

bool isspace(char &now)//�ǲ��ǿհ׷� 
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
	if(f) return isletter(ch)|| (ch == '_'); //����ĸf=true 
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

//��� 
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
	else if(now == '{'||now=='}') Print(str,(char*)"�߽�");
	else fail(str,now,i);
	
	return 0;
}



char nextchar()
{
	if(rollback!=eof) //�ǲ�����Ҫ����һ�� 
	{
		char ch = rollback;
		rollback = eof;
		return ch;
	}
	
	//������ 
	if(buf[p] == eof)//eof 
	{
		if(p>=MAXN)//������β��,�������� 
		{
			int i = 0;p = 0;
			while((i<MAXN)&&(~scanf("%c",&buf[i]))) ++i; 
			buf[i] = buf[i+1] = eof;//������β����eof 
		}
		else ; 
	} 
	
	return buf[p++];
}


//������Ϣ 
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

//��ȡ�߼������ 
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

//��ȡ��������� 
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
		else if(now == '/'||now == '*')//ע��/* 
		{
			str[0] = pre;str[1] = now;str[2] = '\0';
			rollback = now;
			//Print(str,(char*)"ע��");
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


//��ȡ���� 
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
	if(flag&&!mistake)//��ȡС�� 
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

//��ȡ�ؼ��ֺͱ�ʶ�� 
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
	if(isspace(ch)) return 0;//���Իس��Ϳո�ָ��� 
	else if(isariop(ch)) return ARIOP; //��ȡ��������� 
	else if(isrelop(ch)) return RELOP; //��ȡ�߼������
	else if(isdigit(ch)) return DIGIT;//��ȡ���ֳ��� 
	else if(isword(ch,true)) return WORD; //��ȡ�ؼ��ֻ��߱�ʶ�� 
	else if(ch=='\'') return CHAR; //��ȡ�ؼ��ֻ��߱�ʶ��  
	else if(ch=='\"') return STRING; //��ȡ�ؼ��ֻ��߱�ʶ�� 
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
			case  0   : state = get_state(now); break;//��ȥ�հ� 
			case RELOP:	state = get_relop(now); break;//��ȡ�߼������ 
			case ARIOP:	state = get_ariop(now); break;//��ȡ��������� 
			case DIGIT:	state = get_digit(now); break;//��ȡ���� 
			case WORD :	state = get_word(now);  break;//��ȡ�ؼ��ֻ��߱�ʶ��
			case CHAR :	state = get_char(now);  break;//��ȡ�����ַ�
			case STRING :state = get_string(now);  break;//��ȡ�ַ��� 
			case zhushi :state = get_zhushi(now);  break;//��ȡ�ַ��� 
			case OTHER:	state = get_other(now);  break;//��ȡ����
			/*case      :						;break;
			case  :						;break;
			case  :						;break;*/
			case eof : return; //eof �˳� 
			
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
	
	//��Դ:https://www.cnblogs.com/jirglt/archive/2012/06/08/2542303.html 
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

