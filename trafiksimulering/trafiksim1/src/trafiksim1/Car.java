package trafiksim1;

import java.util.Random;

public class Car extends TrafficSystem{
    private int bornTime;
    private int destination; // 1 för rakt fram, 2 för vänstersväng
    private boolean turn;
     
    //konstruktor
    //sätter borntime till bt och slumpar fram om bilen ska till vÃ¤nster eller hÃ¶ger 
    public Car(int bornTime, int destDistribution){
    	this.turn = false;
    	this.bornTime = TrafficSystem.getTime();
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
    //get-metod turn
    public boolean getTurn(){
    	return turn;
    }
    
   
    //set-metod bornTime
    public void setBornTime(int bornTime){
    	this.bornTime =bornTime;
    }
    
    //set-metod destinatin
    public void setDestination(int destination){
    	this.destination =destination;
    }
    
    //set-metod turn
    public void setTurn(boolean turn){
    	this.turn = turn;
    }
    
    public String toString() {
    	if (getDestination()== 1){
    		return "-<>";
    	} else {
    		return ".<>";
    	}
   
    }
    
    
}
