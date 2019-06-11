
#include "lcd_manager.h"
#include <stdlib.h>
#include <stdio.h>
int count = 0;

void lcd_init() {
	LCD_Start();
	char8 intro1[] = "Formula Racing";
	char8 intro2[] = "Charging Circuit";
	LCD_PrintString(intro1);
	LCD_Position(1, 0);
	LCD_PrintString(intro2);
	CyDelay(3000);
}
	
void lcd_print_bms() {
	char8 BMS1[] = "V: 000.0V E:0000";
	char8 BMS2[] = "C: 000.0A T: 00C";  
	
	LCD_ClearDisplay();
	LCD_Position(0, 0);
	LCD_PrintString(BMS1);
	LCD_Position(1, 0);
	LCD_PrintString(BMS2);
}


void lcd_test_print() {
	char8 const test_string[] = "Hi there, test!";
	char8 test_buf[32];
	
	//count++;
	//itoa(count, test_buf, 10);
	LCD_ClearDisplay();
	//LCD_Position(0,0);
	//LCD_PrintString(test_buf);
	//LCD_PrintInt32(count);
	//LCD_PrintInt8(count);
	
	//voltage test print
	uint32_t voltage = 0x00017475;	//095.349
	char8 volt_string[5];
	LCD_Position(0,3);
	//sprintf(volt_string, "%03d.%01d", voltage/1000, voltage/100%10);
	LCD_PrintString(volt_string);
	
	//temp
	uint8_t temperature = 0x24;
	LCD_Position(1, 13);
	LCD_PrintHexUint8(temperature);
	
	//current
	uint16_t current = 0x123;
	char8 curr_string[3];
	sprintf(curr_string, "%03d", current); 
	LCD_Position(1, 3);
	LCD_PrintString(curr_string);
}

void lcd_print(char8* string_val) {
	LCD_PrintString(string_val);
}