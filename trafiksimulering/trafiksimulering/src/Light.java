public class Light {
    private int period = 60;
    private int time = 0 ;  // Intern klocka: 0, 1, ... period-1, 0, 1 ...
    private int green = 30 ; // Signalen gr�n n�r time<green 

    public Light(int period, int green) {
    	this.period = period;   
    	this.green =  green;
    }   	
    
    public Light(){
    	period = 60; 
    	green = 30;
    }
    
    // get och set metoder f�r period och green
    
    public void setPeriod(int period) {
    	this.period = period;
    		}
    	
    public int getPeriod(){
    	return this.period ;
    }
    	
    public void setGreen(int green){
    	this.green = green;
    }
    
    public int getGreen(){
    	return this.green;
    }
 
    
    // Stegar fram klocka ett steg
    public void  step() { 
       int time = time ++ ;
    }
    public boolean isGreen()   {
    	if (time<green) {
    		return true;
    	}else 
    		return false;
    		
    	// Returnerar true om time<green, annars false
    }

    public String  toString()  {
    	return "Light(period = " + this.period +",
    				time = "+ this.time + ",
    				green = " + this.green +")";
    	
    	//...
    	}
	
}