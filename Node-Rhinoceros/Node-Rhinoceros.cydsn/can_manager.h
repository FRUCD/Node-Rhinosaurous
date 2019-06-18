#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H

    
#include <project.h>
#include "data.h"
#include "lcd_manager.h"
	
void can_init();
void can_msg_init(DataPacket* can_msg, uint16_t id);
int can_process(DataPacket* can_msg);
int can_compare(DataPacket* prev_msg, DataPacket* new_msg);
void can_process_BMS_STATUS();
void can_process_BMS_CURR();
void can_process_BMS_VOLT();
void can_process_BMS_TEMP();
void can_process_SOC();
void can_process_current();
void can_test_send();
void can_test_receive();


#endif
