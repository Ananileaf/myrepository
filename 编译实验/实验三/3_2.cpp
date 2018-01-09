#include<bits/stdc++.h>
#define setI(x) freopen(x".txt","r",stdin);
#define setO(x) freopen(x".txt","w",stdout);
#define endl '\n'

using namespace std;


//文件输入输出 


FILE *fp_input ,*fp_input1 ,*fp_input2 ,*fp_input3;
FILE *fp_output,*fp_output1,*fp_output2,*fp_output3;
FILE *fp_test1 ,*fp_test2  ,*fp_test3;

//work out
FILE *fp_work1,*fp_work2,*fp_work3;

//work2 out
FILE *fp_grammar;
FILE *fp_action_table;
FILE *fp_first;
FILE *fp_project_set;



//----------------------------------------------------------------------------------------------------------------------//
//begin------------------------------------------------------------work1-----------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//


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
char work1_buf[MAXN+2];//定义缓冲区大小 
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
	
	fprintf(fp_work1,"< %s , %s >\n",str1,str2);
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
	if(work1_buf[p] == eof)//eof 
	{
		if(p>=MAXN)//缓冲区尾部,继续读入 
		{
			int i = 0;p = 0;
			while((i<MAXN)&&(~fscanf(fp_input,"%c",&work1_buf[i]))) ++i; 
			work1_buf[i] = work1_buf[i+1] = eof;//缓冲区尾部给eof 
		}
		else ; 
	} 
	
	return work1_buf[p++];
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
	fprintf(fp_work1,"error:undefine %s \n",str);
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

void init_1()
{
	p = MAXN;
	work1_buf[p] = eof;
	rollback = eof;
	KEYWORD.clear();
	
	//map来存放的关键字 
	KEYWORD["const"] = KEYWORD["var"] = KEYWORD["call"] = KEYWORD["begin"] = KEYWORD["end"] = KEYWORD["if"] = 
	KEYWORD["then"] = KEYWORD["while"] = KEYWORD["do"] = KEYWORD["odd"] = KEYWORD["procedure"] = KEYWORD["to"] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = 
	KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = KEYWORD[""] = true;
	 
}

void work1()
{
	fp_input = fopen("input.txt","r+");
	fp_work1 = fopen("work1.txt","w+");
	init_1();
	solve();
	fclose(fp_input);
	fclose(fp_work1);
}


//----------------------------------------------------------------------------------------------------------------------//
//end------------------------------------------------------------work1-------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//


//----------------------------------------------------------------------------------------------------------------------//
//begin------------------------------------------------------------work2-----------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//
#define acc 1
#define error 0
#define mov 2
#define guiyue 3
#define begin1 "program'"
#define begin2 "program"
int const Max_N = 400;
int G[Max_N][Max_N];//文法
int length[Max_N];//文法的长度
int number = 0;//文法的个数 
bool is_end[Max_N];//是否是终结符 
bool empty[Max_N];
 
//文法中出现的 单词到数字的映射 
char String[Max_N][80];//文法
map<string,int>mp;
int mp_cnt = 0; 

//first集合 
bool first[Max_N][Max_N];
int buf[Max_N];	//求first(beta a) 
int buf_size;

//项目集
struct project 
{
	int num;//哪一条规则 
	int now;//在当前规则·的位置 
	int search; //RL(1)的1 
	project(int _num = 0,int _now = 0,int _search = 0):num(_num),now(_now),search(_search){
	}
	bool operator == (project & t) const{
		return (t.num==num)&&(t.now==now)&&(t.search==search); 
	 } 
}items[Max_N][Max_N];
int items_size[Max_N]; 
int items_count;
int trains[Max_N][Max_N];//trains[i][j]表示从Ii到Ij使用了String[trains[i][j]]; 

// 分析表
struct action_table
{
	int op;
	int next;
}action[Max_N][Max_N];//第Ii个的输入为J 
int action_num[Max_N];//对应mp的符号在action表中的顺序 
char action_buf[Max_N][1500];
int action_p[Max_N];//对于buf的位置 



//判断语句的输入 

int read[Max_N];
int read_len = 0;



//栈
stack<int>state;//状态栈 
stack<int>sign;//符号栈  

//输出
char anslysis[Max_N*2][1500]; 
int anslysis_len;
char pp[1500];//tmp 



