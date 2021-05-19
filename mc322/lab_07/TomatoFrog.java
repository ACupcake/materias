package com.unicamp.mc322.lab07;

import java.util.ArrayList;

public class TomatoFrog extends Frog {
	public TomatoFrog(String name, String icon, int x, int y) {
		super(name, icon, x, y);
	}
	
	public void useItem(Item item) {
		int points = item.getPoints();
		score += points + (points * 0.1);
	}

	private boolean jumpOffMap(Item item) {
		return item == null;
	}

	public boolean doMove(int moves, Direction direction, Map map) {
		Item collectedItem = new Floor("--");
		int xAxis = this.getPositionX();
		int yAxis = this.getPositionY();

		if(!shouldMoveYAxis(direction)) {
			collectedItem = map.moveObject(xAxis + moves, yAxis, this);
			this.setPositionX(xAxis + moves);
		} else if(shouldMoveXAxis(direction)) {
			collectedItem = map.moveObject(xAxis, yAxis + moves, this);
			this.setPositionY(yAxis + moves);
		}
	
		if(jumpOffMap(collectedItem)) {
			return false;
		} else {
			useItem(collectedItem);
			return true;
		}
	}
	
	private int[] getRange(Direction direction) {
		switch(direction) {
			case RIGHT:
				return new int[] {1,2,3};
			case LEFT:
				return new int[] {1,2,3};
			case UP:
				return new int[] {2,3};
			case DOWN:
				return new int[] {1,2,4};
			default:
				return new int[] {};
		}
	}
	
	private ArrayList<Integer> freePositions(Direction direction, Map map) {
		ArrayList<Integer> validMoves = new ArrayList<Integer>();
		int xAxis = this.getPositionX();
		int yAxis = this.getPositionY();

		int[] range = getRange(direction);

		for(int move: range) {
			if(!shouldMoveXAxis(direction) && map.localIsFree(xAxis + move, yAxis)) {
				validMoves.add(move);
			} else if(map.localIsFree(xAxis, yAxis + move)) {
				validMoves.add(move);
			}
		}

		return validMoves;
	}

	private boolean shouldMoveXAxis(Direction direction) {
		return (direction == Direction.LEFT || direction == Direction.RIGHT);
	}

	private boolean shouldMoveYAxis(Direction direction) {
		return (direction == Direction.UP || direction == Direction.DOWN);
	}

	private int randomPositionFrom(ArrayList<Integer> positions) {
		int size = positions.size();
		return (int)Math.floor((size * Math.random()));
	}

	public boolean chooseMove(Map map, Direction direction) {
		ArrayList<Integer> validPositions = freePositions(direction, map);
		int moves = 0;
		
		if(!validPositions.isEmpty()) {
			moves = validPositions.get(randomPositionFrom(validPositions));
		}
		return doMove(moves, direction, map);
	}
	
	@Override
	public boolean moveUp(Map map) {
		return chooseMove(map, Direction.UP);
	}

	@Override
	public boolean moveDown(Map map) {
		return chooseMove(map, Direction.DOWN);
	}

	@Override
	public boolean moveLeft(Map map) {
		return chooseMove(map, Direction.LEFT);
	}

	@Override
	public boolean moveRight(Map map) {
		return chooseMove(map, Direction.RIGHT);
	}
}
