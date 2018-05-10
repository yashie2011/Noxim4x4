/*
 * constants.h
 *
 *  Created on: Jan 27, 2018
 *      Author: yaswanth
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_


#define NUM_CORES 12
#define MEM_CONTROLLERS 4
#define REQ_DATA_SIZE 8
#define REPLY_DATA_SIZE 128
#define FLIT_SIZE 64
#define MC_BUFF_CAP 32

// positions of each value in trace line
#define NUM_WORDS_IN_A_TRACE_LINE 13
#define TIME_STAMP_POS 9
#define SRC_ID_POS 3
#define DEST_ID_POS 11
#define COMPUTE_TIME_POS 12
#define WID_POS 5

// position in trace line of MC trace
#define NUM_WORDS_IN_A_TRACE_LINE_MC 12
#define TIME_STAMP_POS_MC 9
#define SRC_ID_POS_MC 3
#define DEST_ID_POS_MC 5
#define DATA_POS_MC 7
#define APPROX_POS_MC 10
#define BC_RECEIVERS 3

#define BUFF_CHK 3
#define ERR_THRESH 0.25
#endif /* CONSTANTS_H_ */
