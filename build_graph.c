/*
*@author Matthew Richmond
*Main file to read graph data from stdin
* imports simple graph for all graph related functions
* prints created graph from stdin
* deletes all dynamically created storage at end of main method
* returns 0 on succes
*/


#include "simple_graph.h"
#include <stdio.h>


/*
* Main function to preform all tasks
*/
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

