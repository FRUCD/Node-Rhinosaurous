/* Node-Rhinoceros
	 Charger board FRUCD
	Simply prints BMS statuses to LCD
 */

#include <project.h>
#include "data.h"
#include "can_manager.h"
#include "lcd_manager.h"

// declared external in can_manager.c
volatile uint32_t voltage = 0;
volatile uint8_t charge = 0;


int main(void) {
	CYGlobalIntEnable;      //Uncomment this line to enable global interrupts 

	uint8_t atomic_state = CyEnterCriticalSection(); // BEGIN ATOMIC
	can_init();
	lcd_init();
    lcd_print_bms();
	CyDelay(10);				//give some time to finish setup
	CyExitCriticalSection(atomic_state);               // END ATOMIC
	
	for(;;)	{
        
                    
	} // main loop

	return 0;
} // main()

void msg_recieve(DataPacket * msg) {
	can_process(msg);
}