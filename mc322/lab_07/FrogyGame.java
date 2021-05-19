package com.unicamp.mc322.lab07;

import java.util.Scanner;

public class FrogyGame {
	private Map map;
	private Frog frog;

	public void runGame() {
		
		Scanner keyboard = new Scanner(System.in);
		boolean running = true;
		
		while (running) {
			map.printMap();
			System.out.printf("Enter the command: ");
			
			String command = keyboard.nextLine().toLowerCase();
			if (command.compareTo("quit") == 0) {
				running = false;
			} else if (command.compareTo("w") == 0) {
				running = frog.moveUp(map);
			} else if (command.compareTo("a") == 0) {
				running = frog.moveLeft(map);
			} else if (command.compareTo("s") == 0) {
				running = frog.moveDown(map);
			} else if (command.compareTo("d") == 0) {
				running = frog.moveRight(map);
			}
		}

		System.out.println("Pontuação final: " + frog.score());
	}

	private void generateMap() {
		this.map = new Map(10, 10, "--");
		RockObstacle rock = new RockObstacle("<>");
		map.setItemPositon(2, 7, rock);
		map.setItemPositon(3, 2, rock);
		map.setItemPositon(7, 1, rock);
		map.setItemPositon(8, 4, rock);
		map.setItemPositon(8, 8, rock);

		PredatorObstacle predator = new PredatorObstacle("$$");
		map.setItemPositon(4, 4, predator);
		map.setItemPositon(5, 5, predator);
	
		TrapObstacle trap = new TrapObstacle("{}");
		map.setItemPositon(0, 0, trap);
		map.setItemPositon(0, 1, trap);

		FireflyFood firefly = new FireflyFood("firefly", "va");
		map.setItemPositon(1, 3, firefly);
		
		CricketFood cricket = new CricketFood("cricket", "gr");
		map.setItemPositon(4, 7, cricket);

		this.frog = new GreenFrog("Jogador 1", "J1", 8, 7);
		map.setItemPositon(8, 7, frog);
		
	}
	
	public static void main(String args[]) {
		FrogyGame frogygame = new FrogyGame();
		frogygame.generateMap();
		frogygame.runGame();
	}
}