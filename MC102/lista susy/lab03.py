'''
O programa recebe 5 valores, os quais os dois primeiros sao
diametro e altura respectivamente e os 3 ultimos sao os postos a,b,c.
Um caminhao deve realizar o abastecimento dos 3 postos, se o
esse nao tem gasolina suficiente, o posto atual eh ignorado
passando para o proximo.
A saida  informa quais postos foram reabastecidos e quais nao foram.
'''

diametro=float(input())
altura=float(input())
a=float(input())
b=float(input())
c=float(input())

#lista de nomes e valores dos postos
n_postos=["A","B","C"]
postos=[a,b,c]
contador=0 #contador sera utilizado para percorrer a lista de nomes no loop
raio=diametro/2
gasolina_caminhao=3.14*raio*raio*altura*1000 #multiplicado por 1000 para a conversao m3 para L

#verifica e reabastece postos
for gasolina_posto in postos:
	if(gasolina_caminhao>gasolina_posto):
		print("gasolina_posto %s foi reabastecido" %(n_postos[contador]))
		gasolina_caminhao=gasolina_caminhao-gasolina_posto
	else:
		print("gasolina_posto %s nao foi reabastecido" %(n_postos[contador]))
	contador+=1
