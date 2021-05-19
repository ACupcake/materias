'''

O programa simula uma luta, numeros positivos, na entrada, significam
os danos causados, numeros negativos, na entrada, significam danos sofridos.
Existe uma acumulo de dano, caso o dano causado/sofrido ocorra duas ou
mais vezes.
Tambem existe uma multiplicacao no dano, multiplicamos por 3 caso o dano
seja um numero perfeito, e por 2 caso seja triangular.
Perde quem chegar a 0, ou menos, primeiro.
Sao duas rodadas, caso o um jogador chegue a 0, ou menos, em duas rodadas
seguidas, eh mostrado na tela o ganhador. Se cada um dos
jogadores perder uma partida, eh mostrado "empate" na tela.

'''

#win_ryu e win_ken sao utilizadas para contabilizar
#o numero de partidas ganhas por cada jogador.
win_ryu=int(0)
win_ken=int(0)

#como a luta tem duas rodadas, utilizamos um range de 0 ate 2 (0, 2-1).
for i in range (0,2):

	#vida_ryu e vida_ken mostram a vida de cada jogador,
	#last_atk sera o ultimo dano causado e
	#combo eh a soma de dano que cada jogador recebe.
	vida_ryu=int(2000)
	vida_ken=int(2000)
	last_atk=int(0)
	combo=int(0)
	perfeito=False

	#se a vida de um dos jogadores for menor ou igual
	#a zero o loop para
	while(vida_ryu>0 and vida_ken>0):

		#atk eh a entrada de dano
		#soma eh a soma dos numeros anteriores a "atk"
		atk=int(input())
		soma=0

		#Aqui verificamos se o numero eh perfeito
		for j in range (1, abs(atk)):
			#Se a soma dos divisores de atk eh igual
			#a ele mesmo, entao multiplicamos este por 3
			#e definimos "perfeito como verdadeiro".
			if(abs(atk)%j==0):
				soma+=j
			if(abs(atk)==soma):
				atk=atk*3
				perfeito==True
		
		#Aqui verificamos se o numero eh triangular
		#Se "perfeito" eh False entao podemos prosseguir.
		if(perfeito==False):
			soma=0
			n=0
			#Se a soma dos n numeros menores que "atk"
			#for igual a este, multiplicamos atk por 2.
			while(soma<abs(atk)):
				soma=soma+n
				n+=1
			if(soma==abs(atk)):
				atk=atk*2



		'''
		Se o dano e o ultimo ataque forem maiores que 0
		e a vida do "Ken" for menor que a soma de combo e do
		ultimo ataque, mostramos na tela o que ocorreu e
		subtraimos o como e o ultimo ataque da vida de "Ken".
		'''
		if(atk>0 and last_atk>0 and vida_ken-combo-atk<=0):
			last_atk=atk
			print("Ken: %d - %d = %d" %(vida_ken, combo+atk, vida_ken-combo-atk))
			vida_ken=vida_ken-combo-atk

		#Aqui invertemos o bloco acima, para "Ryu".
		elif(atk<0 and last_atk<0 and vida_ryu-combo+atk<=0):
			#Como o ataque eh negativo, multiplicamos por -1 para
			#Somar com combo.
			last_atk=atk
			print("Ryu: %d - %d = %d" %(vida_ryu,combo+(-1)*atk,vida_ryu-combo+atk))
			vida_ryu=vida_ryu-combo+atk

		
		#Se "atk" e "last_atk" sao diferentes, agora outro jogador ataca
		#Verificamos se o ultimo ataque eh maior que a vida
		#do outro jogador. Se sim Subtraimos o ataque da vida.
		
		elif(atk<0 and last_atk>0 and vida_ryu+atk<=0):
			#Aqui verificamos se ha algum ataque acumulado em combo
			#se sim temos vida-combo, se nao temos vida-ataque
			if(combo>0):
				print("Ken: %d - %d = %d" %(vida_ken,combo,vida_ken-combo))
				vida_ken=vida_ken-combo
			elif(combo<=0):
				print("Ken: %d - %d = %d" %(vida_ken,last_atk,vida_ken-last_atk))
				vida_ken=vida_ken-last_atk

			#salvamos o ultimo ataque em "last_atk" e mostramos na tela
			#o ataque.
			last_atk=atk
			print("Ryu: %d - %d = %d" %(vida_ryu,atk*(-1),vida_ryu+atk))
			vida_ryu=vida_ryu+atk


		#Inverte o bloco acima para a vez do jogador Ken.
		elif(atk>0 and last_atk<0 and vida_ken-atk<=0):
			if(combo>0):
				print("Ryu: %d - %d = %d" %(vida_ryu,combo,vida_ryu-combo))
				vida_ryu=vida_ryu-combo
			elif(combo<=0):
				print("Ryu: %d - %d = %d" %(vida_ryu,last_atk,vida_ryu-last_atk))
				vida_ryu=vida_ryu-last_atk

			last_atk=atk
			print("Ken: %d - %d = %d" %(vida_ken,atk,vida_ken-atk))
			vida_ken=vida_ken-atk

		else:
			'''
			Se o "atk" for menor que 0, Ken ataca
			e se o "last_atk" for menor que 0
			ele ja havia atacado anteriormente.
			Logo, temos um combo e podemos
			somar "atk" e "last_atk
			''' 
			if(atk<0 and last_atk<=0):
				combo=combo+atk*(-1)
				#Se a vida do Ryu menos o combo do Ken for 
				#menor ou igual a 0, a vida do Ryu zera.
				if(vida_ryu-combo<=0):
					print("Ryu: %d - %d = %d" %(vida_ryu,combo,vida_ryu-combo))
					vida_ryu=vida_ryu-combo


			#Se atk>0 e last_atk<0 trocou
			#e mostramos a vida menos o combo antes de trocar
			if(atk>0 and last_atk<0):
				print("Ryu: %d - %d = %d" %(vida_ryu,combo,vida_ryu-combo))
				vida_ryu=vida_ryu-combo


			#Aqui invertemos o ultimo bloco para a vez do jogador "Ken"
			if(atk>0 and last_atk>=0):
				combo=combo+atk

				if(vida_ken-combo<=0):
					print("Ken: %d - %d = %d" %(vida_ken,combo,vida_ken-combo))
					vida_ken=vida_ken-combo

			if(atk<0 and last_atk>0):
				print("Ken: %d - %d = %d" %(vida_ken, combo, vida_ken-combo))
				vida_ken=vida_ken-combo

			'''
			Se "atk" e "last_atk" forem contrarios, em
			relacao ao sinal, entao agora outro jogador
			esta dando um golpe.
			Zeramos o combo, e passamos a somar o(s) ataque(s)
			do outro jogador.
			'''
			if(atk>0 and last_atk<0):
				combo=0
				combo=combo+atk

			if(atk<0 and last_atk>0):
				combo=0
				combo=combo+atk*(-1)


			#guardamos o ataque do jogador para
			#comparar a rodada.
			last_atk=atk

	#se a vida de algum dos jogadores for menor que 0
	#somamos 1 a sua variavel de vitorias
	if(vida_ryu<=0):
		win_ken+=1
	if(vida_ken<=0):
		win_ryu+=1

#aqui verificamos se uma das variaveis eh igual a dois
#e mostramos o vencedor.
#Se forem iguais, entre si, mostramos o empate.
if(win_ryu==win_ken):
	print("empatou")
if(win_ryu==2):
	print("Ryu venceu")
if(win_ken==2):
	print("Ken venceu")