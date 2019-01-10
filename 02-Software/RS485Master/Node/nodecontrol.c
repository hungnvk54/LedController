#include "nodecontrol.h"
#include "const.h"

Nodes_t nodes[MAX_NODES];

void Node_Control_DetectNodes(void){
  uint8_t node_index;
  
  for( node_index = 0 ; node_index < MAX_NODES; ++node_index){
      ///Send Signal to the node
  }
}

void Node_Control_InitNodes(void){
  uint8_t node_index;
  
  for( node_index = 0 ; node_index < MAX_NODES; ++node_index){
    nodes[node_index].is_avaiable = NO;
    nodes[node_index].address = node_index;
    nodes[node_index].output_state = OFF;
    nodes[node_index].input_state = OFF;
  }
}