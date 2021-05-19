"""
O programa recebe C que eh a capacidade maxima
carros sera o numero de carros atual, e sequencia o carro atual.
Enquanto sequencia for diferente de 0 o loop continua.
Apos receber os valores, o program faz as verificacoes, se numero de
vagas atual (carros) for maior que o carro atual (sequencia), vamos
subtrair carros de sequencia (ou somar se negativo).
Se carros-sequencia<0 o veiculo nao cabe, caso contrario se for positivo
ele cabe e sera exibido as boas vindas.
Se sequencia<0 o carro vai sair e eh exibido a mensagem.
"""

#numero de vagas
C=int(input())

#numero de vagas atual
carros=int(C)

#carro atual
sequencia=int(input())

#enquanto sequencia for diferente de 0 entramos no loop
#e no fim recebemos outro valor para sequencia
while(sequencia!=0):
	if(carros-sequencia>=0 and sequencia>0):
		print("Seja bem-vindo! Capacidade restante: %d" %(carros-sequencia))
	if(carros-sequencia<0):
		print("Veiculo muito grande! Capacidade restante: %d" %(carros))
	if(carros-sequencia>=0 and sequencia<0):
		print("Volte sempre! Capacidade restante: %d" %(carros-sequencia))
	if(carros-sequencia>=0):
		carros=carros-sequencia
	sequencia=int(input())
