package trafiksim1;

import java.util.Random;

public class Car extends TrafficSystem{
    public int bornTime;
    private int destination; // 1 f�r rakt fram, 2 f�r v�nstersv�ng
  
     
    //konstruktor
    //sätter borntime till bt och slumpar fram om bilen ska till vänster eller höger 
    public Car(int bornTime, int destDistribution){
    	this.bornTime = bornTime;
    	this.destination = (destDistribution  < randInt(0,100)) ?  1 : 0;
    }
    
    public Car(){
    	//do some random shit here
    }
    public static int randInt(int min, int max) {

        // NOTE: Usually this should be a field rather than a method
        // variable so that it is not re-seeded every call.
        Random rand = new Random();

        // nextInt is normally exclusive of the top value,
        // so add 1 to make it inclusive
        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }
    
    // get-metod borntime 
    public int getBornTime(){
    	return this.bornTime;
    }
    //get-metod bilens destination 
    public int  getDestination(){
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
