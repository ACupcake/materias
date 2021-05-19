package com.unicamp.mc322.lab06;

public class Musicfy {
	public static void main(String[] args) {

		User user1 = new User("Marcos Paulo", "777.777.777-77");
		User user2 = new User("Cookiezi", "111.111.111-11");
		User user3 = new User("Jose da Padaria", "999.999.999-99");

		Song song1 = new Song("Seven Nation Army", "Rock", "The White Stripes", 60);
		Song song2 = new Song("Crazy Train", "Rock", "Ozzy Osbourne", 120);
		Song song3 = new Song("Feels", "Pop", "Calvin Harris", 120);
		Song song4 = new Song("Roar", "Pop", "Katy Perry", 120);
		Song song5 = new Song("Anima", "Hardcore", "Xi", 120);
		Song song6 = new Song("Freedom Dive", "Hardcore", "Xi", 120);
		Song song7 = new Song("Teo", "Hardcore", "Omoi", 120);
		Song song8 = new Song("Sleepwalking", "Metalcore", "Bring Me The Horizon", 120);
		
		Video video = new Video("Video de gatos", "random person", 50, 640, 360, 30.0);
		PodcastChannel podcast = new PodcastChannel("Mike Tyson", "Mike Tyson", 9236, 3);
		Song song = new Song("Lua", "Xama", "album", 120);
		Album album = new Album("Album Grande", 1800, 13);

		Playlist randomPlaylist = new Playlist("Coisas aleatorias", "Tudo");
		//randomPlaylist.addItem(video);
		randomPlaylist.addItem(podcast);
		randomPlaylist.addItem(song);
		randomPlaylist.addItem(album);
		
		Playlist rockPlaylist = new Playlist("Awesome Rock Songs", "Rock");
		rockPlaylist.addItem(song1);
		rockPlaylist.addItem(song2);

		Playlist osuPlaylist = new Playlist("Osu Memories", "hardcore");
		osuPlaylist.addItem(song5);
		osuPlaylist.addItem(song6);
		osuPlaylist.addItem(song7);

		Playlist metalcorePlaylist = new Playlist("Best of Metalcore", "Metalcore");
		metalcorePlaylist.addItem(song8);

		user1.addPlaylist(rockPlaylist);
		user1.addPlaylist(metalcorePlaylist);
		user2.addPlaylist(osuPlaylist);
		user3.addPlaylist(randomPlaylist);

		user1.showPlaylists();
		System.out.println("");
		user2.showInformation();
		System.out.println("");
		user3.showInformation();
		System.out.println("");
		user3.showPlaylists();
		System.out.println("");
		
		Song asong1 = osuPlaylist.play();
		Song asong2 = osuPlaylist.play();
		Song asong3 = osuPlaylist.play(true);
	}
}