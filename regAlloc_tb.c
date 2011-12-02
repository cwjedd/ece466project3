#include <stdlib.h>
#include <stdio.h>
#include "s3inst.h"
#include "functions.h"

int main()
{
	int i, j;
	
	live_range	test[10];
	intNode* 		graph;

	test[0].go_live	= 0;
	test[0].dead		= 0;

	test[1].go_live	= 1;
	test[1].dead		= 5;

	test[2].go_live	= 2;
	test[2].dead		= 3;

	test[3].go_live	= 3;
	test[3].dead		= 6;

	test[4].go_live	= 4;
	test[4].dead		= 9;

	test[5].go_live	= 5;
	test[5].dead		= 7;

	test[6].go_live	= 6;
	test[6].dead		= 7;

	test[7].go_live	= 7;
	test[7].dead		= 8;

	test[8].go_live	= 8;
	test[8].dead		= 8;

	test[9].go_live	= 9;
	test[9].dead		= 9;
	
	graph = calcInterference(test, 10);

	printf("____Interference Graph____\n");
	for(i=0;i<10;i++)
	{
		printf("R%d: ", i);
		for(j=0;j<graph[i].degree;j++)
		{
			printf("%d ", graph[i].interferences[j]);
		}
		printf("\n");
	}
	printf("_________End Graph_________\n\n");

	regAlloc(graph, 10, 3);

	return EXIT_SUCCESS;
}





