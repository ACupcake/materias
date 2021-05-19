.text
  .align 1
  .globl _start

_start:
	#jal leEntradas
	#jal moveCarro
	#jal mostra

	
	jal mostra
	#ascii
	
	# exit
  	li a0, 0  # exit code
  	li a7, 93 # syscall exit
  	ecall




##como ler entrada com espaco
leEntradas:
  	addi sp, sp, -8
  	sw ra, 0(sp)
  	sw s0, 4(sp)
  	addi s0, sp, 8
  
	# le posicao x
	la a0, posx 	 # a0 = endereco de posx
  	jal ler_entrada

	# le posicao y
	la a0, posy 	 # a3 = endereco de posy
	jal ler_entrada

	# le tamanho do eixo y
	la a0, sizey     # a3 = endereco de sizey
	jal ler_entrada  # pula 'P2'
	jal ler_entrada  # pula x (fixo em 64)
	jal ler_entrada  # le tamanho de y

	# le brilho maximo
	la a0, maxLight  # a3 = endereco de maxLight
	jal ler_entrada

	# pula primeira linha (y = 0)
	#la a1,   # a3 = endereco de 0
	#ecall

	##  codigo acima lido como ascii
	##  converter para decimal

	lw ra, 0(sp)
  	lw s0, 4(sp)
  	addi sp, sp, 8
  	jr ra


ler_entrada: # recebe endereco da string em a0
	mv a1, a0 # buffer = endereco
	li a0, 0  # file descriptor = 0 (stdout)
	li a2, 5  # size
	li a7, 63 # syscall read (63)
	ecall
	ret











mostra:
  	addi sp, sp, -8
  	sw ra, 0(sp)
  	sw s0, 4(sp)
  	addi s0, sp, 8
  	
  	#altera valor em x
  	
	la a3, positionText	# a3 = endereco de positionText
	la a5, positionText	# a5 = endereco de positionText
	#li a6, 456
	la a0, posx
	jal asciiToInt
	mv a6, a0
	li t1, 10		# t1 = 10
	
	while:
  		li   t2, 0       	  # se x == 0
  		beq  a6, t2, endWhile 	  # sai do laco
  		rem a4, a6, t1		  # pega resto de x por 10
  		addi a4, a4, 48	  # passa para ascii
   		sb a4, 8(a3)		  # concatena decimal de x
   		addi a3, a3, -1	  # proxima posicao de x
		div a6, a6, t1		  # divide x por 10
  		j while
	endWhile:
	
	# altera valor em y

	la a3, positionText	# a3 = endereco de positionText
	la a5, positionText	# a5 = endereco de positionText
	li a6, 123
	while2:
  		li   t2, 0       	  # se x == 0
  		beq  a6, t2, endWhile2   # sai do laco
  		#li a4, 48		  # a2 = '0'
  		rem a4, a6, t1		  # pega resto de x por 10
  		addi a4, a4, 48	  # passa para ascii
   		sb a4, 13(a3)		  # concatena decimal de x
   		addi a3, a3, -1	  # proxima posicao de x
		div a6, a6, t1		  # divide x por 10
  		j while2
	endWhile2:

   	li a0, 1  # file descriptor = 1 (stdout)
	mv a1, a5 # buffer = endereco de positionText
	li a2, 15 # size
	li a7, 64 # syscall write (64)
	ecall

	lw ra, 0(sp)
  	lw s0, 4(sp)
  	addi sp, sp, 8
  	jr ra

##bugado
asciiToInt: # recebe variavel em a0
	mv t0, a0	# passa ponteiro do argumento para t0
	li a0, 0	# resultado = 0
	li t2, 2	# contador
	li t3, 10	# t3 = 10
	#li t4, 1	# multiplicador = 1

	whileAscii:
	  	li   t1, 0       	# se contador == 0
  		beq  t2, t1, endAscii 	# sai do laco
  		lw   t1, 0(t0)		# argToInt = *argumento
  		addi t0, t0, 1		# argumento++ (ponteiro)
  		addi t1, t1, -48	# ascii para int
  		mul  a0, a0, t3	# argToInt *= 10
  		#mul  t4, t4, t3	# multiplicador *= 10
  		add  a0, a0, t1	# resultado += valor
		addi t2, t2, -1	# contador -= 1
		#j whileAscii		# volta para inicio do loop
	endAscii:
	
	ret


# Additional data variables
.align  4
.data
  #posx: .skip 5
  posy: .skip 5
  sizex: .word 0x40
  sizey: .skip 5
  maxLight: .skip 5
  positionText:  .asciz "POS: 0000 0000\n"  #coloca a string na memoria
  
  posx: .asciz "42"
  #posx: .skip 5 #cada ascii consome um bit ?
  #posy: .skip 5
  #sizex: .word 0x40
  #sizey: .skip 5
  #maxLight: .skip 5