#include "LayoutComputer.hpp"
#include <cstdio>

void print(float x) {
  printf("%.1f\n", x);
}

void print(LayoutComputer comp) {
  printf("%lu elements\n", comp.elements.size());
  for (float f : comp.elements) {
    printf(" - %.1f\n", f);
  }
}

int main() {
  LayoutComputer computer{
    {
      0, {
        {PUSH_V, .value = 6.0},
        {SET_V,  .value = 2.0},
        {MUL_V,  .value = 4.0},
        {MUL_P},
      },
    },
    {
      1, {
        {SET, .element = 0},
      },
    },
    {
      2, {
        {SET_V, .value = 100.0},
      },
    },
    {
      3, {
        {SET_V, .value = 200.0},
      },
    },
    {
      4, {
        {SET,   .element = 0},
        {ADD,   .element = 2},
        {ADD_V, .value = 10.0},
      },
    },
    {
      5, {
        {SET, .element = 1},
      },
    },
    {
      6, {
        {SET, .element = 2},
      },
    },
    {
      7, {
        {SET, .element = 3},
      },
    },
  };

  computer.process();
  print(computer);

  // N.B. This is similar to Reverse Polish Notation, but as Op has an extra "value" field,
  // we have both _P and _V funcs.
  // This reduces the number of operations (fewer pops and pushes).
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
