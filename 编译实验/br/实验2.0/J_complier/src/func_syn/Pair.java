package func_syn;

public class Pair {
	char actionType;// 'r' �����Լ�� ��s'��������
	int n;//��Լ����ʱ��n�����Լ���õĲ���ʽ��s��������ת����״̬
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
