package trafiksim1;

import java.io.FileReader;
import java.util.Properties;
import java.util.Random;

public class TrafficSystem {
	// Definierar de vägar och signaler som ingår i det 
    // system som skall studeras.
    // Samlar statistik
    
    // Attribut som beskriver beståndsdelarna i systemet
    private Lane  r0;
    private Lane  r1;
    private Lane  r2;
    private Light s1;
    private Light s2;

    public static int randInt(int min, int max) {

        // NOTE: Usually this should be a field rather than a method
        // variable so that it is not re-seeded every call.
        Random rand = new Random();

        // nextInt is normally exclusive of the top value,
        // so add 1 to make it inclusive
        int randomNum = rand.nextInt((max - min) + 1) + min;

        return randomNum;
    }  
    
    // Diverse attribut för simuleringsparametrar (ankomstintensiteter,
    // destinationer...)
    // i intervallet 0-100
    private int ankomstintensitet;
    private int destDistribution;
    // Diverse attribut för statistiksamling
    ....    
    
    private int time = 0;

    public TrafficSystem() {...}

    public void readParameters() {
	// Läser in parametrar för simuleringen
	// Metoden kan läsa från terminalfönster, dialogrutor
	// eller från en parameterfil. Det sista alternativet
	// är att föredra vid uttestning av programmet eftersom
	// man inte då behöver mata in värdena vid varje körning.
        // Standardklassen Properties är användbar för detta. 
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
    		    		default:
    		    			System.out.print("properties file is missing!!!");
    			  }
    			}
    		
    	} catch (Exception e){
    			e.printStackTrace();
    			
    	}
 
    }

    public void step() {
	// Stega systemet ett tidssteg m h a komponenternas step-metoder
	// Skapa bilar, lägg in och ta ur på de olika Lane-kompenenterna
    }

    public void printStatistics() {
	// Skriv statistiken samlad så här långt
    }

    public void print() {
	// Skriv ut en grafisk representation av kösituationen
	// med hjälp av klassernas toString-metoder
    }

}
