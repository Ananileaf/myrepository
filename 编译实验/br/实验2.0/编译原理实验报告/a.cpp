#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 500  /*标识符的最大长度*/

main()
{
 FILE *in,*out;

 char word[MAX];   /*存储标识符*/
 char cp;    /*存储当前读入字符*/
 int i;
 int j;
 int t;
 if((in=fopen("in.txt","r"))==NULL)
 {
  printf("不能打开文档in.txt，请检查根目录下是否存在该文档\n");
  exit(0);
 }
 else
 {
  printf("成功打开文档in.txt\n");
 }

 if((out=fopen("out.txt","w"))==NULL)
 {
  printf("不能打开文档out.txt，请检查根目录下是否存在该文档\n");
  exit(0);
 }
 else
 {
  printf("成功打开文档out.txt\n");
 }

 cp=fgetc(in);
 while(cp!=EOF)
 {
  /*消耗掉空格，制表符，换行符*/
  while(cp==' '||cp=='\t'||cp=='\n')
  {
   cp=fgetc(in);
  }

  /*cp数组复位*/
  i=0;

  /*数字检测*/
  if(cp>='0'&&cp<='9')
  {
   word[i++]=cp;
   cp=fgetc(in);
   while((cp>='0'&&cp<='9')||cp=='.')
   {
    word[i++]=cp;                                      
    cp=fgetc(in);
   }
   if(cp==' '||cp=='\t'||cp=='\n'||cp=='='||cp=='+'||cp=='-'||cp=='*'||cp=='/'||cp=='>'||cp=='<'||cp=='!'||cp==';'||cp==':'||cp==','||cp=='{'||cp=='}'||cp=='['||cp==']'||cp=='('||cp==')')
   {
    word[i]='\0';
	t=0;
	for(j=0;j<i;j++)
		if(word[j]=='.')
			t++;
		if(t<=1)
		{
			if(word[--i]=='.')
              fprintf(out,"error:'%s',不是合法的常数\n",word); 
             else fprintf(out,"%c常数：%c%s%c,%d%c\n",'(','"',word,'"',28,')');
		}
		else fprintf(out,"error:'%s',不是合法的常数\n",word);
   }
   else
   {
    while(cp!=' '&&cp!='\t'&&cp!='\n'&&cp!='='&&cp!='+'&&cp!='-'&&cp!='*'&&cp!='/'&&cp!='>'&&cp!='<'&&cp!='!'&&cp!=';'&&cp!=':'&&cp!=','&&cp!='{'&&cp!='}'&&cp!='['&&cp!=']'&&cp!='('&&cp!=')')
    {
     word[i++]=cp;
     cp=fgetc(in);
    }
    word[i]='\0';
    fprintf(out,"%s%c%s%c%s\n","error: ",'"',word,'"',"不是合法的标识符");
   }
   continue;
  }
  if(cp=='.')
  {
	  word[i++]=cp;
	  cp=fgetc(in);
	   while(cp!=' '&&cp!='\t'&&cp!='\n'&&cp!='='&&cp!='+'&&cp!='-'&&cp!='*'&&cp!='/'&&cp!='>'&&cp!='<'&&cp!='!'&&cp!=';'&&cp!=':'&&cp!=','&&cp!='{'&&cp!='}'&&cp!='['&&cp!=']'&&cp!='('&&cp!=')')
    {
     word[i++]=cp;
     cp=fgetc(in);
    }
	   word[i]='\0';
       fprintf(out,"error:'%s',不是合法的常数\n",word);
	   continue;
  }

  /*字符串检测*/
  if((cp>='a'&&cp<='z')||(cp>='A'&&cp<='Z')||cp=='_')
  {
   while((cp>='a'&&cp<='z')||(cp>='0'&&cp<='9')||(cp>='A'&&cp<='Z')||cp=='_')
   {
    word[i++]=cp;
    cp=fgetc(in);
   }

   if(cp==' '||cp=='\t'||cp=='\n'||cp=='='||cp=='+'||cp=='-'||cp=='*'||cp=='/'||cp=='>'||cp=='<'||cp=='!'||cp==';'||cp==':'||cp==','||cp=='{'||cp=='}'||cp=='['||cp==']'||cp=='('||cp==')')
   {
    word[i]='\0';
    /*基本保留字检测*/
    if(strcmp(word,"main")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',1,')');
    else if(strcmp(word,"void")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',2,')');
    else if(strcmp(word,"int")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',3,')');
    else if(strcmp(word,"float")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',4,')');
    else if(strcmp(word,"double")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',5,')');
    else if(strcmp(word,"char")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',6,')');
    else if(strcmp(word,"struct")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',7,')');
      else if(strcmp(word,"const")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',8,')');
    else if(strcmp(word,"extern")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',9,')');
    else if(strcmp(word,"register")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',10,')');
    else if(strcmp(word,"static")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',11,')');
    else if(strcmp(word,"if")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',12,')');
    else if(strcmp(word,"else")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',13,')');
    else if(strcmp(word,"switch")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',14,')');
     else if(strcmp(word,"case")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',15,')');
    else if(strcmp(word,"for")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',16,')');
    else if(strcmp(word,"do")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',17,')');
    else if(strcmp(word,"while")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',18,')');
    else if(strcmp(word,"goto")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',19,')');
    else if(strcmp(word,"continue")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',20,')');
    else if(strcmp(word,"break")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',21,')');
      else if(strcmp(word,"default")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',22,')');
    else if(strcmp(word,"sizeof")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',23,')');
    else if(strcmp(word,"return")==0)
     fprintf(out,"%c关键字：%c%s%c,%d%c\n",'(','"',word,'"',24,')');
    else
     fprintf(out,"%c自定义标识符:%c%s%c,%d%c\n",'(','"',word,'"',29,')');
   }

   /*排错处理（只能以字母、数字、下划线构成）*/
   else
   {
     while(cp!=' '&&cp!='\t'&&cp!='\n'&&cp!='='&&cp!='+'&&cp!='-'&&cp!='*'&&cp!='/'&&cp!='>'&&cp!='<'&&cp!='!'&&cp!=';'&&cp!=':'&&cp!=','&&cp!='{'&&cp!='}'&&cp!='['&&cp!=']'&&cp!='('&&cp!=')')
     {
      word[i++]=cp;
      cp=fgetc(in);
     }
     word[i]='\0';
     fprintf(out,"%s%c%s%c%s\n","error: ",'"',word,'"',"不是合法的标识符");
   }
   continue;
  }

  /*运算符*/
  if(cp=='#')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',50,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='+')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',31,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='-')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',32,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='*')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',33,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='/')//判断是否是注释，若是要略过；
  {
       word[i++]=cp;
        cp=fgetc(in);
     if(cp=='*'){word[--i]='\0';while(cp!='/'){cp=fgetc(in);}cp=fgetc(in);}
     else
         fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',34,')');
             word[i]='\0';
   continue;
  }
  if(cp=='=')
  {
   word[i++]=cp;
   cp=fgetc(in);
   if(cp=='=')
   {
    word[i++]=cp;
    word[i]='\0';
    fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',39,')');
    cp=fgetc(in);
   }
   else
   {
    word[i]='\0';
    fprintf(out,"%c其他运算符：%c%s%c,%d%c\n",'(','"',word,'"',27,')');
   }
   continue;
  }
  if(cp=='<')
  {
   word[i++]=cp;
   cp=fgetc(in);
   if(cp=='=')
   {
    word[i++]=cp;
    word[i]='\0';
    fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',36,')');
    cp=fgetc(in);
   }
   else
   {
    word[i]='\0';
    fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',35,')');
   }
   continue;
  }
  if(cp=='>')
  {
   word[i++]=cp;
   cp=fgetc(in);
   if(cp=='=')
   {
    word[i++]=cp;
    word[i]='\0';
    fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',38,')');
    cp=fgetc(in);
   }
   else
   {
    word[i]='\0';
    fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',37,')');
   }
   continue;
  }
  if(cp=='!')
  {
   word[i++]=cp;
   cp=fgetc(in);
   if(cp=='=')
   {
    word[i++]=cp;
    word[i]='\0';
    fprintf(out,"%c运算符：%c%s%c,%d%c\n",'(','"',word,'"',40,')');
    cp=fgetc(in);
   }
   else
   {
    word[i]='\0';
    fprintf(out,"%s%c%s%c%s\n","error: ",'"',word,'"',"不是合法的标识符");
   }
   continue;
  }
  /*界符*/
  if(cp==';')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',41,')');
   cp=fgetc(in);
   continue;
  }
  if(cp==':')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',42,')');
   cp=fgetc(in);
   continue;
  }
  if(cp==',')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',43,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='{')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',44,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='}')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',45,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='[')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',46,')');
   cp=fgetc(in);
   continue;
  }
  if(cp==']')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',47,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='(')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',48,')');
   cp=fgetc(in);
   continue;
  }
  if(cp==')')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c分隔符：%c%s%c,%d%c\n",'(','"',word,'"',49,')');
   cp=fgetc(in);
   continue;
  }
  /*不能识别的字符*/
  word[i++]=cp;
  cp=fgetc(in);
  word[i]='\0';
  fprintf(out,"%s%c%s%c%s\n","error: ",'"',word,'"',"不是合法的标识符");
 }

 fclose(in);
 fclose(out);
 printf("成功对in.txt文档内代码进行词法分析，分析结果保存在out.txt文档中\n");
 return 0;
 }