void get_grammar()//读入文法 
{
	//setI("pascal");
	for(int i = 0; i < Max_N; ++i) is_end[i] = true;
	int now;
	int i = 0;
	while(~fscanf(fp_grammar,"%*s"))
	{
		while(true)
		{
			char str[80] = {'\0'};
			fscanf(fp_grammar,"%s",str);
			
			if(strcmp(str,"ε") == 0) empty[number] = true; 
			if(strcmp(str,"$")==0)
			{
				length[number] = i; 
				i = 0;
				++number;
				break;
			}
			else if(strcmp(str,"→")==0) continue;
			if(!mp[str]) 
			{
				mp[str] = ++mp_cnt;
				strcpy(String[mp_cnt],str);
			}
			now = mp[str];
			
			if(i==0) is_end[now] = false;
			G[number][i++] = now;			
		}
	}
	
	return ;
	
	for(int i = 0; i < number; ++i)
	{
		for(int j = 0; j < length[i]; ++j)
		{
			printf("%s ",String[G[i][j]]);
		}
		printf("\n");
	}
	 
} 

void get_first()
{
	bool flag = true;
	
	while(flag) //只要有更新就一直循环 
	{
		flag = false;
		for(int i = 0 ; i < number; ++i)
		{
			
			int p = G[i][0];
			
			int j = 1;
			for( ; j < length[i]; ++j)
			{
				int q = G[i][j];
				int t = mp["ε"];
				if(is_end[q] == false)//非总结符 
				{
					for(int k = 1; k <= mp_cnt; ++k)
					{
						if(k==t) continue;//不能为ε 
						if(first[q][k] == true && first[p][k] == false)
						{
							first[p][k] = true;
							flag = true;
						}
					}
				}
				else//总结符
				{
					if(first[p][q] == false)
					{
						first[p][q] = true;
						flag = true;
					}
					break; 
				}
				
				if(first[q][t] == false) break;//Xi不含有 ε
			}
			if(j==length[i])
			{
				int t = mp["ε"];
				if(first[p][t] == false)
				{
					
					first[p][t] = true;
					flag = true;
				}
			}
		}
	}
	
	
}


//判断新增加的e_closure 是否有重复 
bool is_in(project tmp,int T)
{
	for(int i = 0; i < items_size[T]; ++i)
		if(items[T][i] == tmp) return true;
	return false;
}

//获取搜索符 
void get_search(project tmp)
{
	bool vis[Max_N] = {false};//去重 
	buf_size = 0;
	
	int t = mp["ε"]; 
	int i = tmp.now+1;
	for(; i < length[tmp.num]; ++i)
	{
		int p = G[tmp.num][i];
		if(is_end[p] == false)//非终结符 
		{
			//p的first集合 
			for(int j = 0; j <= mp_cnt; ++j)
			{
				if(first[p][j]&&j!=t)
				{
					if(!vis[j])
						buf[buf_size++] = j,vis[j] = true;
				}
			}
			if(first[p][t] == false) return;
		}
		else	//终结符 
		{
			if(!vis[p])
				buf[buf_size++] = p,vis[p] = true;
			return ;
		 } 
	}
	
	if(!vis[tmp.search])
		buf[buf_size++] = tmp.search,vis[tmp.search] = true;
}

void e_closure(int T) //求项目集 
{
	bool flag = true;
	while(flag)
	{
		flag = false;
	
		for(int i = 0; i < items_size[T]; ++i)
		{
			int p = G[items[T][i].num][items[T][i].now];//·后面的单词 
			if(is_end[p]) continue;//当前是总结符
			for(int j = 1; j <= mp_cnt; ++j)
			{
				if(G[j][0] == p)
				{
					get_search(items[T][i]);
					for(int k = 0; k < buf_size; ++k)
					{
						project tmp = project(j,1,buf[k]);
						if(is_in(tmp,T) == false) items[T][items_size[T]++] = tmp,flag = true;
					}
				}
			} 
		}
	}
}


int is_in_project(int k)
{
	for(int i = 0; i < k; ++i)
	{
		if(items_size[k] != items_size[i]) continue;
		int sum = 0;
		for(int j = 0; j < items_size[k]; ++j)
		{
			for(int z = 0; z < items_size[k]; ++z)
				sum += (items[i][j] == items[k][z]);
		}
		if(sum==items_size[k]) return i;
	}
	return 0;
}

