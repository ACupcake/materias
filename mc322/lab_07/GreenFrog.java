package com.unicamp.mc322.lab07;

public class GreenFrog extends Frog {
	public GreenFrog(String name, String icon, int x, int y) {
		super(name, icon, x, y);
	}
	
	private boolean jumpOffMap(Item item) {
		return item == null;
	}
	
	private int getMove(Direction direction) {
		if(direction == Direction.RIGHT)
			return 1;
		if(direction == Direction.LEFT)
			return -1;
		if(direction == Direction.UP)
			return -1;
		if(direction == Direction.DOWN)
			return 1;
		return 0;
	}
	
	private boolean shouldMoveYAxis(Direction direction) {
		return direction == Direction.UP || direction == Direction.DOWN;
	}
	
	private boolean move(Map map, Direction direction) {
		int xAxis = this.getPositionX();
		int yAxis = this.getPositionY();
		int moveX = getMove(direction);
		int moveY = getMove(direction);
		
		if(!shouldMoveYAxis(direction)) {
			moveX = 0;
		} else {
			moveY = 0;
		}
		
		Item collectedItem = new Floor("--");
		if(map.localIsFree(xAxis + moveX, yAxis + moveY)) {
			collectedItem = map.moveObject(xAxis + moveX, yAxis + moveY, this);	
			this.setPositionX(xAxis + moveX);
			this.setPositionY(yAxis + moveY);
		}

		if(jumpOffMap(collectedItem)) {
			return false;
		} else {
			useItem(collectedItem);
			return true;
		}
	}
	
	public boolean moveUp(Map map) {
		return move(map, Direction.UP);
	}

	public boolean moveDown(Map map) {
		return move(map, Direction.DOWN);
	}
	
	public boolean moveLeft(Map map) {
		return move(map, Direction.LEFT);
	}
	
	public boolean moveRight(Map map) {
		return move(map, Direction.RIGHT);
	}
}
