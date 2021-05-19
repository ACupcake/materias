.globl set_motor
.globl set_handbreak
.globl read_sensors
.globl read_sensor_distance
.globl get_time
.globl get_position
.globl get_rotation

set_motor:
	#li t0, 126			  # if(126 < a1)
	#blt t0, a1, motor_end # 	goto motor_end
	#li t0, -126			  # if(a1 < -126)
	#blt a1, t0, motor_end # 	goto motor_end
	#li t0, 1			  # if(a0 > 1)
	#blt t0, a0, motor_end # 	goto motor_end
	#li t0, -1			  # if(a0 < -1)
	#blt a0, t0, motor_end # 	goto motor_end
	li a7, 10			  # chama funcao set_motor
	ecall
	li a5, 0			  # retorna 0
	ret
	motor_end:			  # if(parametros_estao_errados)
	li a5, -1			  # 	retorna -1
    ret

set_handbreak:
	li t0, 1		 # if(a0 == 1)
	beq t0, a0, valid_value # 	goto valid_value
	li t0, 0		 # if(a0 == 0)
	beq t0, a0, valid_value # 	goto valid_value
	ret
	valid_value:
	li a7, 11		 # call handbreak
	ecall
    ret

read_sensors:
	li a7, 12
	ecall
    ret

read_sensor_distance:
	li a7, 13
	ecall
    ret

get_position:
	li a7, 15
	ecall
    ret

get_rotation:
	li a7, 16
	ecall
    ret

get_time:
	li a7, 14
	ecall
    ret