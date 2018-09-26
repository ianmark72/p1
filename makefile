all: 537ps.c sHelper.c UHelper.c SHelper.c vHelper.c cHelper.c
	gcc -Wall -g -c 537ps.c
	gcc -Wall -g -c sHelper.c
	gcc -Wall -g -c UHelper.c
	gcc -Wall -g -c SHelper.c
	gcc -Wall -g -c vHelper.c
	gcc -Wall -g -c cHelper.c
	gcc -o 537ps 537ps.o sHelper.o UHelper.o SHelper.o vHelper.o cHelper.o -lm

clean: 537ps
	rm 537ps
