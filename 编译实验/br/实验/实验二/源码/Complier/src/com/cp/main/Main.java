package com.cp.main;

/**
 *  @author qdl
 *
 */
/*
 test01:
WHILE (next<>NIL)  
--sort by index
DO BEGIN x:=0x1AG; 
Y:=xy-z END;
  
  test02:
while(next=NIL)
x=1234567890;
y=x*(1/2);
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa=1;
aaaaaaaaa
  
 */
/**
 * 
 * 文法
 * 1、  关键字、标识符、数字等：
1.begin  2.if  3.then   4.while  5.do  6.end   10.标识符id   11.整数 num
13.+   14.-   15.*     16./    17.:     18.:=     20.<      21.<>
22.<=    23.>    24.>=     25.=      26.;      27.(      28.)

2、  文法规则:

程序 → begin 语句串 end
语句串 → 语句 { ; 语句 }
语句 → 赋值语句 | 条件语句 | 循环语句
赋值语句 → 变量 := 表达式
条件语句 → if 条件 then ( 语句 | 程序 )
循环语句 → while 条件 do ( 语句 | 程序 )
表达式 → 项 { + 项 | - 项 }
条件 → 表达式 关系符 表达式
关系符 → < | <> | <= | > | >= | =
项 → 因子 { * 因子 | / 因子 }
因子 → 变量 | 数字 | ( 表达式 )
变量 → 标识符 
 *
 */
public class Main {

	public Main() {
		// TODO Auto-generated constructor stub
	}
}
