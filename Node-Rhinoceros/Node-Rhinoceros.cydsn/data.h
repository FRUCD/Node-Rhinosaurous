#ifndef DATA_H
#define DATA_H

#include <project.h>
	
#define MILLI_PERIOD 		43200000	//decrementing timer starting from this val, check top design
    
typedef struct {
	uint32_t millicounter;      //timestamp
	uint16_t id;                //id is for tracking CAN ID
	uint8_t length;         
	uint8_t data[8];            //8bytes for each data packet
} DataPacket;

#endif