/**
 * @brief    Common deque support functions
 *
 * @author   lycon
 * @blog     https://lk361115629.github.io/
 * @github   https://github.com/lk361115629
 *
 */

#ifndef __DEQUE_H_
#define __DEQUE_H_


#include <string.h>
#include <stdlib.h>
#include <pthread.h>




/**
 * @brief deque structure
 */
typedef struct
{
    void *data;
    int   count;
    int   item_size;
    volatile unsigned int begin;
    volatile unsigned int end;
    pthread_mutex_t mutex;
} DEQUE_T;



/**
 * @brief   Initialize deque
 * @param   item_size    : Size of each element item size
 * @param   count        : Size of deque(amount of elements)
 * @return  pointer to the deque initialized
 */
DEQUE_T *new_deque(int item_size, int count);


/* Destroy deque */
void delete_deque(DEQUE_T *deque);


/* Lock the deque */
void deque_lock(DEQUE_T *deque);


/* Lock the deque */
void deque_unlock(DEQUE_T *deque);



/**
 * @brief   get pointer to the begin element
 * @param   deque    : the deque...
 * @return  pointer to the element
 */
void *deque_begin(const DEQUE_T *deque);



/**
 * @brief   get pointer to the end element
 * @param   deque    : the deque...
 * @return  pointer to the element
 */
void *deque_end(const DEQUE_T *deque);



/**
 * @brief   increase the iterator(pointer) to element of deque
 * @param   deque : the deque...
 * @param   ptr   : the pointer to increase
 * @return  pointer increased
 */
void *deque_iterator_inc(DEQUE_T *deque, void *ptr);


/**
 * @brief   flush a deque
 * @param   deque : the deque...
 */
void deque_flush(DEQUE_T *deque);

/**
 * @brief   push a element to the back of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to the data to push
 * @return  0: success
            1: failure
 */
int deque_push_back(DEQUE_T *deque, const void *data);

/**
 * @note upcoming...
 */
int deque_push_front(DEQUE_T *deque, const void *data);

/**
 * @brief   pop a element from the front of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to store the data pop
 * @return  0: success
            1: failure
 */
int deque_pop_front(DEQUE_T *deque, void *data);

/**
 * @note upcoming...
 */
int deque_pop_back(DEQUE_T *deque, void *data);


/**
 * @brief   Return size of deque
 * @param   deque    : Pointer to deque
 * @return  count of elements
 */
int deque_size(const DEQUE_T *deque);


/**
 * @brief   Return full status of deque
 * @param   deque    : Pointer to deque
 * @return  1 if the deque is full, otherwise 0
 */
int deque_is_full(const DEQUE_T *deque);



/**
 * @brief   Return empty status of deque
 * @param   deque    : Pointer to deque
 * @return  1 if the deque is empty, otherwise 0
 */
int deque_is_empty(const DEQUE_T *deque);


/**
 * @}
 */

#endif /* __DEQUE_H_ */
