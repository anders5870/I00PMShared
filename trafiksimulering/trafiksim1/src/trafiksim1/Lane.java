package trafiksim1;


public class Lane {

    private Car theLane[];

    public static class OverflowException extends RuntimeException {
    // Undantag som kastas när det inte gick att lägga 
    // in en ny bil på vägen
    }

    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats för n fordon
        this.theLane = new Car[n];
    	
    }


    public void step(Lane sideLane) {
    	for(int i = 0; i < theLane.length-1; i++){
    	    //se till så att det finns en bil och kolla om bilen i theLane vill svänga
    		if (theLane[i] != null){
    			if (theLane[i].getTurn())
    				//kolla om det går att svänga
    				if(sideLane.theLane[i] == null){
    				//sväng
    				sideLane.theLane[i] = theLane[i];
    				theLane[i] = null;
    				}
    			//kolla om bilen i sideLane vill svänga
    			if(sideLane.theLane[i].getTurn())
    				//kolla om det går att svänga
    				if(theLane[i] == null){
    				//sväng
    				theLane[i] = sideLane.theLane[i];
    				sideLane.theLane[i] = null;
    				}
    		}
    		
        	// Stega fram alla fordon (utom det på plats 0) ett steg 
            // (om det går). (Fordonet på plats 0 tas bort utifrån 
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
