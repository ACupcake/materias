
#O programa tem como objetivo resolver jogos de sudoku
#A entrada consiste em uma matriz de numeros tal que onde ha
#o valor 0, eh necessario preencher com um numero de 1 a 9
#A saida eh uma matriz preenchida caso seja encontrado uma solucao
#e igual a matriz de entrada se nao for encontrado solucao

#!/usr/bin/env python3

# Funcao: print_sudoku
# Essa funcao ja esta implementada no arquivo lab20_main.py
# A funcao imprime o tabuleiro atual do sudoku de forma animada, isto e,
# imprime o tabuleiro e espera 0.1s antes de fazer outra modificacao.
# Voce deve chamar essa funcao a cada modificacao na matriz resposta, assim
# voce tera uma animacao similar a apresentada no enunciado.
# Essa funcao nao tem efeito na execucao no Susy, logo nao ha necessidade de
# remover as chamadas para submissao.
from lab20_main import print_sudoku

# O aluno pode criar outras funcoes que ache necessario

# Funcao: resolve
# Resolve o Sudoku da matriz resposta.
# Retorna True sae encontrar uma resposta, False caso contrario

#Retorna limites da subgrade atual
def verif_sub_grade(valor,resposta):
	minimo=valor
	while(minimo>=3):
		minimo-=3
	maximo=3-minimo
	minimo=minimo*(-1)
	return (minimo,maximo)

#Verifica se numeros da linha, coluna e da subgrade sao diferentes de k
def verifica_nums(a,b,k,resposta):
	#Verifica linha e coluna
	for j in range(0, 9):
		if(resposta[a][j]==k and j!=b):
			return False
		if(resposta[j][b]==k and j!=a):
			return False
	#Verifica subgrade
	a_min,a_max=verif_sub_grade(a, resposta)
	b_min,b_max=verif_sub_grade(b, resposta)
	for i in range(a+a_min, a+a_max):
		for j in range(b+b_min, b+b_max):
			if(resposta[i][j]==k):
				return False
	#Se nenhuma das verificacoes encontrou um numero igual a k, eh retornado "True"
	return True

#Funcao que age com recursao para encontrar os numeros da matriz proposta
def recursao(resposta, a, b):
	#Caso o numero seja diferente de 0, eh passado para a proxima celula
	#ou retornado o a matriz caso chegue ao fim.
	if(resposta[a][b]!=0):
		#Condicao de parada
		if(a==8 and b==8):
			return resposta
		#Pula celulas da matriz
		elif(b==8):
			retorno=recursao(resposta,a+1, 0)
		else:
			retorno=recursao(resposta,a,b+1)
	else:
		for k in range(1, 10):
			#Se nao ha um numero igual a k na linha, coluna ou subgrade, k eh valido
			if(verifica_nums(a,b,k,resposta)==True):
				resposta[a][b]=k
				#Condicao de parada
				if(a==8 and b==8):
					return resposta
				#Passa para a proxima celula.
				elif(b==8):
					retorno=recursao(resposta,a+1, 0)
				else:
					retorno=recursao(resposta,a,b+1)
				if(retorno==resposta):
					return resposta
		#Caso nenhum valor se encaixe na celula atual ela eh zerada e eh retornado falso
		resposta[a][b]=0
		return False

	#Caso nenhum valor se encaixe na celula atual eh retornado falso,
	#caso um se encaixe retornamos a matriz com o valor.
	if(retorno==False):
		return False
	else:
		return resposta

def resolve(resposta):
	#Copia matriz resposta para comparacao posterior
	copia=[]
	for i in range(0, 9):
		copia.append([])
		copia[i]+=resposta[i]

	#Chama a recursao
	resposta=recursao(resposta,0,0)
	print_sudoku(resposta)

	#Se a matriz "resposta" for igual a copia da entrada, retorna "False",
	#caso contrario retorna "True"
	if(resposta==copia):
		return False
	else:
		return True