#include <stdlib.h>
#include <stdio.h>
#include "s3inst.h"
#include "functions.h"


int main()
{
	instr_set* liveIn, liveOut;
	live_range* live;
	
	calc_Range(5, 5, instr_set* liveIn, 
								instr_set* liveOut, live_range* live);
}
