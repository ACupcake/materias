package com.unicamp.mc322.lab03;

public class Room {
	private boolean ehVip;
	private boolean estaOcupado;
	private boolean aceitaFumantes;
	private boolean possuiArCondicionado;
	private int diasReservados;
	private User hospede;

	Room(boolean ehVip, boolean aceitaFumantes, boolean possuiArCondicionado) {
		this.ehVip = ehVip;
		this.estaOcupado = false;
		this.aceitaFumantes = aceitaFumantes;
		this.possuiArCondicionado = possuiArCondicionado;
	}

	boolean estaOcupado() {
		return estaOcupado;
	}

	boolean reservar(User user, int dias) {
		if(!estaOcupado) {
			hospede = user;
			estaOcupado = true;
			diasReservados = dias;
			return true;
		} else {
			return false;
		}
	}

	boolean cancelarReserva() {
		if(estaOcupado) {
			hospede = null;
			estaOcupado = false;
			diasReservados = 0;
			return true;
		} else {
			return false;
		}
	}
	
	int getDiasReservados() {
		return diasReservados;
	}
	
	boolean ehVip() {
		return ehVip;
	}
	
	public boolean estaOcupadoPor(User user) {
		return user == hospede;
	}
	
	boolean getAceitaFumantes() {
		return aceitaFumantes;
	}
	
	boolean getArCondicionado() {
		return aceitaFumantes;
	}
}
