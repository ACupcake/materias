package com.unicamp.mc322.lab06;

public class Song {
	private String name;
	private String genre;
	private String artist;
	private int duration;
	private double storageSize;
	private static int storageSizeUnit = 5;

	Song(String name, String genre, String artist, int duration) {
		this.name = name;
		this.genre = genre;
		this.artist = artist;
		if(duration >= 0)
			this.duration = duration;
		else
			this.duration = 0;
		setStorageSize(duration * storageSizeUnit / 60); //auto set to music but can be changed
	}

	public void setStorageSize(double storageSize) {
		if(storageSize >= 0)
			this.storageSize = storageSize;
	}

	public double getStorageSize() {
		return storageSize;
	}
	
	boolean isAlphabeticallySmallerThan(Song song) {
		return this.getName().compareTo(song.getName()) > 0;
	}
	
	void setName(String name) {
		this.name = name;
	}
	
	void setArtist(String artist) {
		this.artist = artist;
	}

	void setDuration(int duration) {
		this.duration = duration;
	}
	
	void setGenre(String genre) {
		this.genre = genre;
	}
	
	String getName() {
		return name;
	}
	
	String getArtist() {
		return artist;
	}
	
	int getDuration() {
		return duration;
	}
	
	String getGenre() {
		return genre;
	}
}