//构建项目集 
void make_set()
{
	//初始化第一个项目集 
	if(!mp["$"])
	{
		mp["$"] = ++mp_cnt;
		strcpy(String[mp_cnt],"$");
	}
	items[0][0] = project(0,1,mp["$"]);
	items_size[0] = 1;
	e_closure(0); 
	items_count = 1;
	
	
	
	for(int i = 0; i < items_count; ++i)//从第一个项目开始扩展 
	{
		for(int j = 1; j <= mp_cnt; ++j)//暴力每个符号
		{
			if(j==mp["ε"]) continue;
			project tmp[200];
			int tmp_size = 0;	
				
		//	cout << String[j] << endl;
			for(int k = 0; k < items_size[i]; ++k)//第i个项集中的第k个句子 
			{
				int p = items[i][k].num;
				int q = items[i][k].now;
			//	cout << String[G[p][q]] << endl; 
				if(q>=length[p]) continue;//到头了 
				if(G[p][q] == j)
				{
					tmp[tmp_size] = items[i][k];
					++tmp[tmp_size].now;
					tmp_size++;
				} 
			} 
			if(tmp_size)
			{
				for(int k = 0; k < tmp_size; ++k) 
					items[items_count][k] = tmp[k];
				items_size[items_count] = tmp_size;
				
				e_closure(items_count);
				
				int p = is_in_project(items_count); 
				if(p==0)//新的项目集 
				{
					trains[i][items_count] = j; 
					++items_count;
				}
				else//已经存在 
				{
					trains[i][p] = j;
				}
				
			}
		} 
	}
}

//构造分析表 
void get_action()
{
	int t = mp["ε"];
	for(int i = 0; i < items_count; ++i)
	{
		for(int j = 0; j < items_size[i]; ++j)
		{
			int p = items[i][j].num;
			int q = items[i][j].now;
			//到了a -> bcd· 的情况 
			if(q == length[p] || (length[p]==2 && q == 1 &&  G[p][q]== t))
			{
				
				action[i][items[i][j].search].next = items[i][j].num;//归约 
				action[i][items[i][j].search].op = guiyue;//归约 
				
				if(q==length[p] && length[p] == 2 && items[i][j].search == mp["$"] 
					&& G[p][0] == mp[begin1] && G[p][1] == mp[begin2])
				{
					action[i][items[i][j].search].op = acc;//归约 
				}
			}
		}
	}
	for(int i = 0; i <= items_count; ++i)
	{
		for(int j = 0; j <= items_count; ++j)
		{
			if(trains[i][j]!=0)
			{
				action[i][trains[i][j]].next = j;
				action[i][trains[i][j]].op = mov;
			}
		}
	}
}


void work2_read1()
{
//	setI("input");
	char str1[30],str2[30];
	while(~fscanf(fp_input,"%*s"))
	{
		fscanf(fp_input,"%s %*s %s %*s",str1,str2);
		if(mp[str1]) read[read_len++] = mp[str1];
		else 
		{
			read[read_len++] = mp[str2];
		}
	}
	read[read_len++] = mp["$"];
}

void work2_read2()
{
//	setI("input1");
	char str[30];
	while(~fscanf(fp_input1,"%s",str)) 
		read[read_len++] = mp[str];
	read[read_len++] = mp["$"];
}


void Print_first()
{
	for(int i = 1; i <= mp_cnt; ++i)
	{
		if(is_end[i]) continue; 
		fprintf(fp_first,"First(%s) : ",String[i]);
		for(int j = 1; j <= mp_cnt ; ++j)
		{
			if(first[i][j])
			fprintf(fp_first,"%s ",String[j]);
		}
		fprintf(fp_first,"\n");
	 } 
}

