package com.unicamp.mc322.lab02;

public class Song {
	private String name;
	private String genre;
	private String artist;
	private int duration;

	public Song(String name, String genre, String artist) {
		this(name, genre, artist, 0);
	}

	public Song(String name, String genre, String artist, int duration) {
		this.name = name;
		this.genre = genre;
		this.artist = artist;
		this.duration = duration;
	}

	public boolean isAlphabeticallySmallerThan(Song song) {
		return this.getName().compareTo(song.getName()) > 0;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public void setArtist(String artist) {
		this.artist = artist;
	}

	public void setDuration(int duration) {
		this.duration = duration;
	}
	
	public void setGenre(String genre) {
		this.genre = genre;
	}
	
	public String getName() {
		return name;
	}
	
	public String getArtist() {
		return artist;
	}
	
	public int getDuration() {
		return duration;
	}
	
	public String getGenre() {
		return genre;
	}
}
