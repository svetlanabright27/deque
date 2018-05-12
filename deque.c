/**
 * @brief    Common deque support functions
 *
 * @author   lycon
 * @blog     https://lk361115629.github.io/
 * @github   https://github.com/lk361115629
 *
 */

#include "deque.h"




/**
 * @brief   Initialize deque
 * @param   item_size    : Size of each element
 * @param   count        : Size of deque(amount of elements)
 * @return  pointer to the deque initialized
 */
Deque * __new_deque(int item_size, int count) {
    Deque * deque;

    if(count < 2) {
        return NULL;
    }
    deque = malloc(sizeof(Deque));

    if ( !deque ) {
        goto fail1;
    }

    deque->data = malloc((count + 1) * item_size);

    if (!deque->data) {
        goto fail2;
    }

    deque->count = count + 1;
    deque->item_size = item_size;
    deque->begin = 0;
    deque->end = 0;

    if (pthread_mutex_init(&deque->mutex, NULL)) {
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
void delete_deque(Deque * deque) {
    pthread_mutex_destroy(&deque->mutex);
    free(deque->data);
    free(deque);
}

/* Lock the deque */
void deque_lock(Deque * deque) {
    pthread_mutex_lock(&deque->mutex);
}


/* Lock the deque */
void deque_unlock(Deque * deque) {
    pthread_mutex_unlock(&deque->mutex);
}



/**
 * @brief   get pointer to the begin element
 * @param   deque    : the deque...
 * @return  pointer to the element
 */
void * deque_begin(const Deque * deque) {
    char * ptr = (char *)deque->data;

    if (deque_empty(deque)) {
        return NULL;
    }

    return ptr + deque->begin * deque->item_size;
}

/**
 * @brief   get pointer to the end element(no element in fact)
 * @param   deque    : the deque...
 * @return  pointer to the element
 */
void * deque_end(const Deque * deque) {
    char * ptr = (char *)deque->data;

    if (deque_empty(deque)) {
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
void * deque_iter_inc(Deque * deque, void * ptr) {
    char * p_data = deque->data;
    int index = ((char *)ptr - p_data) / deque->item_size;
    index = (index + 1) % deque->count;
    return p_data + index * deque->item_size;
}


/**
 * @brief   clear a deque
 * @param   deque : the deque...
 */
void deque_clear(Deque * deque) {
    deque->begin = deque->end = 0;
}

/**
 * @brief   push a element to the front of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to the data to push
 * @return  0: success
            1: failure
 */
int deque_push_front(Deque * deque, const void * data) {
    char * ptr = deque->data;

    /* We cannot insert when queue is full */
    if (deque_full(deque)) {
        return EXIT_FAILURE;
    }

    deque->begin = (deque->begin + deque->count - 1) % deque->count;
    ptr += deque->begin * deque->item_size;
    memcpy(ptr, data, deque->item_size);

    return EXIT_SUCCESS;
}

/**
 * @brief   push a element to the back of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to the data to push
 * @return  0: success
            1: failure
 */
int deque_push_back(Deque * deque, const void * data) {
    char * ptr = deque->data;

    /* We cannot insert when queue is full */
    if (deque_full(deque)) {
        return EXIT_FAILURE;
    }

    ptr += deque->end * deque->item_size;
    memcpy(ptr, data, deque->item_size);
    deque->end = (deque->end + 1) % deque->count;

    return EXIT_SUCCESS;
}


/**
 * @brief   pop a element from the front of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to store the data pop
 * @return  0: success
            1: failure
 */
int deque_pop_front(Deque * deque, void * data) {
    char * ptr = deque->data;

    /* We cannot pop when queue is empty */
    if (deque_empty(deque)) {
        return EXIT_FAILURE;
    }

    ptr += deque->begin * deque->item_size;
    memcpy(data, ptr, deque->item_size);
    deque->begin = (deque->begin + 1) % deque->count;

    return EXIT_SUCCESS;
}


/**
 * @brief   pop a element from the back of a deque
 * @param   deque : the deque...
 * @param   data  : pointer to store the data pop
 * @return  0: success
            1: failure
 */
int deque_pop_back(Deque * deque, void * data) {
    char * ptr = deque->data;

    /* We cannot pop when queue is empty */
    if (deque_empty(deque)) {
        return EXIT_FAILURE;
    }

    deque->end = (deque->end + deque->count - 1) % deque->count;
    ptr += deque->end * deque->item_size;
    memcpy(data, ptr, deque->item_size);

    return EXIT_SUCCESS;
}

/**
 * @brief   Return size of deque
 * @param   deque    : Pointer to deque
 * @return  count of elements
 */
int deque_size(const Deque * deque) {
    return (deque->end + deque->count - deque->begin) % deque->count;
}

/**
 * @brief   Return full status of deque
 * @param   deque    : Pointer to deque
 * @return  1 if the deque is full, otherwise 0
 */
int deque_full(const Deque * deque) {
    return deque_size(deque) == (deque->count - 1);
}

/**
 * @brief   Return empty status of deque
 * @param   deque    : Pointer to deque
 * @return  1 if the deque is empty, otherwise 0
 */
int deque_empty(const Deque * deque) {
    return !deque_size(deque);
}


