main: main.o firstStep.o secondStep.o dataCode.o machineDcode.o validSyntax.o printTheOutPuts.o mcroValid.o makeAm.o
	gcc -g -ansi main.o firstStep.o secondStep.o dataCode.o machineDcode.o validSyntax.o printTheOutPuts.o mcroValid.o makeAm.o

main.o: main.c main.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o -lm
	
makeAm.o: makeAm.c makeAm.h
	gcc -c -Wall -ansi -pedantic makeAm.c -o makeAm.o -lm


mcroValid.o: mcroValid.c mcroValid.h
	gcc -c -Wall -ansi -pedantic mcroValid.c -o mcroValid.o -lm
	
dataCode.o: dataCode.c dataCode.h
	gcc -c -Wall -ansi -pedantic dataCode.c -o dataCode.o -lm
	
firstStep.o: firstStep.c firstStep.h
	gcc -c -Wall -ansi -pedantic firstStep.c -o firstStep.o -lm
 
secondStep.o: secondStep.c secondStep.h
	gcc -c -Wall -ansi -pedantic secondStep.c -o secondStep.o -lm


machineDcode.o: machineDcode.c machineDcode.h
	gcc -c -Wall -ansi -pedantic machineDcode.c -o machineDcode.o -lm
	
validSyntax.o: validSyntax.c validSyntax.h
	gcc -c -Wall -ansi -pedantic validSyntax.c -o validSyntax.o -lm

printTheOutPuts.o: printTheOutPuts.c printTheOutPuts.h
	gcc -c -Wall -ansi  -pedantic printTheOutPuts.c -o printTheOutPuts.o -lm



