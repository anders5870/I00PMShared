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

    // Diverse attribut f�r statistiksamling
    //....    
    
    private int time = 0;

    public TrafficSystem() {
    	//...
    	}

    public void readParameters() {
	// L�ser in parametrar f�r simuleringen
	// Metoden kan l�sa fr�n terminalf�nster, dialogrutor
	// eller fr�n en parameterfil. Det sista alternativet
	// �r att f�redra vid uttestning av programmet eftersom
	// man inte d� beh�ver mata in v�rdena vid varje k�rning.
        // Standardklassen Properties �r anv�ndbar f�r detta. 
    	try (FileReader reader = new FileReader("parameters.properties")){
    		Properties properties = new Properties();
    		properties.load(reader);
    		
    	} catch (Exception e){
    			e.printStackTrace();
    			
    	}	

    		
    }

    public void step() {
    	CarPosition a = r0.getFirst();
    	CarPosition b = r1.getFirst();
    	CarPosition c = r2.getFirst();
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