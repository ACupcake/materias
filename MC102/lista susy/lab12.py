'''
O objetivo eh saber de onde vira o ataque inimigo,
para isso recebemos uma frase e, a partir de palavras chave,
conferimos a existencia de coordenadas.
'''

#quardamos a frase em "frase"
frase=input()

#convertemos tudo para caixa baixa e
#separamos em uma lista por espaco
frase=frase.lower()
frase=frase.split( )

#listas palavras para comparacao
direcao=[["mercurio", "N"],["venus", "NE"],["terra", "L"],["marte", "SE"],["jupiter", "S"],["saturno", "SO"],["urano", "O"],["netuno", "NO"]]
elevacao=[["verde", 30], ["amarelo", 45], ["vermelho", 60]]

#para cada i na frase
for i in frase:
	#para cada j na lista comparamos a i
	#se for igual mostramos na tela.
	for j in range(0, len(direcao)):
		if(i==direcao[j][0]):
			print(direcao[j][1], end=' - ')

	for j in range(0, len(elevacao)):
		if(i==elevacao[j][0]):
			print(elevacao[j][1])

