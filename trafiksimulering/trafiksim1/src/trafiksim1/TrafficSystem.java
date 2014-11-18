package trafiksim1;

import java.io.FileReader;
import java.util.Properties;

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
    private int ankomstintensitet;
    // Diverse attribut f�r statistiksamling
    ....    
    
    private int time = 0;

    public TrafficSystem() {...}

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
    		
    		String value = properties.getProperty("ankomstintensitet");
    		this.ankomstintensitet = Integer.parseInt(value);
    		value = properties.getProperty("green1");
    		s1.setGreen(Integer.parseInt(value));
    		value = properties.getProperty("green2");
    		s2.setGreen(Integer.parseInt(value));
    		value = properties.getProperty("period1");
    		s1.setPeriod(Integer.parseInt(value));
    		value = properties.getProperty("period2");
    		s2.setPeriod(Integer.parseInt(value));
    		value = properties.getProperty("time1");
    		s1.setTime(Integer.parseInt(value));
    		value = properties.getProperty("time2");
    		s2.setTime(Integer.parseInt(value));
    		
    	} catch (Exception e){
    			e.printStackTrace();
    			
    	}
 
    }

    public void step() {
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
