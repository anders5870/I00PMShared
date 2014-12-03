package trafiksim1;

import java.util.Random;

public class Car {
	private int bornTime;
	private int destination; // 1 goes straight 2 turns left
	private boolean turn;


	/**
	 * @brief Constructor for Car class
	 * @details Constructs a Car with given parameters 
	 * 
	 * @param bornTime: the bortime of the car
	 * @param destDistribution: the distribution of the car, 1 for straight and 2 left turn   
	 * 
	 * @return A Car with given parameters 
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
	 * @param min minimal int 
	 * @param max maximal int
	 * 
	 * @return A randomized int 
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
	 * @return born time of car represented by an int 
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
	 * @brief Method for setting the borntime 
	 * @details set the borntime to the borntime you want
	 * 
	 * @param bornTime is the borntime you want to set 
	 */

	public void setBornTime(int bornTime){
		this.bornTime =bornTime;
	}


	/**
	 * @brief Method to set the destination of the car 
	 * @details set the destination of the car to the destination you want 
	 * 
	 * @param destination is the destination you want to set 
	 */

	public void setDestination(int destination){
		this.destination =destination;
	}

	/**
	 * @brief Method for setting a turn 
	 * @details 
	 */

	public void setTurn(){
		this.turn = true;
	}
	
	public boolean equals(Object obj) {
		if(obj instanceof Car) {
			Car car = (Car) obj;
			boolean isEqual = this.bornTime == car.bornTime 
					&& this.destination == car.destination;
			return isEqual;
		} else {
			return false;
		}
	}

	/**
	 * @brief the toString method for the class Car
	 * @details 
	 * @return A graphical representation of the Car 
	 */
	
	public String toString() {
		if (getDestination()== 2){
			return "-<>";
		} else {
			return ".<>";
		}

	}


}
