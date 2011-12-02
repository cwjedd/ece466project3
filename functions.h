#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

//block_array generate_cfg();

live_range* liveness(int size);
block_array generate_cfg();
ddg_t generate_ddg();
intNode* calcInterference(live_range* live, int size);
void regAlloc(intNode* intGraph, int size, int k, inst_t instList);

#endif	/* FUNCTIONS_H */

