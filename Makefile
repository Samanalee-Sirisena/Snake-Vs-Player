CC = gcc
CFLAGS = -Wall -pedantic -ansi 
OBJ = main.o eatmake.o random.o terminal.o 
EXEC = eat

ifdef PULL
CFLAGS += -DPULL
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)


main.o : main.c eatmake.h random.h
	$(CC) -c main.c $(CFLAGS)

eatmake.o : eatmake.c eatmake.h random.h terminal.h 
	$(CC) -c eatmake.c $(CFLAGS)

random.o : random.c random.h
	$(CC) -c random.c $(CFLAGS)


terminal.o : terminal.c terminal.h 
	$(CC) -c terminal.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)
