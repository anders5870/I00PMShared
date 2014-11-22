package trafiksim1;


public class Lane {

    private Car theLane[];

    public static class OverflowException extends RuntimeException {
    // Undantag som kastas n�r det inte gick att l�gga 
    // in en ny bil p� v�gen
    }

    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats f�r n fordon
        this.theLane = new Car[n];
    	
    }


    public void step(Lane sideLane) {
    	for(int i = 0; i < theLane.length-1; i++){
    	    //se till s� att det finns en bil och kolla om bilen i theLane vill sv�nga
    		if (theLane[i] != null){
    			if (theLane[i].getTurn())
    				//kolla om det g�r att sv�nga
    				if(sideLane.theLane[i] == null){
    				//sv�ng
    				sideLane.theLane[i] = theLane[i];
    				theLane[i] = null;
    				}
    			//kolla om bilen i sideLane vill sv�nga
    			if(sideLane.theLane[i].getTurn())
    				//kolla om det g�r att sv�nga
    				if(theLane[i] == null){
    				//sv�ng
    				theLane[i] = sideLane.theLane[i];
    				sideLane.theLane[i] = null;
    				}
    		}
    		
        	// Stega fram alla fordon (utom det p� plats 0) ett steg 
            // (om det g�r). (Fordonet p� plats 0 tas bort utifr�n 
    		// mha getFirst().    		
    		
			if(theLane[i] == null){ 
				//cars that still wants to turn wait at position 1
				if (i == 0){//first criteria to find the car at position 1
					if (theLane[i+1] != null){//check if there is a car at i+1
						//check if it wants to turn, if so don't move the car
						if (theLane[i+1].getTurn()){;}
						else{//else just step normally
							theLane[i] = theLane[i+1];
							theLane[i+1]=null;	
						}
					}
					else {//else just step normally
					theLane[i] = theLane[i+1];
					theLane[i+1]=null;
					}
				}
        	}
			if(sideLane.theLane[i] == null){//exactly as above but for the parallel lane
				//cars that still wants to turn wait at position 1
				if (i == 0){//first criteria to find the car at position 1
					if (sideLane.theLane[i+1] != null){//check if there is a car at i+1
						//check if it wants to turn, if so don't move the car
						if (sideLane.theLane[i+1].getTurn()){;}
						else{//else just step normally
							sideLane.theLane[i] = sideLane.theLane[i+1];
							sideLane.theLane[i+1]=null;	
						}
					}
					else {//else just step normally
					sideLane.theLane[i] = sideLane.theLane[i+1];
					sideLane.theLane[i+1]=null;
					}
				}
        	}
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
	// Returnera och tag bort bilen som st�r f�rst
    }

    public Car firstCar() {
    	return theLane[0];
	// Returnera bilen som st�r f�rst utan att ta bort den
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
    	
    // St�ll en bil p� sista platsen p� v�gen
	// (om det g�r).
    }

    public int laneFull () {
        for(int i = 0; i < theLane.length; i++){
            
            if(theLane[i] == null) { return 0; } 

        }
        return 1;
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
