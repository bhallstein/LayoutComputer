#include "LayoutData.h"

LayoutData::LayoutData(uint16_t n_elements) :
	elements(n_elements * 4),
	op_cache(1),
	operations(1)
{

}

void LayoutData::add_operation(uint16_t data_property_ind, std::initializer_list<Op> ops) {
	for (auto it = ops.begin(), end = ops.end(); it < end; ++it) {
		op_cache.push(*it);
	}
	const uint16_t n_ops = op_cache.get_n();
	operations.push({
		(uint16_t) (n_ops - ops.size()),
		(uint8_t) ops.size(),
		data_property_ind,
	});
}

void LayoutData::process() {
	auto *arr_elements = elements.unsafe_ptr();
	auto *arr_ops = op_cache.unsafe_ptr();
	auto *arr_operations = operations.unsafe_ptr();
	for (uint16_t i=0, n=operations.get_n(); i < n; ++i) {
		arr_operations[i].process(arr_elements, arr_ops);
	}
}

uint16_t LayoutData::n_elements() const {
	return 0.25 * (elements.get_n());
}
