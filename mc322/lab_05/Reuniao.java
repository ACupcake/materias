package com.unicamp.mc322.lab05;

import java.util.ArrayList;
import java.time.LocalDate;

public class Reuniao extends LembreteEspecifico {
	private ArrayList<Convidado> convidados;

	private class Convidado {
		private Contato contato;
		private boolean confirmouPresenca;
		
		public Convidado(Contato contato, boolean presenca) {
			this.contato = contato;
			confirmouPresenca = presenca;
		}
		
		public void confirmarPresenca() {
			confirmouPresenca = true;
		}
		
		public boolean confirmouPresenca() {
			return confirmouPresenca;
		}
	}

	public Reuniao(String descricao, LocalDate data, ArrayList<Contato> pessoas) {
		super(descricao, data);
		gravarContatos(pessoas);
	}
	
	public void adicionarContato(Contato pessoa) {
		convidados.add(new Convidado(pessoa, false));
	}
	
	private void gravarContatos(ArrayList<Contato> pessoas) {
		for(Contato contato: pessoas) {
			adicionarContato(contato);
		}
	}

	private boolean foiConvidado(Contato contato) {
		int indice = getIndiceDoConvidado(contato);
		if(indice == -1) {
			return false;
		} else {
			return true;
		}
	}

	private int getIndiceDoConvidado(Contato contato) {
		int indice = 0;
		for(Convidado convidado: convidados) {
			if(convidado.contato.equals(contato))
				return indice;
			indice++;
		}
		return -1;
	}

	private Convidado getConvidadoDaLista(Contato contato) {
		int indice = getIndiceDoConvidado(contato);
		if(indice != -1)
			return convidados.get(indice);
		else
			return null;
	}

	public void confirmaPresenca(Contato contato) {
		if(foiConvidado(contato)) {
			getConvidadoDaLista(contato).confirmarPresenca();
		}
	}

	public boolean confirmouPresenca(Contato contato) {
		if(foiConvidado(contato)) {
			return getConvidadoDaLista(contato).confirmouPresenca();
		} else {
			return false;
		}
	}
}
