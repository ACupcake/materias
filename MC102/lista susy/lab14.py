'''
Programa para sistema de gerenciamento da DAC, capaz de realizar operações
como impressão, ordenação, inclusão, remoção e busca de alunos matriculados em cada turma.
A entrada contem um vetor de ra's e, apos, a acao a ser efetuada, juntamente a um ra caso
necessario.
Como saida sera mostrada na tela a acao requerida pelo usuario, "p" para mostrar os ra's
b para mostrar a posicao de um ra e como a busca foi feita, as outras entradas possuem
mensagens de alerta caso uma acao tenha sido feita de maneira invalida ou caso esta nao
possa ser concluida.
'''

#faz busca binaria e retorna o indice, caso nao encontre retorna -1
def buscaBin(vet, ra, ordem):
	ini=0
	fim=len(vet)-1
	while(ini<=fim):
		meio=(ini+fim)//2
		#mostra em que posicao a procura esta
		print(meio, end=" ")
		if(vet[meio]==ra):
			print("")
			return meio
		#procura em ordem crescente
		elif(vet[meio]>ra and ordem==1):
			fim=meio-1
		#procura em ordem decrescente
		elif(vet[meio]<ra and ordem==2):
			fim=meio-1
		else:
			ini=meio+1
	print("")
	return -1

#busca um a um e retorna indice, caso nao encontre retorna -1
def buscaLinear(vet, ra):
	for i in range(len(vet)):
		if(vet[i]==ra):
			return i
	return -1

#recebe vetor de ra's
alunos=[int(i) for i in input().split()]

#ordem da lista, 0=nao ordenado, 1=ordem crescente, 2=ordem descrente
ordem=0
entrada=""

#loop de entradas do usuario, enquanto entrada!=s continua o loop,
#a entrada eh recebida no fim do loop
while(entrada!="s"):
	#mostra o vetor "alunos"
	if(entrada=="p"):
		for i in range(len(alunos)):
			print(alunos[i], end=" ")
		if(len(alunos)!=1):
			print("")

	#ordena o vetor "alunos" de forma crescente
	#caso "entrada" seja igual a "c"
	elif(entrada=="c"):
		for i in range(len(alunos)):
			aux=alunos[i]
			j=i-1
			while(j>=0 and alunos[j]>aux):
				alunos[j+1]=alunos[j]
				j=j-1
			alunos[j+1]=aux
		ordem=1

	#ordena o vetor "alunos" de forma decrescente
	#caso "entrada" seja igual a "d"
	elif(entrada=="d"):
		for i in range(len(alunos)):
			aux=alunos[i]
			j=i-1
			while(j>=0 and alunos[j]<aux):
				alunos[j+1]=alunos[j]
				j=j-1
			alunos[j+1]=aux
		ordem=2

	#faz busca binaria caso "entrada" seja igual a "b"
	#e o vetor "alunos" esteja ordenado
	elif(entrada=="b"):
		if(ordem==0):
			print("Vetor nao ordenado!")
		else:
			pos=buscaBin(alunos, ra, ordem)
			if(pos==-1):
				print("%d nao esta na lista!"%(ra))
			else:
				print("%d esta na posicao: %d"%(ra, pos))

	#insere ra caso "entrada" seja igual a "i"
	elif(entrada=="i"):
		if(len(alunos)>=150):
			print("Limite de vagas excedido!")
		#busca ra na lista e mostra mensagem caso nao encontre
		elif(buscaLinear(alunos, ra)!=-1):
			print("Aluno ja matriculado na turma!")
		else:
			#se o vetor "alunos" nao estiver ordenado, ou 
			#se estiver mas o ultimo ra for menor que o inserido
			#pelo usuario, ele armazena na ultima posicao
			if(ordem==0 or (ordem==1 and alunos[len(alunos)-1]<ra)):
				alunos.append(ra)
			elif(ordem==1 or ordem==2):
				alunos.append(-1)
				i=0
				#verifica em que ordem esta e continua o loop.
				while((alunos[i]<ra and ordem==1) or (alunos[i]>ra and ordem==2)):
					i+=1
				for j in range(len(alunos)-1,i-1,-1):
					alunos[j]=alunos[j-1]
				alunos[i]=ra

	#remove alunos
	elif(entrada=="r"):
		if(len(alunos)==0):
			print("Nao ha alunos cadastrados na turma!")
		else:
			if(buscaLinear(alunos, ra)==-1):
				print("Aluno nao matriculado na turma!")
			else:
				alunos.remove(ra)
		
	#recebe entrada e armazena a acao em "entrada"
	#e o ra do aluno em "ra"
	entrada=[]
	entrada=[i for i in input().split()]
	if(len(entrada)>1):
		ra=int(entrada[1])
	entrada=entrada[0]