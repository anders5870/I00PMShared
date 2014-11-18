package trafiksim1;

public class Lane {
	public static class OverflowException extends RuntimeException {
        // Undantag som kastas när det inte gick att lägga 
        // in en ny bil på vägen
    }

    private Car[] theLane;

    public Lane(int n) {
	// Konstruerar ett Lane-objekt med plats för n fordon
    }

    public void step() {
	// Stega fram alla fordon (utom det på plats 0) ett steg 
        // (om det går). (Fordonet på plats 0 tas bort utifrån 
	// mm h a metoden nedan.)
    }

    public Car getFirst() {
	// Returnera och tag bort bilen som står först
    }

    public Car firstCar() {
	// Returnera bilen som står först utan att ta bort den
    }


    public boolean lastFree() {
	// Returnera true om sista platsen ledig, annars false
    }

    public void putLast(Car c) throws OverflowException {
	// Ställ en bil på sista platsen på vägen
	// (om det går).
    }

    public String toString() {...}

}
