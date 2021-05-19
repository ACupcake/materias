'''
O programa recebe um arquivo com os dados da imagem, e outro
com a matriz nucleo e o divisor. Utilizando o segundo arquivo
sera feita uma modificacao no arquivo da imagem com uma funcao
predefinida da soma dos produtos do pixel e seus vizinhos pela
matriz nucleo, divididos por um divisor d.
A saida sera a imagem modificada ponto a ponto (pixel), com o
mesmo cabecalho da primeira
'''

import sys

try:
#tratamento primeiro arquivo
##############################################
	#abre o arquivo 1 e quarda seu conteudo em leitura1 como matriz
	arquivo=open(sys.argv[1], "r")
	leitura1=arquivo.read()
	arquivo.close()
	leitura1=leitura1.split()

	#exclui itens inuteis da matriz
	#e pega numero de linha e colunas
	leitura1.pop(0)
	m=int(leitura1[0])
	leitura1.pop(0)
	n=int(leitura1[0])
	leitura1.pop(0)
	leitura1.pop(0)

	#cria uma matriz m por n com o conteudo da matriz "leitura1"
	matriz_imagem=[]
	k=0
	for i in range(0, n):
		matriz_imagem.append([])
		for j in range(0, m):
			matriz_imagem[i].append(int(leitura1[k]))
			k+=1

	#faz uma copia da matriz "matriz_imagem" em "modificado"
	modificado=[]
	for i in range (0, n):
		modificado.append([])
		for j in range(0, m):
			modificado[i].append(matriz_imagem[i][j])
##############################################


#tratamento do segundo arquivo
##############################################
	#le o conteudo do arquivo 2 e guarda em "leitura2" como matriz
	arquivo=open(sys.argv[2], "r")
	leitura2=arquivo.read()
	arquivo.close()
	leitura2=leitura2.split()

	#pega o valor do divisor e o exclui da matriz "leitura2"
	d=int(leitura2[0])
	leitura2.pop(0)

	#copia a "leitura2" na matriz "M"
	k=0
	M=[]
	for i in range(0, 3):
		M.append([])
		for j in range(0, 3):
			M[i].append(int(leitura2[k]))
			k+=1
##############################################


#criacao do terceito arquivo e saida
##############################################
	#percorre a matriz "matriz_imagem"
	has=True
	for i in range(1, n-1):
		for j in range(1, m-1):
			total=0
			posi1=-1
			posi2=-1
			#percorre a matriz "M" e faz a operacao de convolucao
			for k in range (0, 3):
				for l in range(0, 3):
					total=total+(M[k][l])*(matriz_imagem[i+posi2][j+posi1])
					posi1+=1
				posi1=-1
				posi2+=1
			#guarda na matriz "modificado" o valor retornado da funcao
			if(total<=0):
				modificado[i][j]=0
			elif(total/d>255):
				modificado[i][j]=255
			else:
				modificado[i][j]=int(total/d)

	#returna o conteudo do arquivo modificado como especificado
	print("P2")
	print(m,n)
	print(255)
	for i in range(0, n):
		for j in range(0, m):
			print(modificado[i][j], end=" ")
		print(" ")
##############################################


except Exception as ex:
	arquivo.close()
	print("Erro: ", end="")
	print(ex)