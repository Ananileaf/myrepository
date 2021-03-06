#include<bits/stdc++.h>
#define setI(x) freopen(x".txt","r",stdin);
#define setO(x) freopen(x".txt","w",stdout);
#define endl '\n'
#define acc 1
#define error 0
#define mov 2
#define guiyue 3
#define begin1 "S'"
#define begin2 "S"
using namespace std;

int const Max_N = 1e6+5;
int n;

int G[300][300];//文法
int length[300];//文法的长度
int number = 0;//文法的个数 
bool is_end[300];//是否是终结符 
bool empty[300];
 
//文法中出现的 单词到数字的映射 
char String[300][80];//文法
map<string,int>mp;
int cnt = 0; 

//first集合 
bool first[300][300];
int buf[300];	//求first(beta a) 
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
}items[300][300];
int items_size[300]; 
int items_count;
int trains[300][300];//trains[i][j]表示从Ii到Ij使用了String[trains[i][j]]; 

// 分析表
struct action_table
{
	int op;
	int next;
}action[300][300];//第Ii个的输入为J 

//判断语句的输入 
int read[300];
int read_len = 0;

//栈
stack<int>state;//状态栈 
stack<int>sign;//符号栈  

//输出
char anslysis[500][1100]; 
int anslysis_len;
char p[1100];//tmp 

//文件读入读出
FILE *fp_grammar;
FILE *fp_action_table;
FILE *fp_first;
FILE *fp_project_set;
FILE *fp_input ,*fp_input1 ,*fp_input2 ,*fp_input3;
FILE *fp_output,*fp_output1,*fp_output2,*fp_output3;
FILE *fp_test1 ,*fp_test2  ,*fp_test3;

