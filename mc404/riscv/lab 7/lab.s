.text
  .align 1
  .globl _start

_start:
  jal leEntradas
  # colocar pos x do carro em a1
  # e depois chamar moveCarro
  jal moveCarro

  # exit
  li a0, 0  # exit code
  li a7, 93 # syscall exit
  ecall



leEntradas:
  li a0,  0 # file descriptor = 0 (stdout)

# le posx
  la a0, posx # a3 = endereco de posx
  jal ler_entrada

# le posy
  la a0, posy # a3 = endereco de posy
  jal ler_entrada

# le tamanho do eixo y
  la a0, sizey  # a3 = endereco de sizey
  ecall       # pula 'P2'
  ecall       # pula x (fixo em 64)
  jal ler_entrada # le tamanho de y

# le brilho maximo
  la a0, maxLight # a3 = endereco de maxLight
  jal ler_entrada

# pula primeira linha (y = 0)
  #la a1,   # a3 = endereco de 0
  #ecall

##  codigo acima lido como ascii
##  converter para decimal/hex/int/sei la
  ret


moveCarro:
  li a1, 0  #i = 0
  enquanto:
    # se i >= sizeY entao sai do laco
    la a1, sizey
    lw t1, 0(t1)
    bge a1, t1, cont

    # decide movimentacao
    mv t1, a1   # salva i
    la a1, posx   # move endereco de x para a1
    lw a1, 0(a1)  # move valor de x para a1
    la a2, sizex  # move endereco de sizeX para a2
    lw a2, 0(a2)  # move sizeX para a2
    jal decidir     # chama funcao decidir
    mv a1, t1   # retorna valor para i

    addi a1, a1, 1  # i=i+1   

    la a2, posx   # move endereco de x para a2
    lw a2, 0(a2)    # move valor de x para a2
    add a2, a2, a0  # x=x+dir (x = posicao carro)
    
    ##salvar a1 em posx, ta certo?
    la a3, positionText # a3 = endereco de positionText
        sb a1, 0(a3)


    jal imprimir_pos
    j    enquanto
  cont:

  ret

decidir:
  # a1 = x
  # a2 = sizeX
  # t1 = xMin
  # t2 = pegouMin
  # t3 = xMax
  # t4 = pegouMax

  li a3, 0        # i = 0
  li t2, 0        # pegouMin = 0
  for:
    bge a3, a2, end   # se i >= 10
              # sai do laco
    jal ler_entrada     # retorna em a0

    li  t5, 100         # Salta para
    bge a0, t1, pulaMin # pula se entrada >= 100
    li  t5, 0       # Salta para
    bne t2, t5, pulaMin # pula se pegouMin != 0
    mv  t1, a3        # xMin = i
    li  t2, 1       # pegouMin = 1
    pulaMin:

    li  t5, 100         # Salta para
    blt a0, t1, pulaMax # pula se entrada < 100
    li  t5, 1       # Salta para
    bne t2, t5, pulaMax # pula se pegouMin != 1
    li  t5, 0       # Salta para
    bne t4, t5, pulaMax # pula se pegouMax != 0
    mv  t3, a3        # xMax = i
    li  t4, 1       # pegouMax = 1
    pulaMax:

    addi a3, a3, 1    # i++
    j for
  end:

  mv t5, a1       	# temp = posx
  slli t5, t5, 1    # temp = 2*temp
  sub t5, t5, t1    # temp = temp - xMin

  beq t5, t3, equal # if t5 == xmax
            # jump to equal
  blt t5, t4, less  # else if t5 < xmax
            # jump to less
            # else go to bigger

  bigger:       #return 1
  li a0, 1
  ret

  less:       #return -1
  li a0, -1
  ret

  equal:        #return 0
  li a0, 0
  ret


ler_entrada:
  mv a3, a0 # a3 = endereco em a0
  li a0,  0 # file descriptor = 0 (stdout)
  li a2,  3 # size
  li a7, 63 # syscall read (63)
  mv a1, a3 # buffer = endereco
  ecall
  lw a0, 0(a1) # carrega valor de a1 em a0
  ret


imprimir_pos: # parametro x=a0 e y=a1
  la a3, positionText # a3 = endereco de positionText

  # fala eixo y
  # coloca eixo x da posicao do carro na string
  mv a1, a0 # a2 = x
  li t1, 1000
  while:
      li   t1, 0          # se x == 0
      beq  a1, t1, endWhile # sai do laco
      li a2, 0        # a2 = 0 
      rem a2, a2, t1      # pega resto de x por t1
      sb a2, 6(a3)      # concatena 'x'
      addi a3, a3, 1
      div a1, a1, t1      # divide x por t1
      li t2, 10
      div t1, t1, t2      # divide t1 por 10
      j while
  endWhile:

  #POS: 0000 0000

  # coloca eixo y da posicao do carro na string
  #li t1, 46       # concatena '.'
      #sb t1, 8(a3)

  #li a0, 1  # file descriptor = 1 (stdout)
  #mv a1, a3 # buffer = endereco de positionText
  #li a2, 15 # size
  #li a7, 64 # syscall write (64)
  #ecall



# Additional data variables
.align  4
.data
  posx: .skip 3 #cada ascii consome um bit ?
  posy: .skip 3
  sizex: .word 0x40
  sizey: .skip 3
  maxLight: .skip 3
  positionText:  .asciz "POS: 0000 0000\n"  #coloca a string na memoria