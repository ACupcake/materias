'''
O objeto eh encontrar a ordem da hierarquia dada uma matriz x, recebemos uma
matriz "cel", um valor de funcionarios "n" e um indice "k" para verificar
sua hierarquia. A saida deve ser um vetor com a hierarquia ordenada.
'''

#ordenacao por insertion-sort
def ordena(cel,k):
	#cel 2 eh um vetor secundario que tem k
	#em seu inicio como pedido pelo problema
	cel2=[k]
	for i in range(1,len(cel)):
		chave=cel[i]
		k=i
		while(k>0 and chave<cel[k-1]):
			cel[k]=cel[k-1]
			k-=1
		cel[k]=chave
	cel2+=cel
	return cel2

def hierarquia(cel,k):
	hie=[]
	j=0
	'''
	para cada valor na linha x na matriz, verifica se existe o numero "1",
	se sim passa para a linha do indice desse "1" e	retorna todos os indices
	onde foi encontrado "1".
	'''
	for i in (cel[k]):
		if(i==1):
			hie.append(j)
			hie+=(hierarquia(cel, j))
		j+=1
	return hie

#recebe e armazena a entrada em n,k
n,k=(int(i) for i in input().split())
#recebe o vetor e armazena em "cel"
cel=[]
for i in range(0, n):
	cel.append([])
	cel[i]+=(int(i) for i in input().split())

#armazenamos o resultado da funcao "hierarquia" em "hiera"
hiera=[]
hiera+=hierarquia(cel,k)
#ordenacao insertion-sort
hiera=ordena(hiera, k)

#mostra o resultado na tela como especificado
for i in range(0, len(hiera)):
	if(i!=len(hiera)-1):
		print(hiera[i],end=" ")
	else:
		print(hiera[i])