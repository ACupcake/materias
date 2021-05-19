package com.unicamp.mc322.lab07;

public class Map {
	private int ySize;
	private int xSize;
	private Floor floor;
	private Item[][] map;
	
	public Map(int x, int y, String floorIcon) {
		this.xSize = x;
		this.ySize = y;
		map = new Item[x][y];
		floor = new Floor(floorIcon);
		buildMap();
	}
	
	private boolean foundEqualItem(int x, int y, int[][] marked, Item item) {
		return !outOfBounds(x, y) && marked[x][y] == 0 && map[x][y] == item;
	}

	private int countAdjacentItems(int x, int y, Item item, int[][] marked) {
		int count = 0;
		marked[x][y] = 1;
		int[] range = new int[] {-1, 0, 1};
		
		for(int i: range) {
			for(int j: range) {
				if(foundEqualItem(x+i, y+j, marked, item)) {
					marked[x+i][y+j] = 1;
					count += countAdjacentItems(x+i, y+i, map[x+i][y+j], marked) + 1;
				}
			}
		}

		return count;
	}
	
	public int getTotalAdjacentItems(int x, int y, Item item) {
		int[][] marked = new int[xSize][ySize];
		return countAdjacentItems(x, y, item, marked);
	}
	
	private boolean outOfBounds(int x, int y) {
		return x < 0 || x >= xSize || y < 0 || y >= ySize;
	}
	
	public boolean localIsFree(int x, int y) {
		if(outOfBounds(x, y) || map[x][y].canInteract()) {
			return true;
		}
		return false;
	}
	
	public Item moveObject(int toX, int toY, Item item) {		
		Item returnItem = null;
		if(outOfBounds(toX, toY)) {
			return null;
		} else if(localIsFree(toX, toY)) {
			returnItem = map[toX][toY];
			map[item.getPositionX()][item.getPositionY()] = floor;
			map[toX][toY] = item;
		}
		
		return returnItem;
	}

	public void setItemPositon(int x, int y, Item item) {
		if(!outOfBounds(x, y)) {
			if(!item.limitAdjacentItems()) {
				map[x][y] = item;
			} else if(getTotalAdjacentItems(x, y, item) <= item.maxAdjacentItems()){
				map[x][y] = item;
			}
		}
	}

	private void buildMap() {
		for(int i = 0; i < map.length; i++) {
			for(int j = 0; j < map[i].length; j++) {
				map[i][j] = floor;
			}
		}
	}

	public void printMap() {
		for(Item[] items: map) {
			for(Item item: items) {
				System.out.printf(item.getIcon() + " ");
			}
			System.out.println();
		}
	}
}
