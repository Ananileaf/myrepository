//运行方式：把待分析的pascal代码放到D盘根目录下，然后运行此程序
#include<string.h>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<iostream>
#include <fstream>
#include<iomanip>
using namespace std;
char *table[]= {" ","program","begin","end","while","do","if","then","else"},ch; //定义关键字
string t[100];//记号流表
string f[100];//符号栈
int a=0,ii=0;
string ACTION[]= {"(",")",",",";",":=","+","*","<",".","begin","end","if","then","else","while","do","id","num","program","$",
	"S","id_lists","compound_stmt","optional_stmts","stmts","stmt","bool","expr","term","factor"};
int stack[100]={0};
string lef[]={"S'","S","id_lists","id_lists","compound_stmt","optional_stmts","optional_stmts","stmts","stmts",
	"stmt","stmt","stmt","stmt","stmt","bool","expr","expr","term","term","factor","factor"};
string rig[]={"S","program id ( id_lists ); compound_stmt .","id","id_lists , id","begin optional_stmts end","stmts","ε","stmt",
	"stmts; stmt","id := expr","compound_stmt","if bool then stmt","if bool then stmt else stmt","while bool  do stmt",
	"expr < expr","expr + term","term","term * factor","factor","id","num"};
int num[21]={1,8,1,3,3,1,0,1,3,3,1,4,6,4,3,3,1,3,1,1,1};

int ana[50][30];//分析表
void init()
{
	//初始化分析表
	ana[0][18]=2;ana[0][20]=1;
	ana[1][19]=99;
	ana[2][16]=3;
	ana[3][0]=4;
	ana[4][16]=6;ana[4][21]=5;
	ana[5][1]=7;ana[5][2]=8;
	ana[6][1]=-2;ana[6][2]=-2;
	ana[7][3]=9;
	ana[8][16]=10;
	ana[9][9]=12;ana[9][22]=11;
	ana[10][1]=-3;ana[10][2]=-3;
	ana[11][8]=13;
	ana[12][9]=12;ana[12][10]=-6;ana[12][11]=19;ana[12][14]=20;ana[12][16]=17;ana[12][22]=18;ana[12][23]=14;ana[12][24]=15;ana[12][25]=16;
	ana[13][19]=-1;
	ana[14][10]=21;
	ana[15][3]=22;ana[15][10]=-5;
	ana[16][3]=-7;ana[16][10]=-7;
	ana[17][4]=23;
	ana[18][3]=-10;ana[18][10]=-10;
	ana[19][16]=28;ana[19][17]=29;ana[19][26]=24;ana[19][27]=25;ana[19][28]=26;ana[19][29]=27;
	ana[20][16]=28;ana[20][17]=29;ana[20][26]=30;ana[20][27]=25;ana[20][28]=26;ana[20][29]=27;
	ana[21][3]=-4;ana[21][8]=-4;ana[21][10]=-4;ana[21][13]=-4;
	ana[22][9]=12;ana[22][11]=19;ana[22][14]=20;ana[22][16]=17;ana[22][22]=18;ana[22][25]=31;
	ana[23][16]=28;ana[23][17]=29;ana[23][27]=32;ana[23][28]=26;ana[23][29]=27;
	ana[24][12]=33;
	ana[25][5]=35;ana[25][7]=34;
	ana[26][3]=-16;ana[26][5]=-16;ana[26][6]=36;ana[26][7]=-16;ana[26][10]=-16;ana[26][12]=-16;ana[26][13]=-16;ana[26][15]=-16;
	ana[27][3]=-18;ana[27][5]=-18;ana[27][6]=-18;ana[27][7]=-18;ana[27][10]=-18;ana[27][12]=-18;ana[27][13]=-18;ana[27][15]=-18;
	ana[28][3]=-19;ana[28][5]=-19;ana[28][6]=-19;ana[28][7]=-19;ana[28][10]=-19;ana[28][12]=-19;ana[28][13]=-19;ana[28][15]=-19;
	ana[29][3]=-20;ana[29][5]=-20;ana[29][6]=-20;ana[29][7]=-20;ana[29][10]=-20;ana[29][12]=-20;ana[29][13]=-20;ana[29][15]=-20;
	ana[30][15]=37;
	ana[31][3]=-8;ana[31][10]=-8;
	ana[32][3]=-9;ana[32][5]=35;ana[32][10]=-9;ana[32][13]=-9;
	ana[33][9]=12;ana[33][11]=19;ana[33][14]=20;ana[33][16]=17;ana[33][22]=18;ana[33][25]=38;
	ana[34][16]=28;ana[34][17]=29;ana[34][27]=39;ana[34][28]=26;ana[34][29]=27;
	ana[35][16]=28;ana[35][17]=29;ana[35][28]=40;ana[35][29]=27;
	ana[36][16]=28;ana[36][17]=29;ana[36][29]=41;
	ana[37][9]=12;ana[37][11]=19;ana[37][14]=20;ana[37][16]=17;ana[37][22]=18;ana[37][25]=42;
	ana[38][3]=-11;ana[38][10]=-11;ana[38][13]=43;
	ana[39][5]=35;ana[39][12]=-14;ana[39][15]=-14;
	ana[40][3]=-15;ana[40][5]=-15;ana[40][6]=36;ana[40][7]=-15;ana[40][10]=-15;ana[40][12]=-15;ana[40][13]=-15;ana[40][15]=-15;
	ana[41][3]=-17;ana[41][5]=-17;ana[41][6]=-17;ana[41][7]=-17;ana[41][10]=-17;ana[41][12]=-17;ana[41][13]=-17;ana[41][15]=-17;
	ana[42][3]=-13;ana[42][10]=-13;ana[42][13]=-13;
	ana[43][9]=12;ana[43][11]=19;ana[43][14]=20;ana[43][16]=17;ana[43][22]=18;ana[43][25]=44;
	ana[44][3]=-12;ana[44][10]=-12;ana[44][13]=-12;
}

