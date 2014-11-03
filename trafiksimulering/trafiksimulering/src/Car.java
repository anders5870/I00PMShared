import java.util.Random;

public class Car {

    private  int bornTime;
    private static int bt = 0;
    private int destination; // 1 för rakt fram, 2 för vänstersväng

    private int currentPosition =-1;
    
    public static void incBornTime(){
    		bt++;
    }
    
    public void step()
    {
    	currentPosition++;
    	// Uppdatera bilen ett tidssteg
    }
    //konstruktor
    public Car(){
    	bornTime = bt;
    	destination = randInt(1,2);
    	currentPosition = 0;
    }
    // get- oct set-metoder
    //...
    //get- metoder
    public int getBornTime(){
    	return this.bornTime;
    }
    public int getDestination(){
    	return this.destination;
    }
    public int getCurrentPosition(){
    	return this.currentPosition;
    }    
    
    //set- metoder
 
    public void setBornTime(int bornTime){
    	this.bornTime =bornTime;
    }
    public void setDestination(int destination){
    	this.destination =destination;
    }
    public void setCurrentPosition(int currentPosition){
    	this.currentPosition =currentPosition;
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
    
    public String toString() {
    	return "Car(bornTime=" + this.bornTime + ", destination=" + this.destination
    			+", currentPosition=" + this.currentPosition + ")";
    	}
	
}