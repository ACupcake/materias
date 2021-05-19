.text
  .align 1
  .globl _start

_start:  
  # Converte angulo inteiro para radianos e coloca em f0
  jal funcao_pegar_angulo
  # Utilizado para calcular a série
  jal funcao_calcula_serie
  # Transforma um PF para inteiro, onde a0 contem o sinal, a1 a parte inteira e a2 a parte fracionaria (truncada com 3 casas decimais)
  jal funcao_float_para_inteiro
  # Imprime o resultado de a0, a1 e a2 na tela
  jal funcao_imprime
  
  li a0, 0 # exit code
  li a7, 93 # syscall exit
  ecall
  
funcao_calcula_serie:
  addi sp, sp, -8
  sw ra, 0(sp)
  sw s0, 4(sp)
  addi s0, sp, 8
  
  #sinal do somatorio 
  li a5, -1
  #i = 1
  li a0, 1
  #salva valor da base em f4
  li t0, 0
  fcvt.s.w f1, t0
  fadd.s f4, f4, f0
  ##acho que esta rodando uma vez a mais
  ##se sim consertar proxima linha de 11 pra 10
  enquanto:
    li t1, 11         #se i >=11
    bge a0, t1, cont  #sai do laco


    # retorna valor da potencia em f1
    # contador = 2i+1
      addi a1, a0, 0         # contador = i
      slli a1, a1, 1         # contador = 2 * contador  (right shift)
      addi a1, a1, 1         # contador = contador + 1

    # resultado = base
    li t0, 0
    fcvt.s.w f1, t0
    fadd.s f1, f1, f4

    # multiplica resultado *= base, 2i+1 vezes
    enquantopow:
      li t1, 1             # se contador = 1
      beq a1, t1, sairpow  # sai do laco
      fmul.s f1, f1, f4    # resultado = resultado * base
      addi a1, a1, -1      # contador = contador - 1
      j enquantopow        # pula para inicio do loop
    sairpow:

    ##mudar registrador r para f porq valor
    ##pode ser maior que 32-bits
    # retorna valor do fatorial em f2
    # contador = 2i+1
      addi a1, a0, 0         # contador = i
      slli a1, a1, 1         # contador = 2 * contador  (right shift)
      addi a1, a1, 1         # contador = contador + 1
    # contador = n
      #addi a2, a1, 0
      fcvt.s.w f2, a1
    # multiplica resultado ate contador chegar a 1
    enquantofat:
      li t1, 1            #se contador = 1
      beq a1, t1, sairfat #sai do laco
      #contador = contador - 1
      addi a1, a1, -1
      #resultado = resultado * contador
      #mul a2, a2, a1
      fcvt.s.w f3, a1
      fmul.s f2, f2, f3
    j enquantofat
    sairfat:
    #fcvt.s.w f2, a2 # carrega resultado em f2


    #f1 = pow/fat
    fdiv.s f1, f1, f2
    #f1 = f1 * sinal
    fcvt.s.w f3, a5
    fmul.s f1, f1, f3
    #inverte sinal
    li t1, -1
    mul a5, a5, t1
    kapp:
    #resultado = resultado + novoValor
    fadd.s f0, f0, f1
    #i = i + 1
    addi a0, a0, 1
    j enquanto
  cont:
  
  
  
  lw ra, 0(sp)
  lw s0, 4(sp)
  addi sp, sp, 8
  jr ra


funcao_imprime:
  addi sp, sp, -8
  sw ra, 0(sp)
  sw s0, 4(sp)
  addi s0, sp, 8
  
  la a3, stringFinal # a3 = endereco da stringFinal

#coloca 'SENO: ' na string
    li t1, 83   #S
    sb t1, 0(a3)
    li t1, 69   #E
    sb t1, 1(a3)
    li t1, 78   #N
    sb t1, 2(a3)
    li t1, 79   #O
    sb t1, 3(a3)
    li t1, 58   #:
    sb t1, 4(a3)
    li t1, 32   #[espaco]
    sb t1, 5(a3)
#=========================

#coloca sinal=====
    bnez a0, else #if a0 == 0
    li t1, 43     #concatena '+' na string
    sb t1, 6(a3)
    j cont1
    else:         #senao
    li t1, 45     #concatena '-'
    sb t1, 6(a3)
    cont1:
