package com.unicamp.mc322.lab05;

import java.util.LinkedList;
import java.time.LocalDate;

public class Agenda {
	private LinkedList<Lembrete> lembretes;

	public Agenda() {
		lembretes = new LinkedList<Lembrete>();
	}

	public void adicionarLembrete(Lembrete lembrete) {
		lembretes.add(lembrete);
	}

	public void cancelarLembrete(Lembrete lembrete) {
		lembretes.remove(lembrete);
	}

	public void confirmaPresenca(Lembrete lembrete, Contato contato) {
		if(lembrete instanceof Reuniao) {
			((Reuniao) lembrete).confirmaPresenca(contato);
		}
	}

	private boolean verificaSeDataEstaNoIntervalo(LocalDate de, LocalDate ate, Lembrete lembrete) {
		if(lembrete instanceof Lembrete) {
			return true;
		} else if(lembrete instanceof LembreteMensal) {
			return ((LembreteMensal) lembrete).ehNoIntervaloDosMeses(de.getMonth(), ate.getMonth());
		} else if(lembrete instanceof LembreteSemanal) {
			return ((LembreteSemanal) lembrete).ehNoIntervaloDosDias(de.getDayOfWeek(), ate.getDayOfWeek());
		} else if(lembrete instanceof LembreteEspecifico) {
			return ((LembreteEspecifico) lembrete).ehNoIntervaloDasDatas(de, ate);
		}
		return false;
	}

	private void mostraLembretes(LocalDate de, LocalDate ate) {
		for(Lembrete lembrete: lembretes) {
			if(verificaSeDataEstaNoIntervalo(de, ate, lembrete)) {
				lembrete.mostrarDescricao();
			}
		}
	}

	public void mostraLembretesDoDiaAtual() {
		mostraLembretes(LocalDate.now(), LocalDate.now());
	}

	public void mostraLembretesDoDia(LocalDate diaAtual) {
		mostraLembretes(diaAtual, diaAtual);
	}

	public void mostraLembretesDoIntervalo(LocalDate de, LocalDate ate) {
		mostraLembretes(de, ate);
	}
}
