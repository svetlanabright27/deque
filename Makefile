
a.out: test.c  deque.c deque.h
	gcc -Wall -lpthread $^ -o $@

clean:
	rm -f a.out 
