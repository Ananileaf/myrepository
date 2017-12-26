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

int const Max_N = 1e6+5;
int n;
int main()
{
	#ifdef Anani_leaf
	  setI("xx");
	#endif
	FILE *fp_grammar         = fopen("pascal.txt","r+");
	char str[200];
	while(~fscanf(fp_grammar,"%*s")) 
	{
		fscanf(fp_grammar,"%s",str);
		cout << str<< endl;
	}
	return 0;
}
	//freopen("in.txt","r",stdin);
//std::ios::sync_with_stdio(false);



