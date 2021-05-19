#!/usr/bin/env python3
#*******************************************************************************
# Funcao: atualizaTabela
#
# Parametros:
#   tabela: uma matriz com os dados da tabela do campeonato
#   jogo: string contendo as informações de um jogo no formato especificado no lab.
#
# Descrição:
#   Deve inserir as informações do parametro 'jogo' na tabela.
#   OBSERVAÇÃO: nesse momento não é necessário ordenar a tabela, apenas inserir as informações.
def atualizaTabela(tabela, jogo):
	jogo=jogo.split() #separa elementos de "jogo"
	empate=0
	#Verifica resultado da partida
	if(jogo[1]>jogo[3]):
		venceu=[jogo[0], int(jogo[1])]
		perdeu=[jogo[4], int(jogo[3])]
	elif(jogo[1]<jogo[3]):
		venceu=[jogo[4], int(jogo[3])]
		perdeu=[jogo[0], int(jogo[1])]
	else:
		empate=1
	#Atribui valores
	if(empate==1):
		for i in range(len(tabela)):
			if(tabela[i][0]==jogo[4]):
				tabela[i][1]+=1
				tabela[i][3]=tabela[i][3]+int(jogo[3])-int(jogo[1])
				tabela[i][4]+=int(jogo[3])
			if(tabela[i][0]==jogo[0]):
				tabela[i][1]+=1
				tabela[i][3]=tabela[i][3]+int(jogo[1])-int(jogo[3])
				tabela[i][4]+=int(jogo[1])		
	else:
		for i in range(len(tabela)):
			if(tabela[i][0]==venceu[0]):
				tabela[i][1]+=3
				tabela[i][2]+=1
				tabela[i][3]=tabela[i][3]+venceu[1]-perdeu[1]
				tabela[i][4]+=venceu[1]
			if(tabela[i][0]==perdeu[0]):
				tabela[i][3]=tabela[i][3]+perdeu[1]-venceu[1]
				tabela[i][4]+=perdeu[1]
#*******************************************************************************

#*******************************************************************************
# Funcao: comparaTimes
#
# Parametros:
#   time1: informações de um time
#   time2: informações de um time
#
# Descricão:
#   retorna 1, se o time1>time2, retorna -1, se time1<time2, e retorna 0, se time1=time2
#   Observe que time1>time2=true significa que o time1 deve estar em uma posição melhor do que o time2 na tabela.
def comparaTimes(time1, time2):
	for i in range (1, 5):
		if(time1[i]>time2[i]):
			return 1
		elif(time2[i]>time1[i]):
			return -1
	return 0
#*******************************************************************************


#*******************************************************************************
# Funcao: ordenaTabela
#
# Parametros:
#   tabela: uma matriz com os dados da tabela do campeonato.
#
# Descricão:
#   Deve ordenar a tabela com campeonato de acordo com as especificaçoes do lab.
#
def ordenaTabela(tabela):
	for i in range(len(tabela)):
		for j in range(i+1, len(tabela)):
			compara=comparaTimes(tabela[i], tabela[j])
			if(compara==-1):
				aux=tabela[j]
				tabela[j]=tabela[i]
				tabela[i]=aux		
#*******************************************************************************


#*******************************************************************************
# Funcao: imprimeTabela
#
# Parametros:
#   tabela: uma matriz com os dados da tabela do campeonato.
#
# Descrição:
#   Deve imprimir a tabela do campeonato de acordo com as especificações do lab.
def imprimeTabela(tabela):
	for i in range (len(tabela)):
		for k in range (len(tabela[i])-1):
			print(tabela[i][k], end=", ")
		print(tabela[i][k+1], end="")
		print("")
#*******************************************************************************