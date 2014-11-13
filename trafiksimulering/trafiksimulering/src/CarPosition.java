// H�ller i en bil och k�nner till sina "grannar". 
public class CarPosition{
	
	private Car currentCar = null; // null om ingen bil finns p� positionen
	
	private Lane owner;
	
	private CarPosition forward;
	private CarPosition turn;
	
	public CarPosition(Lane a_Owner, Car currentCar)
	{
		owner = a_Owner;
		this.currentCar = currentCar;
	}
	
	public boolean isEnd(CarPosition target)
	{
		return owner.matchEnd(target);
	}
	
	public boolean moveForward()
	{
		if(forward.currentCar == null){
			forward.currentCar = this.currentCar;
			this.currentCar = null;
			return true;
		}
			return false;
		// Flytta bilen fram till forward
	}
	
	public boolean turn()
	{
		if(turn!=null && turn.currentCar == null){
			turn.currentCar = this.currentCar;
			this.currentCar = null;	
			return true;
		}
			return false;
		// Flytta bilen till turn
	}

	public void setTurn(CarPosition turn) {
		this.turn = turn;
	}

	public CarPosition getTurn() {
		return turn;
	}
	
	
}