void get_grammar()//读入文法 
{
	//setI("pascal");
	for(int i = 0; i < 200; ++i) is_end[i] = true;
	int now;
	int i = 0;
	while(~fscanf(fp_grammar,"%*s"))
	{
		while(true)
		{
			char str[50] = {'\0'};
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
				mp[str] = ++cnt;
				strcpy(String[cnt],str);
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
					for(int k = 1; k <= cnt; ++k)
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
	bool vis[200] = {false};//去重 
	buf_size = 0;
	
	int t = mp["ε"]; 
	int i = tmp.now+1;
	for(; i < length[tmp.num]; ++i)
	{
		int p = G[tmp.num][i];
		if(is_end[p] == false)//非终结符 
		{
			//p的first集合 
			for(int j = 0; j <= cnt; ++j)
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
			for(int j = 1; j <= cnt; ++j)
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
		mp["$"] = ++cnt;
		strcpy(String[cnt],"$");
	}
	items[0][0] = project(0,1,mp["$"]);
	items_size[0] = 1;
	e_closure(0); 
	items_count = 1;
	
	
	
	for(int i = 0; i < items_count; ++i)//从第一个项目开始扩展 
	{
		for(int j = 1; j <= cnt; ++j)//暴力每个符号
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

void Print_first()
{
	for(int i = 1; i <= cnt; ++i)
	{
		if(is_end[i]) continue; 
		fprintf(fp_first,"First(%s) : ",String[i]);
		for(int j = 1; j <= cnt ; ++j)
		{
			if(first[i][j])
			fprintf(fp_first,"%s ",String[j]);
		}
		fprintf(fp_first,"\n");
	 } 
}

void Print_action()
{
	//setO("action_table"); 
	for(int i = 0; i < items_count;++i)
	{
		fprintf(fp_action_table,"I%d :",i);
		for(int j = 1; j <= cnt; ++j)
		{
			if(action[i][j].op != error)
			{
				if(is_end[j])
				{
					if(action[i][j].op == acc) 	fprintf(fp_action_table,"(%s , acc)  ",String[j]);
					else fprintf(fp_action_table,"(%s , %c%d)  ",String[j],"sr"[action[i][j].op==guiyue],action[i][j].next);
				}
				else
				{
					fprintf(fp_action_table,"(%s , %d)  ",String[j],action[i][j].next);
				}		
			}
		}
		fprintf(fp_action_table,"\n");
	}
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
	memset(p,' ',sizeof(p));
	p[900] = '\0';
	
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
			p[i++] = s.top();
			s.pop();
		} 
		
		t2.pop(),p[i++] = ' ';
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
		for(int j = 0; j < len; ++j) p[i++] = String[t][j];	
		p[i++] = ' ';
	}
} 

void Print_input(int q)
{
	int i = 250;
	for(;q<read_len; ++q)
	{
		int t = read[q];
		int len = strlen(String[t]);
		for(int j = 0; j < len; ++j) p[i++] = String[t][j];
		p[i++] = ' ';
	}
}
void Print_ACTION(int q)
{
	int i = 500;
	
	if(q==-1)
	{
		char s[] = "mov";
		int len = strlen(s);
		for(int j = 0; j < len; ++j) p[i++] = s[j];
		return ;
	}
	else if(q==-2)
	{	
		char s[] = "acc";
		int len = strlen(s);
		for(int j = 0; j < len; ++j) p[i++] = s[j];
		return ;
		
	}
	int t = G[q][0];
	int len = strlen(String[t]);
	for(int j = 0; j < len; ++j) p[i++] = String[t][j];
	char s[] = "→" ;
	p[i++] = s[0];
	p[i++] = s[1];
	for(int k = 1; k < length[q]; ++k)
	{
		int t = G[q][k];
		int len = strlen(String[t]);
		for(int j = 0; j < len; ++j) p[i++] = String[t][j];
	}
}

void Print_anslysis()
{
	for(int i = 0; i < anslysis_len; ++i) 
		fprintf(fp_output,"%s\n",anslysis[i]);
}
void Print_all()
{
	Print_first();
	Print_set();
	Print_action();
	Print_anslysis();
}

void read1()
{
//	setI("input");
	char str1[30],str2[30];
	while(~fscanf(fp_input,"%*s"))
	{
		fscanf(fp_input,"%s %*s %s %*s",str1,str2);
		if(mp[str1]) read[read_len++] = mp[str1];
		else read[read_len++] = mp[str2];
	}
	read[read_len++] = mp["$"];
}

void read2()
{
//	setI("input1");
	char str[20];
	while(~fscanf(fp_input1,"%s",str)) 
		read[read_len++] = mp[str];
	read[read_len++] = mp["$"];
}


void cal()
{	
	read1();
	//setO("output");
		
	bool ERROR = false;
	
	state.push(0);
	sign.push(mp["$"]);
	char s[1100] = "状态栈                                                                符号栈                                                                                                                                                                              输入串                                                                                                                                                                                                                                                     ACTION  ";
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
			fprintf(fp_output,"error!");
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
		strcpy(anslysis[anslysis_len++],p);
	}
	
} 
void open_file()
{
	//文件读入读出
	fp_grammar         = fopen("pascal.txt","r+");

	
	fp_input           = fopen("input.txt","r+");
	fp_input1          = fopen("input1.txt","r+");
	fp_input2          = fopen("input2.txt","r+");
	fp_input3          = fopen("input3.txt","r+");
	
	fp_action_table    = fopen("action_table.txt","w+");
	fp_first           = fopen("first.txt","w+");
	fp_project_set     = fopen("project_set.txt","w+");
	
	fp_output          = fopen("output.txt","w+");
	fp_output1         = fopen("output1.txt","w+");
	fp_output2         = fopen("output2.txt","w+");
	fp_output3         = fopen("output3.txt","w+");
	
	fp_test1           = fopen("test1.txt","w+");
	fp_test2           = fopen("test2.txt","w+");
	fp_test3           = fopen("test3.txt","w+");
	}

void close_file()
{
	fclose(fp_grammar);
	
	fclose(fp_input1);
	fclose(fp_input2);
	fclose(fp_input3);
	
	fclose(fp_action_table);
	fclose(fp_first);
	fclose(fp_project_set);
	
	fclose(fp_output);
	fclose(fp_output1);
	fclose(fp_output2);
	fclose(fp_output3);
	
	fclose(fp_test1);
	fclose(fp_test2);
	fclose(fp_test3);
	
}


int main()
{
	open_file();
	get_grammar();
	get_first(); 
	make_set();
	get_action();
	cal();
	Print_all();
	close_file();
	return 0;
}


