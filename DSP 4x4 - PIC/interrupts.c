// USB DETECTION
#INT_EXT1 
void USBDETECT_ISR(void) 
{ 

   	disable_interrupts (INT_EXT1);

	delay_us(100);

	if(input(PIN_B1)) {
		IS_USB_CONNECTED = true;
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] PIN_B1 is high. USB CONNECT EVENT. Triggering on H_TO_L.\r\n");
		}
		ext_int_edge(1,H_TO_L); 

	} else {
		IS_USB_CONNECTED = false;
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] PIN_B1 is low. USB DISCONNECT EVENT. Triggering on L_TO_H.\r\n");
		}
		ext_int_edge(1,L_TO_H); 
	}
	
	enable_interrupts(INT_EXT1);
	clear_interrupt(INT_EXT1);
} 