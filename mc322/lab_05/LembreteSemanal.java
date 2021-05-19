package com.unicamp.mc322.lab05;

import java.time.DayOfWeek;

public class LembreteSemanal extends Lembrete {
	private DayOfWeek dia;
	
	public LembreteSemanal(String descricao, DayOfWeek dia) {
		super(descricao);
		this.dia = dia;
	}
	
	public boolean ehNaSemana(DayOfWeek day) {
		return dia.equals(day);
	}
	
	public boolean ehNoIntervaloDosDias(DayOfWeek de, DayOfWeek ate) {
		return dia.compareTo(de) >= 0 && dia.compareTo(ate) <= 0;
	}

}
