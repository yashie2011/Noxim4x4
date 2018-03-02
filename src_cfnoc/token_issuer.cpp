#include "token_issuer.h"


token_issuer::token_issuer(){

}

bool token_issuer::set_token(int mem_c, NoximCoord src_coord, int core_id){

	bool ret_flag = false;
	int mem_C = 0;
	if(mem_c == 2)
		mem_C = 0;
	else if (mem_c == 7)
		mem_C = 1;
	else if (mem_c == 8)
		mem_C = 2;
	else if (mem_c == 13)
		mem_C = 3;

	if (is_mc(src_coord))
		return true;

	//get slice of the enetwork
	int slice_id = 0;
	if(src_coord.x == 0 ){slice_id = 0;}  // column 0 choose slice 0
	if(src_coord.x == 1 ){slice_id = 1;}  // column 1 choose slice 1
	if(src_coord.x == 2 ){slice_id = 2;}  // column 2 choose slice 2
	if(src_coord.x == 3 ){slice_id = 3;}  // column 3 choose slice 3


	assert(mem_C < MEM_CONTROLLERS && slice_id < SLICES);

	mtx.lock();

	if(token_issuer::tokens[slice_id][mem_C] == -1){
			ret_flag = true;
			token_issuer::tokens[slice_id][mem_C] = core_id;
	}

	mtx.unlock();

	return ret_flag;



}

bool token_issuer::reset_token(int mem_c, NoximCoord src_coord){

	//get slice of the enetwork
	int slice_id = 0;
        int mem_C = 0;
        if(mem_c == 2)
                mem_C = 0;
        else if (mem_c == 7)
                mem_C = 1;
        else if (mem_c == 8)
                mem_C = 2;
        else if (mem_c == 13)
                mem_C = 3;

	if(src_coord.x == 0 ){slice_id = 0;}  // column 0 choose slice 0
	if(src_coord.x == 1 ){slice_id = 1;}  // column 1 choose slice 1
	if(src_coord.x == 2 ){slice_id = 2;}  // column 2 choose slice 2
	if(src_coord.x == 3 ){slice_id = 3;}  // column 3 choose slice 3


	assert(mem_C < MEM_CONTROLLERS && slice_id < SLICES);

	mtx.lock();

	token_issuer::tokens[slice_id][mem_C] = -1;

	mtx.unlock();

	return true;

}
