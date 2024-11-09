#include "../Headers/list_functions.h"

#ifndef LIST_OUTPUT_HEADER
#define LIST_OUTPUT_HEADER


const size_t START_OUTPUT_FILE_SIZE = 10;
const char default_pointer_color[20] = "#0000CD";
const char next_pointer_color[20] = "#FF0000";
const char prev_pointer_color[20] = "#00FF00";

const char fillcolor[20] = "#FFFACD";
const char bgcolor[20] = "#FFD7DC";


struct File_graph
{
    FILE* stream;
    size_t stream_size;
};

void StartOutput( struct File_graph* file );
void FinishOutput( struct File_graph* file );
enum Errors WritePrimaryNodes( struct Array* list, struct File_graph* file );
enum Errors WriteSecondaryNodes( struct Array* list, struct File_graph* file );

#endif
