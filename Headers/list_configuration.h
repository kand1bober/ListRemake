#ifndef CONFIGURATION_LIST_HEADER
#define CONFIGURATION_LIST_HEADER

//=======NAME OF GRAPH FILE=====
const char output_image_name[] = "ListGraph.svg";
const char output_html_name[]  = "ListGraph.html";
const char output_graph_name[] = "ListGraph.dot";
//===============================

#define DEBUG
// #define RELIZ

#ifdef DEBUG
    #ifdef RELIZ
        #undef DEBUG
        #undef RELIZ
    #endif
#endif

#ifdef DEBUG
    #undef RELIZ
#endif

#ifdef RELIZ
    #undef DEBUG
#endif

#endif // CONFIGURATION_LIST_HEADER