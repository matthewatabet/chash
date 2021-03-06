CC = gcc
CFLAGS = -I ./
DEPS = chash.h
OBJ = chash.o test_chash.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_chash: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test : 
	./test_chash

clean:
	rm -f *.o
