package com.unicamp.mc322.lab07;

public class Item {
	private String icon;
	private int positionX;
	private int positionY;

	public Item(String icon, int x, int y) {
		this.icon = icon;
		this.positionX = x;
		this.positionY = y;
	}

	public boolean limitAdjacentItems() {
		return false;
	}
	
	public int maxAdjacentItems() {
		return 0;
	}
	
	public Item(String icon) {
		this.icon = icon;
	}
	
	public String getIcon() {
		return icon;
	}

	public boolean canInteract() {
		return true;
	}
	
	public int getPositionX() {
		return positionX;
	}
	
	public int getPositionY() {
		return positionY;
	}
	
	public void setPositionY(int y) {
		positionY = y;
	}
	
	public void setPositionX(int x) {
		positionX = x;
	}
	
	public int getPoints() {
		return 0;
	}
}