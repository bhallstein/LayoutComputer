#include "LayoutComputer/include.h"
#include <cstdio>

int main() {
	uint16_t n_elements = 2;
	LayoutData layout_data(n_elements);
	layout_data.add_operation(
		PROPERTY_INDEX(0, PROP_X),
		{
			(Op) { PUSH_V, {.value=5.f} },
			(Op) { SET_V,  {.value=2.f} },
			(Op) { MUL_V,  {.value=4.f} },
			(Op) { MUL_P },
		}
	);
	layout_data.add_operation(
		PROPERTY_INDEX(0, PROP_Y),
		{
			(Op) { SET, {.property_ind=PROPERTY_INDEX(0, PROP_X)} },
		}
	);
	layout_data.add_operation(
		PROPERTY_INDEX(0, PROP_W),
		{
			(Op) { SET_V, {.value=100.f} },
		}
	);
	layout_data.add_operation(
		PROPERTY_INDEX(0, PROP_H),
		{
			(Op) { SET_V, {.value=200.f} },
		}
	);
	
	layout_data.add_operation(
		PROPERTY_INDEX(1, PROP_X),
		{
			(Op) { SET, {.property_ind=PROPERTY_INDEX(0, PROP_X)} },
			(Op) { ADD, {.property_ind=PROPERTY_INDEX(0, PROP_W)} },
			(Op) { ADD_V, {.value=10.f} },
		}
	);
	layout_data.add_operation(
		PROPERTY_INDEX(1, PROP_Y),
		{
			(Op) { SET, {.property_ind=PROPERTY_INDEX(0, PROP_Y)} },
		}
	);
	layout_data.add_operation(
		PROPERTY_INDEX(1, PROP_W),
		{
			(Op) { SET, {.property_ind=PROPERTY_INDEX(0, PROP_W)} },
		}
	);
	layout_data.add_operation(
		PROPERTY_INDEX(1, PROP_H),
		{
			(Op) { SET, {.property_ind=PROPERTY_INDEX(0, PROP_H)} },
		}
	);

	layout_data.process();
	printf("%.1f\n", layout_data.elements.arr[0]);
	printf("%.1f\n", layout_data.elements.arr[1]);
	printf("%.1f\n", layout_data.elements.arr[2]);
	printf("%.1f\n\n", layout_data.elements.arr[3]);
	
	printf("%.1f\n", layout_data.elements.arr[4]);
	printf("%.1f\n", layout_data.elements.arr[5]);
	printf("%.1f\n", layout_data.elements.arr[6]);
	printf("%.1f\n", layout_data.elements.arr[7]);

	// N.B. This is a little different from Reverse Polish Notation because of the presence of an extra 'value' field.
	// The field essentially acts as the top of the stack, so reducing the number of pops & pushes.
	// THe result is in fact a little more explicit than RPN. For example:
	//   5 + (2 x 4) -> RPN:  5 2 4 x +
	//               -> Ours: push 5, set_v 2, mul_v 4, add_p
	//                        s5 v0   s5 v2    s5 v8    s- v13


	// We now have a fairly semantic way to push a set of operations into a LayoutData object.
	// - No functionality exists yet to refer to elements beyond abstract indices into the data object.
	// - At one layer above this, it might be good to push elements, getting back their 'id' (index),
	//   so that operations can then be created referencing them.
	
	return 0;
}
