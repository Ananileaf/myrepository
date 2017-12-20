#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<list>
using namespace std;
char Keywords[55][10] = {"call", "auto", "bool", "break", "case", "catch", "char", "class", 
"const", "continue", "default", "delete", "do", "double", "else", "enum", "extern", 
"false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "namespace", 
"new", "operator", "private", "protected", "public", "register", "return", "short", 
"signed", "sizeof", "static", "struct", "switch", "template", "this", "throw", "true", 
"try", "typedef", "typename", "union", "unsigned", "using", "main", "void", "volatile", "while"};

int f[45][30];// 分析表 赋值（s9=900,r1=1;acc=20）
char wf[20][15]={"0","P->S","S->BD","B->bH;","B->","H->i","H->H,i","D->i=E","D->c(i)","D->f(K)DeD","D->w(K)dD","K->E>E","E->T","E->E+T","T->T*F","T->F","F->i","F->n","F->(E)"};//文法单元；
char tempchr[10],p,in_put[100],table[100][10];//存放识别字符串；
int t,j,val,b,flag;
char flag1,put[100],*arr;
int begin=0,forward=0,pos;// 开始符号和向前看指针；

int main()
{
f[0][8]=300;f[0][17]=4;//分析表
f[1][17]=20;
f[2][1]=500;f[2][3]=600;f[2][4]=700;f[2][6]=800;
f[3][1]=1000;
f[4][17]=2;
f[5][14]=1100;
f[6][15]=1200;
f[7][15]=1300;
f[8][15]=1400;
f[9][9]=1500;f[9][10]=2800;
f[10][9]=5;f[10][10]=5;
f[11][1]=2000;f[11][2]=2100;f[11][15]=2200;
f[12][1]=2300;
f[13][1]=2000;f[13][2]=2100;f[13][15]=2200;
f[14][1]=2000;f[14][2]=2100;f[14][15]=2200;
f[15][1]=1600;
f[16][9]=6;f[16][10]=6;
f[17][12]=3700;f[17][17]=7;
f[18][11]=3900;f[18][12]=12;f[18][13]=12;f[18][16]=12;f[18][17]=12;
f[19][11]=15;f[19][12]=15;f[19][13]=15;f[19][16]=15;f[19][17]=15;
f[20][11]=16;f[20][12]=16;f[20][13]=16;f[20][16]=16;f[20][17]=16;
f[21][11]=17;f[21][12]=17;f[21][13]=17;f[21][16]=17;f[21][17]=17;
f[22][1]=2000;f[22][2]=2100;
f[23][16]=2400;
f[24][17]=8;
f[25][16]=2600;
f[26][7]=2700;
f[27][1]=500;f[27][3]=600;f[27][4]=700;f[27][6]=800;
f[28][17]=3;f[28][1]=3;f[28][3]=3;f[28][4]=3;f[28][6]=3;f[28][8]=3;
f[29][1]=500;f[29][3]=600;f[29][4]=700;f[29][6]=800;f[29][17]=10;
f[30][16]=4300;
f[31][5]=3200;
f[32][1]=500;f[32][3]=600;f[32][4]=700;f[32][6]=800;
f[33][17]=9;
f[34][13]=3500;
f[35][1]=2000;f[35][2]=2100;f[35][15]=2200;
f[36][12]=3700;f[36][16]=11;
f[37][1]=2000;f[37][2]=2100;f[37][15]=2200;
f[38][11]=3900;f[38][12]=13;f[38][13]=13;f[38][16]=13;f[38][17]=13;
f[39][1]=2000;f[39][2]=2100;f[39][15]=2200;
f[40][12]=3700;f[40][16]=4100;
f[41][11]=18;f[41][12]=18;f[41][13]=18;f[41][16]=18;f[41][17]=18;
f[42][11]=14;f[42][12]=14;f[42][13]=14;f[42][16]=14;f[42][17]=14;
f[43][1]=500;f[43][3]=600;f[43][6]=800;f[43][20]=3100;
f[0][18]=100;f[0][19]=200;
f[2][20]=400;
f[3][21]=900;
f[11][23]=1700;f[11][24]=1800;f[11][25]=1900;
f[13][22]=3000;f[13][23]=3400;f[13][24]=1800;f[13][25]=1900;
f[14][22]=2500;f[14][23]=3400;f[14][24]=1800;f[14][25]=1900;
f[22][23]=4000;f[22][24]=1800;f[22][25]=1900;
f[27][20]=2900;
f[32][20]=3300;
f[35][23]=3600;f[35][24]=1800;f[35][25]=1900;
f[37][24]=3800;f[37][25]=1900;
f[39][25]=4200;
f[17][5]=7;f[18][5]=12;f[19][5]=15;f[20][5]=16;f[21][5]=17;f[24][5]=8;
f[29][5]=10;f[33][5]=9;f[38][5]=13;f[41][5]=18;f[42][5]=14;

	
list<int> list1;//链表定义
	list<char> list2;
	list<int>::iterator it1;
	list<char>::iterator it2;
	
	void print(int flag);
	int change(char flag1 );
	int size,i=0;
	char ch; 
	FILE *fp=fopen("file.txt","r");
	if (fp==NULL){ return 0;}
	fseek(fp,0,2);
	size=ftell(fp); 
	arr=new char[size];
	if ((fp=fopen("file.txt","r"))==NULL) exit(1);
	while (!feof(fp))
	{
		ch=fgetc(fp);
		arr[i++]=ch;
	}
	fclose(fp);  
	size=i-1;
	int state;//状态；
	i=0; 
	
	while(i<=size)
	{
				for(t=0;t<8;t++)
				tempchr[t]=0;
		if(begin==forward)
		{
			ch=arr[forward];
			if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z') state=9;
			else if(ch>='0'&&ch<='9')state=12;
			else if(ch=='+'||ch=='-'||ch=='*'||ch=='/')state=25;
			else if(ch=='<'||ch=='>'||ch=='=')state=0;
			else if(ch==','||ch==';'||ch=='('||ch==')')state=30;
			else if (ch=='\n'||ch=='\t'||ch==' ') state=22;
			else state=31;
			
		}		
		


switch(state)
		{
		case 0: {ch=arr[i++];forward++;}	
			if(ch=='<')state=1;
			else if(ch=='=')state=5;
			else if(ch='>')state=6;
			break;
		case 1:{ch=arr[i++];forward++;}	
			if(ch=='=')state=2;
			else if(ch=='>')state=3;
			else state=4;
			break;
		case 2:print(5);	break;		
		case 3:print(5);	break;		
		case 4:{i=i-1;forward=forward-1;print(5);}
			break;
		case 5:print(5);break;
		case 6:{ch=arr[i++];forward++;}	
			if(ch=='=')state=7;
			else state=8;
			break;
		case 7:print(5);break;			
		case 8:{i=i-1;forward=forward-1;print(5);}
			break;
		case 9:{ch=arr[i++];forward++;}	
			if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))state=10;
			break;
		case 10:{ch=arr[i++];forward++;}	
			if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))state=10;
			else if(ch>='0'&&ch<='9')state=10;
			else state=11;
			break;
		case 11:
			i=i-1;forward=forward-1;print(1);
			break;
		case 12:{ch=arr[i++];forward++;}	
			if(ch>='0'&&ch<='9')state=13;
			break;
		case 13:{ch=arr[i++];forward++;}	
			if(ch>='0'&&ch<='9')state=13;
			else if (ch=='E')state=16;
			else if(ch=='.')state=14;
			else state=20;
			break;
		case 14:{ch=arr[i++];forward++;}	
			if(ch>='0'&&ch<='9')state=15;
			else state=32;
			break;
		case 15:{ch=arr[i++];forward++;}	
			if(ch>='0'&&ch<='9')state=15;
			else if(ch=='E')state=16;
			else state=21;
			break;
		case 16:{ch=arr[i++];forward++;}	
			if(ch>='0'&&ch<='9')state=18;
			else if(ch=='+'||ch=='-')state=17;
			else state=32;
			break;
		case 17:{ch=arr[i++];forward++;}	
			if(ch>='0'&&ch<='9')state=18;
			else state=32;
			break;
		case 18:{ch=arr[i++];forward++;}	
			if(ch>='0'&&ch<='9')state=18;
			else   state=19;
			break;
		case 19:{i=i-1;forward=forward-1;print(2);}break;
		case 20:{i=i-1;forward=forward-1;print(2);}break;
		case 21:{i=i-1;forward=forward-1;print(2);}break;
		case 22:{ch=arr[i++];forward++;}	
			if(ch=='\n'||ch=='\t'||ch==' ')
				state=23;
			break;
		case 23:{ch=arr[i++];forward++;}	
			if(ch=='\n'||ch=='\t'||ch==' ')	state=23;
			else   state=24;
			break;
		case 24:{i=i-1; forward=forward-1;begin+=1; forward=begin;}
			break;
		case 25:{ch=arr[i++];forward++;}	
			if(ch=='+')state=26;
			else if(ch=='-')state=27;
			else if(ch=='*')state=28;
			else if(ch=='/')state=29;	
			break;
		case 26:print(4);break;
		case 27:print(4);break;
		case 28:print(4);break;
		case 29:print(4);break;
		case 30:{ch=arr[i++];forward++;}print(3);break;
		case 31:{ch=arr[i++];forward++;}print(6);break;	
		case 32:{i=i-1;forward=forward-1;}print(6);break;	
		}
	}
	//语法分析；字符串输入以@结束
	printf("输入的字符串以结束@\n");
	in_put[val]='@';
	printf("%s",in_put);
	printf("\n");
	i=0;j=0;
	list1.push_back(0);
	char n,c;
	int m,bg,len;
	printf("栈         符号           输入                           动作 \n\n");
	while(1)
	{ 
		for(it1=list1.begin();it1!=list1.end();it1++)
			printf("%d",*it1);
		printf("       ");
		for(it2=list2.begin();it2!=list2.end();it2++)
			printf("%c",*it2);
		printf("         ");
		for(i=j;i<=val;i++)
			printf("%c",in_put[i]);
		printf("       ");
	
		bg=list1.back();
		n=in_put[j];
		flag=change(n);
		
		if(f[bg][flag]>100)
		{
			m=f[bg][flag]/100;
			printf("移入\n");	
			list1.push_back(m);
			list2.push_back(in_put[j]);
			j++;
		}
		else if(f[bg][flag]<100&&f[bg][flag]!=20&&f[bg][flag]!=0)
		{
			m=f[bg][flag];
			printf("根据%s规约\n",wf[m]);
			c=wf[m][0]; 			  
			flag=change(c);		  
			len=strlen(wf[m])-3;
			for(i=0;i<len;i++)

			{	 list1.pop_back();
			list2.pop_back();
			}

			bg=list1.back();
			list2.push_back(c);
			m=f[bg][flag]/100;

			list1.push_back(m);
		}
		else if(f[bg][flag]==20)
		{ 
			printf("接受\n");
			break;
		}
		else if(f[bg][flag]==0)
		{
			printf("\n");
                        printf("%s",table[j-1]);
			printf("%s ",table[j]);
			printf("ERROR\n");
			break;
		}
	}
	return 0;
	}	
	void print(int b) //输出 
	{	
		pos=begin;
		for(t=0;t<forward-begin;t++)
		{
			p=arr[pos++];tempchr[t]=p;			
		}
		begin=forward;
		
		switch(b)
		{
        case 1:        
			{
				for(j=0; j<55; j++)
				
					if(strcmp(tempchr,Keywords[j])==0)
					{
						printf("<%s keyword>\n",tempchr);
						if(strcmp(tempchr,"if")==0)
						{	
							strcpy(table[val],tempchr);
							in_put[val++]='f';	break;}
						else if(strcmp(tempchr,"else")==0)
						{
							strcpy(table[val],tempchr);
							in_put[val++]='e';	break;}
						else if(strcmp(tempchr,"while")==0)
						{
							strcpy(table[val],tempchr);	
							in_put[val++]='w';	break;}
						else if(strcmp(tempchr,"do")==0)
						{
							strcpy(table[val],tempchr);
						in_put[val++]='d';	break;}
							else if(strcmp(tempchr,"call")==0)
							{
								strcpy(table[val],tempchr);
							in_put[val++]='c';	break;}
						else 
						{ 
							strcpy(table[val],tempchr);
							in_put[val++]='b';	break;	}										   
					}
					if(j==55) 
					{	printf("<%s ident>\n",tempchr);
					strcpy(table[val],tempchr);
					in_put[val++]='i';}
            }break;
		case 2:
		 	printf("<%s number>\n",tempchr);
			strcpy(table[val],tempchr);
			in_put[val++]='n';			 
			break;
		case 3:
		 	printf("<%s division>\n",tempchr);
			 strcpy(table[val],tempchr);
			in_put[val++]=tempchr[0];			
			break;
		case 4:
			 	printf("<%s relation>\n",tempchr);
				 strcpy(table[val],tempchr);
			in_put[val++]=tempchr[0];
			break;
		case 5:
			 	printf("<%s operator>\n",tempchr);
				 strcpy(table[val],tempchr);
			in_put[val++]=tempchr[0];			
			break;
		case 6:
			 	printf("<%s ERROR>\n",tempchr);
			break;
		}		
	}
	int change(char flag1 )
	{
		if(flag1=='i')
			flag=1;
		else if(flag1=='n')
			flag=2;
		else if(flag1=='c')
			flag=3;		
		else if(flag1=='f')
			flag=4;
		else if(flag1=='e')
			flag=5;
		else if(flag1=='w')
			flag=6;
		else if(flag1=='d')
			flag=7;
		else if(flag1=='b')
			flag=8;
		else if(flag1==',')
			flag=9;
		else if(flag1==';')
			flag=10;
		else if(flag1=='*')
			flag=11;
		else if(flag1=='+')
			flag=12;
		else if(flag1=='>')
			flag=13;
		else if(flag1=='=')
			flag=14;
		else if(flag1=='(')
			flag=15;
		else if(flag1==')')
			flag=16;
		else if(flag1=='@')
			flag=17;
		else if(flag1=='S')
			flag=18;
		else if(flag1=='B')
			flag=19;
		else if(flag1=='D')
			flag=20;
		else if(flag1=='H')
			flag=21;
		else if(flag1=='K')
			flag=22;
		else if(flag1=='E')
			flag=23;
		else if(flag1=='T')
			flag=24;
		else if(flag1=='F')
			flag=25;
		return(flag);
	
} 