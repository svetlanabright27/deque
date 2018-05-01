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


#ifndef  EXIT_SUCCESS
#define  EXIT_SUCCESS  0
#endif
#ifndef  EXIT_FAILURE
#define  EXIT_FAILURE  1
#endif


/**
 * @brief deque structure
 */
typedef struct {
    void * data;
    int   count;
    int   item_size;
    volatile unsigned int begin;
    volatile unsigned int end;
    pthread_mutex_t mutex;
} Deque;




/**
 * @brief   Initialize deque
 * @param   type    : type of element
 * @param   count   : Size of deque(amount of elements)
 * @return  pointer to the deque initialized
 */
#define new_deque(type, count) \
    __new_deque(sizeof(type), count)
Deque * __new_deque(int item_size, int count);


/* Destroy deque */
void delete_deque(Deque * deque);


/* Lock the deque */
void deque_lock(Deque * deque);


/* Lock the deque */
void deque_unlock(Deque * deque);



/**
 * @brief   get pointer to the begin element
 * @param   deque    : the deque...
 * @return  pointer to the element
 */
void * deque_begin(const Deque * deque);



/**
 * @brief   get pointer to the end element
 * @param   deque    : the deque...
 * @return  pointer to the element
 */
void * deque_end(const Deque * deque);



/**
 * @brief   increase the iterator(pointer) to element of deque
 * @param   deque : the deque...
 * @param   ptr   : the pointer to increase
 * @return  pointer increased
 */
void * deque_iter_inc(Deque * deque, void * ptr);


/**
 * @brief   flush a deque
 * @param   deque : the deque...
 */
void deque_clear(Deque * deque);

/**
 * @brief   push a element to the back of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to the data to push
 * @return  0: success
            1: failure
 */
int deque_push_back(Deque * deque, const void * data);

/**
 * @brief   push a element to the front of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to the data to push
 * @return  0: success
            1: failure
 */
int deque_push_front(Deque * deque, const void * data);

/**
 * @brief   pop a element from the front of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to store the data pop
 * @return  0: success
            1: failure
 */
int deque_pop_front(Deque * deque, void * data);

/**
 * @brief   pop a element from the back of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to store the data pop
 * @return  0: success
            1: failure
 */
int deque_pop_back(Deque * deque, void * data);


/**
 * @brief   Return size of deque
 * @param   deque    : Pointer to deque
 * @return  count of elements
 */
int deque_size(const Deque * deque);


/**
 * @brief   Return full status of deque
 * @param   deque    : Pointer to deque
 * @return  1 if the deque is full, otherwise 0
 */
int deque_full(const Deque * deque);



/**
 * @brief   Return empty status of deque
 * @param   deque    : Pointer to deque
 * @return  1 if the deque is empty, otherwise 0
 */
int deque_empty(const Deque * deque);


/**
 * @}
 */

#endif /* __DEQUE_H_ */
