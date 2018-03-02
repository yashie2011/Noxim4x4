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
#define REPLY_DATA_SIZE 128
#define FLIT_SIZE 16
#define REQ_FLIT_SIZE 16
#define REPLY_FLIT_SIZE 64
#define REQ_PACKET_SIZE 48 //bits http://xillybus.com/tutorials/pci-express-tlp-pcie-primer-tutorial-guide-1
#define NUM_CORES_PER_COL 3
#define MC_BUFF_CAP 64

// positions of each value in trace line
#define NUM_WORDS_IN_A_TRACE_LINE 12
#define TIME_STAMP_POS 9
#define SRC_ID_POS 3
#define DEST_ID_POS 11
#define COMPUTE_TIME_POS 12

#endif /* CONSTANTS_H_ */
