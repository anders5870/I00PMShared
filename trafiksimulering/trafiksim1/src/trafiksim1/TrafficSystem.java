package trafiksim1;

import java.io.FileReader;
import java.util.Properties;
import java.util.Random;

public class TrafficSystem {
	// Definierar de v�gar och signaler som ing�r i det 
    // system som skall studeras.
    // Samlar statistik
    
    // Attribut som beskriver best�ndsdelarna i systemet
    private Lane  r0;
    private Lane  r1;
    private Lane  r2;
    private Light s1;
    private Light s2;

  
    
    // Diverse attribut f�r simuleringsparametrar (ankomstintensiteter,
    // destinationer...)
    // i intervallet 0-100
    private int ankomstintensitet;
    private int destDistribution;
    public int example;
    // Diverse attribut f�r statistiksamling
 
    private int carWrongLane;
    private int carPassed = 0;
    private int carEntered = 0;
    private static int time = 0;
    private Car[] passed;
    private Car[] entered;

    public TrafficSystem() {
    	this.s1 = new Light(0,0);
    	this.s2 = new Light(0,0);
    	readParameters();	   	
    }

    private void readParameters() {
	// L�ser in parametrar f�r simuleringen
	// Metoden kan l�sa fr�n terminalf�nster, dialogrutor
	// eller fr�n en parameterfil. Det sista alternativet
	// �r att f�redra vid uttestning av programmet eftersom
	// man inte d� beh�ver mata in v�rdena vid varje k�rning.
        // Standardklassen Properties �r anv�ndbar f�r detta. 
    	try (FileReader reader = new FileReader("attributes.properties")){
    		Properties properties = new Properties();
    		properties.load(reader);
    		
    		for(String key : properties.stringPropertyNames()) {
    			  String value = properties.getProperty(key);
    			  switch (key){
    			  case "ankomstintensitet":
    			   		this.ankomstintensitet = Integer.parseInt(value);
    			   		break;
    			  case "destDistribution":
  			   			this.destDistribution = Integer.parseInt(value);
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

    public int randInt(int min, int max) {

        // NOTE: Usually this should be a field rather than a method
        // variable so that it is not re-seeded every call.
        Random rand = new Random();

        // nextInt is normally exclusive of the top value,
        // so add 1 to make it inclusive
        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }
    
    public void step() {
    	//left: bilen som sv�ngt v�nster i korsningen
    	//straight: bilen som k�rt rakt fram i korsningen
    	//deciding: bilen som skall v�lja fil
    	//newCar: nyinstoppad bil i systemets ena �nde
    	Car left, straight, deciding, newCar;
    	//kollar om s1 �r gr�n, om s�, d� tar vi bort bilen vid trafikljuset
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
    	//stegar fram de parallella v�garna och l�ter bilar byta fil om det g�r
     	r2.step(r1); 
    	//tar bort f�rsta bilen i r0 och returnerar den
    	deciding = r0.getFirst();
    	//avg�r vart bilen skall �ka efter r0
    	if (deciding != null){
	    	if(deciding.getDestination() == 1){
	    		if(r1.lastFree()){
	    			r1.putLast(deciding);
	    		}
	    		//flagga bilen f�r sv�ngning
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
    	//L�t bilen �ka vidare p� fel v�g om r�tt v�g �r upptagen
    	//F�rs�k sv�nga in p� r�tt v�g
     	r0.step();
     	
    		//kollar om det g�r att stoppa in en ny bil p� v�gen
        if(r0.lastFree()){
        	//avg�r om en ny bil anl�nder eller ej
        	if (ankomstintensitet >= randInt(0,100)){
            //skapar bilen	
        	++carEntered;
        	newCar = new Car(time, destDistribution);
        	//stoppar in bilen
            r0.putLast(newCar);
        	}


        }
        //stegar fram v�gen ett steg
       time++;	
       s1.step();
       s2.step();
    	
	// Stega systemet ett tidssteg m h a komponenternas step-metoder
	// Skapa bilar, l�gg in och ta ur p� de olika Lane-kompenenterna
    }
    
    public int sysLen(){
    	return r0.getLen() + r1.getLen();
    }
   
    public void printStatistics() {
	// Skriv statistiken samlad s� h�r l�ngt
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

    public void print() {
	// Skriv ut en grafisk representation av k�situationen
	// med hj�lp av klassernas toString-metoder
    	System.out.print(r2.toString());
       	System.out.print(" ");
    	System.out.println(r0.toString());
    	System.out.println(r1.toString());
    	
    }
   
    public static int getTime(){
    	return time;
    }
}




