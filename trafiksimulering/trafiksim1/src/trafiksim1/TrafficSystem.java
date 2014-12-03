package trafiksim1;

import java.io.FileReader;
import java.util.Properties;
import java.util.Random;
import java.util.Scanner;

public class TrafficSystem {
	// Definierar de vagar och signaler som ingar i det 
    // system som skall studeras.
    // Samlar statistik
    
    // Attribut som beskriver bestandsdelarna i systemet
    private Lane  r0;
    private Lane  r1;
    private Lane  r2;
    private Light s1;
    private Light s2;

   
    
    // Diverse attribut for simuleringsparametrar (ankomstintensiteter,
    // destinationer...)
    // i intervallet 0-100
    private int ankomstintensitet;
    private int destDistribution;
    public int example;
    // Diverse attribut far statistiksamling
 
    private int carWrongLane;
    private int carPassed = 0;
    private int carEntered = 0;
    private static int time = 0;
    private Car[] passed;
    private Car[] entered;


    /**
     * @brief Constructor for trafficSystem class.
     * @details constructs a trafficSystem with specified parameters.
     * 
     * 
     * @return a trafficSystem 
     */

    public TrafficSystem() {
    	this.s1 = new Light(0,0);
    	this.s2 = new Light(0,0);
    	readParameters();	   	
    }


