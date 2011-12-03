#include <stdio.h>
#include <stdlib.h>
#include "s3inst.h"
#include "functions.h"

/*
 * Test Bench Function for caclulating live range
 */
 /*
int main()
{
	int i;
	
	instr_set* liveIn;
	instr_set* liveOut;
	live_range* liveRange;

	liveIn  		= (instr_set*)malloc(10*sizeof(instr_set));
	liveOut 		= (instr_set*)malloc(10*sizeof(instr_set));
	liveRange 	= (live_range*)malloc(6*sizeof(live_range));

	liveIn[0].instr = -1;
	liveIn[0].next = NULL;
	
	liveIn[1].instr = -1;
	liveIn[1].next = NULL;
	
	liveIn[2].instr = -1;
	liveIn[2].next = NULL;
	
	liveIn[3].instr = -1;
	liveIn[4].next = NULL;

	liveIn[4].instr = 0;
	liveIn[4].next = NULL;

	liveIn[5].instr = 0;
	liveIn[5].next  = (instr_set*)malloc(sizeof(instr_set));
	liveIn[5].next->instr = 1;
	liveIn[5].next->next = NULL;

	liveIn[6].instr = 1;
	liveIn[6].next  = (instr_set*)malloc(sizeof(instr_set));
	liveIn[6].next->instr = 2;
	liveIn[6].next->next = NULL;

	liveIn[7].instr = 1;
	liveIn[7].next  = (instr_set*)malloc(sizeof(instr_set));
	liveIn[7].next->instr = 3;
	liveIn[7].next->next = NULL;

	liveIn[8].instr = 1;
	liveIn[8].next  = (instr_set*)malloc(sizeof(instr_set));
	liveIn[8].next->instr = 4;
	liveIn[8].next->next = NULL;

	liveIn[9].instr = 5;
	liveIn[9].next = NULL;


	liveOut[0].instr = -1;
	liveOut[0].next = NULL;

	liveOut[1].instr = -1;
	liveOut[1].next = NULL;

	liveOut[2].instr = -1;
	liveOut[2].next = NULL;

	liveOut[3].instr = 0;
	liveOut[3].next = NULL;

	liveOut[4].instr = 0;
	liveOut[4].next  = (instr_set*)malloc(sizeof(instr_set));
	liveOut[4].next->instr = 1;
	liveOut[4].next->next = NULL;

	liveOut[5].instr = 1;
	liveOut[5].next  = (instr_set*)malloc(sizeof(instr_set));
	liveOut[5].next->instr = 2;
	liveOut[5].next->next = NULL;

	liveOut[6].instr = 1;
	liveOut[6].next  = (instr_set*)malloc(sizeof(instr_set));
	liveOut[6].next->instr = 3;
	liveOut[6].next->next = NULL;

	liveOut[7].instr = 1;
	liveOut[7].next  = (instr_set*)malloc(sizeof(instr_set));
	liveOut[7].next->instr = 4;
	liveOut[7].next->next = NULL;

	liveOut[8].instr = 4;
	liveOut[8].next  = (instr_set*)malloc(sizeof(instr_set));
	liveOut[8].next->instr = 5;
	liveOut[8].next->next = NULL;

	liveOut[9].instr = -1;
	liveOut[9].next  = NULL;
	
	calc_Range(10, 6, liveIn, liveOut, liveRange);

	for(i=0;i<6;i++)
	{
		printf("R%d: %02d -> %02d\n", i, liveRange[i].go_live, liveRange[i].dead);
	}
	
	return 1;
}
*/


void calc_Range(int numInstrs, int numRegs, instr_set* liveIn, 
								instr_set* liveOut, live_range* live)

{
	int i, j;
	int found, rangeStart, rangeEnd;
	instr_set* current;

	for(i=0;i<numRegs;i++)				// iterate through all registers and determine ranges
	{
		rangeStart = -1;
		rangeEnd   = -1;
		
		for(j=3;j<numInstrs;j++)		// interate through all instructions
		{
			current = &liveOut[j];
			found = 0;

			while(current != NULL)
			{
				if(current->instr == i)
				{
					rangeStart = j;
					//printf("Found Live Out Reg %d, Instruction %d\n", i, j);
					found = 1;
					break;
				}
				current = current->next;
			}
			if(found == 1)
				break;
		}

		if(found == 0)
			printf("Error Determining Live In for register %d\n", i);

		found = 0;
		
		for(j=3;j<numInstrs;j++)		// interate through all instructions
		{
			current = &liveIn[j];

			while(current != NULL)
			{
				if(current->instr == i)
				{
					rangeEnd = j;
					//printf("Found Live In Reg %d, Instruction %d\n", i, j);
					found = 1;
				}
				current = current->next;
			}
		}
		//printf("\n");

		if(found == 0)
			printf("Error Determining Live Out for register %d\n", i);

		live[i].go_live = rangeStart;
		live[i].dead    = rangeEnd;
	}
}


















