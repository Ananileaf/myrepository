package func_syn;

import java.io.FileWriter;
import java.io.IOException;

/**
 * 存储语法分析表中的每个状态是转移情况(不包含任何文法信息)
 * ***/
public class ItemSetCluster {
	public State[] state = new State[40];
	
	ItemSetCluster()
	{
		state[0] = new State(0);
		state[0].act.action.put("id", new Pair('r',4));
		state[0].act.action.put("if", new Pair('r',4));
		state[0].act.action.put("while", new Pair('r',4));
		state[0].act.action.put("begin", new Pair('r',4));
		state[0].act.action.put("end", new Pair('r',4));
		state[0].act.action.put("$", new Pair('r',4));
		state[0].go_to._goto.put("program", 1);
		state[0].go_to._goto.put("stmts", 2);
		//S1
		state[1] = new State(1);
		state[1].act.action.put("$", new Pair('r',1));
		//S2		
		state[2] = new State(2);
		state[2].act.action.put("id", new Pair('s',4));
		state[2].act.action.put("if", new Pair('s',5));
		state[2].act.action.put("while", new Pair('s',6));
		state[2].act.action.put("begin", new Pair('s',7));
		state[2].act.action.put("$", new Pair('r',2));
		state[2].go_to._goto.put("stmt", 3);
		//S3	
		state[3] = new State(3);
		state[3].act.action.put("id", new Pair('r',3));
		state[3].act.action.put("if", new Pair('r',3));
		state[3].act.action.put("while", new Pair('r',3));
		state[3].act.action.put("begin", new Pair('r',3));
		state[3].act.action.put("end", new Pair('r',3));
		state[3].act.action.put("$", new Pair('r',3));
		//S4
		state[4] = new State(4);
		state[4].act.action.put(":=", new Pair('s',8));
		//S5
		state[5] = new State(5);
		state[5].act.action.put("(", new Pair('s',9));
		//S6
		state[6] = new State(6);
		state[6].act.action.put("(", new Pair('s',10));
		//S7
		state[7] = new State(7);
		state[7].act.action.put("id", new Pair('r',4));
		state[7].act.action.put("if", new Pair('r',4));
		state[7].act.action.put("while", new Pair('r',4));
		state[7].act.action.put("begin", new Pair('r',4));
		state[7].act.action.put("end", new Pair('r',4));
		state[7].act.action.put("$", new Pair('r',4));
		state[7].go_to._goto.put("stmts", 11);
		//S8
		state[8] = new State(8);
		state[8].act.action.put("id", new Pair('s',15));
		state[8].act.action.put("num", new Pair('s',16));
		state[8].go_to._goto.put("expr", 12);
		state[8].go_to._goto.put("term", 13);
		state[8].go_to._goto.put("factor", 14);
		//S9
		state[9] = new State(9);
		state[9].act.action.put("id", new Pair('s',15));
		state[9].act.action.put("num", new Pair('s',16));
		state[9].go_to._goto.put("expr", 12);
		state[9].go_to._goto.put("bool", 17);
		state[9].go_to._goto.put("term", 13);
		state[9].go_to._goto.put("factor", 14);
		//S10		
		state[10] = new State(10);
		state[10].act.action.put("id", new Pair('s',15));
		state[10].act.action.put("num", new Pair('s',16));
		state[10].go_to._goto.put("expr", 12);
		state[10].go_to._goto.put("bool", 18);
		state[10].go_to._goto.put("term", 13);
		state[10].go_to._goto.put("factor", 14);
		//S11
		state[11] = new State(11);
		state[11].act.action.put("id", new Pair('s',4));
		state[11].act.action.put("if", new Pair('s',5));
		state[11].act.action.put("while", new Pair('s',6));
		state[11].act.action.put("begin", new Pair('s',7));
		state[11].act.action.put("end", new Pair('s',19));
		state[11].go_to._goto.put("stmt", 3);
		//S12
		state[12] = new State(12);
		state[12].act.action.put("<=", new Pair('s',20));
		state[12].act.action.put(">", new Pair('s',21));
		state[12].act.action.put("+", new Pair('s',22));
		state[12].act.action.put("-", new Pair('s',23));
		state[12].act.action.put(";", new Pair('s',38));
		//S13
		state[13] = new State(13);
		state[13].act.action.put("<=", new Pair('r',14));
		state[13].act.action.put(">", new Pair('r',14));
		state[13].act.action.put("+", new Pair('r',14));
		state[13].act.action.put("-", new Pair('r',14));
		state[13].act.action.put("*", new Pair('s',24));
		state[13].act.action.put("/", new Pair('s',25));
		state[13].act.action.put(";", new Pair('r',14));
		state[13].act.action.put(")", new Pair('r',14));
		//S14
		state[14] = new State(14);
		state[14].act.action.put("<=", new Pair('r',17));
		state[14].act.action.put(">", new Pair('r',17));
		state[14].act.action.put("+", new Pair('r',17));
		state[14].act.action.put("-", new Pair('r',17));
		state[14].act.action.put("*", new Pair('r',17));
		state[14].act.action.put("/", new Pair('r',17));
		state[14].act.action.put(";", new Pair('r',17));
		state[14].act.action.put(")", new Pair('r',17));
		//S15
		state[15] = new State(15);
		state[15].act.action.put("<=", new Pair('r',18));
		state[15].act.action.put(">", new Pair('r',18));
		state[15].act.action.put("+", new Pair('r',18));
		state[15].act.action.put("-", new Pair('r',18));
		state[15].act.action.put("*", new Pair('r',18));
		state[15].act.action.put("/", new Pair('r',18));
		state[15].act.action.put(";", new Pair('r',18));
		state[15].act.action.put(")", new Pair('r',18));
		//S16
		state[16] = new State(16);
		state[16].act.action.put("<=", new Pair('r',19));
		state[16].act.action.put(">", new Pair('r',19));
		state[16].act.action.put("+", new Pair('r',19));
		state[16].act.action.put("-", new Pair('r',19));
		state[16].act.action.put("*", new Pair('r',19));
		state[16].act.action.put("/", new Pair('r',19));
		state[16].act.action.put(";", new Pair('r',19));
		state[16].act.action.put(")", new Pair('r',19));
		//S17		
		state[17] = new State(17);
		state[17].act.action.put(")", new Pair('s',26));
		//S18
		state[19] = new State(19);
		state[19].act.action.put("id", new Pair('r',9));
		state[19].act.action.put("if", new Pair('r',9));
		state[19].act.action.put("else", new Pair('r',9));
		state[19].act.action.put("while", new Pair('r',9));
		state[19].act.action.put("begin", new Pair('r',9));
		state[19].act.action.put("end", new Pair('r',9));
		state[19].act.action.put("$", new Pair('r',9));
		//S18
		state[18] = new State(18);
		state[18].act.action.put(")", new Pair('s',27));
		
		state[20] = new State(20);
		state[20].act.action.put("id", new Pair('s',15));
		state[20].act.action.put("num", new Pair('s',16));
		state[20].go_to._goto.put("expr",28);
		state[20].go_to._goto.put("term", 13);
		state[20].go_to._goto.put("factor", 14);
		
		state[21] = new State(21);
		state[21].act.action.put("id", new Pair('s',15));
		state[21].act.action.put("num", new Pair('s',16));
		state[21].go_to._goto.put("expr",29);
		state[21].go_to._goto.put("term", 13);
		state[21].go_to._goto.put("factor", 14);
		
		state[22] = new State(22);
		state[22].act.action.put("id", new Pair('s',15));
		state[22].act.action.put("num", new Pair('s',16));
		state[22].go_to._goto.put("term", 30);
		state[22].go_to._goto.put("factor", 14);
		
		state[23] = new State(23);
		state[23].act.action.put("id", new Pair('s',15));
		state[23].act.action.put("num", new Pair('s',16));
		state[23].go_to._goto.put("term", 31);
		state[23].go_to._goto.put("factor", 14);
		
		state[24] = new State(24);
		state[24].act.action.put("id", new Pair('s',15));
		state[24].act.action.put("num", new Pair('s',16));
		state[24].go_to._goto.put("factor", 32);
		
		state[25] = new State(25);
		state[25].act.action.put("id", new Pair('s',15));
		state[25].act.action.put("num", new Pair('s',16));
		state[25].go_to._goto.put("factor", 33);
		
		state[26] = new State(26);
		state[26].act.action.put("id", new Pair('s',4));
		state[26].act.action.put("if", new Pair('s',5));
		state[26].act.action.put("while", new Pair('s',6));
		state[26].act.action.put("begin", new Pair('s',7));
		state[26].go_to._goto.put("stmt", 34);
		
		state[27] = new State(27);
		state[27].act.action.put("id", new Pair('s',4));
		state[27].act.action.put("if", new Pair('s',5));
		state[27].act.action.put("while", new Pair('s',6));
		state[27].act.action.put("begin", new Pair('s',7));
		state[27].go_to._goto.put("stmt", 35);
		
		state[28] = new State(28);
		state[28].act.action.put("+", new Pair('s',22));
		state[28].act.action.put("-", new Pair('s',23));
		state[28].act.action.put(")", new Pair('r',10));
		
		state[29] = new State(29);
		state[29].act.action.put("+", new Pair('s',22));
		state[29].act.action.put("-", new Pair('s',23));
		state[29].act.action.put(")", new Pair('r',11));
		
		
		state[30] = new State(30);
		state[30].act.action.put("<=", new Pair('r',12));
		state[30].act.action.put(">", new Pair('r',12));
		state[30].act.action.put("+", new Pair('r',12));
		state[30].act.action.put("-", new Pair('r',12));
		state[30].act.action.put("*", new Pair('s',24));
		state[30].act.action.put("/", new Pair('s',25));
		state[30].act.action.put(";", new Pair('r',12));
		state[30].act.action.put(")", new Pair('r',12));
		
		state[31] = new State(31);
		state[31].act.action.put("<=", new Pair('r',13));
		state[31].act.action.put(">", new Pair('r',13));
		state[31].act.action.put("+", new Pair('r',13));
		state[31].act.action.put("-", new Pair('r',13));
		state[31].act.action.put("*", new Pair('s',24));
		state[31].act.action.put("/", new Pair('s',25));
		state[31].act.action.put(";", new Pair('r',13));
		state[31].act.action.put(")", new Pair('r',13));
		
		state[32] = new State(32);
		state[32].act.action.put("<=", new Pair('r',15));
		state[32].act.action.put(">", new Pair('r',15));
		state[32].act.action.put("+", new Pair('r',15));
		state[32].act.action.put("-", new Pair('r',15));
		state[32].act.action.put("*", new Pair('r',15));
		state[32].act.action.put("/", new Pair('r',15));
		state[32].act.action.put(";", new Pair('r',15));
		state[32].act.action.put(")", new Pair('r',15));
		
		state[33] = new State(33);
		state[33].act.action.put("<=", new Pair('r',16));
		state[33].act.action.put(">", new Pair('r',16));
		state[33].act.action.put("+", new Pair('r',16));
		state[33].act.action.put("-", new Pair('r',16));
		state[33].act.action.put("*", new Pair('r',16));
		state[33].act.action.put("/", new Pair('r',16));
		state[33].act.action.put(";", new Pair('r',16));
		state[33].act.action.put(")", new Pair('r',16));
	
	/*	state[34] = new State(34);
		state[34].act.action.put("id", new Pair('r',6));
		state[34].act.action.put("if", new Pair('r',6));
		state[34].act.action.put("else", new Pair('s',36));
		state[34].act.action.put("while", new Pair('r',6));
		state[34].act.action.put("begin", new Pair('r',6));
		state[34].act.action.put("end", new Pair('r',6));
		state[34].act.action.put("$", new Pair('r',6));*/
		
		state[34] = new State(34);
		state[34].act.action.put("id", new Pair('r',6));
		state[34].act.action.put("if", new Pair('r',6));
		state[34].act.action.put("else", new Pair('r',20));/////
		state[34].act.action.put("while", new Pair('r',6));
		state[34].act.action.put("begin", new Pair('r',6));
		state[34].act.action.put("end", new Pair('r',6));
		state[34].act.action.put("$", new Pair('r',6));
		state[34].go_to._goto.put("N", 39);///////
		
		state[35] = new State(35);
		state[35].act.action.put("id", new Pair('r',8));
		state[35].act.action.put("if", new Pair('r',8));
		state[35].act.action.put("else", new Pair('r',8));
		state[35].act.action.put("while", new Pair('r',8));
		state[35].act.action.put("begin", new Pair('r',8));
		state[35].act.action.put("end", new Pair('r',8));
		state[35].act.action.put("$", new Pair('r',8));
		
		state[36] = new State(36);
		state[36].act.action.put("id", new Pair('s',4));
		state[36].act.action.put("if", new Pair('s',5));
		state[36].act.action.put("while", new Pair('s',6));
		state[36].act.action.put("begin", new Pair('s',7));
		state[36].go_to._goto.put("stmt", 37);
		

		state[37] = new State(37);
		state[37].act.action.put("id", new Pair('r',7));
		state[37].act.action.put("if", new Pair('r',7));
		state[37].act.action.put("else", new Pair('r',7));
		state[37].act.action.put("while", new Pair('r',7));
		state[37].act.action.put("begin", new Pair('r',7));
		state[37].act.action.put("end", new Pair('r',7));
		state[37].act.action.put("$", new Pair('r',7));
		
		state[38] = new State(38);
		state[38].act.action.put("id", new Pair('r',5));
		state[38].act.action.put("if", new Pair('r',5));
		state[38].act.action.put("else", new Pair('r',5));
		state[38].act.action.put("while", new Pair('r',5));
		state[38].act.action.put("begin", new Pair('r',5));
		state[38].act.action.put("end", new Pair('r',5));
		state[38].act.action.put("$", new Pair('r',5));
		
		state[39] = new State(39);
		state[39].act.action.put("else", new Pair('s',36));

	}
	public static void main(String[] args) throws IOException
	{
		ItemSetCluster itemSet = new ItemSetCluster();
		State tmp[] = itemSet.state;
		
	/*	if(null == tmp[0].act.action.get("id"))
			System.out.println("null");
		else
			System.out.println(tmp[0].act.action.get("id"));
		*/
	//	System.out.println(tmp.length);
		FileWriter out = new FileWriter("c:\\out.txt");
		
		String[] terminal={"id","num","if","else","while","begin","end",
				":=","<=",">","+","-","*","/",";","(",")","$"};
		String[] nonTerminal={"program","stmts","stmt","expr",
				"bool","term","factor"};

		

		
		
		out.write("状态\t id\t num\t if\t else\t while\t begin\t end\t "
				+ ":=\t <=\t >\t +\t -\t *\t /\t ;\t (\t )\t $\t "
				+ "program\t stmts\t stmt\t expr\t bool\t term\t factor\t"
				+ "\r\n");
		for(int i = 0;i<tmp.length;i++)
		{
			out.write(tmp[i].stateNumber+"\t");
			
			for(int j = 0;j<terminal.length;j++)
			{
				if(tmp[i].act.action.get(terminal[j]) == null)
				{
					out.write("\t");
				//	System.out.println(i+" "+ terminal[j]);
				}
				else
					out.write(tmp[i].act.action.get(terminal[j]).toString()+"\t");
			}
			for(int j = 0;j<nonTerminal.length;j++)
			{
				if(tmp[i].go_to._goto.get(nonTerminal[j]) == null)
				{
					out.write("\t");
				//	System.out.println(i+" "+ nonTerminal[j]);
				}
				else
					out.write(tmp[i].go_to._goto.get(nonTerminal[j])+"\t");
			}	
			out.write("\r\n");
		}
		out.flush();
		out.close();
	}
}