package com.unicamp.mc322.lab07;

public class PredatorObstacle extends Obstacle {

	public PredatorObstacle(String icon) {
		super(icon);
	}

	@Override
	public int maxAdjacentItems() {
		return 2;
	}
	
	@Override
	public boolean limitAdjacentItems() {
		return true;
	}
}
