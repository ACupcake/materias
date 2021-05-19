package com.unicamp.mc322.lab04;

public class Runner {

	public static void main(String[] args) {
		Pidao pidaoApp = new Pidao("MARAMBAR", "123.456.789-10", 10, 2);
		
		User user1 = pidaoApp.cadastrarUsuario("Marcos Paulo", "123.789.643-11", 1, 2);
		User user2 = pidaoApp.cadastrarUsuario("Pereira", "123.789.643-11", 8, 4);
		
		Lanche cuscuz = new Lanche("CCZ00", "Cuscuz com ovo", 10.00);	
		Lanche macaxeira = new Lanche("MXCOS", "Macaxeira com costela no bafo", 15.00);
		Lanche coxinhaFrango = new Lanche("CXFRA", "Coxinha de frango", 8.00);
				
		pidaoApp.adicionarAoCardapio(cuscuz);
		pidaoApp.adicionarAoCardapio(macaxeira);
		pidaoApp.adicionarAoCardapio(coxinhaFrango);
		
		pidaoApp.aplicarDesconto("CCZ00", 10, TipoDesconto.PORCENTAGEM);
		
		Pedido p1 = new Pedido(user1);
		p1.addItem(cuscuz);
		p1.addItem(macaxeira);
		pidaoApp.fazerPedido(p1);
				
		Pedido p2 = new Pedido(user2);
		p2.addItem(coxinhaFrango);
		p2.addItem(coxinhaFrango);
		pidaoApp.fazerPedido(p2);
		
		Pedido p3 = new Pedido(user2);
		p3.addItem(coxinhaFrango);
		p3.addItem(coxinhaFrango);
		pidaoApp.fazerPedido(p3);
		
		pidaoApp.imprimirCardapio();
		
		pidaoApp.imprimirResumoPedidos();
	}

}
