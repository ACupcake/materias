'''

O objetivo do programa eh calcular, baseado em resultados passados,
o valor do poder de combate futuro de uma dado pokemae.
Recebemos uma quantidade n de dados contendo id do pokemae, poder de
combate inicial e poder de combate final (depois da evolucao).
Depois recebemos m valores contendo o id e o pca atual de um dado
pokemae, ate as duas entradas serem 0. Mostramos na tela todos os
poderes de combate final dos m pokemaes.
'''

import math

#recebemos o numero n de pokemaes e a matriz de valores
n=int(input())
pokemaes=[]
for i in range (0, n):
	pokemaes.append(0)
	pokemaes[i] = input().split()

#guardamos a matriz de valore em outra matriz
temp=[]
for i in range (0, n):
	temp.append(pokemaes[i])


pcf=[]
j=0
i=0
total=0

#enquanto de pokemaes for maior do que i continuamos o loop
while(i<n):
	j=0
	num=1
	
	#somamos os valores de todos os pokemons de mesmo id
	soma=(int(temp[i][2])/int(temp[i][1]))

    #se o id for igual ao q verificamos, somamos a 'soma'
    #e removemos esse valore da matriz temporaria.
	while(j<n):
		if(temp[i][0]==temp[j][0] and i!=j):
			soma=soma+(int(temp[j][2])/int(temp[j][1]))
			num+=1
			temp.pop(j)
			n-=1
		else:
			j+=1

        #apos somar todos os multiplicadores de um dado pokemae
        #calculamos sua media
	if(num!=0):
		total=total+1
		media=soma/num
		pcf.append([])
		pcf[i].append(int(temp[i][0]))
		pcf[i].append(media)

	else:
		total=total+1
		pcf.append([])
		pcf[i].append(temp[i][0])
		pcf[i].append(temp[i][1])
	i+=1

#recebemos os pokemaes para o calculo futuro
i, pca = [int(x) for x in input().split()]

#enquanto os valores para o calculo futuro nao forem 0 continuamos
while(i!=0 and pca!=0):
	#calculamos o multiplicador para todos os pokemaes e mostramos
	for j in range (0, total):
		if(pcf[j][0]==i):
			print(math.ceil(pcf[j][1]*pca))
	i, pca = [int(x) for x in input().split()]
