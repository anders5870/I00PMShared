package trafiksim1;


public class Lane {

    private Car theLane[];
    private int numberOfTurns = 0;
    public static class OverflowException extends RuntimeException {
    // Undantag som kastas när det inte gick att lägga 
    // in en ny bil på vägen
    }


    /**  
     * @brief Constructor for Lane class.
     * @details constructs a Lane object with given parameters  
     * 
     * @param n the length of the lane 
     * 
     * @return an object Lane with given parameters.
    */
    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats för n fordon
        this.theLane = new Car[n];
    	
    }
    
    /**  
     * @brief Help method for step 
     * @details checks if the first position in the side lane is empty and puts a care there
     * 
     * @param sideLane the turn Lane 
     * @param i length of the turn lane 
     * 
    */
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
	/**  
     * @brief Help method for step 
     * @details checks if the first position in the side lane is empty. Waits if it is not and steps the lane 
     * 
     * @param i length of the lane 
     * 
    */
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

    /**  
     * @brief Method to step the lane 
     * @details steps sidelane
     * 
     * @param sideLane the turn lane 
     * 
    */
    public void step(Lane sideLane) {
    	for(int i = 0; i < theLane.length-1; i++){
    		this.turnAttempt(sideLane, i);			
    		sideLane.turnAttempt(this, i);
    		this.stepWait(i);
    		sideLane.stepWait(i);	
    	}	
    }
    
    
    /**  
     * @brief Method to get the length of the lane
     * @details 
     * 
     * @return the length of the lane 
     * 
    */
    public int getLen(){
    	return theLane.length;
    }
    

    /**  
     * @brief Method to step the lane 
     * @details steps lane 
     * 
     * @param 
     * 
    */
    public void step(){
    	for(int i = 0; i < theLane.length-1; i++){
			if(theLane[i] == null){
        		theLane[i] = theLane[i+1];
            	theLane[i+1]=null;
        	}
    	}
    }


    /**  
     * @brief Method to remove the first car
     * @details 
     * 
     * @return the first car 
     * 
    */
    public Car getFirst(){
    	
    	Car firstcar = theLane[0];
    	theLane[0] = null;
    	return firstcar;
	// Returnera och tag bort bilen som står först
    }


    /**  
     * @brief Method to return the first car without removing it 
     * @details 
     * 
     * @return the first car 
     * 
    */
    public Car firstCar() {
    	return theLane[0];
	// Returnera bilen som stï¿½r fï¿½rst utan att ta bort den
    }

    /**  
     * @brief Method to check if the last place in the lane is empty 
     * @details 
     * 
     * @return true if it is empty else false 
     * 
    */
    public boolean lastFree() {
    	return(theLane[theLane.length-1] == null);
	// Returnera true om sista platsen ledig, annars false
    }

    /**  
     * @brief Method put a car in the last place in the lane if it is empty
     * @details 
     * 
     * @param c is the car you want to insert into the sytstem 
     * 
    */

    public void putLast(Car c) throws OverflowException {
    	if (lastFree()) {
    		theLane[theLane.length - 1] = c;
    	}
    	else{throw new OverflowException();
    	}
    	
    // Ställ en bil på sista platsen på vägen
	// (om det går).
    }

    /**  
     * @brief Method to check if the lane is full
     * @details 
     * 
     * @return returns true if it is full else false 
     * 
    */
    public boolean laneFull () {
        for(int i = 0; i < theLane.length; i++){
            
            if(theLane[i] == null) { return false; } 

        }
        return true;
    }
    
    /**  
     * @brief Method to get the number of displaced cars 
     * @details 
     * 
     * @return the number of cars who wants to turn but can't 
     * 
    */
    public int getNumberOfMisplacedCars(){
    	int j = 0;
    	for(int i = 0; theLane.length > i; i++){
    		if (theLane[i] != null)
    			if (theLane[i].getTurn()) j++;
    	}
    	return j;
    }
    
    /**  
     * @brief Method to see if a placein the lane is vacant 
     * @details 
     * 
     * @param index the place in the lane you want to check     
     * @return true if it is empty else false 
     * 
    */
    public boolean isVacant(int index){
    	if ((theLane[index]) == null)
    		return true;
    	else return false;
    }
    
    /**  
     * @brief Method to get the number of turns in the system 
     * @details 
     * 
     * @return the number of turns in the system
     * 
    */
    public int getNumberOfTurns(){
    	return this.numberOfTurns;
    }

    /**  
     * @brief Method to represent a lane 
     * @details 
     * 
     * @return representation of a lane  
     * 
    */
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
