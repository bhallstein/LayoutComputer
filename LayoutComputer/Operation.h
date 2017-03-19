#ifndef __Operation_h
#define __Operation_h

#include "StretchyArray/StretchyArray.h"
#include "Op.h"

struct Operation {
	uint16_t i_first_op;
	uint8_t n_ops;
	uint16_t dest_property;

	static StretchyArray<float, uint8_t> stack;

	void process(float *data, Op *op_cache);
};

#endif
