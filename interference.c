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

	graph = (intNode*)malloc(size * sizeof(intNode));

	for(i=0;i<size;i++)
	{
		degree = 0;
		interferences = (int*)malloc(5*sizeof(int));
		
		for(j=0;j<size;j++)
		{
			if(i != j)
			{
				if(((live[j].go_live >= live[i].go_live) &&
						 (live[j].go_live <= live[i].dead)) ||
						((live[j].dead >= live[i].go_live) && 
						 (live[j].dead <= live[i].dead)))
				{
					// found that j is an interference to i
					if(degree%5 == 0)
						interferences = (int*)realloc(interferences, (degree+5)*sizeof(int));

					interferences[degree] = j;
					
					degree++;
				}
			}
		}
		graph[i].interferences = interferences;
		graph[i].degree = degree;
	}
	return graph;
}
