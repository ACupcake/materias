package com.unicamp.mc322.lab05;

import java.time.Month;

public class LembreteMensal extends Lembrete {
	Month mes;
	
	public LembreteMensal(String descricao, Month mes) {
		super(descricao);
		this.mes = mes;
	}
	
	public boolean ehNoMes(Month month) {
		return mes.equals(month);
	}
	
	public boolean ehNoIntervaloDosMeses(Month de, Month ate) {
		return mes.compareTo(de) >= 0 && mes.compareTo(ate) <= 0;
	}
}
