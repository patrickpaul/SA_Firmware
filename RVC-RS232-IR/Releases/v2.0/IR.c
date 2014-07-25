int get_RC5_command(void)
{
   
   	int16 tmp,t;
   	int i;
   	int inp;
   
   	disable_interrupts(INT_EXT);
	// First measure the start bit to see if we have RC-5 protocol
   
   	set_timer1(0); // Each tick is 1.6uS
   	while(IR_STATUS == 1);
   	t=get_timer1();
   
   	if ((t<400) || (t>800)) {
		enable_interrupts(INT_EXT);
		return 0;   // Not RC-5 protocol, escape
	}
   
   // Get remaining bits
   for (i=0;i<13;i++)
   {
      inp = IR_STATUS; // Get the high/low state on first half of the bit
      set_timer1(0);

      while (IR_STATUS==inp)
      {
         t=get_timer1();
         if (t>800) {
            
			enable_interrupts(INT_EXT);
			return 0; // Not RC-5 protocol, escape
         }
      }

      tmp<<=1; // Shift over one byte

      if (inp==0) tmp++;
	
      
		delay_us(900); // Skip second half of bit 
   }
   
   tmp = tmp & 0x7FF; // Remove toggle and start bits

   // Get 6-bit command from LSB side of transmission
   IR.command = tmp & 0x3F;
   
   tmp>>=6;
   // Get 5-bit address from rest of transmission
   IR.address = tmp & 0xff;

   // Successful reception
   IR.state = 1;

   
   // Return OR we can do change_vol() action here
   if(DEBUG_IR) {
		//printf("IR RECEIVED - Address: %u, Command: %u\n\r",IR.address,IR.command);
   }
   
	if(IR.address == 0 && IR.command == 16) {
    	vol_up();
		//if(DEBUG_IR) { printf("VOL UP"); }
   	} else if(IR.address == 0 && IR.command == 17) {
      	vol_down();
		//if(DEBUG_IR) { printf("VOL DOWN"); }
   	} else if(IR.address == 0 && IR.command == 13) {
      	mute_toggle();
		//if(DEBUG_IR) { printf("MUTE TOGGLE"); }
   	}
	
   
   IR.state = 0; // Clear state flag
   delay_ms(250); // similar to debounce..
   enable_interrupts(INT_EXT); // Ready to receive new command
   return 1;
}