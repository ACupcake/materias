package com.unicamp.mc322.lab06;

public class Video extends Song{
	private double fps;
	private int screenWeight;
	private int screenLength;
	private final double BYTE = 1048576;

	Video(String name, String artist, int duration, int screenWeight, int screenLength, double fps) {
		super(name, "", artist, duration);
		this.fps = fps;
		this.screenWeight = screenWeight;
		this.screenLength = screenLength;
		setStorageSize(getVideoSize(duration, screenWeight, screenLength, fps));
	}

	private double getVideoSize(int duration, int screenWeight, int screenLength, double fps) {
		int pixels = screenWeight * screenLength;
		return (audioSize() + videoSize(pixels, fps)) * duration;
	}

	private double audioSize() {
		return 5.0 / 60.0; // 5 MB/minute
	}
	
	private double videoSize(double pixels, double fps) {
		return pixels * fps / BYTE;
	}
}


