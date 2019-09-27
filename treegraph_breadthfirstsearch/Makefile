MAINPATH=./main
INCPATH=./main/inc
OBJPATH=./obj
LIBPATH=./lib
CFLAGS=-g -Wall

install:  app

app:	main.o
	gcc  $(CFLAGS) -o App main.o

main.o: ./main.c ./config.h
	gcc  $(CFLAGS) -I./. main.c -c 


clean:
	-rm -f App
	-rm -f main.o
