package com.unicamp.mc322.lab03;

public class Booking {
	public static void main(String[] args) {
		Booking booking = new Booking();
		
		//1
		Hotel hotel1 = new Hotel("Praia Tropical", "Rua Tajubá, 201 - Florianópolis, SC; 3225-8997", "", 100, 900);
		Hotel hotel2 = new Hotel("Campo Florestal","Rua Monteiro, 456 - Goiânia, GO; 3654-8974", "", 50, 2000);
		
		//2
		User user1 = new User("Roberci Silva", "784245698-21", "12/04/1996", "Masculino", 1000, true);
		User user2 = new User("Marcela Domingues", "269784061-45", "22/07/1998", "Feminino", 2000, false);
		
		//3
		Room room1 = new Room(false, false, false);
		Room room2 = new Room(true, true, true);

		hotel1.adicionaQuartos(room1, room2);
		hotel2.adicionaQuartos(room1, room2);
	
		//4
		booking.criarReserva(user1, hotel1, 2, 1);
		booking.criarReserva(user2, hotel2, 13, 4);

		//5
		booking.criarReserva(user1, hotel1, 87, 1);

		//6
		booking.cancelarReserva(user2, hotel1, 22);

		//7
		booking.criarReserva(user1, hotel2, 99, 1);

		//8
		booking.cancelarReserva(user1, hotel2, 99);

		//9
		booking.criarReserva(user2, hotel2, 87, 1);

		System.out.println();
		hotel1.estadoDoHotel();
		System.out.println();
		hotel2.estadoDoHotel();

	}

	private boolean criarReserva(User user, Hotel hotel, int numeroQuarto, int dias) {
		return hotel.criarReserva(user, numeroQuarto, dias);
	}
	
	private boolean cancelarReserva(User user, Hotel hotel, int numeroQuarto) {
		return hotel.cancelarReserva(user, numeroQuarto);
	}
}
