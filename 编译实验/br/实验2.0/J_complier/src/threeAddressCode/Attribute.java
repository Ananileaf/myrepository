package threeAddressCode;

import java.util.List;

public class Attribute {

	public int first;
	public int falseEntry;
	public int trueEntry;
	public String addr="";
	public List<Integer> nextList;
	
	public Attribute()
	{
		this.first = -1;
		this.falseEntry = -1;
		this.trueEntry = -1;
		this.addr = "";
		this.nextList = null;
	}
	public String toString()
	{
		return addr;
	}
}
