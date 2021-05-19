package com.unicamp.mc322.lab03;

public class User {
	private String nome;
	private String cpf;
	private String nascimenpackage com.unicamp.mc322.lab03;

public class User {
	private String nome;
	private String cpf;
	private String nascimento;
	private String genero;
	private float saldo;
	private boolean ehFumante;
	
	User(String nome, String cpf, String nascimento, String genero, float saldo, boolean ehFumante) {
		this.nome = nome;
		this.cpf = cpf;
		this.nascimento = nascimento;
		this.genero = genero;
		this.saldo = saldo;
		this.ehFumante = ehFumante;
	}
	
	void mostrarInfo() {
		System.out.println("Nome: " + nome +
						   "\nCPF: " + cpf +
						   "\nNascimento: " + nascimento +
						   "\nGênero: " + genero +
						   "\nÉ Fumante: " + ehFumante +
						   "\nSaldo: " + saldo);
	}
	
	void mostrarSaldo() {
		System.out.println("Saldo: " + saldo);
	}
	
	boolean temSaldoSuficiente(float deposito) {
		return saldo >= deposito;
	}

	boolean reembolsar(float precoQuarto) {
		saldo += (precoQuarto * 0.70);
		return true;
	}

	boolean removeSaldo(float retirada) {
		if(saldo >= retirada) {
			saldo -= retirada;
			return true;
		}
		return false;
	}
	
	boolean ehFumante() {
		return ehFumante;
	}
}
to;
	private String genero;
	private float saldo;
	private boolean ehFumante;
	
	User(String nome, String cpf, String nascimento, String genero, float saldo, boolean ehFumante) {
		this.nome = nome;
		this.cpf = cpf;
		this.nascimento = nascimento;
		this.genero = genero;
		this.saldo = saldo;
		this.ehFumante = ehFumante;
	}
	
	void mostrarInfo() {
		System.out.println("Nome: " + nome +
						   "\nCPF: " + cpf +
						   "\nNascimento: " + nascimento +
						   "\nGênero: " + genero +
						   "\nÉ Fumante: " + ehFumante +
						   "\nSaldo: " + saldo);
	}
	
	void mostrarSaldo() {
		System.out.println("Saldo: " + saldo);
	}
	
	boolean temSaldoSuficiente(float deposito) {
		return saldo >= deposito;
	}

	boolean reembolsar(float precoQuarto) {
		saldo += (precoQuarto * 0.70);
		return true;
	}

	boolean removeSaldo(float retirada) {
		if(saldo >= retirada) {
			saldo -= retirada;
			return true;
		}
		return false;
	}
	
	boolean ehFumante() {
		return ehFumante;
	}
}
