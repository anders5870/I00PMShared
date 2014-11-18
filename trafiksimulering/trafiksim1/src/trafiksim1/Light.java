package trafiksim1;

public class Light {
	private int period;
    private int time;  // Intern klocka: 0, 1, ... period-1, 0, 1 ...
    private int green; // Signalen gr�n n�r time<green 

    public Light(int period, int green) {
    	this.period = period;   
    	this.green =  green;
    }

    // Stegar fram klocka ett steg
    public void    step() { 
    	this.time = time++
    }

// get och set metoder f�r period och green
    
    //set-metod för perioden
    public void setPeriod(int period) {
    	this.period = period;
    		}
    //get-metod för period	
    public int getPeriod(){
    	return this.period ;
    }
    	
    //set-metod för green
    public void setGreen(int green){
    	this.green = green;
    }
    
    //get-metod för green 
    public int getGreen(){
    	return this.green;
    }
    
    // Returnerar true om time<green, annars false
    public boolean isGreen()   {
		if (time<green) {
    		return true;
    	}else 
    		return false;
    }
    
    //tostring metod som skriver ut perioden, tiden och gröntiden 
    public String toString() {
    	return "Light(period=" + this.period + ", time=" + this.time
    			+", green=" + this.green + ")";
    }

}
