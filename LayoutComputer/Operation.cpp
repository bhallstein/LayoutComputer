#include "Operation.h"
// #include <cstdio>

StretchyArray<float, uint8_t> Operation::stack(1);

void Operation::process(float *data, Op *op_cache) {
	float value = 0;
	stack.reset();
	
	for (uint8_t i=i_first_op, end=i_first_op + n_ops; i < end; ++i) {
		const Op &op = op_cache[i];
		// printf("%d/%d %.1f  ", i-i_first_op, end-i_first_op, value);
		switch (op.func) {
			case ADD: value = value + data[op.data.property_ind]; break;
			case SUB: value = value - data[op.data.property_ind]; break;
			case MUL: value = value * data[op.data.property_ind]; break;
			case DIV: value = value / data[op.data.property_ind]; break;
			case ADD_P: value = value + stack.pop(); break;
			case SUB_P: value = value - stack.pop(); break;
			case MUL_P: value = value * stack.pop(); break;
			case DIV_P: value = value / stack.pop(); break;
			case ADD_V: value = value + op.data.value; break;
			case SUB_V: value = value - op.data.value; break;
			case MUL_V: value = value * op.data.value; break;
			case DIV_V: value = value / op.data.value; break;
			case SET:   value = data[op.data.property_ind]; break;
			case SET_V: value = op.data.value; break;
			case PUSH:   stack.push(data[op.data.property_ind]); break;
			case PUSH_V: stack.push(op.data.value); break;
			case PUSH_P: stack.push(value); break;
			default: break;
		}
		// printf("->  %.1f\n", value);
	}
	data[dest_property] = value;
}
