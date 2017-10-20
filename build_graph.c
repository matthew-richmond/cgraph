/*
*
*
*
*
*
*/


#include "simple_graph.h"
#include <stdio.h>

int main(void){
	printf("Reading graph data...\n");
	ObjectList *graph = ol_create();
	grh_load_file(graph,stdin);
	printf("Finished reading graph data.\n");
	printf("Graph: {name: neighbor names list}\n");
	grh_print_graph(graph);
	grh_delete_graph(graph);
	return 0;
}

