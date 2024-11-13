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

const uint64_t POISON_VALUE = 0xBA5ED; 

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

//односвязный список свободных ячеек
struct FreeCell
{
    int free_elem; //реальный номер ячейки
    int next; //рельный номер
    // int prev; //реальный номер
};

struct Cell
{
    ListElem value; 
    int next; //реальный
    int prev; //реальный
};

struct Array
{
    Cell* elem;
    uint64_t list_size; //логический размер, двигаемся с первого члена, отсчёт от нулевого

    FreeCell* free;
    uint64_t free_size; //логический размер, двигаемся с первого члена, отсчёт от нулевого

    uint64_t real_capacity; //реальное место в памяти 
};  


//========================================
enum Errors ListCtor( struct Array* list );
enum Errors ListDtor( struct Array* list );
void ListDump( struct Array* list );
enum Errors ListInsert( struct Array* list, int pivot, ListElem elem  );
enum Errors ListDelete( struct Array* list, int pivot );
enum Errors ListTake( );
//=======================================

//=======================================
enum Errors FreeInsert( struct Array* list, int ip );
enum Errors FreeDelete( struct Array* list, int* ip );
//=======================================

#endif