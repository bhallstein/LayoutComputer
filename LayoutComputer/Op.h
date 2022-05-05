#ifndef __Op_h
#define __Op_h

#include <cstdint>

#define ADD    ((uint8_t) 0)   // From index in data
#define SUB    ((uint8_t) 1)
#define MUL    ((uint8_t) 2)
#define DIV    ((uint8_t) 3)
#define ADD_V  ((uint8_t) 4)   // From value in op
#define SUB_V  ((uint8_t) 5)
#define MUL_V  ((uint8_t) 6)
#define DIV_V  ((uint8_t) 7)
#define ADD_P  ((uint8_t) 8)   // From previously pushed value in stack
#define SUB_P  ((uint8_t) 9)
#define MUL_P  ((uint8_t) 10)
#define DIV_P  ((uint8_t) 11)
#define SET    ((uint8_t) 12)  // Set from index
#define SET_V  ((uint8_t) 13)  //     from value in op
#define PUSH   ((uint8_t) 14)  // Push to stack from index
#define PUSH_V ((uint8_t) 15)  //     from value in op
#define PUSH_P ((uint8_t) 16)  //     from current computed value

struct Op {
	uint8_t func;
	union {
		uint16_t property_ind;
		float value;
	} data;
};

#endif 