void Print_action_table()
{
	//setO("action_table"); 
	int tot = 1; 
	int f[Max_N] = {0};
	int t1 = mp["ε"];
	int t2 = mp[begin1];
	int t3; 
	
	for(int i = 1; i <= mp_cnt;++i)
		if(is_end[i] == true && i!=t1)  f[tot] = i,action_num[i]= tot++;
	t3 = tot-1;
	for(int i = 1; i <= mp_cnt;++i)
		if(is_end[i] == false && i!=t2) f[tot] = i,action_num[i] = tot++;
	
	
	char tmp[1500];
	memset(tmp,' ',sizeof(tmp)); 
	memset(action_buf,' ',sizeof(action_buf));
	tmp[500] = '\0';
	
	for(int i = 0; i < Max_N; ++i) 
	{
		action_buf[i][350] = '\0';
		if(i==0) continue;
		int num = i-1;
		stack<int>s;
		
		while(num||s.empty())
		{
			s.push(num%10+'0');
			num /= 10;
		}
		if(i)action_buf[i][2] = 'I';
		int t = 3;
		while(!s.empty())
		{
			action_buf[i][t++] = s.top();
			s.pop();
		 } 
	}
	
	
	
	char s[20] = "status";
	int l = strlen(s);
	for(int i = 0; i < l; ++i) tmp[i] = s[i];
	
	int now = 8;
	{
		char s[] = "action";
		int l = strlen(s);
		for(int i = now; i < now+l; ++i) tmp[i] = s[i-now];
	
	}
	
	for(int i = 1; i <= tot; ++i)
	{
		int t = f[i];
		action_p[t] = now;
		int l = strlen(String[t]);
		for(int j = 0; j < l; ++j)
			action_buf[0][now++] = String[t][j];
		now += 5;
		if(t3 == i)
		{
			now += 2;
			char s[] = "goto";
			int l = strlen(s);
			for(int i = now; i < now+l; ++i) tmp[i] = s[i-now];
		}
	} 
	
	action_buf[0][now] = '\0'; 
		
	for(int i = 0; i < items_count;++i)
	{
		for(int j = 1; j <= mp_cnt; ++j)
		{
			if(action[i][j].op != error)
			{
				int k = action_p[j];
				
				if(is_end[j] == true)
				{
					if(action[i][j].op == acc) 	
					{
						char s[] = "acc";
						int l = strlen(s);
						for(int z = 0; z < l; ++z)
							action_buf[i+1][k++] = s[z];
					}
					else 
					{
						if(action[i][j].op == guiyue) action_buf[i+1][k++] = 'r';
						else action_buf[i+1][k++] = 's';
						int num = action[i][j].next;
						stack<int>s;
						while(s.empty()||num)
						{
							s.push(num%10+'0');
							num /= 10;
						}
						while(s.empty() == false)
						{
							action_buf[i+1][k++] = s.top();
							s.pop();
						}
						
						
					}
				}
				else
				{
					
					int num = action[i][j].next;
					stack<int>s;
					while(s.empty()||num)
					{
						s.push(num%10+'0');
						num /= 10;
					}
					while(s.empty() == false)
					{
						action_buf[i+1][k++] = s.top();
						s.pop();
					}
				}		
			}
		}
	}
	
	fprintf(fp_action_table,"%s\n",tmp);
	for(int i = 0; i <= items_count; ++i) 
		fprintf(fp_action_table,"%s\n",action_buf[i]);
	
}
void Print_set()
{
	//setO("project_set");

	for(int i = 0; i < items_count; ++i)
	{
		fprintf(fp_project_set,"I%d:\n",i);
		for(int j = 0; j < items_size[i]; ++j)
		{
			int p = items[i][j].num;
			int q = items[i][j].now;
			fprintf(fp_project_set,"%s -> ",String[G[p][0]]);
			for(int k = 1; k < q; ++k) fprintf(fp_project_set,"%s ",String[G[p][k]]);
			fprintf(fp_project_set,"· ");
			for(int k = q; k < length[p]; ++k ) fprintf(fp_project_set,"%s ",String[G[p][k]]);
			fprintf(fp_project_set,"  , %s",String[items[i][j].search]);
			fprintf(fp_project_set,"\n");
		}
		fprintf(fp_project_set,"\n");
	}
}

void Print_state()
{
	memset(pp,' ',sizeof(pp));
	pp[1000] = '\0';
	
	int i = 0;
	stack<int> t1 = state;
	stack<int> t2;
	while(!t1.empty()) t2.push(t1.top()),t1.pop();
	while(!t2.empty()) 
	{
		int num = t2.top();
		stack<int>s;
		s.push(num%10 + '0');
		num/=10;
		while(num)
		{
			s.push( num%10 + '0');
			num/=10;
		}
		while(!s.empty())
		{
			pp[i++] = s.top();
			s.pop();
		} 
		
		t2.pop(),pp[i++] = ' ';
	}
} 

void Print_sign()
{
	stack<int> t1 = sign;
	stack<int> t2;
	int i = 70;
	while(!t1.empty()) t2.push(t1.top()),t1.pop();
	while(!t2.empty()) 
	{
		int t =  t2.top();
		t2.pop();
		int len = strlen(String[t]);
		for(int j = 0; j < len; ++j) pp[i++] = String[t][j];	
		pp[i++] = ' ';
	}
} 

