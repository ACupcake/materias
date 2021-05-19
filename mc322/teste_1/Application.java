package br.unicamp.ic.mc322.teste1;

public class Application {

	public static void main(String[] args) {
		
		Position p1 = new Position(2, 3);
		Position p2 = new Position(10, 5);

		double distance = p1.getDistance(p2);
		
	}
}