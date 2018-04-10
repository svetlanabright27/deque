#include <stdio.h>
#include <string.h>
#include "deque.h"


typedef struct
{
    char str[16];
} String;


void print_deque( DEQUE_T *deque)
{
    String *p;

    deque_lock(deque);
    printf("begin,end = %d,%d %p,%p\n" , deque->begin, deque->end,
           deque_begin(deque),
           deque_end(deque));
    printf("deque-size = %d\n" , deque_size(deque));

    /* full or empty */
    if ( deque_is_empty(deque))
    {
        printf("the deque is EMPTY\n");
    }
    else if ( deque_is_full(deque))
    {
        printf("the deque is FULL\n");
    }

    /* ±éÀú */
    for ( p = deque_begin(deque);
          p != deque_end(deque);
          p = deque_iterator_inc(deque, p))
    {
        printf( "%s -> " , p->str );
    }

    printf("\n\n");
    deque_unlock(deque);
}


int main(int argc , char **argv)
{
    DEQUE_T *deque = deque_constructor(sizeof(String), 5);

    for (;;)
    {
        char line[1024];
        String tmp;
        printf("enter your command(push <string> or pop): ");
        fgets(line , sizeof line , stdin);

        /* for examle, type "push aaa" */
        if ( !strncmp(line , "push " , 5)  )
        {
            line[strlen(line) - 1] = 0;
            strcpy(tmp.str , line + 5 );
            deque_lock(deque);

            if (deque_push_back(deque, &tmp))
            {
                printf("push_back FAILED!!!\n");
            }

            deque_unlock(deque);
        }
        /* for example, type "pop" */
        else if ( !strncmp(line , "pop" , 3) )
        {
            deque_lock(deque);

            if (deque_pop_front(deque , &tmp))
            {
                printf("pop_front FAILED!!!\n");
            }

            deque_unlock(deque);
            printf("pop %s\n" , tmp.str);
        }
        /* destroy */
        else if ( !strncmp(line , "des" , 3) )
        {
            deque_destructor( deque);
            printf("WARNING: the deque has been destroyed, followed with SEGMENT-FAULT probably\n");
        }

        print_deque(deque);
    }

    return 0;
}

