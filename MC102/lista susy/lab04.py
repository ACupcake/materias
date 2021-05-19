'''

O programa recebe 4 valores que representam pesos e tenta
encontrar equilíbrio em uma balança com os mesmos.
O programa mostra "sim" caso o equilíbrio possa ser feito,
e "nao" caso contrário.

'''

#Verifica todas as permutações de pesos
def temPermutacaoValida(peso):
	permutacaoEhValida = False

	for permutacao in range(4):
		if(peso[0] == peso[1] + peso[2] + peso[3]):
			permutacaoEhValida = True
		elif(peso[0] + peso[1] == peso[2] + peso[3]):
			permutacaoEhValida = True
		elif(peso[0] + peso[3] == peso[2] + peso[1]):
			permutacaoEhValida = True
		elif(peso[0] + peso[1] + peso[2] == peso[3]):
			permutacaoEhValida = True
		#Permuta peso
		primeiroPeso = peso[0]
		peso[0] = peso[permutacao]
		peso[permutacao] = primeiroPeso

	return permutacaoEhValida

#Lê pesos
p1 = int(input())
p2 = int(input())
p3 = int(input())
p4 = int(input())

peso = [p1,p2,p3,p4]

if(permutacaoEhValida(peso)):
	print("sim")
else:
	print("nao")
