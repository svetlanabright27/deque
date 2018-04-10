all: a.out

a.out: test.o deque.o
	gcc -lpthread $^ -o $@

%.o: %.c
	gcc -Wall -c $< -o $@

clean:
	rm -f a.out *.o
