/*
 * edge-detect-algo.h
 *
 *  Created on: Jun 10, 2016
 *      Author: oscar
 */

#ifndef DRIVER_EDGE_DETECT_ALGO_H_
#define DRIVER_EDGE_DETECT_ALGO_H_

typedef enum    {
	SOBEL = 0,
	PREWITT = 1,
	ROBERTS = 2
} EdgeDetectAlgorithm_T;

typedef enum {
	SET_ALGO ,
	SET_MASK_SIZE
} EdgeDetectIOCTL;

#endif /* DRIVER_EDGE_DETECT_ALGO_H_ */
