package com.unicamp.mc322.lab04;

public class User {
	private String nome;
	private String cpf;
	private Endereco endereco;
	private int numeroDeCompras;
	
	public User(String nome, String cpf, int x, int y) {
		this.nome = nome;
		this.cpf = cpf;
		this.endereco = new Endereco(x, y);
	}
	
	public int getNumeroDeCompras() {
		return numeroDeCompras;
	}
	
	public void aumentaNumeroDeCompras() {
		numeroDeCompras++;
	}
	
	public String getNome() {
		return nome;
	}
	
	public String getCpf() {
		return cpf;
	}
}
