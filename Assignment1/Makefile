compileShell:
	gcc -o shell Shell.c
	./shell

compileLs:
	gcc -o lsSelf ls.c
	sudo mv lsSelf ../../../../usr/bin


compileCat:
	gcc -o catSelf cat.c
	sudo mv catSelf ../../../../usr/bin

compileDate:
	gcc -o dateSelf date.c
	sudo mv dateSelf ../../../../usr/bin

compileRemove:
	gcc -o rmSelf rm.c
	sudo mv rmSelf ../../../../usr/bin

compileAll:
	make compileLs
	make compileCat
	make compileDate
	make compileRemove
	make compileShell
