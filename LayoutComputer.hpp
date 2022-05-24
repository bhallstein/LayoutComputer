#include <vector>
#include <initializer_list>


typedef std::vector<int>::size_type index_t;


// Ops
#define ADD      ((index_t) 0)   // Operate current-value with element
#define SUB      ((index_t) 1)
#define MUL      ((index_t) 2)
#define DIV      ((index_t) 3)

#define ADD_V    ((index_t) 4)   // Operate current-value with explicit value
#define SUB_V    ((index_t) 5)
#define MUL_V    ((index_t) 6)
#define DIV_V    ((index_t) 7)

#define ADD_P    ((index_t) 8)   // Operate current-value with top of stack (and pop)
#define SUB_P    ((index_t) 9)
#define MUL_P    ((index_t) 10)
#define DIV_P    ((index_t) 11)

#define SET      ((index_t) 12)  // Set current-value, from element
#define SET_V    ((index_t) 13)  //     current-value, explicit

#define PUSH     ((index_t) 14)  // Push to stack, from element
#define PUSH_V   ((index_t) 15)  //                from explicit value
#define PUSH_C   ((index_t) 16)  //                from current-value


template<class T>
T pop(std::vector<T> &v) {
  T last = v.back();
  v.pop_back();
  return last;
}


struct LayoutComputer {
  struct Op {
    index_t func;
    index_t element;
    float value;
  };

  struct Expression {
    index_t target_element;
    std::vector<Op> ops;
  };

  std::vector<Expression> expressions;
  std::vector<float> elements;

  LayoutComputer(std::initializer_list<Expression> exps) {
    for (auto i : exps) {
      expressions.push_back(i);
    }
  }

  void add_expression(Expression expr) {
    expressions.push_back(expr);
  }

  void set_element(index_t index, float value) {
    if (index >= elements.size()) {
      elements.resize(index + 1);
    }
    elements[index] = value;
  }

  void process() {
    for (auto expr : expressions) {
      process_expression(expr);
    }
  }

  void process_expression(const Expression &expr) {
    float value = 0;
    std::vector<float> stack;

    for (auto op : expr.ops) {
      switch (op.func) {
        case ADD:     value = value + elements[op.element];   break;
        case SUB:     value = value - elements[op.element];   break;
        case MUL:     value = value * elements[op.element];   break;
        case DIV:     value = value / elements[op.element];   break;
        case ADD_P:   value = value + pop(stack);             break;
        case SUB_P:   value = value - pop(stack);             break;
        case MUL_P:   value = value * pop(stack);             break;
        case DIV_P:   value = value / pop(stack);             break;
        case ADD_V:   value = value + op.value;               break;
        case SUB_V:   value = value - op.value;               break;
        case MUL_V:   value = value * op.value;               break;
        case DIV_V:   value = value / op.value;               break;
        case SET:     value = elements[op.element];           break;
        case SET_V:   value = op.value;                       break;
        case PUSH:    stack.push_back(elements[op.element]);  break;
        case PUSH_V:  stack.push_back(op.value);              break;
        case PUSH_C:  stack.push_back(value);                 break;
        default:      break;
      }
    }

    set_element(expr.target_element, value);
  }
};
