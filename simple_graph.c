/*
* @author Matthew Richmond
* CSCI-243 Homework 5
* Simple_graph.h implementation source file
*/

#include <stdio.h>
#include "simple_graph.h"
#include <string.h>

GraphNode * grh_create_node( char * name ){
	GraphNode * node = NULL;
	node = malloc(sizeof(GraphNode));
	strcpy(node->name, name);
	node->neighbors = ol_create();
	return node;
}

void grh_delete_node(GraphNode * node){
	Iter *nb = ol_iterator(node->neighbors);
	GraphNode *nbr = NULL;
	while(ol_has_next(nb)){
		nbr = ol_next(nb);
		Iter *nbnb = ol_iterator(nbr->neighbors);
		ObjectList *newnbr = ol_create();
		GraphNode *nptr = NULL;
		while(ol_has_next(nbnb)){
			nptr = ol_next(nbnb);
			if(nptr != node){
				ol_insert(newnbr, nptr);
			}
		}
		ol_destroy(nbr->neighbors);
		nbr->neighbors = newnbr;
		free(nbnb);
	}
	free(nb);
	ol_destroy(node->neighbors);
	free(node);
}

void grh_delete_graph(ObjectList * graph){
	Iter * gr = ol_iterator(graph);
	GraphNode *node = NULL;
	while(ol_has_next(gr)){
		node = ol_next(gr);
		grh_delete_node(node);
	}
	ol_destroy(graph);
	free(gr);
}

GraphNode * grh_find_node_by_name(ObjectList * graph, char * name){
	Iter * gr = ol_iterator(graph);
	GraphNode *node = NULL; 
	while(ol_has_next(gr)){
		node = ol_next(gr);
		if(strcmp(node->name, name)==0){
			free(gr);
			return node;
		}
	}
	free(gr);
	return NULL;
}

void grh_print_graph(ObjectList * graph){
	Iter * gr = ol_iterator(graph);
	GraphNode * node = NULL;
	GraphNode *nb = NULL;
	while(ol_has_next(gr)){
		node = ol_next(gr);
		printf("%s:" , node->name);
		Iter *nbr = ol_iterator(node->neighbors);
		while(ol_has_next(nbr)){
			nb = ol_next(nbr);
			if(ol_has_next(nbr)){printf(" %s,", nb->name);}
			else{printf(" %s", nb->name);}
		}
		printf("\n");
		free(nbr);
	}
	free(gr);
}
		

void grh_load_file(ObjectList * graph, FILE * input){	
	int size = MAX_FILE_LINE_LENGTH;
	char buff[MAX_FILE_LINE_LENGTH];
	char *toke;
	char *swap = ",";
	GraphNode *node = NULL;
	GraphNode *nbr = NULL;
	while(fgets(buff,size,input)!='\0'){
		if(!(strcmp(buff,"\n")==0)){
			toke = strtok(buff, "\n");
			toke = strtok(buff, swap);
			if(grh_find_node_by_name(graph,toke) == NULL){
				node = grh_create_node(toke);
				ol_insert(graph, node);
			}
			else{
				node = grh_find_node_by_name(graph, toke);
			}
			toke = strtok(NULL, swap);
			while(toke != NULL){
				if(grh_find_node_by_name(graph,toke) == NULL){
					nbr = grh_create_node(toke);
					ol_insert(graph, nbr);
				}
				else{
					nbr = grh_find_node_by_name(graph,toke);
				}
				if(grh_find_node_by_name(node->neighbors, toke) == NULL){
					ol_insert(node->neighbors, nbr);
				}
				if(grh_find_node_by_name(nbr->neighbors, toke) == NULL){
					ol_insert(nbr->neighbors, node);
				}
				toke = strtok(NULL, swap);
			}
		}
	}
}	
