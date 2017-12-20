package threeAddressCode;

public class TempVarGenerator {
	private static int counter = 1;
	public static String newTemp()
	{
		String tmp = "t"+Integer.toString(counter ++);
		return tmp;
	}
}
