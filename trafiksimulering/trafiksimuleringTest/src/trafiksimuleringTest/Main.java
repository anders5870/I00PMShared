	package trafiksimuleringTest;
	
	public class Main {
	
		public static void main(String[] args) {
		Car c1 = new Car();
		Car c2 = new Car();
		Car.incBornTime();
		Car c3 = new Car();
		c1.step(); c2.step(); c3.step();c3.step();
		System.out.println(c1.toString());
		System.out.println(c2.toString());
		System.out.println(c3.toString());
		
		
	
				
		Light l1 = new Light();
		Light l2 = new Light(50, 25);
		System.out.println(l1.toString());
		System.out.println(l2.toString());
		
	}		
}

