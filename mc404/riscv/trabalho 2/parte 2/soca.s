.globl _start
.text
.align 4

int_handler:
    ###### Tratador de interrupções e syscalls ######
    # <= Implemente o tratamento da sua syscall aqui =>

    # Salvar o contexto
    csrrw sp, mscratch, sp # Troca sp com mscratch
    addi sp, sp, -24 # Aloca espaço na pilha
    sw a4, 0(sp)
    sw a5, 4(sp)
    sw a6, 8(sp)
    sw a7, 12(sp)


    # Identifica chamada
    mv t0, a7                        # switch(numero_da_chamada)
    li t1, 10                        #     case(10) 
    beq t0, t1, set_motor            #         goto set_motor
    li t1, 11                        #     case(11):
    beq t0, t1, set_handbreak        #         goto set_handbreak
    li t1, 12                        #     case(12):
    beq t0, t1, read_sensors         #         goto read_sensors
    li t1, 13                        #     case(13):
    beq t0, t1, read_sensor_distance #          goto read_sensor_distance
    li t1, 14                        #     case(14):
    beq t0, t1, get_time             #         goto get_time
    li t1, 15                        #     case(15):
    beq t0, t1, get_positon          #         goto get_positon
    li t1, 16                        #     case(16):
    beq t0, t1, get_rotation         #         goto get_rotation
    j fim



    set_motor:
        # Muda deslocamento vertical
        li t0, 0xFFFF0121 # t0 = &deslocamento_vertical
        sb a0, 0(t0)      # *deslocamento_vertical = a0

        # Muda deslocamento horizontal
        li t1, 0xFFFF0120 # t1 = &deslocamento_horizontal
        sb a1, 0(t1)      # *deslocamento_horizontal = a1
        j fim




    set_handbreak:
        # Ativa freio
        li t0, 0xFFFF0122 # coloca valor de a0
        mv t1, a0         # no endereco de
        sb t1, 0(t0)      # 0xFFFF0122
        j fim




    read_sensors:
        # Ativa leitura dos sensores
        li t1, 1          # coloca 1 no
        li t0, 0xFFFF0101 # endereco 0xFFFF0101
        sw t1, 0(t0)      # para iniciar leitura

        li t1, 0       # t1 = 0

        # Espera leitura do sensor
        while_is_reading_sensor:        # while(*is_reading_sensor)
            lb t2, 0(t0)                # t2 = *t0
            beq t1, t2, end_sensor_read # if(t2 == 0) goto end_sensor_read
            j while_is_reading_sensor   # else goto while_is_reading_sensor
        end_sensor_read:

        # Define valores iniciais para leitura
        li t0, 0xFFFF0124 # t0 = &valores_lidos
        li t1, 0          # contador = 0
        li t2, 256        # max = 256
        # Armazena leitura do sensor
        while_not_finish_copy:      # while(estaCopiando)
            beq t1, t2, finish_copy # if(contador == max) goto finish_copy
            lb t3, 0(t0)            # t3 = *valores_lidos
            sw t3, 0(a0)            # *vetor_claridade_pista = t3
            addi a0, a0, 1          # vetor_claridade_pista++
            addi t0, t0, 1          # valores_lidos++
            addi t1, t1, 1          # contador++
            j while_not_finish_copy # goto while_not_finish_copy
        finish_copy:

        j fim




    read_sensor_distance:
        # Ativa leitura
        li t0, 1          # coloca 1 no
        li t1, 0xFFFF0102 # endereco de 0xFFFF0102
        sw t0, 0(t1)      # para iniciar leitura
        
        li t1, 0 # t1 = 0

        # Espera leitura
        while_is_reading_sonic_sensor:        # while(*is_reading_sonic_sensor)
            li t0, 0xFFFF0102                 # t0 = is_reading_sonic_sensor
            lb t0, 0(t0)                      # t0 = *t0
            beq t0, t1, end_sonic_sensor_read # if(t0 == 0) goto end_sensor_read
            j while_is_reading_sonic_sensor   # goto while_is_reading_sensor
        end_sonic_sensor_read:

        # Lê distância
        li t1, 0xFFFF011C # t1 = &distancia_sensor_ultrasonico
        lw a0, 0(t1)      # a0 = *t1
        j fim




    get_time:
        # Ativa leitura do tempo
        li t0, 1          # coloca 1
        li t1, 0xFFFF0300 # no endereco
        sw t0, 0(t1)      # de 0xFFFF0300

        # Espera leitura do tempo
        while_is_reading_time:        # while(*is_reading_time)
            lb t0, 0(t1)              # t0 = *is_reading_time
            li t2, 0                  # t2 = 0
            beq t0, t2, end_read_time # if(t0 == 0) goto end_read_time
            j while_is_reading_time   # goto while_is_reading_sensor
        end_read_time:

        # Lê tempo
        li t1, 0xFFFF0304 # t1 = &tempo_decorrido
        lw a0, 0(t1)      # a0 = *t1
        j fim




    get_positon:
        # Ativa leitura da posicao
        li t0, 1          # coloca 1
        li t1, 0xFFFF0100 # no endereco
        sw t0, 0(t1)      # de 0xFFFF0100

        # Espera leitura da posicao
        while_is_reading_position:        # while(*is_reading_position)
            li t0, 0xFFFF0100             # t0 = is_reading_position
            lb t0, 0(t0)                  # t0 = *t0
            li t1, 0                      # t1 = 1
            beq t0, t1, end_read_position # if(t0 == 0)
            j while_is_reading_position   # goto while_is_reading_position
        end_read_position:

        # Lê posição
        li t1, 0xFFFF0110 # t1 = &posição_do_carro
        lw a0, 0(t1)      # a0 = *t1
        li t1, 0xFFFF0114 # t1 = &posição_do_carro
        lw a1, 0(t1)      # a0 = *t1
        li t1, 0xFFFF0118 # t1 = &posição_do_carro
        lw a2, 0(t1)      # a0 = *t1
        j fim




    get_rotation:
        # Ativa leitura da rotação
        li t0, 1          # coloca 1
        li t1, 0xFFFF0100 # no endereco
        sw t0, 0(t1)      # de 0xFFFF0100

        # Espera leitura da rotação
        while_is_reading_rotation:        # while(*is_reading_rotation)
            li t0, 0xFFFF0100             # t0 = is_reading_rotation
            lb t0, 0(t0)                  # t0 = *t0
            li t1, 0                      # t1 = 1
            beq t0, t1, end_read_rotation # if(t0 == 0)
            j while_is_reading_rotation   # goto while_is_reading_rotation
        end_read_rotation:

        # Lê rotação
        li t1, 0xFFFF0104 # t1 = &rotação_do_carro
        lw a0, 0(t1)      # a0 = *t1
        li t1, 0xFFFF0108 # t1 = &rotação_do_carro
        lw a1, 0(t1)      # a0 = *t1
        li t1, 0xFFFF010C # t1 = &rotação_do_carro
        lw a2, 0(t1)      # a0 = *t1
        j fim



    fim:
    # Recupera contexto
    lw a7, 12(sp)
    lw a6, 8(sp)
    lw a5, 4(sp)
    lw a4, 0(sp)
    addi sp, sp, 24 # Desaloca espaço da pilha
    csrrw sp, mscratch, sp # troca sp com mscratch

    csrr t0, mepc  # carrega endereço de retorno (endereço da instrução que invocou a syscall)
    addi t0, t0, 4 # soma 4 no endereço de retorno (para retornar após a ecall)
    csrw mepc, t0  # armazena endereço de retorno de volta no mepc
    mret           # Recuperar o restante do contexto (pc <- mepc)





_start:
    la t0, int_handler  # Carregar o endereço da rotina que tratará as syscalls
    csrw mtvec, t0      # no registrador MTVEC
    
    ## Configura vetor de interrupções (é necessário?)
    ##la t0, ivt # Load the interrupt vector table address into t0
    ##ori t0, t0, 0x1 # Set the least significant bit (MODE = vectored)
    ##csrw mtvec, t0 # Copy t0 value into mtvec CSR

    li sp, 0x7fffffc # endereço da pilha = 0x7fffffc

    # Muda para modo usuário
    csrr t1, mstatus # Update the mstatus.MPP
    li t2, ~0x1800 # field (bits 11 and 12)
    and t1, t1, t2 # with value 00 (U-mode)
    csrw mstatus, t1
    la t0, user_code # Loads the user software
    csrw mepc, t0 # entry point into mepc
    mret # PC <= MEPC; mode <= MPP;

    ## Salta para o código do usuario (é necessário?)
    jal user_code
  loop_infinito:
    j loop_infinito
