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
#endif /* CONSTANTS_H_ */


int convtex_vals[] = {1, 14, 12, 6, 8, 3, 5};
int dct_vals[] = {1102053376 , 3266969600 , 1102577664 , 3253731328 , 3266838528 , 3246915584 , 1098907648 , 3251109888 };
int dxtc_vals[] = {1476393640 , 1610612384 , 1431654400 , 1610612712 , 1604845568 , 1476307626 , 1432264704 , 1431658474 };
int hist_vals[] = {431563413 , 946919909 , 658322570 ,3925699270 ,  656493282 , 1858020044 , 2678794759 , 137042737};
int black_vals[] = {1092670054 , 1099581098 , 1087545660 , 1095476404 , 1099607090 , 1094694200 , 1091488520 , 1099910159 };
int fwt_vals[] = {1055520064, 1058541633, 1061617699, 1063090604, 1020306588, 1060502051, 1053751792, 1040265986};

int* most_used_values[8] = {convtex_vals, dct_vals, dxtc_vals, hist_vals, black_vals, fwt_vals};
