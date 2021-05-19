.text
	.align 1
	.globl _start

_start:
	#jal move

	li a0, 1000	# 100 = 64
	li a1, 1	# 1 = 1
	li a2, 0	# 0 = 0
	li a7, 2100	# 2100 = 834
	ecall

	# exit
	li a0, 0  # exit code
	li a7, 93 # syscall exit
	ecall

move:
	addi sp, sp, -8
	sw ra, 0(sp)
	sw s0, 4(sp)
	addi s0, sp, 8



	lw ra, 0(sp)
	lw s0, 4(sp)
	addi sp, sp, 8
	jr ra