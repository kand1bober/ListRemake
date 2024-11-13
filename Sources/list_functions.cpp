#include "../Headers/list_functions.h"
#include <cstdlib>

enum Errors ListCtor( struct Array* list )
{
    list->elem = (Cell*)calloc( START_LIST_SIZE, sizeof( Cell ) );
    list->free = (FreeCell*)calloc( START_LIST_SIZE, sizeof( FreeCell ) );

    list->list_size = 0; 
    list->free_size = 0;
    list->real_capacity = START_LIST_SIZE;

    //--------------------
    for(int i = 0; i < (int)list->real_capacity; i++)
    {
        (list->elem + i)->next = -1;
        (list->elem + i)->prev = -1;
    }
    //---------------------
    list->elem->value = 0;
    list->elem->next = 1;
    list->elem->prev = 1;
    //---------------------
    (list->free + 1)->free_elem = 1;

    for(size_t i = 0; i < list->real_capacity - 1; i++)
    {
        (list->free + i)->next = i + 1;
    }
    list->free_size = 1;

    return GOOD_CTOR;
}


enum Errors ListDtor( struct Array* list )
{
    free( list->elem );
    free( list->free );

    if( (!list->free) && (!list->elem) )
        return GOOD_DTOR;
    else
        return BAD_DTOR;
}


enum Errors ListInsert( struct Array* list, int pivot, ListElem elem  )
{
    ON_DEBUG( printf(GREEN "====== Start of ListInsert ======\n" DELETE_COLOR); )

    assert( list );
    assert( list->elem );
    assert( list->free);

    ON_DEBUG( ListDump(list); )

    if( ((uint64_t)pivot >= list->real_capacity) || ((uint64_t)pivot > list->list_size + 1) || (pivot == 0) )
    {
        printf(RED "Just wrong input\n" DELETE_COLOR);
        return BAD_INSERT;
    }


    int free_elem = 0;
    FreeDelete( list, &free_elem );
        ON_DEBUG( printf(YELLOW "free_elem: %d\n" DELETE_COLOR, free_elem); )
    (list->elem + free_elem)->value = elem;
    //---------------NEXTS-----------------------------------
    int next_target = 0;
    for(int i = 0; i < pivot - 1; i++)
    {
        next_target = (list->elem + next_target)->next;
    }
    int pivot_next_target = (list->elem + next_target)->next;

    (list->elem + next_target)->next = free_elem;
    if( pivot_next_target != free_elem ) //TODO: частные случаи
    {
        (list->elem + free_elem)->next = pivot_next_target;
        
    }
    //-------------------------------------------------------

    //----------------PREVS----------------------------------
    int prev_target = 0;
    if( (list->list_size > 1) )
    {
        for(int i = 0; i < (int)(list->list_size - pivot ); i++)
        {
            prev_target = (list->elem + prev_target)->prev;
            printf(GREEN "prev_target to: %d\n" DELETE_COLOR, prev_target);
        }
        int pivot_prev_target = (list->elem + prev_target)->prev;
        (list->elem + prev_target)->prev = free_elem;
        (list->elem + free_elem)->prev = pivot_prev_target;
    }
    else 
    {
        int pivot_prev_target = (list->elem + prev_target)->prev;
        (list->elem + prev_target)->prev = free_elem;
        (list->elem + free_elem)->prev = pivot_prev_target;
    }
    
    //-------------------------------------------------------
    list->list_size++;

    //---------------------
    // int new_target = 0;
    // for(int i = 0; i < (int)list->list_size - 1; i++)
    // {
    //     new_target = (list->elem + new_target)->next;
    // }
    // (list->elem + new_target)->next = 0;
    //---------------------

    ON_DEBUG( ListDump(list); )

    ON_DEBUG( printf(GREEN "====== End of ListInsert ======\n" DELETE_COLOR); )

    return GOOD_INSERT;
}
        

