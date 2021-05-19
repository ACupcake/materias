package com.unicamp.mc322.lab07;

public class Food extends Item {
	private String name;
	private int points;
	
	public Food(String name, String icon, int points) {
		super(icon);
		this.points = points;
		this.name = name;
	}
	
	@Override
	public int getPoints() {
		return points;
	}
}
