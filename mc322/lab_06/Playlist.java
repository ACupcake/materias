package com.unicamp.mc322.lab06;

import java.util.HashMap;
import java.util.LinkedList;

public class Playlist {
	private String name;
	private String genre;
	private LinkedList<Song> songs;
	private int totalDuration = 0;
	private int maxDuration = 0;
	private int minDuration = 0;
	private int currentSongPosition;
	private boolean premiumPlaylist;
	private User owner;
	private double storageSize;
	
	Playlist(String name, String genre) {
		songs = new LinkedList<Song>();
		this.name = name;
		this.genre = genre;
		this.currentSongPosition = 0;
		this.owner = null;
		this.premiumPlaylist = false;
		storageSize = 0;
	}

	private void updatePlaylist(Song song) {
		addAlphabetically(song);
		this.storageSize = song.getStorageSize() + this.storageSize;
		updatePremium();
		maxDuration = Math.max(song.getDuration(), maxDuration);
		minDuration = Math.min(song.getDuration(), minDuration);
		totalDuration += song.getDuration();
	}
	
	public double getStorageSize() {
		return this.storageSize;
	}

	private boolean onlyHas1MinItems() {
		for(Song song: songs) {
			if(song.getDuration() >= 1) {
				return false;
			}
		}
		return true;
	}
	
	private boolean validStorage(Song song) {
		if(onlyHas1MinItems()) {
			return true;
		}
		
		if(isOwnerDefined()) {
			boolean limitNotExceeded = (this.storageSize - song.getStorageSize()) >= 0;
			if(isPremiumPlaylist()) {
				return this.storageSize < 900 && limitNotExceeded;
			} else {
				return this.storageSize < 200 && limitNotExceeded;
			}
		} else {
			return true;
		}
	}

	boolean addItem(Song song) {
		if(!songs.contains(song) && validStorage(song)) {
			updatePlaylist(song);
			return true;
		} else {
			return false;
		}
	}

	private void addAlphabetically(Song song) {
		int position;
		for(position = 0; position < songs.size(); position++) {
			Song currentSong = songs.get(position);
			if(currentSong.isAlphabeticallySmallerThan(song)) {
				break;
			}
		}
		/* Add song at the end if it is bigger */
		songs.add(position, song);
	}

	private void updatePremium() {
		premiumPlaylist = (this.getStorageSize() > 200.0) ? true : false;
	}

	Song removeSong(Song song) {
		if(songs.remove(song) == true) {
			updatePremium();
			storageSize -= song.getStorageSize();
		}
		return song;
	}

	private int getNextSong() {
		if(currentSongPosition == getNumberOfSongs()) {
			currentSongPosition = 0;
		}
		return currentSongPosition++;
	}

	Song play() {
		Song currentSong = songs.get(getNextSong());
		System.out.println("Tocando: " + currentSong.getName());
		return currentSong;
	}

	Song play(Boolean shuffle) {
		if(!shuffle) {
			return play();
		}

		int position = currentSongPosition-1;
		if(getNumberOfSongs() > 1) {
			while(position == currentSongPosition-1) {
				position = (int) Math.floor(Math.random() * getNumberOfSongs());
			}
		}

		Song nextSong = songs.get(position);
		System.out.println("Tocando: " + nextSong.getName());
		
		return nextSong;
	}

	private int artistCurrentSongCount(HashMap<String, Integer> artistMap, String artist) {
		if(!artistMap.containsKey(artist)) {
			return 1;
		} else {
			return artistMap.get(artist) + 1;
		}
	}

	String getArtistWithMostSongs() {
		HashMap<String, Integer> artistMap = new HashMap<String, Integer>();
		String artistWithMostSongs = null;
		int maxNumberOfSongs = 0;

		for(Song song: songs) {
			String artist = song.getArtist();
			int totalArtistSongs = artistCurrentSongCount(artistMap, artist);
			artistMap.put(artist, totalArtistSongs);

			if(totalArtistSongs > maxNumberOfSongs) {
				maxNumberOfSongs = totalArtistSongs;
				artistWithMostSongs = artist;
			}
		}
		
		return artistWithMostSongs;
	}

	boolean setOwner(User user) {
		if(!isOwnerDefined()) {
			owner = user;
			if(user.isSubscriber()) {
				premiumPlaylist = true;
			} else {
				premiumPlaylist = false;
			}
			return true;
		} else {
			return false;
		}
	}

	void showSongList() {
		for(Song song: songs) {
			System.out.println("\t- " + song.getName() + " - " + song.getArtist());
		}
	}

	private boolean isOwnerDefined() {
		return owner != null;
	}
	
	boolean isPremiumPlaylist() {
		return premiumPlaylist;
	}

	int getSmallestDuration() {
		return minDuration;
	}

	int getBiggestDuration() {
		return maxDuration;
	}
	
	int getAverageDuration() {
		return getTotalDuration() / songs.size();
	}

	int getTotalDuration() {
		return totalDuration;
	}
	
	int getNumberOfSongs() {
		return songs.size();
	}
	
	String getName() {
		return name;
	}
	
	User getOwner() {
		return owner;
	}
	
	void showGenre() {
		System.out.print(getGenre());
	}
	
	private String getGenre() {
		return genre;
	}
	
}
