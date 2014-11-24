package trafiksim1;

import java.util.Random;

public class Car {
    private int bornTime;
    private int destination; // 1 goes straight 2 turs left
    private boolean turn;
   

   /**  
     * @brief Constructor for Car class.
     * @details constructs a car object with specified parameters and a set turn value 
     * 
     * @param bornTime time when the car was created 
     * @param destDistribution if the car should turn keft or go straight 
     * 
     * @return an object Car with given parameters.
    */
    public Car(int bornTime, int destDistribution){
    	this.turn = false;
    	this.bornTime = TrafficSystem.getTime();
    	this.destination = (destDistribution  < randInt(0,100)) ?  1 : 2;
    }

    /**  
     * @brief Method for randomizing an int          
     * @details 
     * 
     * @param the minimal value of the int
     * @param the maximal value of the inte
     * 
     * @return a randomized int 
    */
    
    public int randInt(int min, int max) {

        // NOTE: Usually this should be a field rather than a method
        // variable so that it is not re-seeded every call.
        Random rand = new Random();

        // nextInt is normally exclusive of the top value,
        // so add 1 to make it inclusive
        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }
    
    /**
     * @brief Method to get born time of a car (when the car was created).
     * @details 
     * @return born time of car.
     */
    public int getBornTime(){
    	return this.bornTime;
    }
    /**
     * @brief Method to se if the car is going to turn or go straight
     * @details 
     * @return destination of the car
     */
    public int  getDestination(){
    	return this.destination;
    }
    /**
     * @brief Method to see if the car is going to turn
     * @details 
     * @return true or false 
     */
    public boolean getTurn(){
    	return turn;
    }
    
   
    /**
     * @brief Method to set the borntime 
     * @details 
     * 
     * @param bornTime when the car is born
     * @return 
     */
    public void setBornTime(int bornTime){
    	this.bornTime =bornTime;
    }
    
    
    /**
     * @brief Method to set the destination
     * @details 
     * 
     * @param destination if the car is going to turn or not. 
     * @return 
     */
    public void setDestination(int destination){
    	this.destination =destination;
    }
    
    /**
     * @brief Method to set turn
     * @details sets the turnvalue to true  
     * 
     * @return 
     */
    public void setTurn(){
    	this.turn = true;
    }
    
    /**
     * @brief Method to represent a car.
     * @details 
     * @return representation of a car in the lane.
     */
    public String toString() {
    	if (getDestination()== 2){
    		return "-<>";
    	} else {
    		return ".<>";
    	}
   
    }
    
    
}
