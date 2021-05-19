package com.unicamp.mc322.lab07;

public abstract class Obstacle extends Item {
	public Obstacle(String icon) {
		super(icon);
	}
	
	public abstract int maxAdjacentItems();
	
}