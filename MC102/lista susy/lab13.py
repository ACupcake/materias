'''
Houve um apocalipse zumbi e eh necessario estimar sua propagacao, as entradas sao
numero de linhas, colunas e valores da matriz de pessoas, alem do numero de dias.
0 indica vazio, 1 indica humano e 2 indica zumbi. Se x for zumbi e ao seu redor
existir mais de dois ou nenhum humano x morre. Se x for humano e ao seu redor
existir um zumbi x morre. Se x for vazio e ao seu redor estiverem 2 humanos, exatamente,
x vira humano. Na saida sera mostrado a interacao atual (dia) e a matriz de elementos.
'''

#funcao para mostrar a matriz
def mostra(mat, n, m):
	for i in range(1, n+1):
		for j in range(1, m+1):
			print(mat[i][j], end="")
		print("")

#funcao para realizar interacoes
def acao(cont, n, m):
	#percorre matriz
	for i in range(1, n+1):
		for j in range(1, m+1):
			h=0
			z=0
			#percorre elementos em volta do elemento cont[i][j]
			#e conta zumbis e humanos.
			for k in range (i-1, i+2):
				for g in range (j-1, j+2):
					if(not(k==i and j==g)):
						if(matriz[k][g]==1):
							h+=1
						if(matriz[k][g]==2):
							z+=1
			#verifica cada possibilidade de interacao
			if(matriz[i][j]==1 and z>0):
				cont[i][j]=2
			elif(matriz[i][j]==2 and h>1):
				cont[i][j]=0
			elif(matriz[i][j]==2 and h==0):
				cont[i][j]=0
			elif(matriz[i][j]==0 and h==2):
				cont[i][j]=1
	return cont

#entrada com especificacoes da matriz
m=[int(x) for x in input().split()]
#dias
i=int(input())

matriz=[]
#adiciona uma linha preenchida por -1 no inicio da matriz
matriz.append([])
for p in range (0, m[1]+2):
	matriz[0].append(-1)

#adiciona os valores recebidos na matriz com fim e inicio igual a -1
for k in range (1, m[0]+1):
	matriz.append([])
	matriz[k].append(-1)
	matriz[k]+=[int(x) for x in input().split()]
	matriz[k].append(-1)

#adiciona uma linha preenchida por -1 no fim da matriz
matriz.append([])
for p in range (0, m[1]+2):
	matriz[k+1].append(-1)

conta=[]
#mostra e realiza as interacoes i(dias) vezes
for k in range(0, i+1):
	print("iteracao %d" %(k))
	mostra(matriz, m[0], m[1])
	#copia a matriz "matriz" para a matriz "conta"
	conta=[]
	for pa in range (0, len(matriz)):
		conta.append([])
		conta[pa]+=matriz[pa].copy()
	matriz=acao(conta, m[0], m[1])