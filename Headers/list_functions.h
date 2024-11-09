#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "list_macros.h"
#include "list_utilities.h"
#include"list_decoration.h"

#ifndef LIST_FUNCTIONS_HEADER
#define LIST_FUNCTIONS_HEADER

typedef double ListElem;

const int START_LIST_SIZE = 10;

const uint64_t POISON_VALUE = 0xBA5ED; // TODO: в конструкторе и деструкторе заполнять 

// Все с большой буквы (kHuyPizda  HUY_PIZDA)
enum Errors
{
    GOOD_CTOR = 0,
    BAD_CTOR,
    GOOD_DTOR,
    BAD_DTOR,
    GOOD_INSERT,
    BAD_INSERT,
    GOOD_DELETE,
    BAD_DELETE,
    GOOD_TAKE,
    BAD_TAKE,

    GOOD_WRITE_NODES,
    BAD_WRITE_NODES,

    GOOD_FREE_INSERT,
    BAD_FREE_INSERT,
    GOOD_FREE_DELETE,
    BAD_FREE_DELETE,
};

struct FreeCell
{
    int next;
    int prev;
};

struct Cell
{
    ListElem value;
    int next;
    int prev;
};

struct Array
{
    Cell* elem;
    uint64_t list_size;
    FreeCell* free;
    uint64_t free_size;
    uint64_t real_capacity;
};  


//========================================
enum Errors ListCtor( );
enum Errors ListDtor( );
void ListDump( );
enum Errors ListInsert( ) ;
enum Errors ListDelete( );
enum Errors ListTakeHead( );
enum Errors ListTakeTale( );
//=======================================

//=======================================
enum Errors FreeInsert();
enum Errors FreeDelete();
//=======================================

#endif