    /**
     * @brief Method to read parameters from a file 
     * @details
     * 
     *  
     */

    
    private void readParameters() {
	// Laser in parametrar for simuleringen
	// Metoden kan lasa fr�n terminalfonster, dialogrutor
	// eller fr�a en parameterfil. Det sista alternativet
	// ar att foredra vid uttestning av programmet eftersom
	// man inte da beh�ver mata in vardena vid varje korning.
        // Standardklassen Properties ar anvandbar for detta. 
    	try (FileReader reader = new FileReader("attributes.properties")){
    		Properties properties = new Properties();
    		properties.load(reader);
    		
    		for(String key : properties.stringPropertyNames()) {
    			  String value = properties.getProperty(key);
    			  switch (key){
    			  case "ankomstintensitet":
    				  	assert (Integer.parseInt(value) <=100 && Integer.parseInt(value) >= 0);
    			   		this.ankomstintensitet = Integer.parseInt(value);
    			   		break;
    			  case "destDistribution":
    				  	int i =  Integer.parseInt(value);
		   				Scanner sc = new Scanner(System.in);
  			   			while (!(i >=0 && i<=100)){		
			   					System.out.println("error in .properties file: destDistribution");
  			   					System.out.println("Please enter a value 0-100");
  			   					System.out.print("> ");
  			   					i = sc.nextInt();

  			   			}
	  			   			this.destDistribution = i;
  			   			break;
    			  case "green1":
    		    		s1.setGreen(Integer.parseInt(value));
    		    		break;
    			  case "green2":
    		    		s2.setGreen(Integer.parseInt(value));
    		    		break;
    			  case "period1":
    		    		s1.setPeriod(Integer.parseInt(value));
    		    		break;
    			  case "period2":
    		    		s2.setPeriod(Integer.parseInt(value));
    		    		break;
    			  case "time1":
    		    		s1.setTime(Integer.parseInt(value));
    		    		break;
    			  case "time2":
    		    		s2.setTime(Integer.parseInt(value));
    		    		break;
    			  case "r0_len":
  		    			this.r0 = new Lane(Integer.parseInt(value));
  		    			break;	    	
    			  case "r1_r2_len":
    				  try {
		    			this.r1 = new Lane(Integer.parseInt(value));
		    			this.r2 = new Lane(Integer.parseInt(value));
    				  } catch (NumberFormatException e) {
    					  System.out.println("This is not a number");
    					  System.out.println(e.getMessage());
    				  }
		    			break;    		    	
    			  }
    			}
    		
    	} catch (Exception e){
    			e.printStackTrace();
    			
    	}
 
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
    
//    public double randInt(){
//        Random r = new Random();
//        int ret = r.nextInt(60 + 1);
//        return ret / 1000.0;
//    }

    /**  
     * @brief Method stepping the traffic system         
     * @details steps through the whole system once  
    */

    public void step() {
    	//left: bilen som svangt vanster i korsningen
    	//straight: bilen som kort rakt fram i korsningen
    	//deciding: bilen som skall valja fil
    	//newCar: nyinstoppad bil i systemets ena ande
    	Car left, straight, deciding, newCar;
    	//kollar om s1 �r gron, om sa, da tar vi bort bilen vid trafikljuset
    	if(s1.isGreen()){
    		if (r1.getFirst() != null){
	    		left = r1.getFirst();
	    		++carPassed;
    		}
    	}
    	//samma som ovan fast andra trafikljuset	
    	if(s1.isGreen()){
    		if (r2.getFirst() != null){
	    		straight = r2.getFirst();
	    		++carPassed;
    		}
    	}	
    	//stegar fram de parallella vagarna och later bilar byta fil om det gar
     	r2.step(r1); 
    	//tar bort forsta bilen i r0 och returnerar den
    	deciding = r0.getFirst();
    	//avgor vart bilen skall aka efter r0
    	if (deciding != null){
	    	if(deciding.getDestination() == 1){
	    		if(r1.lastFree()){
	    			r1.putLast(deciding);
	    		}
	    		//flagga bilen f�r svangning
	    		else if (r2.lastFree()){
	    			r2.putLast(deciding);
	    			deciding.setTurn();
	    		}
	    	}
			else{
				if(r2.lastFree()){
					r2.putLast(deciding);
				}
		   		else if (r1.lastFree()){
	    			r1.putLast(deciding);
	    			deciding.setTurn();
	    		}
			}
    	}
    	//Lat bilen aka vidare pa fel vag om ratt vag ar upptagen
    	//Forsok sv�nga in p� ratt vag
     	r0.step();
     	
    		//kollar om det gar att stoppa in en ny bil p� vagen
        if(r0.lastFree()){
        	//avgor om en ny bil anlander eller ej
        	if (ankomstintensitet >= randInt(0,100)){
            //skapar bilen	
        	++carEntered;
        	newCar = new Car(time, destDistribution);
        	//stoppar in bilen
            r0.putLast(newCar);
        	}


        }
        //stegar fram vagen ett steg
       time++;	
       s1.step();
       s2.step();
    	
	// Stega systemet ett tidssteg m h a komponenternas step-metoder
	// Skapa bilar, lagg in och ta ur p� de olika Lane-kompenenterna
    }
    
    /**  
     * @brief Method for getting the length of the system        
     * @details 
     * 
     * 
     * @return the lenght of both lengths added together 
    */
   
    public int sysLen(){
    	return r0.getLen() + r1.getLen();
    }

    /**  
     * @brief Method for randomizing an int          
     * @details prints the statistics for the trafficsystem 
    */
  
    public void printStatistics() {
	// Skriv statistiken samlad sa har langt
    	carWrongLane = r1.getNumberOfMisplacedCars() + r2.getNumberOfMisplacedCars();
    	System.out.println("time: " + time);
    	System.out.println("dest distribution: " + this.destDistribution);
    	System.out.println("spawn chance: " + this.ankomstintensitet);
    	System.out.println("cars entered: " + carEntered);
    	System.out.println("cars passed: " + carPassed);
    	System.out.println("misplaced cars: " + carWrongLane);
    	System.out.println("s1 green: " + s1.getGreen());
    	System.out.println("s2 green: " + s2.getGreen());
    	System.out.println("s1 period: " + s1.getPeriod());
    	System.out.println("s2 period: " + s2.getPeriod());
    	System.out.println("s1 time: " + s1.getTime());
    	System.out.println("s2 time: " + s2.getTime());
    	System.out.println("r1 Number of turns: " + r1.getNumberOfTurns());
    	System.out.println("r2 Number of turns: " + r2.getNumberOfTurns());
    	System.out.println("r0,r1,r2 len: " + r0.getLen() + " " + r1.getLen() + " " + r2.getLen());
    	System.out.printf("The system is %s \n",(r0.laneFull() && r1.laneFull() && r2.laneFull()) ? "full" : "not full");
    }

    /**  
     * @brief Method for representing the que          
     * @details prints a representation of the whole system by using the other classes toString-methods   
    */

    public void print() {
	// Skriv ut en grafisk representation av kosituationen
	// med hjalp av klassernas toString-metoder
    	System.out.print(r2.toString());
       	System.out.print(" ");
    	System.out.println(r0.toString());
    	System.out.println(r1.toString());
    	
    }

    /**  
     * @brief Method for getting the time for how long the system has been active           
     * @details 
     * 
     * 
     * @return the time the system has been active  
    */
   
    public static int getTime(){
    	return time;
    }
}


