createPreprocessed:
	gcc -E prog-add.c -o prog-add.i

createAssemblyProgram:
	gcc -S prog-add.i -o prog-add.s

createByteCode:
	gcc -c prog-add.s -o prog-add.o

compileAssembly:
	nasm -felf64 add.asm

linkCreateExecutableAndRun:
	gcc prog-add.o add.o -o output &&./output

runAllTargets:
	make compileAssembly
	make createPreprocessed
	make createAssemblyProgram
	make createByteCode
	make linkCreateExecutableAndRun