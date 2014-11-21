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
    	for(int i = theLane.length; i > 0; i--){
    	    //kolla om bilen i theLane vill svänga
    		if(theLane[i].getTurn())
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
        	// Stega fram alla fordon (utom det på plats 0) ett steg 
            // (om det går). (Fordonet på plats 0 tas bort utifrån 
    		// mha getFirst().)
			if(theLane[i] == null){
        		theLane[i] = theLane[i+1];
            	theLane[i+1]=null;
        	}
			if(sideLane.theLane[i] == null){
        		sideLane.theLane[i] = sideLane.theLane[i+1];
            	sideLane.theLane[i+1]=null;
        	}
    	}
    	

    }
    
    public void step(){
    	for(int i = theLane.length; i > 0; i--){
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
    	
    // Stï¿½ll en bil pï¿½ sista platsen pï¿½ vï¿½gen
	// (om det gï¿½r).
    }

    public int laneFull () {
        for(int i = 0; i < theLane.length; i++){
            
            if(theLane[i] == null) { return 0; } 

        }
        return 1;
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
