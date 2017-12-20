package func_syn;

public class Pair {
	char actionType;// 'r' 代表归约， ‘s'代表移入
	int n;//归约动作时，n代表归约所用的产生式，s代表所跳转到的状态
	Pair(char actionType,int n)
	{
		this.actionType = actionType;
		this.n = n;
	}
	
	public String toString()
	{
		if(actionType == 'r')
		{
			return "r"+Integer.toString(n);
		}
		else
			return "s"+Integer.toString(n);
	}
}
