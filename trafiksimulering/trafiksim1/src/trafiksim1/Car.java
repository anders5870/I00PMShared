public class Car {
    private int bornTime;
    private int destination; // 1 f�r rakt fram, 2 f�r v�nstersv�ng
  
     
    //konstruktor
    //sätter borntime till bt och slumpar fram om bilen ska till vänster eller höger 
    public Car(int bornTime, int destination){
    	this.bornTime = bornTime;
    	this.destination = destination;	
    }
    
    
    // get-metod borntime 
    public int getBornTime(){
    	return this.bornTime;
    }
    //get-metod bilens destination 
    public int getDestination(){
    	return this.destination;
    }
    
   
    //set-metod bornTime
    public void setBornTime(int bornTime){
    	this.bornTime =bornTime;
    }
    
    //set-metod destinatin
    public void setDestination(int destination){
    	this.destination =destination;
    }
    
    
    public String toString() {
    	if (getDestination()== 0){
    		return "-<>";
    	} else {
    		return ".<>";
    	}
   
    }

}
