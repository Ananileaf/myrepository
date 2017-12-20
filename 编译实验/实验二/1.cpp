#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a>b?b:a)
#define INF 0x3f3f3f3f
#define sz() size()
#define pb push_back
#define ph push
#define mem(x, y) memset(x, y, sizeof(x));
#define mem0(x) mem(x,0)
#define mem1(x) mem(x,-1)
#define memINF(x) mem(x,INF)
#define all(x) x.begin(),x.end()
#define fi first
#define se second
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define per(i,a,b) for(int i=a;i>(b);--i)
#define setI(x) freopen(x".txt","r",stdin);
#define setIO(x) freopen("xx.in","r",stdin);freopen("xx.out","w",stdout);
using namespace std;
typedef __int64 ll;
#define endl '\n'
int const Max_N = 1e6+5;
int n;

struct ini
{
	vector<string>v[100];
	int len;
}a;
int cnt;
map<string,int>mp;

struct II
{
	vector<string>v[100];
	vector<string>p[100];
	int len;
}I[200];

 

string get_string(char *str1,int &i)
{
	string str2 = "";
	while(str1[i]!=' '&&str1[i]!='\n'&&str1[i] != '\0'&&str2[i]!='\t')
	{
		if(str1[i]=='<'||str1[i] == '>') 
		{
			++i;
			continue;
		}
		str2 += str1[i++];
	}
	//++i;
	while(str1[i]==' '||str1[i] == '\n'||str1[i]=='\t') ++i;
	//cout << "str2 = " << str2 << " , i = " << i << endl;
	return str2;
}

void init()
{
	setI("LR1");
	char s1[200];
	string s2;
	a.len = 0;
	while(gets(s1))
	{
		int i = 0;
		int len = strlen(s1);
		get_string(s1,i);
		a.v[a.len].pb(get_string(s1,i));
		get_string(s1,i);
		while(len > i) a.v[a.len].pb(get_string(s1,i));
		a.len++;
	}
	 
	for(int i = 0; i < a.len; ++i)
	{
		for(int j = 0; j < a.v[i].sz(); ++j)
		{
			cout << a.v[i][j] << ' ';
		}
		cout << endl;
	}
}


string Next_string(vector<string> &v)
{
	string s = "`";
	for(int i = 1; i < v.size(); ++i)
	{
		if(v[i-1] == s) return v[i];
	}
	return NULL;
} 

void CLOSURE(I &i)
{
	map<string,bool>mp;
	
	queue<string>que;
	for(int j = 0; j < i.len; ++j)
	{
		
	}
	 
}


int main()
{
	init();
	char s[] = "`";
	cout << strlen(s) << endl; 
	return 0;
}
	//freopen("in.txt","r",stdin);
//std::ios::sync_with_stdio(false);



