createPreprocessed:
	gcc -E fork.c -o fork.i

createAssemblyProgram:
	gcc -S fork.i -o fork.s

createByteCode:
	gcc -c fork.s -o fork.o

linkCreateExecutableAndRun:
	gcc -o fork fork.o

runAllTargets:
	make compileAssembly
	make createPreprocessed
	make createAssemblyProgram
	make createByteCode
	make linkCreateExecutableAndRun