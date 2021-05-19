package com.unicamp.mc322.lab02;

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

	public Playlist(String name, String genre) {
		songs = new LinkedList<Song>();
		this.name = name;
		this.genre = genre;
		this.currentSongPosition = 0;
		this.owner = null;
		this.premiumPlaylist = false;
	}

	private void updatePlaylist(Song song) {
		addAlphabetically(song);
		premiumPlaylist = (getNumberOfSongs() > 10) ? true : false;
		maxDuration = Math.max(song.getDuration(), maxDuration);
		minDuration = Math.min(song.getDuration(), minDuration);
		totalDuration += song.getDuration();
	}
	
	public boolean addSong(Song song) {
		if(getNumberOfSongs() == 100 || songs.contains(song)) {
			System.out.println("[!] Não foi possível adicionar" + song.getName() +
					           " a playlist " + this.getName() + "!");
			return false;
		} else {
			updatePlaylist(song);
			System.out.println("[*] Música " + song.getName() + " adiciona a playlist!");
			return true;
		}
	}

	public void addAlphabetically(Song song) {
		int position;
		for(position = 0; position < songs.size(); position++) {
			Song currentSong = songs.get(position);
			if(currentSong.isAlphabeticallySmallerThan(song)) {
				break;
			}
		}
		songs.add(position, song);
	}

	public Song removeSong(Song song) {
		if(songs.remove(song) == true) {
			System.out.println("[*] " + song.getName() + " foi removida!");
		} else {
			System.out.println("[!] Não foi possível remover " + song.getName() + "!");
		}
		return song;
	}

	private int getNextSong() {
		if(currentSongPosition == getNumberOfSongs()) {
			currentSongPosition = 0;
		}
		return currentSongPosition++;
	}

	public Song play() {
		Song currentSong = songs.get(getNextSong());
		System.out.println("Tocando: " + currentSong.getName());
		return currentSong;
	}

	public Song play(Boolean shuffle) {
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

	public String getArtistWithMostSongs() {
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

	public boolean setOwner(User user) {
		if(!isOwnerDefined()) {
			owner = user;
			if(user.isSubscriber()) {
				this.setPremium();
			}
			System.out.println("[*] " + user.getName() +
							   " agora é dono da playlist " + this.getName() + "!");
			return true;
		} else {
			System.out.println("[!] Não foi possível definir " + user.getName() +
						   " como dono da playlist " + this.getName() + "!");
			return false;
		}
	}

	public void showSongList() {
		for(Song currentSong: songs) {
			System.out.println("	- " + currentSong.getName() + " - " + currentSong.getArtist());
		}
	}

	private boolean isOwnerDefined() {
		return owner != null;
	}
	
	public boolean isPremiumPlaylist() {
		return premiumPlaylist;
	}
	
	private void setPremium() {
		premiumPlaylist = true;
	}

	public int getSmallestDuration() {
		return minDuration;
	}

	public int getBiggestDuration() {
		return maxDuration;
	}
	
	public int getAverageDuration() {
		return getTotalDuration() / songs.size();
	}
	
	public int getTotalDuration() {
		return totalDuration;
	}
	
	public int getNumberOfSongs() {
		return songs.size();
	}
	
	public String getName() {
		return name;
	}
	
	public User getOwner() {
		return owner;
	}
	
	public String getGenre() {
		return genre;
	}
	
}
