# deque
A deque implementation in C supposed to be similar with deque in STL

## available interfaces:

```C
/* constructor and destructor */
Deque * new_deque(int item_size, int count);
void    delete_deque(Deque *deque);

/* user interfaces */
void   deque_lock(Deque *deque);
void   deque_unlock(Deque *deque);
void * deque_begin(const Deque *deque);
void * deque_end(const Deque *deque);
void * deque_iter_inc(Deque *deque, void *ptr);
void   deque_clear(Deque *deque);
int    deque_push_front(Deque *deque, const void *data);
int    deque_push_back(Deque *deque, const void *data);
int    deque_pop_front(Deque *deque, void *data);
int    deque_pop_back(Deque *deque, void *data);
int    deque_size(const Deque *deque);
int    deque_full(const Deque *deque);
int    deque_empty(const Deque *deque);
```
