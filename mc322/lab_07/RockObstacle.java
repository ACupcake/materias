package com.unicamp.mc322.lab07;

public class RockObstacle extends Obstacle {

	public RockObstacle(String icon) {
		super(icon);
	}
	
	public boolean canInteract() {
		return false;
	}

	@Override
	public int maxAdjacentItems() {
		return 0;
	}
	
	@Override
	public boolean limitAdjacentItems() {
		return true;
	}
}
