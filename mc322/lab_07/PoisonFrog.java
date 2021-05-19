package com.unicamp.mc322.lab07;

import java.util.ArrayList;

public class PoisonFrog extends Frog {
	public PoisonFrog(String name, String icon, int x, int y) {
		super(name, icon, x, y);
	}

	public void useItem(Item item) {
		int points = item.getPoints();
		score += points + (points * 0.2);
	}
	
	private int[] getRange() {
		return new int[] {-4, -3, -2, -1, 1, 2, 3, 4};
	}
	
	private ArrayList<Integer> freePositions(Direction direction, Map map) {
		ArrayList<Integer> validMoves = new ArrayList<Integer>();
		int xAxis = this.getPositionX();
		int yAxis = this.getPositionY();
		
		int[] range = getRange();

		for(int move: range) {
			if(shouldMoveXAxis(direction) && map.localIsFree(xAxis, yAxis + move)) {
				validMoves.add(move);
			} else if(map.localIsFree(xAxis + move, yAxis)) {
				validMoves.add(move);
			}
		}
		
		return validMoves;
	}
	
	private boolean jumpOffMap(Item item) {
		return item == null;
	}
	
	public boolean doMove(int moves, Direction direction, Map map) {
		Item collectedItem = new Floor("--");;
		int xAxis = this.getPositionX();
		int yAxis = this.getPositionY();

		if(shouldMoveYAxis(direction)) {
			if(map.localIsFree(xAxis + moves, yAxis)) {
			collectedItem = map.moveObject(xAxis + moves, yAxis, this);
			this.setPositionY(yAxis + moves);
			}
		} else if(shouldMoveXAxis(direction)) {
			if(map.localIsFree(xAxis, yAxis + moves)) {
				collectedItem = map.moveObject(xAxis, yAxis + moves, this);
				this.setPositionX(xAxis + moves);
			}
		}
	
		if(jumpOffMap(collectedItem)) {
			return false;
		} else {
			useItem(collectedItem);
			return true;
		}
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
	
	private Direction getRandomDirection() {
		int chooseDirection = (int)Math.floor(Math.random() * 2);
		return chooseDirection == 0 ? Direction.Y : Direction.X;
	}
	
	public boolean chooseMove(Map map) {
		Direction direction = getRandomDirection();
		ArrayList<Integer> validPositions = freePositions(direction, map);
		int moves = 0;
		
		if(!validPositions.isEmpty()) {
			moves = validPositions.get(randomPositionFrom(validPositions));
		}
		return doMove(moves, direction, map);
	}
	
	@Override
	public boolean moveUp(Map map) {
		return chooseMove(map);
	}

	@Override
	public boolean moveDown(Map map) {
		return chooseMove(map);
		
	}

	@Override
	public boolean moveLeft(Map map) {
		return chooseMove(map);
		
	}

	@Override
	public boolean moveRight(Map map) {
		return chooseMove(map);
	}	
}