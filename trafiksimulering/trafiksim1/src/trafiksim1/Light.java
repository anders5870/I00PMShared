package trafiksim1;

public class Light {
	private int period;
    private int time = 0;  // Intern klocka: 0, 1, ... period-1, 0, 1 ...
    private int green; // Signalen grï¿½n nï¿½r time<green 

    public Light(int period, int green) {
    	if(period > green && period > 0 && green > 0){
    	this.period = period;   
    	this.green =  green;
    	}
    	//om instoppade värden inte är valida så ger vi några standardvärden
    	else{
    		this.period = 60;
    		this.green = 30;
    	}
    }

    // Stegar fram klocka ett steg
    public void step() { 
    	this.time++;
    }

// get och set metoder fï¿½r period och green
    
    //set-metod fÃ¶r perioden
    public void setPeriod(int period) {
    	this.period = period;
    		}
    //get-metod fÃ¶r period	
    public int getPeriod(){
    	return this.period ;
    }
    	
    //set-metod fÃ¶r green
    public void setGreen(int green){
    	this.green = green;
    }
    
    //get-metod fÃ¶r green 
    public int getGreen(){
    	return this.green;
    }
    
    public int getTime(){
    	return this.time;
    }
    
    public void setTime(int _time){
    	this.time = _time;
    }


    
    // Returnerar true om det är grönt, annars false
    public boolean isGreen()   {
		if ((time%period)<green) {
    		return true;
    	}else 
    		return false;
    }
    
    //tostring metod som skriver ut perioden, tiden och grÃ¶ntiden 
    public String toString() {
    	return "Light(period=" + this.period + ", time=" + this.time
    			+", green=" + this.green + ")";
    }

}
