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
	
	/**����µ�����ַ��***/
	public void addNewThreeAddrCode(String s)
	{
		threeAddressCodeList.put(currentLabel, s);
		
		currentLabel = nextLabel ++;
	}
	
	/**���ֻ����һ��ָ��
	 * ��destLabel���label��ָ���������ַ���β��
	 * **/
	public void backPatch(int label,int destLabel)
	{
		if(label == -1)
			return ;
		String code = threeAddressCodeList.get(label);
		if(code == null)
		{
			System.out.println("��������Ҳ���ָ����ŵ�����ַ��!");
			return ;
		}
		
		code += Integer.toString(destLabel);
		threeAddressCodeList.put(label, code);
	}
	/**
	 * ����������һ����һ�������ǻ������ָ��
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
	 * �������ַ��
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
