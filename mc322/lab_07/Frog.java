package com.unicamp.mc322.lab07;

public abstract class Frog extends Item {
	private String name;
	protected int previousPosX;
	protected int previousPosY;
	protected int score;
	
	public Frog(String name, String icon, int x, int y) {
		super(icon, x, y);
		this.name = name;
		this.score = 0;
	}
	
	public void useItem(Item item) {
		if(item != null)
			score += item.getPoints();
	}
	
	public int score() {
		return score;
	}
	
	abstract public boolean moveUp(Map map);

	abstract public boolean moveDown(Map map);
	
	abstract public boolean moveLeft(Map map);
	
	abstract public boolean moveRight(Map map);
}
