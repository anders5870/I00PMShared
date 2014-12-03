package trafiksim1;

public class Light {
	private int period;
    private int time = 0;  // Intern klocka: 0, 1, ... period-1, 0, 1 ...
    private int green; // Signalen gron nar time<green 


    /**  
     * @brief Constructor for Light class.
     * @details constructs a Light object with specified parameters for greentime and period  
     * 
     * @param period the period for wich the light is either green or red 
     * @param green how long the traffic light will be green
     * 
     * @return an object Light object with given parameters.
    */

    
    public Light(int period, int green) {
    	if(period > green && period > 0 && green > 0){
    	this.period = period;   
    	this.green =  green;
    	}
    	//om instoppade varden inte �r valida sa ger vi nagra standardv�rden
    	else{
    		this.period = 60;
    		this.green = 30;
    	}
    }

   

    /**
     * @brief Method to step the Light's clock 
     * @details [long description]
     */
    public void step() { 
    	this.time++;
    }


    /**  
     * @brief Method to set the light's preiod
     * @details  
     * 
     * @param period is the period you want 
    */
    
    public void setPeriod(int period) {
    	this.period = period;
    		}

   
    /**
     * @brief Method to get the light's preiod
     * @details 
     * @return the period 
     */
    public int getPeriod(){
    	return this.period ;
    }
    	
    /**  
     * @brief Method to set the light's greentime
     * @details  
     * 
     * @param green is the greentime you want
    */

    public void setGreen(int green){
    	this.green = green;
    }
    
    /**  
     * @brief Method to get the light's greentime 
     * @details  
     * 
     * @return The greentime
    */

    public int getGreen(){
    	return this.green;
    }

    /**  
     * @brief Method to get the light's clock
     * @details  
     * 
     * @return The time
    */

    public int getTime(){
    	return this.time;
    }

   
    /**
     * @brief Method to set the light's clock
     * @details 
     * 
     * @param _time is the time you want to set 
     */
    public void setTime(int _time){
    	this.time = _time;
    }

    /**  
     * @brief Method to see if the light is green
     * @details  
     * @return true if the light is green else false  
    */
    
    public boolean isGreen()   {
		if ((time%period)<green) {
    		return true;
    	}else 
    		return false;
    }

    /**
     * @brief Method to represent a light
     * @details 
     * @return representation of a light
     */
   
    public String toString() {
    	return "Light(period=" + this.period + ", time=" + this.time
    			+", green=" + this.green + ")";
    }

}