void Print_input(int q)
{
	int i = 350;
	for(;q<read_len; ++q)
	{
		int t = read[q];
		int len = strlen(String[t]);
		for(int j = 0; j < len; ++j) pp[i++] = String[t][j];
		pp[i++] = ' ';
	}
}
void Print_ACTION(int q)
{
	int i = 750;
	
	if(q==-1)
	{
		char s[] = "mov";
		int len = strlen(s);
		for(int j = 0; j < len; ++j) pp[i++] = s[j];
		return ;
	}
	else if(q==-2)
	{	
		char s[] = "acc";
		int len = strlen(s);
		for(int j = 0; j < len; ++j) pp[i++] = s[j];
		return ;
		
	}
	int t = G[q][0];
	int len = strlen(String[t]);
	for(int j = 0; j < len; ++j) pp[i++] = String[t][j];
	char s[] = "→" ;
	pp[i++] = ' ';
	pp[i++] = s[0];
	pp[i++] = s[1];
	pp[i++] = ' ';
	for(int k = 1; k < length[q]; ++k)
	{
		int t = G[q][k];
		int len = strlen(String[t]);
		for(int j = 0; j < len; ++j) pp[i++] = String[t][j];
		pp[i++] = ' ';
	}
}

void Print_anslysis()
{
	fprintf(fp_work2,"%s\n",anslysis[0]);
	for(int i = 1; i < anslysis_len; ++i) 
	{
		char tmp[16] = "(     ";
		{
			int num = i;
			int j = 1;
			stack<int>s;
			s.push(num%10 + '0');
			num/=10;
			while(num)
			{
				s.push( num%10 + '0');
				num/=10;
			}
			while(!s.empty())
			{
				tmp[j++] = s.top();
				s.pop();
			} 
			tmp[j++] = ')';
		}
		fprintf(fp_work2,"%s%s\n",tmp,anslysis[i]);
	}
		
}
void Print_all()
{
	Print_first();
	Print_set();
	Print_action_table();
	Print_anslysis();
}

void cal()
{	
	work2_read1();
	//setO("output");
		
	bool ERROR = false;
	
	state.push(0);
	sign.push(mp["$"]);
	char s[1500] = "       状态栈                                                                符号栈                                                                                                                                                                                                                                                                                   输入串                                                                                                                                                                                                                                                                                                                                                                                                         ACTION ";
	strcpy(anslysis[anslysis_len++],s);
	
	int i = 0;
	bool end = false;
	while(ERROR == false &&end == false)
	{
		int now_state = state.top();//当前是Ii or Si
		int now_input = read[i];//输入 
		
		Print_state();
		Print_sign();
		Print_input(i);
		
		int op = action[now_state][now_input].op;
		int next_state =  action[now_state][now_input].next;
		
		if(op==error)
		{
			char p[] = "error!";
			strcpy(anslysis[anslysis_len++],p);
			ERROR = true;
			continue;
		}
		else if(op == mov)
		{
			state.push(next_state);//状态压栈 
			sign.push(now_input);//移入到输入栈 
			Print_ACTION(-1);
			++i;
		}
		else if(op == acc||guiyue)
		{
			int l = length[next_state]-1;//A->B
			if(empty[next_state] == true) l = 0;
			//弹出l个 状态
			for(int i = 0; i < l; ++i) state.pop(),sign.pop();
			
			int t = state.top();
			int A = G[next_state][0]; 
			//GOTO[t,A] 压栈
			
			int tmp = next_state; 
			
			next_state = action[t][A].next;
			state.push(next_state);
			sign.push(A);
			
			
			if(op==acc)
			{
				end = true;
				Print_ACTION(-2);//输出A->B 
			}	
			else Print_ACTION(tmp);//输出A->B 
			
			
		}
		strcpy(anslysis[anslysis_len++],pp);
	}
	
} 


void work2_open_file()
{
	//文件读入读出
	fp_grammar         = fopen("pascal.txt","r+");
//	fp_grammar         = fopen("test3.txt","r+");
	
	fp_input           = fopen("work1.txt","r+");
	//fp_input1          = fopen("input1.txt","r+");
	//fp_input2          = fopen("input2.txt","r+");
	//fp_input3          = fopen("input3.txt","r+");
	
	fp_action_table    = fopen("action_table.txt","w+");
	fp_first           = fopen("first.txt","w+");
	fp_project_set     = fopen("project_set.txt","w+");
	
	fp_work2           = fopen("work2.txt","w+");
	//fp_output1         = fopen("output1.txt","w+");
	//fp_output2         = fopen("output2.txt","w+");
	//fp_output3         = fopen("output3.txt","w+");
	
	//fp_test1           = fopen("test1.txt","r+");
	//fp_test2           = fopen("test2.txt","r+");
	//fp_test3           = fopen("test3.txt","r+");
}

