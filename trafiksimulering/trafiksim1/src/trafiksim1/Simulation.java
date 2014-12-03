package trafiksim1;

import java.util.Scanner;



/**
 * @brief Constructor for Simulation class.
 * @details gives you 6 options on what you want to do with the program and then simulates your choice 
 * 
 * @param args 
 */
public class Simulation {
	  public static void main(String [] args) {
			// Skapar ett TrafficSystem
			// Utfor stegningen, anropar utskriftsmetoder

			TrafficSystem system = new TrafficSystem();
			Scanner sc = new Scanner(System.in);
			int  choice = -1;
			while(choice != 0) {
				System.out.println("Hello! WHAT DO YOU WANT!?!?!:");
				System.out.println("1. to step the system once");
				System.out.println("2. to step through the whole system once");
				System.out.println("3. to step through the system a number of times by your choice");
				System.out.println("4. to print the system");
				System.out.println("5. to print the statistics collected so far");
				System.out.println("0. to exit the program!");
				System.out.print("> ");
				choice = sc.nextInt();
				switch(choice){
					case 1:
						system.step();
						break;
					case 2:
						for (int i = 0; system.sysLen() > i; i++) system.step();
						break;
					case 3:
						for (int i = (sc.nextInt()); i > 0; i--) system.step();
						break;
					case 4:
						system.print();
						break;
					case 5:
						system.printStatistics();
						break;	
					case 0:
						System.out.println("Goodbye!");
						break;
					default:
						System.out.println("Could not parse choice, please try again");
				}

			}

			sc.close();
	


	  	}
}
