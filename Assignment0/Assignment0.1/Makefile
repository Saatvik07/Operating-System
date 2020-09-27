createPreprocessed:
	gcc -E hello.c -o output.i

createAssemblyProgram:
	gcc -S output.i -o output.s

createByteCode:
	gcc -c output.s -o output.o

createExecutableAndRun:
	gcc output.o -o output && ./output

runAllTargets:
	make createPreprocessed
	make createAssemblyProgram
	make createByteCode
	make createExecutableAndRun