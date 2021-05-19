package com.unicamp.mc322.lab05;

public class Lembrete {
	private String descricao;
	
	public Lembrete(String descricao) {
		this.descricao = descricao;
	}
	
	public void mostrarDescricao() {
		System.out.println(descricao);
	}
}
