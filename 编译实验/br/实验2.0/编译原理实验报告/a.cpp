#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 500  /*��ʶ������󳤶�*/

main()
{
 FILE *in,*out;

 char word[MAX];   /*�洢��ʶ��*/
 char cp;    /*�洢��ǰ�����ַ�*/
 int i;
 int j;
 int t;
 if((in=fopen("in.txt","r"))==NULL)
 {
  printf("���ܴ��ĵ�in.txt�������Ŀ¼���Ƿ���ڸ��ĵ�\n");
  exit(0);
 }
 else
 {
  printf("�ɹ����ĵ�in.txt\n");
 }

 if((out=fopen("out.txt","w"))==NULL)
 {
  printf("���ܴ��ĵ�out.txt�������Ŀ¼���Ƿ���ڸ��ĵ�\n");
  exit(0);
 }
 else
 {
  printf("�ɹ����ĵ�out.txt\n");
 }

 cp=fgetc(in);
 while(cp!=EOF)
 {
  /*���ĵ��ո��Ʊ�������з�*/
  while(cp==' '||cp=='\t'||cp=='\n')
  {
   cp=fgetc(in);
  }

  /*cp���鸴λ*/
  i=0;

  /*���ּ��*/
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
              fprintf(out,"error:'%s',���ǺϷ��ĳ���\n",word); 
             else fprintf(out,"%c������%c%s%c,%d%c\n",'(','"',word,'"',28,')');
		}
		else fprintf(out,"error:'%s',���ǺϷ��ĳ���\n",word);
   }
   else
   {
    while(cp!=' '&&cp!='\t'&&cp!='\n'&&cp!='='&&cp!='+'&&cp!='-'&&cp!='*'&&cp!='/'&&cp!='>'&&cp!='<'&&cp!='!'&&cp!=';'&&cp!=':'&&cp!=','&&cp!='{'&&cp!='}'&&cp!='['&&cp!=']'&&cp!='('&&cp!=')')
    {
     word[i++]=cp;
     cp=fgetc(in);
    }
    word[i]='\0';
    fprintf(out,"%s%c%s%c%s\n","error: ",'"',word,'"',"���ǺϷ��ı�ʶ��");
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
       fprintf(out,"error:'%s',���ǺϷ��ĳ���\n",word);
	   continue;
  }

  /*�ַ������*/
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
    /*���������ּ��*/
    if(strcmp(word,"main")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',1,')');
    else if(strcmp(word,"void")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',2,')');
    else if(strcmp(word,"int")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',3,')');
    else if(strcmp(word,"float")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',4,')');
    else if(strcmp(word,"double")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',5,')');
    else if(strcmp(word,"char")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',6,')');
    else if(strcmp(word,"struct")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',7,')');
      else if(strcmp(word,"const")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',8,')');
    else if(strcmp(word,"extern")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',9,')');
    else if(strcmp(word,"register")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',10,')');
    else if(strcmp(word,"static")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',11,')');
    else if(strcmp(word,"if")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',12,')');
    else if(strcmp(word,"else")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',13,')');
    else if(strcmp(word,"switch")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',14,')');
     else if(strcmp(word,"case")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',15,')');
    else if(strcmp(word,"for")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',16,')');
    else if(strcmp(word,"do")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',17,')');
    else if(strcmp(word,"while")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',18,')');
    else if(strcmp(word,"goto")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',19,')');
    else if(strcmp(word,"continue")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',20,')');
    else if(strcmp(word,"break")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',21,')');
      else if(strcmp(word,"default")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',22,')');
    else if(strcmp(word,"sizeof")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',23,')');
    else if(strcmp(word,"return")==0)
     fprintf(out,"%c�ؼ��֣�%c%s%c,%d%c\n",'(','"',word,'"',24,')');
    else
     fprintf(out,"%c�Զ����ʶ��:%c%s%c,%d%c\n",'(','"',word,'"',29,')');
   }

   /*�Ŵ���ֻ������ĸ�����֡��»��߹��ɣ�*/
   else
   {
     while(cp!=' '&&cp!='\t'&&cp!='\n'&&cp!='='&&cp!='+'&&cp!='-'&&cp!='*'&&cp!='/'&&cp!='>'&&cp!='<'&&cp!='!'&&cp!=';'&&cp!=':'&&cp!=','&&cp!='{'&&cp!='}'&&cp!='['&&cp!=']'&&cp!='('&&cp!=')')
     {
      word[i++]=cp;
      cp=fgetc(in);
     }
     word[i]='\0';
     fprintf(out,"%s%c%s%c%s\n","error: ",'"',word,'"',"���ǺϷ��ı�ʶ��");
   }
   continue;
  }

  /*�����*/
  if(cp=='#')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',50,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='+')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',31,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='-')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',32,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='*')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',33,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='/')//�ж��Ƿ���ע�ͣ�����Ҫ�Թ���
  {
       word[i++]=cp;
        cp=fgetc(in);
     if(cp=='*'){word[--i]='\0';while(cp!='/'){cp=fgetc(in);}cp=fgetc(in);}
     else
         fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',34,')');
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
    fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',39,')');
    cp=fgetc(in);
   }
   else
   {
    word[i]='\0';
    fprintf(out,"%c�����������%c%s%c,%d%c\n",'(','"',word,'"',27,')');
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
    fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',36,')');
    cp=fgetc(in);
   }
   else
   {
    word[i]='\0';
    fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',35,')');
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
    fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',38,')');
    cp=fgetc(in);
   }
   else
   {
    word[i]='\0';
    fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',37,')');
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
    fprintf(out,"%c�������%c%s%c,%d%c\n",'(','"',word,'"',40,')');
    cp=fgetc(in);
   }
   else
   {
    word[i]='\0';
    fprintf(out,"%s%c%s%c%s\n","error: ",'"',word,'"',"���ǺϷ��ı�ʶ��");
   }
   continue;
  }
  /*���*/
  if(cp==';')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',41,')');
   cp=fgetc(in);
   continue;
  }
  if(cp==':')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',42,')');
   cp=fgetc(in);
   continue;
  }
  if(cp==',')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',43,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='{')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',44,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='}')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',45,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='[')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',46,')');
   cp=fgetc(in);
   continue;
  }
  if(cp==']')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',47,')');
   cp=fgetc(in);
   continue;
  }
  if(cp=='(')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',48,')');
   cp=fgetc(in);
   continue;
  }
  if(cp==')')
  {
   word[i++]=cp;
   word[i]='\0';
   fprintf(out,"%c�ָ�����%c%s%c,%d%c\n",'(','"',word,'"',49,')');
   cp=fgetc(in);
   continue;
  }
  /*����ʶ����ַ�*/
  word[i++]=cp;
  cp=fgetc(in);
  word[i]='\0';
  fprintf(out,"%s%c%s%c%s\n","error: ",'"',word,'"',"���ǺϷ��ı�ʶ��");
 }

 fclose(in);
 fclose(out);
 printf("�ɹ���in.txt�ĵ��ڴ�����дʷ��������������������out.txt�ĵ���\n");
 return 0;
 }