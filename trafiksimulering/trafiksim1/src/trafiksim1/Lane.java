package trafiksim1;


public class Lane {

    private Car theLane[];
    private int numberOfTurns = 0;
    public static class OverflowException extends RuntimeException {
    // Undantag som kastas när det inte gick att lägga 
    // in en ny bil på vägen
    }

    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats för n fordon
        this.theLane = new Car[n];
    	
    }
    //help function to step()
	private void turnAttempt(Lane sideLane, int i){
		//se till så att det finns en bil och kolla om den vill svänga
		if (theLane[i] != null){
			if (theLane[i].getTurn()){
				System.out.println("kommer hit");
				//kolla om det går att svänga
				if(sideLane.theLane[i] == null){
				//sväng
				System.out.println("en bil har svängt");
				sideLane.theLane[i] = theLane[i];
				theLane[i] = null;
				numberOfTurns++;
				}
			}
		}
		
	}
	//help function to step()
	private void stepWait(int i){
    	//theLane step/wait 		
		if (i != 0 && theLane[i+1] == null){
			if(theLane[i] == null){
        		theLane[i] = theLane[i+1];
            	theLane[i+1]=null; 
			}
		}
		else{
			if (theLane[i+1] != null){
				if (!theLane[i+1].getTurn()){
	    			if(theLane[i] == null){
	            		theLane[i] = theLane[i+1];
	                	theLane[i+1]=null; 
	    			}
				}
			}
		}
	}

    public void step(Lane sideLane) {
    	for(int i = 0; i < theLane.length-1; i++){
    		this.turnAttempt(sideLane, i);			
    		sideLane.turnAttempt(this, i);
    		this.stepWait(i);
    		sideLane.stepWait(i);	
    	}	
    }
    
    public int getLen(){
    	return theLane.length;
    }
    
    public void step(){
    	for(int i = 0; i < theLane.length-1; i++){
			if(theLane[i] == null){
        		theLane[i] = theLane[i+1];
            	theLane[i+1]=null;
        	}
    	}
    }

    public Car getFirst(){
    	
    	Car firstcar = theLane[0];
    	theLane[0] = null;
    	return firstcar;
	// Returnera och tag bort bilen som står först
    }

    public Car firstCar() {
    	return theLane[0];
	// Returnera bilen som stï¿½r fï¿½rst utan att ta bort den
    }


    public boolean lastFree() {
    	return(theLane[theLane.length-1] == null);
	// Returnera true om sista platsen ledig, annars false
    }

    public void putLast(Car c) throws OverflowException {
    	if (lastFree()) {
    		theLane[theLane.length - 1] = c;
    	}
    	else{throw new OverflowException();
    	}
    	
    // Ställ en bil på sista platsen på vägen
	// (om det går).
    }

    public boolean laneFull () {
        for(int i = 0; i < theLane.length; i++){
            
            if(theLane[i] == null) { return false; } 

        }
        return true;
    }
    
    public int getNumberOfMisplacedCars(){
    	int j = 0;
    	for(int i = 0; theLane.length > i; i++){
    		if (theLane[i] != null)
    			if (theLane[i].getTurn()) j++;
    	}
    	return j;
    }
    
    public boolean isVacant(int index){
    	if ((theLane[index]) == null)
    		return true;
    	else return false;
    }
    
    public int getNumberOfTurns(){
    	return this.numberOfTurns;
    }

    public String toString() {
    	String lane = "";
    	for(int i=0; i<theLane.length; i++) {
    		if(theLane[i]== null) {
    			lane = lane + "---";
    		} else {
                lane = lane + theLane[i].toString();   
    		
    		}
    	}
        return lane;
    }
}
