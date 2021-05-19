package com.unicamp.mc322.lab04;

import java.util.ArrayList;

public class Pedido {
	User user;
	EstadoPedido estado;
	Double preco;
	ArrayList<Lanche> arrayLanches;
	
	public Pedido(User user) {
		this.user = user;
		estado = EstadoPedido.NOVO;
		preco = 0.0;
		arrayLanches = new ArrayList<Lanche>();
	}
	
	void addItem(Lanche lanche) {
		arrayLanches.add(lanche);
	}
	
	private void calculaPreco() {
		for(Lanche lanche: arrayLanches) {
			preco += lanche.getPreco();
		}
		
		if(user.getNumeroDeCompras() == 0) {
			preco -= 20*preco/100;
		} else if(user.getNumeroDeCompras() % 10 == 0) {
			preco = preco <= 60 ? 0.0 : preco-60;
		} else if(preco > 100) {
			preco -= 10*preco/100;
		}
	}
	
	boolean atualizaEstado() {
		switch(estado) {
			case NOVO:
				estado = EstadoPedido.EM_PREPARACAO;
				calculaPreco();
				user.aumentaNumeroDeCompras();
				break;
			case EM_PREPARACAO:
				estado = EstadoPedido.SAIU_PARA_ENTREGA;
				break;
			case SAIU_PARA_ENTREGA:
				estado = EstadoPedido.ENTREGUE;
				break;
			default:
				return false;
		}
		return true;
	}
	
	public EstadoPedido getEstadoPedido() {
		return estado;
	}
	
	public boolean cancelaPedido() {
		if(estado == EstadoPedido.NOVO || estado == EstadoPedido.EM_PREPARACAO) {
			estado = EstadoPedido.CANCELADO;
			return true;
		} else {
			return false;
		}
	}
	
	public void imprimirPedido() {
		System.out.println("Usuário: " + user.getNome() + " (" + user.getCpf() + ")");
		for(Lanche lanche: arrayLanches) {
			System.out.println(" - " + lanche.getId());
		}
		System.out.println("Valor Total: R$" + preco);
	}
}
