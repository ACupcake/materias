### instrucoes ###
.org 0x000
 inicio:
	#Acha valor do vetor1 e do vetor 2 na posicao i
	LOAD M(0x3FF) STA M(001)
	LOAD M(0x000) STOR M(temporario)
	LOAD M(0x3FE) STA M(003)

	#Multiplica vetor1[i] * vetor2[i]
	LOAD MQ,M(0x000) MUL M(temporario)

	#Soma novo valor ao somatorio
	LOAD MQ ADD M(somatorio)

	#Atualiza endereco dos vetores 1 e 2 e o valor indice
	STOR M(somatorio) LOAD M(0x3FF) 
	ADD M(um) STOR M(0x3FF)
	LOAD M(0x3FE) ADD M(um)
	STOR M(0x3FE) LOAD M(indice)
	ADD M(um) STOR M(indice)

	#if((tamanhoVetor - indice) >= 0) goto inicio
	LOAD M(0x3FD) SUB M(indice)
	JUMP+ M(inicio,0:19) LOAD M(somatorio)

	#Sai do programa
	JUMP M(0x400)


### variaveis ###
.org 0x050
indice: .word 0000000001 #(indice do vetor)
somatorio: .word 0000000000
um: .word 0000000001
temporario: .word 0000000000