void work2_close_file()
{
	fclose(fp_grammar);
	
	fclose(fp_input);
//	fclose(fp_input1);
//	fclose(fp_input2);
//	fclose(fp_input3);
	
	fclose(fp_action_table);
	fclose(fp_first);
	fclose(fp_project_set);
	
	fclose(fp_work2);
//	fclose(fp_output1);
//	fclose(fp_output2);
//	fclose(fp_output3);
	
//	fclose(fp_test1);
//	fclose(fp_test2);
//	fclose(fp_test3);
	
}

void work2()
{
	work2_open_file();
	get_grammar();
	get_first(); 
	make_set();
	get_action();
	cal();
	Print_all();
	work2_close_file();
}

//----------------------------------------------------------------------------------------------------------------------//
//end------------------------------------------------------------work2-------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//


//----------------------------------------------------------------------------------------------------------------------//
//begin-----------------------------------------------------------work3-------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//

int addr = 0;

char read_num[Max_N][40];
char read_id[Max_N][40];
int read_op[Max_N];

stack<int>expr;// +-*/
stack<int>oper;
stack<int>term;
stack<int>factor;
stack<int>rela;
stack<int>goto_condition_true;
stack<int>goto_condition_false; 
stack<int>label_condition_true;
stack<int>label_condition_false; 
stack<int>statement_next;
stack<int>begin;

int L[Max_N];
int GOTO_L[Max_N];
int L_len = 0;

char work3_p[Max_N][100];
int p_len = 0;

int put_i = 0;

int Temp()
{
	return ++addr;
}

int newlabel()
{
	return ++L_len;
}

void work3_read()
{

	char str1[30],str2[30];
	while(~fscanf(fp_input,"%*s"))
	{
		fscanf(fp_input,"%s %*s %s %*s",str1,str2);
	//	cout << str1 << ' ' << str2 << endl;
	
		if(str1[0] == '+' || str1[0] == '-' || str1[0] == '*' || str1[0] == '/')
		{
			
			int a = 1;
			
			 read_op[read_len] = mp[str1];
			 cout << read_op[read_len] << endl;
		}
	
		if(mp[str1]) read[read_len++] = mp[str1];
		else 
		{
			if(strcmp(str2,"number") == 0) strcpy(read_num[read_len],str1);
			
			if(strcmp(str2,"ident") == 0) strcpy(read_id[read_len],str1);
			
			if(strcmp)
			read[read_len++] = mp[str2];
		}
	}
	read[read_len++] = mp["$"];
}

void insert_num(char *str,int num)
{
	
	if(num<0)//id
	{
		str--;
		int id = -num;
		int len = strlen(read_id[id]);
		for(int i = 0; i < len; ++i) str[i] = read_id[id][i];
		
		return;
	}
	else if(num>=10000)
	{
		str--;
		num -= 10000;
		int len = strlen(read_num[num]);
		for(int i = 0; i < len; ++i) str[i] = read_num[num][i];
		
		return ;
	}
	
	int j = 0;
	stack<int>s;
	s.push(num%10 + '0');
	num/=10;
	while(num)
	{
		s.push( num%10 + '0');
		num/=10;
	}
	while(!s.empty())
	{
		str[j++] = s.top();
		s.pop();
	} 
}

