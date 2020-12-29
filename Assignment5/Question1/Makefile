compile:
	nasm -f bin bootloader_2019097.asm -o bootloader.bin
	
run:	compile
	qemu-system-x86_64 -fda bootloader.bin
	
