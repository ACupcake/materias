package com.unicamp.mc322.lab06;

public class PodcastChannel extends Song {
	private int numberOfEpisodes;
	private static int storageSizeUnit = 1;

	PodcastChannel(String name, String artist, int duration, int episodes) {
		super(name, "", artist, duration);
		this.numberOfEpisodes = episodes;
		setStorageSize(duration * storageSizeUnit / 60);
	}
}
