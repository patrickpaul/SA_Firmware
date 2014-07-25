#include <16F628A.h>
#include <RVC-RS232-IR.h>
#include <DPOT.c>
#include <IR.c>
#include <RS232.c>

// Interrupt triggers when IR_INPUT goes from HIGH to LOW
#int_EXT
void EXT_isr() {
    get_RC5_command();
}



void main() 
{
	int rs232_command = 0, eeprom_volume = 0, eeprom_mute = 0;
   	
	setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   	setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   
   	setup_timer_2(T2_DISABLED,0,1);
   	setup_comparator(NC_NC_NC_NC);
   	setup_vref(FALSE);

   	enable_interrupts(INT_EXT);
   	ext_int_edge(H_TO_L);
   	enable_interrupts(GLOBAL);

   	IR.state = 0;

   	/** READ CONFIGURATION VALUES FROM EEPROM, RESET IF EEPROM EMPTY **/
   	eeprom_volume = read_eeprom(10);
   	eeprom_mute = read_eeprom(12);

   	if(eeprom_volume == 0xFF) { // EEPROM empty
    	//CHANGEME
		current_volume = 100;
		is_muted = 0;
   	} else {
		current_volume = eeprom_volume;
		muted_volume = eeprom_volume;
		is_muted = eeprom_mute;
	}
	
    if(is_muted == 0) {
   		saveAndSetVol();
	}

	if(DEBUG) { printf("EEPROM VOL: %d MUTE: %d\n\r",current_volume,is_muted); }

   /** END EEPROM INIT **/
   
	putc(COMMAND_START_BYTE);
	putc('O');
	putc('K');
	putc(COMMAND_END_BYTE);

   while (true) // Infinite loop
   {
		rs232_command = get_serial_command();
      	switch(rs232_command) {
			case 0 :
				// error;

				putc(COMMAND_START_BYTE);
				putc('E');
				putc('R');
				putc(COMMAND_END_BYTE);
			break;

			case COMMAND_VOL_UP :
				vol_up();
			break;

			case COMMAND_VOL_DOWN :
				vol_down();
			break;

			case COMMAND_MUTE_TOGGLE :
				mute_toggle();
			break;

			case COMMAND_FORCE_MUTE :
				mute_forcemute();
			break;

			case COMMAND_FORCE_UNMUTE :
				mute_forceunmute();
			break;

			case COMMAND_VOL_DISCRETE :
				vol_discrete();
			break;

			case COMMAND_MUTE_STATUS :
				// Mute status
				putc(COMMAND_START_BYTE);
				putc(MUTE_START_BYTE);
				if(is_muted == 1) {
					putc(0x01);
				} else {
					putc(0x00);
				}
				putc(COMMAND_END_BYTE);
			break;

			case COMMAND_VOL_STATUS :
					putc(COMMAND_START_BYTE);
					putc(VOL_START_BYTE);
					putc(current_volume);
					putc(COMMAND_END_BYTE);
			break;

			case COMMAND_GET_VERSION	:
				putc(COMMAND_START_BYTE);
				putc(VERSION_MAJOR);
				putc(VERSION_MINOR);
				putc(COMMAND_END_BYTE);
			break;
	
			default :
				// error

				putc(COMMAND_START_BYTE);
				putc('E');
				putc('R');
				putc(COMMAND_END_BYTE);

			break;
		}
      
   } 
}