void work3_trainslate(int state,int k)
{
	char str[100];
	memset(str,' ',sizeof(str));
	str[70] = '\0';
	int op = 10,arg1 = 22,arg2 = 35,result = 50;
	
	
	str[0] = '(';
	{
		int num = put_i;
		int j = 1;
		stack<int>s;
		s.push(num%10 + '0');
		num/=10;
		while(num)
		{
			s.push( num%10 + '0');
			num/=10;
		}
		while(!s.empty())
		{
			str[j++] = s.top();
			s.pop();
		} 
		str[j++] = ')';
	}
	
	
	int id = k, num = k,len;
	if(state == 5 || state == 6) //赋值  id = num
	{
		while(strlen(read_id[id]) == 0)--id;	
		while(strlen(read_num[num]) == 0) --num;
		
		//op
		str[op] = '=';
		
		//arg1
		len = strlen(read_num[num]); 
		for(int i = 0;i<len; ++i) str[i+arg1] = read_num[num][i];
		
		//result
		len = strlen(read_id[id]);
		for(int i = 0;i<len; ++i) str[i+result] = read_id[id][i];
		
		read_id[id][0] = '\0';
		
		strcpy(work3_p[p_len++],str);put_i++;
	} 
	else if(state == 13) // id = expression; 
	{
		while(strlen(read_id[id]) == 0)--id;
		//op
		str[op] = '=';
		
		//arg1	
		int num = expr.top();expr.pop();			
		str[arg1] = 't';
		insert_num(str+arg1+1,num);
		
		//result
		len = strlen(read_id[id]);
		for(int i = 0;i<len; ++i) str[i+result] = read_id[id][i];
		
		
		read_id[id][0] = '\0';
		strcpy(work3_p[p_len++],str);put_i++;
	} 
	else if(state == 31) // expression1 adding-operator term
	{
		int t1 = Temp();
		int t2 = expr.top();expr.pop();
		int o = oper.top();oper.pop();
		int t3 = term.top();term.pop();
				
		str[op] = String[o][0];
		
		//arg1
		str[arg1] = 't';
		insert_num(str+arg1+1,t2);
		
		//arg2
		str[arg2] = 't';
		insert_num(str+arg2+1,t3);
		
		//result
		str[result] = 't';
		insert_num(str+result+1,t1);
	
		expr.push(t1);	
		strcpy(work3_p[p_len++],str);put_i++;
 	}
 	else if(state == 35) //term1 multiplying-operator factor
 	{
 		int t1 = Temp();
		int t2 = term.top();term.pop();
		int o = oper.top();oper.pop();
		int t3 = factor.top();factor.pop();
				
		str[op] = String[o][0];
		
		//arg1
		str[arg1] = 't';
		insert_num(str+arg1+1,t2);
		
		//arg2
		str[arg2] = 't';
		insert_num(str+arg2+1,t3);
		
		//result
		str[result] = 't';
		insert_num(str+result+1,t1);
	
		term.push(t1);	
		strcpy(work3_p[p_len++],str);put_i++;
	}
	else if(state == 29) //expression   =   term 
	{
		int t = term.top();term.pop();
		expr.push(t);
	}
	else if(state == 30)  //expression   =   adding-operator term 
	{
		int t1 = Temp();
		int o = oper.top();oper.pop();
		int t2 = term.top();term.pop();
		
		str[op] = String[o][0];
		
		//arg1
		str[arg1] = 't';
		insert_num(str+arg1+1,t2);
		
		//result 
		str[result] = 't';
		insert_num(str+result+1,t1);
			
		expr.push(t1);
		strcpy(work3_p[p_len++],str);put_i++;
	}
	else if(state == 34)// term.addr = factor.addr
	{
		int t = factor.top();factor.pop();
		term.push(t);
	}
	else if(state == 38)// factor.addr = ident.addr
	{
		while(strlen(read_id[id]) == 0)--id;
		factor.push(-id); 
		
	}
	else if(state == 39)
	{
		while(strlen(read_num[num]) == 0)--num;
		
		factor.push(num+10000);
	}
	else if(state == 40)
	{
		int t = expr.top();expr.pop();
		factor.push(t);
	}
	else if(state == 32 || state == 33 || state == 36 || state == 37) 	//op = +-/*
	{
		int o = k;
		while(read_op[o] == 0) --o;
		oper.push(read_op[o]);
		read_op[o] = 0;
		
	}
	else if(state >=24 && state <= 28) // relation = = <> < > <= >=
	{
		int r = G[state][1];
		rela.push(r);
	}
	else if(state == 21)
	{
		int t1 = expr.top();expr.pop();
		int t2 = expr.top();expr.pop();
		int rel = rela.top();rela.pop();
		
		//op
		str[op] = 'J';
		insert_num(str+op+1,rel);
		
		//arg1
		str[arg1] = 't';
		insert_num(str+arg1+1,t1);
		
		//arg2
		str[arg2] = 't';
		insert_num(str+arg2+1,t2);
		
		//result 
		str[result] = 'L';
		GOTO_L[p_len] = goto_condition_true.top();goto_condition_true.pop();
				
		strcpy(work3_p[p_len++],str);put_i++;

		
		// goto Li
		memset(str,' ',sizeof(str));
		str[70] = '\0';
		str[op] = 'g';
		str[op+1] = '0';
		str[result] = 'L';
		GOTO_L[p_len] = goto_condition_false.top();goto_condition_false.pop();
		
		str[0] = '(';
		{
			int num = put_i;
			int j = 1;
			stack<int>s;
			s.push(num%10 + '0');
			num/=10;
			while(num)
			{
				s.push( num%10 + '0');
				num/=10;
			}
			while(!s.empty())
			{
				str[j++] = s.top();
				s.pop();
			} 
			str[j++] = ')';
		}
		
		strcpy(work3_p[p_len++],str);put_i++;
		
	}
	else if(state == 2)
	{
		
	}
	else if(state == )
	{
		
	}
	else if(state == )
	{
		
	} 
	
}

