all: 537ps.c sHelper.c UHelper.c SHelper.c vHelper.c cHelper.c
	gcc -Wall -Wextra -g -c 537ps.c
	gcc -Wall -Wextra -g -c sHelper.c
	gcc -Wall -Wextra -g -c UHelper.c
	gcc -Wall -Wextra -g -c SHelper.c
	gcc -Wall -Wextra -g -c vHelper.c
	gcc -Wall -Wextra -g -c cHelper.c
	gcc -o 537ps 537ps.o sHelper.o UHelper.o SHelper.o vHelper.o cHelper.o -lm

clean: 537ps
	rm -f 537ps *.o
	rm -rf scanBuildDir

scan-build: clean
	scan-build -o scanBuildDir make

scan-view: scan-build
	firefox -new-window scanBuildDir/*/index.html
