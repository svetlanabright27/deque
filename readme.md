# deque
A deque implementation in C supposed to be similar with deque in STL

## available interfaces:


- DEQUE_T * **new_deque**(int item_size, int count);
- void **delete_deque**(DEQUE_T *deque);
- void **deque_lock**(DEQUE_T *deque);
- void **deque_unlock**(DEQUE_T *deque);
- void * **deque_begin**(const DEQUE_T *deque);
- void * **deque_end**(const DEQUE_T *deque);
- void * **deque_iterator_inc**(DEQUE_T *deque, void *ptr);
- void **deque_flush**(DEQUE_T *deque);
- int **deque_push_back**(DEQUE_T *deque, const void *data);
- int **deque_pop_front**(DEQUE_T *deque, void *data);
- int **deque_size**(const DEQUE_T *deque);
- int **deque_is_full**(const DEQUE_T *deque);
- int **deque_is_empty**(const DEQUE_T *deque);