void work3_mov_trainslate(int state,int k)
{
	if(state==2)
	{
		statement_next.push(newlabel());
	}
	else if(state==16)
	{
		int t = newlabel();
		goto_condition_true,push(t);
		label_condition_true,push(t);
	}
	else if(state==)
	{
		
	}
}

void work3_solve()
{		
	work3_read();

	char str[] = "          op          arg1          arg2          result";
	fprintf(fp_work3,"%s\n",str);
	
		
	bool ERROR = false;
	
	while(!state.empty()) state.pop();
	while(!sign.empty()) sign.pop();
	
	state.push(0);
	sign.push(mp["$"]);
	
	int i = 0;
	bool end = false;
	while(ERROR == false &&end == false)
	{
		int now_state = state.top();//当前是Ii or Si
		int now_input = read[i];//输入 
		
		
		
		int op = action[now_state][now_input].op;
		int next_state =  action[now_state][now_input].next;
		
		if(op==error)
		{
			ERROR = true;
			continue;
		}
		else if(op == mov)
		{
			state.push(next_state);//状态压栈 
			sign.push(now_input);//移入到输入栈 
			++i;
		}
		else if(op == acc||guiyue)
		{
			
			work3_trainslate(next_state,i);//翻译成四元式 
			
			int l = length[next_state]-1;//A->B
			if(empty[next_state] == true) l = 0;
			//弹出l个 状态
			for(int i = 0; i < l; ++i) state.pop(),sign.pop();
			
			int t = state.top();
			int A = G[next_state][0]; 
			//GOTO[t,A] 压栈
			
			int tmp = next_state; 
			
			next_state = action[t][A].next;
			state.push(next_state);
			sign.push(A);
			
			
			if(op==acc) end = true;
			
			
		}
		
	}
	
} 

void work3_Print()
{
	for(int i = 0; i < p_len; ++i) fprintf(fp_work3,"%s\n",work3_p[i]);
}

void work3_open_file()
{
	//文件读入读出
	//fp_grammar         = fopen("pascal.txt","r+");
//	fp_grammar         = fopen("test3.txt","r+");
	
	fp_input           = fopen("work1.txt","r+");
	//fp_input1          = fopen("input1.txt","r+");
	//fp_input2          = fopen("input2.txt","r+");
	//fp_input3          = fopen("input3.txt","r+");
	
	//fp_action_table    = fopen("action_table.txt","w+");
	//fp_first           = fopen("first.txt","w+");
	//fp_project_set     = fopen("project_set.txt","w+");
	
	fp_work3           = fopen("work3.txt","w+");
	//fp_output1         = fopen("output1.txt","w+");
	//fp_output2         = fopen("output2.txt","w+");
	//fp_output3         = fopen("output3.txt","w+");
	
	//fp_test1           = fopen("test1.txt","r+");
	//fp_test2           = fopen("test2.txt","r+");
	//fp_test3           = fopen("test3.txt","r+");
}

void work3_close_file()
{
	//fclose(fp_grammar);
	
	fclose(fp_input);
//	fclose(fp_input1);
//	fclose(fp_input2);
//	fclose(fp_input3);
	
	//fclose(fp_action_table);
	//fclose(fp_first);
	//fclose(fp_project_set);
	
	fclose(fp_work3);
//	fclose(fp_output1);
//	fclose(fp_output2);
//	fclose(fp_output3);
	
//	fclose(fp_test1);
//	fclose(fp_test2);
//	fclose(fp_test3);
	
}

void work3_init()
{
	memset(L,-1,sizeof(L));
	memset(GOTO_L,-1,sizeof(GOTO_L));
	memset(read_num,'\0',sizeof(read_num));
	memset(read_id,'\0',sizeof(read_id));
	memset(read_op,0,sizeof(read_op));
	read_len = addr = L_len = 0;
}

void work3()
{
	work3_init(); 
	work3_open_file();
	work3_solve();
	work3_Print();
	work3_close_file();
}

//----------------------------------------------------------------------------------------------------------------------//
//end------------------------------------------------------------work3-------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------//

int main()
{
	work1();
	work2();
	work3();
	return 0;
}


