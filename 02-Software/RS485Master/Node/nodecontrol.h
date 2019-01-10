
#ifndef NODE_CONTROL_H
#define NODE_CONTROL_H

#include "inc.h"

#define MAX_NODES		25

typedef struct {
	uint8_t is_avaiable;
	uint8_t address;
	uint8_t output_state;
	uint8_t input_state;
} Nodes_t;


void Node_Control_InitNodes(void);
void Node_Control_DetectNodes(void);


#endif //NODE_CONTROL_H