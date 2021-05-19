package com.unicamp.mc322.lab07;

public class TrapObstacle extends Obstacle {

	public TrapObstacle(String icon) {
		super(icon);
	}

	@Override
	public int maxAdjacentItems() {
		return 3;
	}
	
	@Override
	public boolean limitAdjacentItems() {
		return true;
	}
}