int lookup(char *TOKEN)
{
	//关键字匹配函数
	int m,i;
	for(i=1; i<=8; i++)
	{
		if((m=strcmp(TOKEN,table[i]))==0)
			return 1;
	}
	return 0;
}
int match(string a)
{
	//关键字匹配函数
	int i;
	for(i=0; i<=30; i++)
	{
		if(a==ACTION[i])
			return i;
	}
	return 0;
}
void mark(char *TOKEN)
{
	//存入记号流表
	t[ii]=TOKEN;
	ii++;
}

void checkElse(FILE *fp,char h,char *TOKEN)
{
	//非字母和数字时
	TOKEN[0]=ch;
	switch(ch)
	{
	case'(':
		mark(TOKEN);
		break;
	case')':
		mark(TOKEN);
		break;
	case',':
		mark(TOKEN);
		break;
	case'.':
		mark(TOKEN);
		break;
	case';':
		mark(TOKEN);
		break;
	case'+':
		mark(TOKEN);
		break;
	case'-':
		mark(TOKEN);
		break;
	case'*':
		mark(TOKEN);
		break;
	case'<':
		mark(TOKEN);
		break;
	case':':
		ch=fgetc(fp);
		if(ch=='=')//存在:=时
		{
			TOKEN[1]=ch;
			mark(TOKEN);
		}
		else
		{
			fseek(fp,-1,1);
			printf("error!");;
		}
		break;
	default:
		printf("error!");
		break;
	}
}

