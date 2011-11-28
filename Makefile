CC = g++
FLAG = `pkg-config --libs opencv --cflags opencv`

#objects = main.o
objects += utils.o
objects += dct.o

a.out : $(objects) main.o
	$(CC) $(FLAG) -o a.out $(objects) main.o
match : $(objects) match.o
	$(CC) $(FLAG) -o a.out $(objects) match.o
main.o : main.cpp
	$(CC) $(FLAG) -c $<
match.o : match.cpp
	$(CC) $(FLAG) -c $<
utils.o : utils.cpp
	$(CC) $(FLAG) -c $<
dct.o : dct.cpp
	$(CC) $(FLAG) -c $<

clean:
	rm $(objects) ./a.out
