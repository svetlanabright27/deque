/*
 * @brief Common deque support functions
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

#include "deque.h"




/**
 * @brief   Initialize deque
 * @param   item_size    : Size of each element
 * @param   count        : Size of deque(amount of elements)
 * @return  pointer to the deque initialized
 */
DEQUE_T *new_deque(int item_size, int count)
{
    DEQUE_T *deque = malloc(sizeof(DEQUE_T));

    if ( !deque )
    {
        goto fail1;
    }

    deque->data = malloc((count + 1) * item_size);

    if (!deque->data)
    {
        goto fail2;
    }

    deque->count = count + 1;
    deque->item_size = item_size;
    deque->begin = 0;
    deque->end = 0;

    if (pthread_mutex_init(&deque->mutex, NULL))
    {
        goto fail3;
    }

    return deque;
fail3:
    free(deque->data);
fail2:
    free(deque);
fail1:
    return NULL;
}


/* Destroy deque */
void delete_deque(DEQUE_T *deque)
{
    pthread_mutex_destroy(&deque->mutex);
    free(deque->data);
    free(deque);
}

/* Lock the deque */
void deque_lock(DEQUE_T *deque)
{
    pthread_mutex_lock(&deque->mutex);
}


/* Lock the deque */
void deque_unlock(DEQUE_T *deque)
{
    pthread_mutex_unlock(&deque->mutex);
}



/**
 * @brief   get pointer to the begin element
 * @param   deque    : the deque...
 * @return  pointer to the element
 */
void *deque_begin(const DEQUE_T *deque)
{
    char *ptr = (char *)deque->data;

    if (deque_is_empty(deque))
    {
        return NULL;
    }

    return ptr + deque->begin * deque->item_size;
}

/**
 * @brief   get pointer to the end element(no element in fact)
 * @param   deque    : the deque...
 * @return  pointer to the element
 */
void *deque_end(const DEQUE_T *deque)
{
    char *ptr = (char *)deque->data;

    if (deque_is_empty(deque))
    {
        return NULL;
    }

    return ptr + deque->end * deque->item_size;
}

/**
 * @brief   increase the iterator(pointer) to element of deque
 * @param   deque : the deque...
 * @param   ptr   : the pointer to increase
 * @return  pointer increased
 */
void *deque_iterator_inc(DEQUE_T *deque, void *ptr)
{
    char *p_data = deque->data;
    int index = ((char *)ptr - p_data) / deque->item_size;
    index = (index + 1) % deque->count;
    return p_data + index * deque->item_size;
}


/**
 * @brief   push a element to the back of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to the data to push
 * @return  0: success
            1: failure
 */
int deque_push_back(DEQUE_T *deque, const void *data)
{
    char *ptr = deque->data;

    /* We cannot insert when queue is full */
    if (deque_is_full(deque))
    {
        return DEQUE_FAILURE;
    }

    ptr += deque->end * deque->item_size;
    memcpy(ptr, data, deque->item_size);
    deque->end = (deque->end + 1) % deque->count;

    return DEQUE_SUCCESS;
}


/**
 * @brief   pop a element from the front of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to store the data pop
 * @return  0: success
            1: failure
 */
int deque_pop_front(DEQUE_T *deque, void *data)
{
    char *ptr = deque->data;

    /* We cannot pop when queue is empty */
    if (deque_is_empty(deque))
    {
        return DEQUE_FAILURE;
    }

    ptr += deque->begin * deque->item_size;
    memcpy(data, ptr, deque->item_size);
    deque->begin = (deque->begin + 1) % deque->count;

    return DEQUE_SUCCESS;
}

/**
 * @brief   Return size of deque
 * @param   deque    : Pointer to deque
 * @return  count of elements
 */
int deque_size(const DEQUE_T *deque)
{
    return (deque->end + deque->count - deque->begin) % deque->count;
}

/**
 * @brief   Return full status of deque
 * @param   deque    : Pointer to deque
 * @return  1 if the deque is full, otherwise 0
 */
int deque_is_full(const DEQUE_T *deque)
{
    return deque_size(deque) == (deque->count - 1);
}

/**
 * @brief   Return empty status of deque
 * @param   deque    : Pointer to deque
 * @return  1 if the deque is empty, otherwise 0
 */
int deque_is_empty(const DEQUE_T *deque)
{
    return !deque_size(deque);
}


