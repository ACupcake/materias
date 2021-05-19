package com.unicamp.mc322.lab02;

import java.util.LinkedList;

public class User {
	private String name;
	private String cpf;
	private String birth;
	private String genre;
	private Boolean subscriber;
	private LinkedList<Playlist> userPlaylist;

	public User(String name, String cpf, String birth, String genre, Boolean subscriber) {
		userPlaylist = new LinkedList<Playlist>();
		this.name = name;
		this.cpf = cpf;
		this.birth = birth;
		this.genre = genre;
		this.subscriber = subscriber;
	}

	public User(String name, String cpf) {
		this(name, cpf, null, null, false);
		this.name = name;
		this.cpf = cpf;
	}

	private boolean userCanAddPlayList(Playlist playlist) {
		if(this.isSubscriber() && userPlaylist.size() < 10) {
			return true;
		}
		if(!playlist.isPremiumPlaylist() && userPlaylist.size() < 3) {
			return true;
		}
		return false;
	}

	public boolean addPlaylist(Playlist playlist) {
		if(userCanAddPlayList(playlist)) {
			userPlaylist.add(playlist);
			this.setOwner(playlist);
			System.out.println("[*] A playlist " + playlist.getName() + " foi adicionada!");
			return true;
		} else {
			System.out.println("[!] A playlist " + playlist.getName() + " não foi adicionada!");
			return false;
		}
	}

	public void showPlaylists() {
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

	public void removePlaylist(Playlist playlistToRemove) {
		if(userPlaylist.remove(playlistToRemove) == true) {
			System.out.println("[*] A playlist " + playlistToRemove.getName() + " foi removida!");
		} else {
			System.out.println("[!] A playlist " + playlistToRemove.getName() + " não foi removida!");
		}
	}

	public void showInformation() {
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
	
	public boolean transferPlayList(Playlist playlist, User receiver) {
		if(transferenceSucceed(playlist, receiver)) {
			System.out.println("[*] A playlist " + playlist.getName() +
							   " foi transferida de " + receiver.getName() +
							   " para " + this.getName() + "!");
			return true;
		} else {
			System.out.println("[*] A playlist " + playlist.getName() +
			 				   "não pode ser transferida de " + receiver.getName() +
			 				   " para " + this.getName() + "!");
			return false;
		}
	}

	public void changeSubscription(boolean status) {
		subscriber = status;
		System.out.println("[*] A inscrição de " + this.getName() + " foi atualizada!");
	}
	
	public boolean isSubscriber() {
		return subscriber;
	}
	
	private void setOwner(Playlist playlist) {
		if(playlist.getOwner() == null) {
			playlist.setOwner(this);
		}
	}
	
	public String getName() {
		return this.name;
	}
}
