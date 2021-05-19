### instrucoes ###
.org 0x000 @iae boi
  #Multiplica entrada por 10
  LOAD MQ,M(0x110) MUL M(gravidade)
  LOAD MQ STOR M(y)
  
  #Divide y por 2
  RSH STOR M(k)

 loop:
    #Faz operacao ((y/k) + k)/2
	LOAD M(y) DIV M(k)
	LOAD MQ ADD M(k)
	RSH STOR M(k)
    
    #Subtrai 1 do contador
	LOAD M(contador) SUB M(um)

    #if(contador >= 0) goto loop
	STOR M(contador) JUMP+ M(loop, 0:19)

    #Armazena AC = k' e sai do programa
	LOAD M(k) JUMP M(0x400)

### variaveis ###
.org 0x050
y: .word 0000000000
k: .word 0000000000
um: .word 0000000001
contador: .word 0000000009
gravidade: .word 0000000010