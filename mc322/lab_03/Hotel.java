package com.unicamp.mc322.lab03;

public class Hotel {
	private static final int MAXIMO_DE_QUARTOS = 100;
	
	private String nome;
	private String endereco;
	private String telefone;
	private float precoNormal;
	private float precoVip;
	private Room[] roomArray;
	private int quartosVipVagos;
	private int quartosNormaisVagos;

	Hotel(String nome, String endereco, String telefone, float precoNormal, float precoVip) {
		this.nome = nome;
		this.endereco = endereco;
		this.telefone = telefone;
		this.precoNormal = precoNormal;
		this.precoVip = precoVip;
		roomArray = new Room[MAXIMO_DE_QUARTOS];
		quartosNormaisVagos = 90;
		quartosVipVagos = 10;
	}

	private void mostrarQuartosVipsDisponiveis() {
		for(int i = 0; i < 10; i++) {
			if(quartoEstaDisponivel(i)) {
				System.out.print(i+1 + " ");
			}
		}
		System.out.println();
	}

	private void mostrarQuartosDisponiveis() {
		for(int i = 10; i < MAXIMO_DE_QUARTOS; i++) {
			if(quartoEstaDisponivel(i)) {
				System.out.print(i+1 + " ");
			}
		}
		System.out.println();
	}

	boolean quartoEstaDisponivel(int numero) {
		return !(roomArray[numero].estaOcupado());
	}
	
	boolean quartoEhVip(int numero) {
		return numero <= 10;
	}

	void estadoDoHotel() {
		System.out.println("Hotel " + this.nome);
		if(!quartoEstaInstanciado(0)) {
			System.out.println("Quartos vips ainda n�o foram construidos no hotel!");
		} else {
			System.out.println(" |" + quartosVipVagos + " quartos vips est�o dispon�veis pelo pre�o de " + precoVip);
			System.out.println(" |Servi�os:");
			System.out.println("[+] Aceita Fumantes: " + roomArray[0].getAceitaFumantes());
			System.out.println("[+] Possui Ar Condicionado: " + roomArray[0].getArCondicionado());
			System.out.print(" |Quartos dispon�veis: ");
			mostrarQuartosVipsDisponiveis();
		}
		
		if(!quartoEstaInstanciado(0)) {
			System.out.println("Quartos n�o vip ainda n�o foram construidos no hotel!");
		} else {
			System.out.println(" |" + quartosNormaisVagos + " quartos normais est�o dispon�veis pelo pre�o de " + precoNormal);
			System.out.println(" |Servi�os:");
			System.out.println("[+] Aceita Fumantes: " + roomArray[11].getAceitaFumantes());
			System.out.println("[+] Possui Ar Condicionado: " + roomArray[11].getArCondicionado());
			System.out.print(" |Quartos dispon�veis: ");
			mostrarQuartosDisponiveis();
		}
	}

	void adicionaQuartos(Room normal, Room vip) {
		
		if(vip.ehVip()) {
			for(int i = 0; i < 10; i++) {
				roomArray[i] = new Room(vip.ehVip(), vip.getAceitaFumantes(), vip.getArCondicionado());
			}
		} else {
			System.out.println("Quarto n�o est� definido como vip!");
		}
	
		if(!normal.ehVip()) {
			for(int i = 10; i < MAXIMO_DE_QUARTOS; i++) {
				roomArray[i] = new Room(normal.ehVip(), normal.getAceitaFumantes(), normal.getArCondicionado());
			}
		} else {
			System.out.println("Quarto n�o est� definido como normal!");
		}
	}
	
	boolean quartoEstaInstanciado(int numero) {
		return roomArray[numero] != null;
	}

	boolean criarReserva(User user, int numeroQuarto, int dias) {
		numeroQuarto--;
		
		if(!quartoEstaInstanciado(numeroQuarto)) {
			System.out.println("Esse quarto ainda n�o foi construido no hotel!");
			return false;
		}
		
		if(quartoEstaDisponivel(numeroQuarto)) {
			if(user.ehFumante() && !roomArray[numeroQuarto].getAceitaFumantes()) {
				System.out.println("Quarto " + (numeroQuarto+1) + " n�o aceita fumantes!");
			} else if(quartoEhVip(numeroQuarto)) {
				if(user.temSaldoSuficiente(precoVip)) {
					user.removeSaldo(precoVip);
					roomArray[numeroQuarto].reservar(user);
					quartosVipVagos--;
					System.out.println("Reserva vip criada: " + dias + " dia(s), Quarto " + (numeroQuarto+1) +
									   ", Hotel " + this.nome);
					return true;
				} else {
					System.out.println("Usu�rio n�o tem saldo suficiente!");
				}
			} else {
				if(user.temSaldoSuficiente(precoNormal)) {
					user.removeSaldo(precoNormal);
					roomArray[numeroQuarto].reservar(user);
					quartosNormaisVagos--;
					System.out.println("Reserva normal criada: " + dias + " dia(s), Quarto " + (numeroQuarto+1) +
							   ", Hotel " + this.nome);
					return true;
				} else {
					System.out.println("Usu�rio n�o tem saldo suficiente!");
				}
			}
		} else {
			System.out.println("Quarto n�mero " + (numeroQuarto+1) + " n�o est� dispon�vel");
		}
		
		return false;
	}

	boolean cancelarReserva(User user, int numeroQuarto) {
		numeroQuarto--;
		if(!quartoEstaInstanciado(numeroQuarto)) {
			System.out.println("Esse quarto ainda n�o foi construido no hotel!");
			return false;
		}
		
		if(roomArray[numeroQuarto].estaOcupadoPor(user)) {
			if(roomArray[numeroQuarto].ehVip()) {
				user.reembolsar(precoVip);
				quartosVipVagos++;
			} else {
				user.reembolsar(precoNormal);
				quartosNormaisVagos++;
			}
			roomArray[numeroQuarto].cancelarReserva();
			System.out.println("Reserva cancelada: Quarto " + (numeroQuarto+1) +
					           ", Hotel " + this.nome);
			return true;
		} else {
			System.out.println("Usu�rio n�o � hospede no quarto " + (numeroQuarto+1));
		}
		return false;
	}	
	
}
