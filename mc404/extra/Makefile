#linux linker:
#ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib64/crt1.o /usr/lib64/crti.o -L/usr/lib64 main.o log.o math.o -lc /usr/lib64/crtn.o -o prog.x
#WSL2 linker:
#ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/Scrt1.o /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/crti.o -L/usr/lib64 main.o log.o math.o -lc /usr/lib/gcc/x86_64-linux-gnu/7/../../../x86_64-linux-gnu/crtn.o -o prog.x

files = /lib64/ld-linux-x86-64.so.2 /usr/lib64/crt1.o\
	 		 /usr/lib64/crti.o -L/usr/lib64 main.o log.o math.o\
	  		 -lc /usr/lib64/crtn.o

prog.x: main.o math.o log.o
	ld -dynamic-linker $(files) -o prog.x
main.s: main.c
	gcc -S main.c -o main.s
main.o: main.s
	as -o main.o main.s
math.s: math.c
	gcc -S math.c -o math.s
math.o: math.s
	as -o math.o math.s
log.s: log.c
	gcc -S log.c -o log.s
log.o: log.s
	as -o log.o log.s
clean:
	rm -f main.s math.s log.s main.o math.o log.o prog.x