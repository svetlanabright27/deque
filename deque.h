/*
 * @brief Common deque support functions in C
 *
 * @note
 * author: lycon[lk361115629.github.io]
 *
 * IGNORE FOLLOWING DESCRIPTIONS...
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
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


#define DEQUE_SUCCESS    0u
#define DEQUE_FAILURE    1u


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
 * @brief   push a element to the back of a deque(no element in fact)
 * @param   deque : the deque...
 * @param   data  : pointer to the data to push
 * @return  0: success
            1: failure
 */
int deque_push_back(DEQUE_T *deque, const void *data);



/**
 * @brief   pop a element from the front of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to store the data pop
 * @return  0: success
            1: failure
 */
int deque_pop_front(DEQUE_T *deque, void *data);



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
