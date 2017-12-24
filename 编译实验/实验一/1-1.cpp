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
char buf[MAXN+2];//���建������С 
int p = -1;

char rollback;	//�����Ҫ����һ�����ַ� 
bool mistake = false;//�жϵ�ǰ�Ƿ����,���������������Ϣ,������ʷ���Ԫ 

map<string,bool>KEYWORD;

bool isspace(char &now)//�ǲ��ǿհ׷� 
{
	return now == '\n' || now == ' ' || now == '\t';
}

bool iskeyword(char *str)//�ж��ǲ��ǹؼ��� 
{
	return KEYWORD[str] == true; 
}


bool isdigit(char ch)	//	�ж��ǲ������� 
{
	return (ch>='0'&&ch<='9');
}


bool isletter(char ch)	//�ж��ǲ�����ĸ 
{
	return (ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z');
}

bool isword(char ch,bool f)	//�ж��ǲ��ǵ���,true:����ĸ 
{
	if(f) return isletter(ch)|| (ch == '_'); //����ĸf=true 
	else return isletter(ch) || isdigit(ch) || ch == '_';
}


bool isariop(char ch)	//�ж��ǲ����߼������ 
{
	return (ch == '+')||(ch == '-')||(ch == '*')||(ch == '/');
}


bool isrelop(char ch)	//�ж��ǲ������������ 
{
	return (ch == '>')||(ch == '<')||(ch == '=');
}
bool isoperator(char ch)//�ж��ǲ�������� 
{
	return isariop(ch) || isrelop(ch);
}


//��� 
void Print(char *str1,char *str2)
{
	if(mistake)
	{
		mistake = false;
		 return;
	}
	
	printf("< %s , %s >\n",str1,str2);
}

//��ȡ��һ���ַ�,ģ�⻺���� 
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

//��ȡ�����Ϸ����ţ���: () 
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


//��ȡ��������� 
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
	if(flag&&!mistake)//��ȡС�� 
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


//��ȡ�߼������   = | <> | < | > | <= | >=
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

//��ȡע�� 
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
	if(isspace(ch)) return 0;//���Իس��Ϳո�ָ��� 	  
	else if(isariop(ch)) return ARIOP; //��ȡ���������   
	else if(isrelop(ch)) return RELOP; //��ȡ�߼������
	else if(isdigit(ch)) return DIGIT;//��ȡ���ֳ��� 
	else if(isword(ch,true)) return WORD; //��ȡ�ؼ��ֻ��߱�ʶ�� 
	else if(ch==eof) return eof;
	else return OTHER;
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
			case  0   : state = get_state(now); break;//��ȥ�հ� 		      
			case ARIOP:	state = get_ariop(now); break;//��ȡ��������� 	       
			case RELOP:	state = get_relop(now); break;//��ȡ�߼������ 		   
			case DIGIT:	state = get_digit(now); break;//��ȡ����               
			case WORD :	state = get_word(now);  break;//��ȡ�ؼ��ֻ��߱�ʶ��   
			case zhushi :state = get_zhushi(now);  break;//��ȡע�� 
			case OTHER:	state = get_other(now);  break;//��ȡ����	
			case eof : return; //eof �˳� 
			
		}
	}
}

void init()
{
	p = MAXN;
	buf[p] = eof;
	rollback = eof;
	KEYWORD.clear();
	
	//map����ŵĹؼ��� 
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

