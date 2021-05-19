'''
O objetivo do programa eh, dado 4 empresas, encontrar os dias onde o lucro eh maximo.
Com uma entrada d (dias), recebemos d valores 4 vezes. Assim, encontramos quais são os dias de
investimento de maior retorno, tal que nao eh possivel haver interseccao entre os dias
nem entre as empresas, ou seja, ha a possibilidade de apenas uma compra por dia tal que se
ja houve uma compra em uma empresa x, esta empresa nao sera mais usada para a proxima compra.
A saida deve conter o lucro total e de cada empresa, alem dos dias de compra e o id da empresa.
'''

#recebe dias
d=int(input())

#recebe lista de acoes e gera lista de empresas
lista_acao=[]
for j in range (0, 4):
	lista_acao.append([])
	for i in range (0, d):
		lista_acao[j].append(float(input()))


lista_tudo=[]
n=0

#Teste para encontrar o lucro, e seus respectivos dias, para cada empresa.
for i in range (0, 4):
	lista_tudo.append([])
	n=0
	for j in range (0, d):
		for k in range (j+1, d):
			#Se preço de compra menos o de venda da empresa i for maior
			#que zero, eh guardado o lucro e os dias em uma lista.
			if(lista_acao[i][k]-lista_acao[i][j]>0):
				lista_tudo[i].append([])
				lista_tudo[i][n].append(lista_acao[i][k]-lista_acao[i][j])
				lista_tudo[i][n].append(j)
				lista_tudo[i][n].append(k)
				n+=1

#Para cada intervalo de lucro, se nao houver interseccao entre
#os dias, eh retornado o lucro total e os dados de cada empresa.
def intervalo_4(l1, l2, l3, l4):
	for w in range (l1[1]+1, l1[2]+1):
		for x in range (l2[1]+1, l2[2]+1):
			for y in range (l3[1]+1, l3[2]+1):
				for z in range (l4[1]+1, l4[2]+1):
					if(w==x or w==y or w==z or x==y or x==z or y==z):
						return 0
	
	data=[[l4[0]+l3[0]+l2[0]+l1[0]], [l1[1],l1[2],l1[0]], [l2[1],l2[2],l2[0]], [l3[1],l3[2],l3[0]], [l4[1],l4[2],l4[0]]]
	return (data)


def intervalo_3(l1, l2, l3):
	for w in range (l1[1]+1, l1[2]+1):
		for x in range (l2[1]+1, l2[2]+1):
			for y in range (l3[1]+1, l3[2]+1):
				if(w==x or w==y or x==y):
					return 0

	data=[[l3[0]+l2[0]+l1[0]], [l1[1],l1[2],l1[0]], [l2[1],l2[2],l2[0]], [l3[1],l3[2],l3[0]]]
	return (data)


def intervalo_2(l1, l2):
	for w in range (l1[1], l1[2]+1):
		for x in range (l2[1], l2[2]+1):
			if(w==x and l1[1]!=l2[2] and l2[1]!=l1[2]):
				return 0
	data=[[l2[0]+l1[0]], [l1[1],l1[2],l1[0]], [l2[1],l2[2],l2[0]]]
	return (data)


maior=0
check=True

#Se o lucro de todas as empresas for 0, o programa nao testa nada.
if(not(len(lista_tudo[0])==0 and len(lista_tudo[1])==0 and len(lista_tudo[2])==0 and len(lista_tudo[3])==0)):

	#Se uma, ou mais empresas, tem lucro 0, adicionamos	o maximo
	#de dias, assim, a empresa n sera incluida nos testes pois sua
	#interseccao com os dias de todas as empresas sempre existira.
	for i in range (0, 4):
		if(len(lista_tudo[i])==0):
			lista_tudo[i].append([])
			lista_tudo[i][0].append(0)
			lista_tudo[i][0].append(0)
			lista_tudo[i][0].append(d)
			check=False

	#para cada uma das empresas testamos
	for i in (lista_tudo[0]):
		for j in (lista_tudo[1]):
			for k in (lista_tudo[2]):
				for l in (lista_tudo[3]):

					testes=[i,j,k,l]

					#se uma das empresas tem lucro 0
					#ignoramos o teste onde as 4 tem lucro.
					if(check==True):
						#chama a funcao para verificar a interseccao
						#caso nao haja os dados das empresas serao retornados.
						m4=(intervalo_4(i,j,k,l))
						if(m4!=0):
							if(m4[0][0]>maior):
								#Se o lucro total que a funcao retornou for maior que
								#o anterior, seus dados sao guardados para uso posterior.
								maior=m4[0][0]
								empresa=[testes.index(i)+1, testes.index(j)+1, testes.index(k)+1, testes.index(l)+1]
								data=m4

					for t in testes:
						for q in testes:
							for y in testes:
								#t, q, y serao as empresas, se nao sao iguais
								#entre si, eh chamada a funcao para teste.
								if(t!=q and t!=y and q!=y):
									m3=(intervalo_3(t,q,y))
									if(m3!=0):
										if(m3[0][0]>maior):
											maior=m3[0][0]
											empresa=[testes.index(t)+1, testes.index(q)+1, testes.index(y)+1]
											data=m3
					for t in testes:
						for q in testes:
							if(t!=q):
								m2=(intervalo_2(t,q))
								if(m2!=0):
									if(m2[0][0]>maior):
										maior=m2[0][0]
										empresa=[testes.index(t)+1, testes.index(q)+1]
										data=m2
					if(i[0]>maior):
						maior=i[0]
						empresa=[1]
					if(j[0]>maior):
						maior=j[0]
						empresa=[2]
					if(k[0]>maior):
						maior=k[0]
						empresa=[3]
					if(l[0]>maior):
						maior=l[0]
						empresa=[4]

	#eh mostrado o lucro e os dados de cada empresa
	for i in range (1, len(data)):
		print("acao %d: compra %d, venda %d, lucro %.2f" % (empresa[i-1], data[i][0]+1, data[i][1]+1, data[i][2]))
	print("Lucro: %.2f" %maior)
#Se todas as empresas tem lucro 0, eh mostrado na tela.
else:
	print("Lucro: 0.00")