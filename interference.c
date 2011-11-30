#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s3inst.h"
#include "cmdline.h"
#include "functions.h"


intNode* calcInterference(live_range* live, int size)
{
	int i, j;

	int degree;

	intNode* graph;
	int* interferences;

	// malloc memory for graph one location for each Register number
	graph = (intNode*)malloc(size * sizeof(intNode));

	for(i=0;i<size;i++)								// iterate through every register
	{
		degree = 0;								// reset degree for new node
		interferences = (int*)malloc(5*sizeof(int));		// malloc memory for node's interferences
		
		for(j=0;j<size;j++)							// compare register i with every register
		{
			if(i != j)							// do not check node against itself
			{
				if( ((live[j].go_live >= live[i].go_live) && (live[j].go_live <= live[i].dead)) ||	// check if j's go_live falls within i's live range
				    ((live[j].dead >= live[i].go_live) && (live[j].dead <= live[i].dead)) ||		// check if j's dead falls within i's live range

				    ((live[i].go_live >= live[j].go_live) && (live[i].go_live <= live[j].dead)) ||	// check if i's go_live falls within j's live range
				    ((live[i].dead >= live[j].go_live) && (live[i].dead <= live[j].dead)) )		// check if i's dead falls within j's live range
				{
					// found that j is an interference to i

					// if interferences array size to small to add more realloc to a larger size
					if(degree%5 == 0)
						interferences = (int*)realloc(interferences, (degree+5)*sizeof(int));

					interferences[degree] = j;		// add register to list of interferences
					
					degree++;						// increment degree of node
				}
			}
		}
		graph[i].interferences = interferences;			// add interferences to the graph
		graph[i].degree = degree;					// add degree information to the graph
	}
	return graph;									// return completed graph
}
