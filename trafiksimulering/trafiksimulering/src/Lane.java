
public class Lane {

    public static class OverflowException extends RuntimeException {
        // Undantag som kastas n�r det inte gick att l�gga 
        // in en ny bil p� v�gen
    }

    protected CarPosition[] theLane;

    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats f�r n fordon
    // Samt l�nker ihop varje CarPosition med forward f�r den framf�r
    }
    
    public boolean matchEnd(CarPosition target)
    {
    	if(theLane[0] == target)
    		return true;
    	else
    		return false;
    }
    
    public int getLength(){
    	return theLane.length;
    }
    
    public void setParallel(Lane sideLane)
    {
    	int i = 0;
    	
    	while(i < sideLane.getLength() && i < theLane.length)
    	{
    		theLane[i].setTurn(sideLane.theLane[i]);
    		i++;
    	}
    }

    public void step() {
	// Stega fram alla fordon (utom det p� plats 0) ett steg 
        // (om det g�r). (Fordonet p� plats 0 tas bort utifr�n 
	// mm h a metoden nedan.)
    	
    	for (int i = 0; i<getLength()-1;i++){
    		if(theLane[i] == null) theLane[i+1].moveForward();
    		//else do nothing
    	}	
    }   

    public CarPosition getFirst() {
    	CarPosition temp = theLane[0];
    	theLane[0] = null;
    	return temp;
	// Returnera och tag bort bilen som st�r f�rst
    }

    public CarPosition firstCar() {
    		return theLane[0];
	// Returnera bilen som st�r f�rst utan att ta bort den
    }


    public boolean lastFree() {
    	return false;
	// Returnera true om sista platsen ledig, annars false
    }

    public void putLast(Car c) throws OverflowException {
    	if (lastFree()){
    		CarPosition temp = new CarPosition(this, c);
    		temp = theLane[this.getLength()-1];
    	}
	// St�ll en bil p� sista platsen p� v�gen
	// (om det g�r).
    }
     
    public String toString(CarPosition[] lane) {
    	String string = null;
    	for (int i = 0;lane != null; i++){
    		if (lane[i] == null) string = string + "-[ ]-";
    		else string = string + "-[X]-";
    	}
    	return string;
    	//...
    	}

}