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

int G[300][300];//�ķ�
int length[300];//�ķ��ĳ���
int number = 0;//�ķ��ĸ��� 
bool is_end[300];//�Ƿ����ս�� 
bool empty[300];
 
//�ķ��г��ֵ� ���ʵ����ֵ�ӳ�� 
char String[300][80];//�ķ�
map<string,int>mp;
int cnt = 0; 

//first���� 
bool first[300][300];
int buf[300];	//��first(beta a) 
int buf_size;

//��Ŀ��
struct project 
{
	int num;//��һ������ 
	int now;//�ڵ�ǰ���򡤵�λ�� 
	int search; //RL(1)��1 
	project(int _num = 0,int _now = 0,int _search = 0):num(_num),now(_now),search(_search){
	}
	bool operator == (project & t) const{
		return (t.num==num)&&(t.now==now)&&(t.search==search); 
	 } 
}items[300][300];
int items_size[300]; 
int items_count;
int trains[300][300];//trains[i][j]��ʾ��Ii��Ijʹ����String[trains[i][j]]; 

// ������
struct action_table
{
	int op;
	int next;
}action[300][300];//��Ii��������ΪJ 

//�ж��������� 
int read[300];
int read_len = 0;

//ջ
stack<int>state;//״̬ջ 
stack<int>sign;//����ջ  

//���
char p[1100]; 


