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
 
    
    private int time = 0;

    public TrafficSystem() {
//    	r0 = new Lane(10);
//    	r1 = new Lane(5);
//    	r2 = new Lane(5);
    	
    }

    public void readParameters() {
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
		    			this.r1 = new Lane(Integer.parseInt(value));
		    			this.r2 = new Lane(Integer.parseInt(value));
		    			break;    		    	
  		    		    		    		
    		    		default:
    		    			System.out.print("properties file is empty or missing!!!");
    			  }
    			}
    		
    	} catch (Exception e){
    			e.printStackTrace();
    			
    	}
 
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
    
    public void step() {
    	//kollar om s1 �r gr�n, om s�, d� tar vi bort bilen vid trafikljuset
    	if(s1.isGreen()){
    		Car c = r1.getFirst();
    		c.bornTime = 5;
    	}
    	//samma som ovan fast andra trafikljuset	
    	if(s1.isGreen()){
    		Car c = r2.getFirst();
    	}	
    	//stegar fram de parallella v�garna och l�ter bilar byta fil om det g�r
     	r1.step(r2);	
    	//tar bort f�rsta bilen i r0 och returnerar den
    	Car c = r0.getFirst();
    	//avg�r vart bilen skall �ka efter r0
    	if(c.getDestination() == 1){
    		if(r1.lastFree()){
    			r1.putLast(c);
    		}
    		//flagga bilen f�r sv�ngning
    		else if (r2.lastFree()){
    			r2.putLast(c);
    			c.setTurn(true);
    		}
    	}
		else{
			if(r2.lastFree()){
				r2.putLast(c);
			}
	   		else if (r1.lastFree()){
    			r1.putLast(c);
    			c.setTurn(true);
    		}
		}
    	
    	//L�t bilen �ka vidare p� fel v�g om r�tt v�g �r upptagen
    	//F�rs�k sv�nga in p� r�tt v�g
     	r0.step();
     	
    		//kollar om det g�r att stoppa in en ny bil p� v�gen
        if(r0.lastFree()){
        	//avg�r om en ny bil anl�nder eller ej
        	if (ankomstintensitet < randInt(0,100)){
            //skapar bilen		
        	Car d = new Car(time, destDistribution);
        	Car f = new Car();
        	//stoppar in bilen
            r0.putLast(d);
        	}


        }
        //stegar fram v�gen ett steg
    	

    	
	// Stega systemet ett tidssteg m h a komponenternas step-metoder
	// Skapa bilar, l�gg in och ta ur p� de olika Lane-kompenenterna
    }

    public void printStatistics() {
	// Skriv statistiken samlad s� h�r l�ngt
    }

    public void print() {
	// Skriv ut en grafisk representation av k�situationen
	// med hj�lp av klassernas toString-metoder
    }

}
