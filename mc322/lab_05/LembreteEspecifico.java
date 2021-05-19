package com.unicamp.mc322.lab05;

import java.time.LocalDate;

public class LembreteEspecifico extends Lembrete {
	private LocalDate data;

	public LembreteEspecifico(String descricao, LocalDate data) {
		super(descricao);
		this.data = data;
	}
	
	public boolean ehNaData(LocalDate dataAtual) {
		return data.equals(dataAtual);
	}
	
	public boolean ehNoIntervaloDasDatas(LocalDate de, LocalDate ate) {
		return data.compareTo(de) >= 0 && data.compareTo(ate) <= 0;
	}
}
