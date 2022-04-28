all: escritor lector ejecutar
escritor: writee.c
	gcc writee.c -o Miescritor
lector:p1-odProgram.c 
	gcc p1-odProgram.c -o LectorHash
ejecutar:
	gcc writee.c -o Miescritor
	gcc p1-odProgram.c -o LectorHash	
	./LectorHash &
	./Miescritor  
