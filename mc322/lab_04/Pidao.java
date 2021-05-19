package com.unicamp.mc322.lab04;

import java.util.HashSet;
import java.util.HashMap;

public class Pidao {
	private String nome;
	private String cnpj;
	private Endereco endereco;
	private HashSet<User> usuarios;
	private HashMap<String, Lanche> cardapio;
	private HashSet<Pedido> pedidos;
	
	public Pidao(String nome, String cnpj, int x, int y) {
		this.nome = nome;
		this.cnpj = cnpj;
		this.endereco = new Endereco(x, y);
		usuarios = new HashSet<User>();
		cardapio = new HashMap<String, Lanche>();
		pedidos = new HashSet<Pedido>();
	}
	
	User cadastrarUsuario(String nome, String cpf, int x, int y) {
		User novoUser = new User(nome, cpf, x, y);
		usuarios.add(novoUser);
		return novoUser;
	}
	
	public boolean idFoiCadastrado(Lanche lanche) {
		return cardapio.containsKey(lanche.getId());
	}
	
	void adicionarAoCardapio(Lanche lanche) {
		if(idFoiCadastrado(lanche) == false) {
			cardapio.put(lanche.getId(), lanche);
		}
	}
	
	void imprimirCardapio() {
		System.out.println("Restaurante " + nome);
		System.out.println("(CNPJ: " + cnpj + ")\n");
		System.out.println("Cardapio de hoje:");
		cardapio.forEach((ID, pedido) -> pedido.mostrarInfo());
		System.out.println();
	}
	
	void imprimirResumoPedidos() {
		System.out.println("Existem " + pedidos.size() + " pedidos:");
		System.out.println("============================================");
		
		for(Pedido pedido: pedidos) {
			pedido.imprimirPedido();
			System.out.println("============================================");
		}
	}
	
	void aplicarDesconto(String id, double valor, TipoDesconto tipoDeDesconto) {
		Lanche lanche = cardapio.get(id);
		lanche.adicionarDesconto(valor, tipoDeDesconto);
	}

	void removerDesconto(String id) {
		Lanche lanche = cardapio.get(id);
		lanche.removerDesconto();	
	}
	
	void fazerPedido(Pedido pedido) {
		pedidos.add(pedido);
		pedido.atualizaEstado();
	}

	boolean cancelaPedido(Pedido pedido) {
		return pedido.cancelaPedido();
	}
	
	boolean atualizaEstado(Pedido pedido) {
		return pedido.atualizaEstado();
	}
}
