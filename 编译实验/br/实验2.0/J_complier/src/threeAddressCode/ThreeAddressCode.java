package threeAddressCode;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class ThreeAddressCode {
	static public int currentLabel = 100;
	static public int nextLabel = 101;
	
	private Map<Integer,String> threeAddressCodeList = new TreeMap<Integer,String>();
	
	/**添加新的三地址码***/
	public void addNewThreeAddrCode(String s)
	{
		threeAddressCodeList.put(currentLabel, s);
		
		currentLabel = nextLabel ++;
	}
	
	/**回填，只回填一条指令
	 * 将destLabel回填到label所指向的三个地址码的尾部
	 * **/
	public void backPatch(int label,int destLabel)
	{
		if(label == -1)
			return ;
		String code = threeAddressCodeList.get(label);
		if(code == null)
		{
			System.out.println("回填错误，找不到指定标号的三地址码!");
			return ;
		}
		
		code += Integer.toString(destLabel);
		threeAddressCodeList.put(label, code);
	}
	/**
	 * 功能与上面一函数一样，但是回填多条指令
	 * ***/
	public void backPatch(List<Integer> label,int destLabel)
	{
		if(label == null)
			return ;
		Iterator<Integer> iter = label.iterator();
		while(iter.hasNext())
		{
			backPatch(iter.next(),destLabel);
		}
	
	}

	
	/**
	 * 输出三地址码
	 * 
	 */
	public String outThreeAddrCode()
	{
		String reString="";
		for(int i = 100;i<ThreeAddressCode.currentLabel;i++)
		{
			System.out.print(i+":");
			reString+=(i+":");
			System.out.println(threeAddressCodeList.get(i));
			reString+=(threeAddressCodeList.get(i)+"\n");
		}
		return reString;
	}
	public static void main(String args[])
	{
		ThreeAddressCode t = new ThreeAddressCode();
		
		t.addNewThreeAddrCode("if a<b goto");
		t.addNewThreeAddrCode("goto ");
		t.addNewThreeAddrCode("if a>b goto ");
		t.addNewThreeAddrCode("if a>3 goto ");
		t.addNewThreeAddrCode("if 3>b goto ");
		t.addNewThreeAddrCode("if 33>b goto ");

		
		t.outThreeAddrCode();
	}
}
