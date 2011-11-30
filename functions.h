#ifndef FUNCTIONS_H
#define	FUNCTIONS_H

//block_array generate_cfg();

live_range* liveness(int size);
block_array generate_cfg();
ddg_t generate_ddg();
intNode* calcInterference(live_range* live, int size);

#endif	/* FUNCTIONS_H */

