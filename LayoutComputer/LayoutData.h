#ifndef __LayoutData_h
#define __LayoutData_h

#include <initializer_list>
#include "StretchyArray/StretchyArray.h"
#include "Op.h"
#include "Operation.h"

struct LayoutData {
	LayoutData(uint16_t n_elements);

	// Operations
	StretchyArray<Op, uint16_t> op_cache;
	StretchyArray<Operation, uint16_t> operations;

	// Data
	StretchyArray<float, uint16_t> elements;
	uint16_t n_elements() const;

	void add_operation(uint16_t data_property_ind, std::initializer_list<Op> ops);
	void process();
};

#endif
