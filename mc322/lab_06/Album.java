package com.unicamp.mc322.lab06;

import java.util.ArrayList;

public class Album extends Song {
	private ArrayList<Song> songs;
	private double albumStorageSize;
	private int totalSongs;
	
	Album(String name, int duration, int songs) {
		super(name, "", "", duration);
		this.albumStorageSize = 0;
		setStorageSize(albumStorageSize);
		totalSongs = songs;
	}

	void addSong(Song song) {
		songs.add(song);
		setAuthor();
		albumStorageSize += song.getStorageSize();
	}

	void removeSong(Song song) {
		if(songs.remove(song))
			albumStorageSize -= song.getStorageSize();
	}
	
	private void setAuthor() {
		String author = songs.get(0).getArtist();
		
		for(Song song: songs) {
			if(!song.getArtist().equals(author)) {
				setArtist("Vários autores");
				return;
			}
		}
		setArtist(author);
	}
	
	
}