void scanner(FILE *fp)//扫描函数
{
	char TOKEN[36]= {'\0'};
	char ch;
	int i,c;
	ch=tolower(fgetc(fp));//获取字符指针fp并自动指向下一个字符
	if(isalpha(ch))
	{
		//判断该字符是否是字母
		TOKEN[0]=ch;
		ch=tolower(fgetc(fp));
		i=1;
		while(isalnum(ch))//判断该字符是否是字母或数字
		{
			TOKEN[i]=ch;
			i++;
			ch=tolower(fgetc(fp));
		}
		TOKEN[i]='\0';
		fseek(fp,-1,1);//回退一个字符
		c=lookup(TOKEN);
		if(!c)
			mark("id");//输出标识符			
		else mark(TOKEN);//输出关键字
	}
	else if(isdigit(ch))//判断是否是数字
	{
		fseek(fp,-1,1);
		int num;		
		//TOKEN[0]=ch;
		ch=fgetc(fp);
		i=1;
		while(isdigit(ch))//逐个读入数字及小数点
		{
			//TOKEN[i]=ch;
			i++;
			ch=fgetc(fp);
		}
		//TOKEN[i]='\0';
		i--;
		fseek(fp,-1,1);
		mark("num");
		if(ch=='.')
		{
			ch=fgetc(fp);
			ch=fgetc(fp);
			while(isdigit(ch))//逐个读入数字
				ch=fgetc(fp);
			fseek(fp,-1,1);
		}
	}	
	else
		checkElse(fp,ch,TOKEN);
}
int main()
{
	FILE *fp;
	if((fp=fopen("E:\\新建文件夹\\编译原理\\实验二\\in.txt","r"))==NULL)//读取文件内容,并返回文件指针,该指针指向文件的第一个字符
		fprintf(stderr,"error opening.\n");
	//exit(1);

	while(ch!=EOF)
	{
		ch=tolower(fgetc(fp));
		if(ch==EOF)break;
		if(ch==' ')//如果是空格，自动跳到下个字符
			;
		else if(ch==10)//换行时行数加1
			;
		else
		{
			fseek(fp,-1,1);//如果不是空格，则回退一个字符并扫描
			scanner(fp);
		}
	}
	t[ii]='$';
	init();
	int i,j=1,x,y,k,l=2,a,flag;
	ofstream outfile("E:\\新建文件夹\\编译原理\\实验二\\out.txt",ios::out);
	outfile<<"<1>  0 | | ";
	//for(a=0;a<=ii;a++)
			outfile<<t[0]<<" ";
	outfile.close();
	for(i=0;i<=ii;l++)
	{
		y=match(t[i]);
		if(ana[stack[j-1]][y]>0&&ana[stack[j-1]][y]!=99)
		{
			stack[j]=ana[stack[j-1]][y];//stack[j-1]栈顶
			f[j]=t[i];
			j++;i++;flag=1;
		}
		else if(ana[stack[j-1]][y]==99)
		{
			ofstream outfile("E:\\新建文件夹\\编译原理\\实验二\\out.txt",ios::app);
			outfile<<"| accept"<<endl<<endl;
			break;
		}
		else if(ana[stack[j-1]][y]==0)
		{
			ofstream outfile("E:\\新建文件夹\\编译原理\\实验二\\out.txt",ios::app);
			outfile<<"| error"<<endl<<endl;
			break;
		}
		else
		{
			flag=ana[stack[j-1]][y];
			string m=lef[-ana[stack[j-1]][y]];
			j=j-num[-ana[stack[j-1]][y]];
			f[j]=lef[-flag];
			stack[j]=ana[stack[j-1]][match(m)];
			j++;
			//i--;
		}
		ofstream outfile("E:\\新建文件夹\\编译原理\\实验二\\out.txt",ios::app);
		if(!outfile)
			cerr<<"open error!"<<endl;
		//第l-1行的动作
		if(flag>0)outfile<<"| shift";
		//else if(flag==0)outfile<<"| accept";
		else outfile<<"| reduce:"<<lef[-flag]<<"->"<<rig[-flag];
		outfile<<endl<<endl;

		outfile<<'<'<<l<<"> ";
		if(l<=9)outfile<<" ";
		//栈
		for(k=0;k<j;k++)
		{
			if(stack[k]!=99)
				outfile<<stack[k];
			else break;
		}
		outfile<<" | ";
		for(k=0;k<j;k++)
			outfile<<f[k]<<" ";
		outfile<<" | ";
		//输入
		//for(a=i;a<=ii;a++)
			outfile<<t[i]<<" ";
		outfile.close();
	}
	//
	
	return 0;
}