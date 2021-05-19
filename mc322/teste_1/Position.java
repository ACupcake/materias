package br.unicamp.ic.mc322.teste1;

public class Position {
	private int x;
	private int y;
	
	public Position(int theX, int theY) {
		x = theX;
		y = theY;
	}

	public double getDistance(Position p2) {
		return Math.sqrt(Math.pow(p2.x + this.x, 2) + Math.pow(p2.y + this.y, 2));
	}
}