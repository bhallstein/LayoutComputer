#include "Op.h"
#include "LayoutElement.h"
#include "Operation.h"
#include "LayoutData.h"


// These are useful for clients to access properties in within layoutdata
#define PROP_X 0
#define PROP_Y 1
#define PROP_W 2
#define PROP_H 3
#define PROPERTY_INDEX(element_ind, property) (element_ind*4 + property)
