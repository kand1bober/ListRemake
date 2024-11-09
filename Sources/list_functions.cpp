#include "../Headers/list_functions.h"

enum Errors ListCtor( struct Array* list )
{
    list->elem = (Cell*)calloc( START_LIST_SIZE, sizeof( Cell ) );
    list->free = (FreeCell*)calloc( START_LIST_SIZE, sizeof( FreeCell ) );

    list->list_size = 0; 
    list->free_size = 0;
    list->real_capacity = START_LIST_SIZE;

    //---------------------
    list->elem->value = 0;
    list->elem->next = 1;
    list->elem->prev = 1;
    //---------------------
    list->free->next = 1;
    list->free->prev = 1;
    //---------------------

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


enum Errors ListInsert( struct Array* list, int pivot, ListElem* elem  )
{
    assert( list );
    assert( list->elem );
    assert( list->free);

    list->list_size++;

    int free_elem = 0;
    free_elem = FreeDelete();
    (list->elem + free_elem)->value = *elem;
    //---------------NEXTS-----------------------------------
    int next_target = 0;
    for(int i = 0; i < pivot - 1; i++)
    {
        next_target = (list->elem + next_target)->next;
    }
    int pivot_next_target = (list->elem + next_target)->next;

    (list->elem + next_target)->next = free_elem;
    if( pivot_next_target != free_elem )
    {
        (list->elem + free_elem)->next = pivot_next_target;
    }
    //-------------------------------------------------------

    //----------------PREVS----------------------------------
    int prev_target = 0;
    for(int i = 0; i < (list->list_size - pivot + 1); i++)
    {
        prev_target = (list->elem + prev_target)->prev;
    }

    //TODO:
    //-------------------------------------------------------
}


enum Errors ListDelete( struct Array* list, int pivot )
{
    assert( list );
    assert( list->elem );
    assert( list->free);

    

    //---------------NEXTS-----------------------------------
    int next_target = 0;
    for(int i = 0; i < pivot - 1; i++)
    {
        next_target = (list->elem + next_target)->next;
    }
    int pivot_next_target = (list->elem + next_target)->next;


    //-------------------------------------------------------

    //----------------PREVS----------------------------------
    int prev_target = 0;
    for(int i = 0; i < (list->list_size - pivot + 1); i++)
    {
        prev_target = (list->elem + prev_target)->prev
    }

    //TODO:
    list->list_size--;
    //-------------------------------------------------------
}


enum Errors Take( struct Array* list, int number, ListElem* elem )
{
    int target = 0;
    for(int i = 0; (i < number) && (i < list->list_size); i++)
    {
        target = (list->elem + target)->next;
    }

    *elem = (list->elem + target)->value;

    return GOOD_TAKE;
}


enum Errors FreeDelete( struct Array* list, int* ip )
{
    int target_ip = 0;
    for(int i = 0; i < list->list_size + 1; i++)
    {
        target_ip = (list->free + target_ip)->
    }

}


enum Errors FreeInsert()
{

}


void ListDump( struct Array* list )
{
    printf(GREEN "====== Begin of ListDump ======\n" DELETE_COLOR);

    printf("list->real_capacity: %lu\nlist->size%lu\nlist->free_size%lu\n\n", list->real_capacity, list->list_size, list->free_size);
    printf(SINIY "\n[i]  Number Dump     Next    Prev     [i]\n" DELETE_COLOR);
    for(size_t i = 0 ; i < list->real_capacity; i++)
    {
        printf(ORANGE "[%02lu]" DELETE_COLOR "  %7.2lf   ---  %3d    %3d      " ORANGE "[%02lu]" DELETE_COLOR "\n",
        i, list->elem[i].value, list->elem[i].next, list->elem[i].prev, i );
    }
    printf("\n\n");


    printf(SINIY "\n[i]  Free  Dump      Next    Prev     [i]\n" DELETE_COLOR);
    for(size_t i = 0 ; i < list->real_capacity; i++)
    {
        printf(ORANGE "[%02lu]" DELETE_COLOR "  %7d   ---  %3d    " ORANGE "[%02lu]" DELETE_COLOR "\n", 
        i, list->free[i].next, list->free[i].prev, i );
    }
    printf("\n");

    printf(GREEN "====== End of ListDump ======\n\n" DELETE_COLOR);
}

