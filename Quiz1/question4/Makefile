question4:
	nasm -felf32 question4.asm
	gcc -m32 -c q4.c
	gcc -m32 question4.o q4.o -o output4
	./output4
question4_2:
	nasm -felf64 question4_2.asm
	gcc -c q4.c -o q4.o
	gcc question4_2.o q4.o -o output4_2
	./output4_2