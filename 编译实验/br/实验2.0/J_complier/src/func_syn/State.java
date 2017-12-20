package func_syn;

public class State {
	int stateNumber;
	Goto go_to = new Goto();
	Action act = new Action();
	public State(int num)
	{
		this.stateNumber = num;
	}
}
