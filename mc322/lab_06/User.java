package com.unicamp.mc322.lab06;

import java.util.LinkedList;

public class User {
	private String name;
	private String cpf;
	private String birth;
	private String genre;
	private Boolean subscriber;
	private LinkedList<Playlist> userPlaylist;
	private int capacity;

	User(String name, String cpf, String birth, String genre, Boolean subscriber) {
		userPlaylist = new LinkedList<Playlist>();
		this.name = name;
		this.cpf = cpf;
		this.birth = birth;
		this.genre = genre;
		this.subscriber = subscriber;
		setCapacity();
	}

	User(String name, String cpf) {
		this(name, cpf, null, null, false);
		this.name = name;
		this.cpf = cpf;
	}

	private boolean userCanAddPlayList(Playlist playlist) {
		if(capacity <= 0) {
			return false;
		}
		if(this.isSubscriber()) {
			return true;
		}
		if(!playlist.isPremiumPlaylist()) {
			return true;
		}
		return false;
	}

	boolean addPlaylist(Playlist playlist) {
		if(userCanAddPlayList(playlist)) {
			userPlaylist.add(playlist);
			this.setOwner(playlist);
			capacity -= playlist.getStorageSize();
			return true;
		} else {
			return false;
		}
	}

	void showPlaylists() {
		System.out.println("User: " + name);
		System.out.println("Number of Playlists: " + userPlaylist.size());
	
		int currentPlaylist = 1;

		for(Playlist playlist: userPlaylist) {
			System.out.println("Playlist " + currentPlaylist + ": " + playlist.getName());
			System.out.println("	Number of songs: " + playlist.getNumberOfSongs());
			System.out.println("	Songs:");
			playlist.showSongList();
			currentPlaylist++;
		}	
	}

	void removePlaylist(Playlist playlistToRemove) {
		if(userPlaylist.remove(playlistToRemove) == true)
			capacity += playlistToRemove.getStorageSize();
	}

	void showInformation() {
		System.out.println("Nome: " + name);
		System.out.println("CPF: " + cpf);
		System.out.println("Nascimento: " + birth);
		System.out.println("Gênero: " + genre);
		System.out.println("Assinatura: " + subscriber);
	}

	private boolean transferenceSucceed(Playlist playlist, User receiver) {
		if(playlist.getOwner() != this) {
			return false;
		} else if(playlist.isPremiumPlaylist() && !receiver.isSubscriber()) {
			return false;
		} else {
			return receiver.addPlaylist(playlist);
		}		
	}
	
	boolean transferPlayList(Playlist playlist, User receiver) {
		if(transferenceSucceed(playlist, receiver)) {
			return true;
		} else {
			return false;
		}
	}

	void changeSubscription(boolean status) {
		subscriber = status;
		setCapacity();
	}
	
	boolean isSubscriber() {
		return subscriber;
	}

	private void setCapacity() {
		if(isSubscriber()) {
			capacity = 900;
		} else {
			capacity = 200;
		}
	}
	
	private void setOwner(Playlist playlist) {
		if(playlist.getOwner() == null) {
			playlist.setOwner(this);
		}
	}
	
	String getName() {
		return this.name;
	}
}
