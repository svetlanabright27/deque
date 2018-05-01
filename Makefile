
a.out: test.c  deque.c deque.h
	gcc -lpthread $^ -o $@

clean:
	rm -f a.out 
