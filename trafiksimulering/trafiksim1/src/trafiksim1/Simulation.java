package trafiksim1;

public class Simulation {
	  public static void main(String [] args) {
			// Skapar ett TrafficSystem
			// Utför stegningen, anropar utskriftsmetoder

			TrafficSystem system = new TrafficSystem();

			//X how to know when a complete iteration is done?
			for(int i = 0; system.sysLen()*10 > i; i++){
				system.step();
			}
			
			//X how to show the current time of the system?
			//X how to show how many cars are in the wrong lane?
			//X how to know how many cars have passed the system?
			system.printStatistics();
			//X how to show where there are cars in the system?
			system.print();

		    }
}
