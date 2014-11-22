package trafiksim1;

public class Light {
	private int period;
    private int time = 0;  // Intern klocka: 0, 1, ... period-1, 0, 1 ...
    private int green; // Signalen gr�n n�r time<green 

    public Light(int period, int green) {
    	if(period > green && period > 0 && green > 0){
    	this.period = period;   
    	this.green =  green;
    	}
    	//om instoppade v�rden inte �r valida s� ger vi n�gra standardv�rden
    	else{
    		this.period = 60;
    		this.green = 30;
    	}
    }

    // Stegar fram klocka ett steg
    public void step() { 
    	this.time++;
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
    
    public int getTime(){
    	return this.time;
    }
    
    public void setTime(int _time){
    	this.time = _time;
    }


    
    // Returnerar true om det �r gr�nt, annars false
    public boolean isGreen()   {
		if ((time%period)<green) {
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
