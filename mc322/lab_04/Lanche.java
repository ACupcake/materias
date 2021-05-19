package com.unicamp.mc322.lab04;

public class Lanche {
	private String nome;
	private String ID;
	private double preco;
	private double desconto;
	
	public Lanche(String ID, String nome, double preco) {
		this.nome = nome;
		this.preco = preco;
		this.ID = ID;
		desconto = 0;
	}
	
	public String getId() {
		return ID;
	}
	
	public double getPreco() {
		return preco;
	}

	public boolean adicionarDesconto(double valor, TipoDesconto tipoDeDesconto) {
		if(desconto != 0) {
			return false;
		}
		
		if(tipoDeDesconto == TipoDesconto.PORCENTAGEM) {
			desconto = (preco * valor / 100);
			preco -= desconto;
		} else if(tipoDeDesconto == TipoDesconto.FIXO) {
			desconto = valor;
			preco -= desconto;
		}
		
		return true;
	}
	
	public void removerDesconto() {
		preco += desconto;
		desconto = 0;
	}
	
	public void mostrarInfo() {
		System.out.print("[" + ID + "] " + nome + " R$ " + preco);
		if(desconto != 0) {
			System.out.print(" (PROMOÇÃO! Preço normal: R$ " + (preco+desconto) + ")");
		}
		System.out.println();
	}
}
