'''

O programa tem como entrada um numero n que sera usado para mostrar
uma matriz n por n. Ha dois lacos 'for' o primeiro de 1 ate n+1 linhas
cujo objetivo é mostrar uma quebra de linha e entrar no segundo 'for'.
O segundo eh de 1 ate n+1 colunas e testa se a divisao eh linhas por
coluna, ou coluna por linhas eh igual a 0, caso verdadeiro a saida eh
um asterisco(*), caso falso a saida eh um menos(-).
'''

#recebe um numero n e numero de divisores como 0.
n=int(input())
divs=0

#a cada novo valor mostramos uma quebra de linha e vamos para o prox loop
for i in range (1, n+1):
	

	#de 1 ate n+1, testamos se  i eh divisivel por j
	#e se j eh divisivel por i
	for j in range (1, n+1):
		#se verdadeiro somamos 1 em 'divs' e mostramos um asterisco(*).
		if(j%i==0 or i%j==0):
			print("*", end='')
			divs+=1
		#caso contrario mostramos um menos(-).
		else:
			print("-", end='')
	print("")
#No fim pulamos uma linha e mostramos o numero de divisoes feitas (divs).
#print("")
print(divs)