#=================

#inteiro===============
    mv t1, a1       # concatena inteiro
    addi t1, t1, 48 # passa para ascii
    sb t1, 7(a3)
#=====================

#ponto==========
    li t1, 46     #concatena '.'
    sb t1, 8(a3)
#================

#fracao===============
    mv t3, a2       #move fracao para temp
    li t2, 100      # divisor = 100
    div t3, t3, t2  # pega resto de a2
    addi t3, t3, 48 # passa para ascii
    sb t3, 9(a3)    # coloca na string
    
    #repete o mesmo para os outros dois numeros
    mv t3, a2
    li t2, 10       # divisor = 10
    div t3, t3, t2
    rem t3, t3, t2
    addi t3, t3, 48
    sb t3, 10(a3)

    mv t3, a2
    li t2, 10       # divisor = 10
    rem t3, t3, t2
    addi t3, t3, 48
    sb t3, 11(a3)

#======================

#pula linha========
    li t1, 10     #concatena '\n'
    sb t1, 12(a3)
#==================

    li a0, 1  # file descriptor = 1 (stdout)
    mv a1, a3 # buffer = endereco stringFinal
    li a2, 15  # size
    li a7, 64 # syscall write (64)
    ecall

    li a0, 0 # exit code
    li a7, 93 # syscall exit
    ecall
  
  lw ra, 0(sp)
  lw s0, 4(sp)
  addi sp, sp, 8
  jr ra

  
funcao_pegar_angulo:
  addi sp, sp, -8
  sw ra, 0(sp)
  sw s0, 4(sp)
  addi s0, sp, 8
  
  # load angle value to a0
  lw a0, angle
  # convert angle to float and put in f0
  fcvt.s.w f0, a0
  # load pi address to a0
  la a0, .float_pi
  # load float_pi value (from a0 address) into f1
  flw f1, 0(a0)
  # load value 180 into a0
  li a0, 180
  # convert 180 to float and put in f2
  fcvt.s.w f2, a0

  # f0 -> angle, f1 -> pi, f2 -> 180
  # Now, put angle in radians (angle*pi/180)
  # f0 = angle * pi
  fmul.s f0, f0, f1
  # f0 = f0 / 180
  fdiv.s f0, f0, f2
  
  lw ra, 0(sp)
  lw s0, 4(sp)
  addi sp, sp, 8
  jr ra
  
funcao_float_para_inteiro:
  addi sp, sp, -8
  sw ra, 0(sp)
  sw s0, 4(sp)
  addi s0, sp, 8
  
  # Get signal
  li a0, 0
  fcvt.s.w f1, a0
  flt.s a0, f0, f1
  
  # Drop float signal
  fabs.s f0, f0
  
  # Truncate integer part
  fcvt.s.w f1, a0
  fadd.s f1, f1, f0
  jal funcao_truncar_float
  fcvt.w.s a1, f0
  
  # Truncate float part with 3 decimal places
  fsub.s f1, f1, f0
  li a3, 1000
  fcvt.s.w f2, a3
  fmul.s f0, f1, f2
  jal funcao_truncar_float
  fcvt.w.s a2, f0
  li a3, 1000
  rem a2, a2, a3
  
  lw ra, 0(sp)
  lw s0, 4(sp)
  addi sp, sp, 8
  jr ra
  
funcao_truncar_float:
  addi sp, sp, -8
  sw ra, 0(sp)
  sw s0, 4(sp)
  addi s0, sp, 8
  
  fmv.x.w a5, f0
  li a3, 22
  srai a4, a5,0x17
  andi a4, a4, 255
  addi a4, a4, -127
  addi a2, a5, 0
  blt a3, a4, .funcao_truncar_float_continue
  lui a5, 0x80000
  and a5, a5, a2
  bltz a4, .funcao_truncar_float_continue
  lui a5, 0x800
  addi a5, a5, -1
  sra a5, a5, a4
  not a5, a5
  and a5, a5, a2
.funcao_truncar_float_continue:
  fmv.w.x f0, a5
  
  lw ra, 0(sp)
  lw s0, 4(sp)
  addi sp, sp, 8
  jr ra
  
  
# Additional data variables
.align  4
.data
  angle:
    .word 300
  .float_pi:
    .word 0x40490fdb
  stringFinal: .skip 15