void get_grammar()//�����ķ� 
{
	setI("LR(1)");
	//setI("test5");
	//setO("out");
	for(int i = 0; i < 200; ++i) is_end[i] = true;
	int now;
	int i = 0;
	while(~scanf("%*s"))
	{
		while(true)
		{
			char str[50] = {'\0'};
			scanf("%s",str);
			
			if(strcmp(str,"��") == 0) empty[number] = true; 
			if(strcmp(str,"$")==0)
			{
				length[number] = i; 
				i = 0;
				++number;
				break;
			}
			else if(strcmp(str,"��")==0) continue;
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
	
	while(flag) //ֻҪ�и��¾�һֱѭ�� 
	{
		flag = false;
		for(int i = 0 ; i < number; ++i)
		{
			
			int p = G[i][0];
			
			int j = 1;
			for( ; j < length[i]; ++j)
			{
				int q = G[i][j];
				int t = mp["��"];
				if(is_end[q] == false)//���ܽ�� 
				{
					for(int k = 1; k <= cnt; ++k)
					{
						if(k==t) continue;//����Ϊ�� 
						if(first[q][k] == true && first[p][k] == false)
						{
							first[p][k] = true;
							flag = true;
						}
					}
				}
				else//�ܽ��
				{
					if(first[p][q] == false)
					{
						first[p][q] = true;
						flag = true;
					}
					break; 
				}
				
				if(first[q][t] == false) break;//Xi������ ��
			}
			if(j==length[i])
			{
				int t = mp["��"];
				if(first[p][t] == false)
				{
					
					first[p][t] = true;
					flag = true;
				}
			}
		}
	}
	
	return ;
	for(int i = 1; i <= cnt; ++i)
	{
		if(is_end[i]) continue; 
		printf("First(%s) : ",String[i]);
		for(int j = 1; j <= cnt ; ++j)
		{
			if(first[i][j])
			printf("%s ",String[j]);
		}
		printf("\n");
	 } 
}


//�ж������ӵ�e_closure �Ƿ����ظ� 
bool is_in(project tmp,int T)
{
	for(int i = 0; i < items_size[T]; ++i)
		if(items[T][i] == tmp) return true;
	return false;
}

//��ȡ������ 
void get_search(project tmp)
{
	bool vis[200] = {false};//ȥ�� 
	buf_size = 0;
	
	int t = mp["��"]; 
	int i = tmp.now+1;
	for(; i < length[tmp.num]; ++i)
	{
		int p = G[tmp.num][i];
		if(is_end[p] == false)//���ս�� 
		{
			//p��first���� 
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
		else	//�ս�� 
		{
			if(!vis[p])
				buf[buf_size++] = p,vis[p] = true;
			return ;
		 } 
	}
	
	if(!vis[tmp.search])
		buf[buf_size++] = tmp.search,vis[tmp.search] = true;
}

void e_closure(int T) //����Ŀ�� 
{
	bool flag = true;
	while(flag)
	{
		flag = false;
	
		for(int i = 0; i < items_size[T]; ++i)
		{
			int p = G[items[T][i].num][items[T][i].now];//������ĵ��� 
			if(is_end[p]) continue;//��ǰ���ܽ��
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

//������Ŀ�� 
void make_set()
{
	//��ʼ����һ����Ŀ�� 
	if(!mp["$"])
	{
		mp["$"] = ++cnt;
		strcpy(String[cnt],"$");
	}
	items[0][0] = project(0,1,mp["$"]);
	items_size[0] = 1;
	e_closure(0); 
	items_count = 1;
	
	
	
	for(int i = 0; i < items_count; ++i)//�ӵ�һ����Ŀ��ʼ��չ 
	{
		for(int j = 1; j <= cnt; ++j)//����ÿ������
		{
			if(j==mp["��"]) continue;
			project tmp[200];
			int tmp_size = 0;	
				
		//	cout << String[j] << endl;
			for(int k = 0; k < items_size[i]; ++k)//��i����еĵ�k������ 
			{
				int p = items[i][k].num;
				int q = items[i][k].now;
			//	cout << String[G[p][q]] << endl; 
				if(q>=length[p]) continue;//��ͷ�� 
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
				if(p==0)//�µ���Ŀ�� 
				{
					trains[i][items_count] = j; 
					++items_count;
				}
				else//�Ѿ����� 
				{
					trains[i][p] = j;
				}
				
			}
		} 
	}
}

//��������� 
void get_action()
{
	int t = mp["��"];
	for(int i = 0; i < items_count; ++i)
	{
		for(int j = 0; j < items_size[i]; ++j)
		{
			int p = items[i][j].num;
			int q = items[i][j].now;
			//����a -> bcd�� ����� 
			if(q == length[p] || (length[p]==2 && q == 1 &&  G[p][q]== t))
			{
				
				action[i][items[i][j].search].next = items[i][j].num;//��Լ 
				action[i][items[i][j].search].op = guiyue;//��Լ 
				
				if(q==length[p] && length[p] == 2 && items[i][j].search == mp["$"] 
					&& G[p][0] == mp[begin1] && G[p][1] == mp[begin2])
				{
					action[i][items[i][j].search].op = acc;//��Լ 
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

void Print_action()
{
	setO("action_table"); 
	for(int i = 0; i < items_count;++i)
	{
		printf("I%d :",i);
		for(int j = 1; j <= cnt; ++j)
		{
			if(action[i][j].op != error)
			{
				if(is_end[j])
				{
					if(action[i][j].op == acc) 	printf("(%s , acc)  ",String[j]);
					else printf("(%s , %c%d)  ",String[j],"sr"[action[i][j].op==guiyue],action[i][j].next);
				}
				else
				{
					printf("(%s , %d)  ",String[j],action[i][j].next);
				}		
			}
		}
		printf("\n");
	}
}
void Print_set()
{
	setO("project_set");
	for(int i = 0; i < items_count; ++i)
	{
		printf("I%d:\n",i);
		for(int j = 0; j < items_size[i]; ++j)
		{
			int p = items[i][j].num;
			int q = items[i][j].now;
			printf("%s -> ",String[G[p][0]]);
			for(int k = 1; k < q; ++k) printf("%s ",String[G[p][k]]);
			printf("�� ");
			for(int k = q; k < length[p]; ++k ) printf("%s ",String[G[p][k]]);
			printf("  , %s",String[items[i][j].search]);
			printf("\n");
		}
		printf("\n");
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
	char s[] = "��" ;
	p[i++] = s[0];
	p[i++] = s[1];
	for(int k = 1; k < length[q]; ++k)
	{
		int t = G[q][k];
		int len = strlen(String[t]);
		for(int j = 0; j < len; ++j) p[i++] = String[t][j];
	}
}



void read1()
{
	setI("input");
	char str1[30],str2[30];
	while(~scanf("%*s"))
	{
		scanf("%s %*s %s %*s",str1,str2);
		if(mp[str1]) read[read_len++] = mp[str1];
		else read[read_len++] = mp[str2];
	}
	read[read_len++] = mp["$"];
}

void read2()
{
	setI("input1");
	char str[20];
	while(~scanf("%s",str)) 
		read[read_len++] = mp[str];
	read[read_len++] = mp["$"];
//	Print_input(0);
}


void cal()
{
	
	read1();
	
	setO("output");
	
	bool ERROR = false;
	
	state.push(0);
	sign.push(mp["$"]);
	char s[800] = "״̬ջ                                                                ����ջ                                                                                                                                                                              ���봮                                                                                                                                                                                                                                                     ACTION  ";
	
	printf("%s\n",s);
	
	int i = 0;
	bool end = false;
	while(ERROR == false &&end == false)
	{
		int now_state = state.top();//��ǰ��Ii or Si
		int now_input = read[i];//���� 
		
		Print_state();
		Print_sign();
		Print_input(i);
		
		int op = action[now_state][now_input].op;
		int next_state =  action[now_state][now_input].next;
		
		if(op==error)
		{
			printf("error!");
			ERROR = true;
			continue;
		}
		else if(op == mov)
		{
			state.push(next_state);//״̬ѹջ 
			sign.push(now_input);//���뵽����ջ 
			Print_ACTION(-1);
			++i;
		}
		else if(op == acc||guiyue)
		{
			int l = length[next_state]-1;//A->B
			if(empty[next_state] == true) l = 0;
			//����l�� ״̬
			for(int i = 0; i < l; ++i) state.pop(),sign.pop();
			
			int t = state.top();
			int A = G[next_state][0]; 
			//GOTO[t,A] ѹջ
			
			int tmp = next_state; 
			
			next_state = action[t][A].next;
			state.push(next_state);
			sign.push(A);
			
			
			if(op==acc)
			{
				end = true;
				Print_ACTION(-2);//���A->B 
			}	
			else Print_ACTION(tmp);//���A->B 
			
			
		}
		
		printf("%s\n",p);
	}
	
} 

int main()
{
	get_grammar();
	get_first(); 
	make_set();
	Print_set();
	get_action();
	Print_action();
	cal();
	scanf("%*d");
	return 0;
}