enum Errors ListDelete( struct Array* list, int pivot )
{
    ON_DEBUG( printf(GREEN "====== Start of ListDelete ======\n" DELETE_COLOR); )

    assert( list );
    assert( list->elem );
    assert( list->free);

    ON_DEBUG( ListDump(list); )

    //---------------NEXTS-----------------------------------
    int next_target = 0;
    for(int i = 0; i < pivot - 1; i++)
    {
        next_target = (list->elem + next_target)->next;
    }
    int pivot_next_target = (list->elem + next_target)->next;

    (list->elem + next_target)->next = (list->elem + pivot_next_target)->next;
    (list->elem + pivot_next_target)->next = -1;
        ON_DEBUG( (list->elem + pivot_next_target)->value = -(list->elem + pivot_next_target)->value; )
        ON_RELIZ( (uint64_t)(list->elem + pivot_next_target)->value = POISON_VALUE; )
    
    //-------------------------------------------------------
/*
    //----------------PREVS----------------------------------
    int prev_target = 0;
    for(int i = 0; i < (list->list_size - pivot + 1); i++)
    {
        prev_target = (list->elem + prev_target)->prev
    }

    //TODO:

    FreeInstert( list, pivot );
    //-------------------------------------------------------
    */
    list->list_size--;

    ON_DEBUG( ListDump(list); )
    ON_DEBUG( printf(GREEN "====== End of ListDelete ======\n" DELETE_COLOR); )

    return GOOD_DELETE;
}


enum Errors Take( struct Array* list, int number, ListElem* elem )
{
    int target = 0;
    for(int i = 0; (i < number) && (i < (int)list->list_size); i++)
    {
        target = (list->elem + target)->next;
    }

    *elem = (list->elem + target)->value;

    return GOOD_TAKE;
}


enum Errors FreeInsert( struct Array* list, int ip )
{
    (list->free + list->free_size + 1)->free_elem = ip;
    (list->free + list->free_size + 1)->next = 0;
    (list->free + list->free_size)->next = list->free_size + 1;
    list->free_size++;
        
    return GOOD_FREE_INSERT;
}


enum Errors FreeDelete( struct Array* list, int* ip )
{
    *ip = (list->free + list->free_size)->free_elem;

    if( list->free_size < 2)
    {
        (list->free + list->free_size)->free_elem = (list->free + list->free_size)->free_elem + 1;
        return GOOD_FREE_DELETE;
    }
    else 
    {    
        (list->free + list->free_size)->free_elem = -1;
        (list->free + list->free_size)->next = -1;
        (list->free + list->free_size - 1)->next = 0;

        list->free_size--;
        return GOOD_FREE_DELETE;
    }
}


void ListDump( struct Array* list )
{
    printf(GREEN "====== Begin of ListDump ======\n" DELETE_COLOR);

    printf("list->real_capacity: %lu\nlist->size: %lu\nlist->free_size: %lu\n\n", list->real_capacity, list->list_size, list->free_size);
    printf(SINIY "\n[i]  Number Dump     Next    Prev     [i]\n" DELETE_COLOR);
    for(size_t i = 0 ; i < list->real_capacity; i++)
    {
        printf(ORANGE "[%02lu]" DELETE_COLOR "  %7.2lf   ---  %3d    %3d      " ORANGE "[%02lu]" DELETE_COLOR "\n",
        i, list->elem[i].value, list->elem[i].next, list->elem[i].prev, i );
    }
    printf("\n\n");


    printf(SINIY "\n[i]  Free  Dump      Next      [i]\n" DELETE_COLOR);
    for(size_t i = 0 ; i < list->real_capacity; i++)
    {
        printf(ORANGE "[%02lu]" DELETE_COLOR "  %7d        %3d     " ORANGE "[%02lu]" DELETE_COLOR "\n", 
        i, list->free[i].free_elem, list->free[i].next, i );
    }
    printf("\n");

    printf(GREEN "====== End of ListDump ======\n\n" DELETE_COLOR);
}


