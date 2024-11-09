#include "../Headers/list_functions.h"
#include "../Headers/list_output.h"

int main()
{
    struct Array my_list = {};
    struct File_graph dump_file = {};

    ListCtor( &my_list );

    ListDump( &my_list );

    ListElem to_insert = 14.88;
    ListInsert( &my_list, 1, to_insert );
    ListInsert( &my_list, 2, 1.22 );
    ListInsert( &my_list, 3, 1.23 );
    ListInsert( &my_list, 4, 1.24 );
    ListDelete( &my_list, 4 );
    // ListInsert( &my_list, 3, 7.77 );

    StartOutput( &dump_file );
    WritePrimaryNodes( &my_list, &dump_file );
    WriteSecondaryNodes( &my_list, &dump_file );
    FinishOutput( &dump_file );
    ListDtor( &my_list );

    return 0;
}