#include <18LF46K22.h>
#device adc=8

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES WDT128                	//Watch Dog Timer uses 1:128 Postscale
#FUSES HSM                   	//High speed Osc, medium power 4MHz-16MHz
#FUSES NOPLLEN               	//4X HW PLL disabled, 4X PLL enabled in software
#FUSES PUT                   	//Power Up Timer
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES WDT_SW                	//No Watch Dog Timer, enabled in Software
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST               	//Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=14745600)

#define BOOTLOADER_START        0x2A 
#define BOOTLOADER_END          0x3FF + 0x400
#build (reset=BOOTLOADER_END +1  , interrupt=0x408 + 0x400 ) 
#org 0, BOOTLOADER_END {} 

#include <DSP4x4_PINS.h>
#include <DSP4x4_CONFIG.h>

#include <main.h>

#include <DSP_mapping.h>

#include <memory.c>

#include <w25q80bv.c>

#include <errorlist.h>
#include <dsp_comm.c>
#include <debug.c>
#include <eeprom.c>
#include <phantom.c>
#include <presets.c>
#include <device_boot.c>
#include <remote_volume.c>
#include <timed_getc.c>
#include <streaming.c>
#include <sa_usb.c>
#include <rs232.c>

#include <interrupts.c>

void main()
{
	delay_ms(100);
	// Setup ADC's and Timers
	setup_peripherals();

	// Initializes and reads external EEPROM. Loads default DEVICE_CONFIG if necessary
	device_boot();
	
	// Reset amplifier and DSP then load values into DSP
	softboot();

	// Enable/disable interrupts based on DEVICE_CONFIG parameters
	setup_interrupts();
	
	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Saving addresses into FLASH [R&D only]...");
	}

	default_addr();

	FLASH_ADDR_WRITE(14);

	if(DEBUG) {
		fprintf(RS232,"Done!\r\n");
	}

	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Disabling 100Hz High-Pass since we're a DSP 4x4...");
	}

	send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,SEVENTYVHP_BYPASS,0x00000001);

	if(DEBUG) {
		fprintf(RS232,"Done!\r\n");
	}

	while(true)	
	{	
		//if(IS_USB_CONNECTED) {
			process_usb_data();
		//}

		if(rs232_data_available) {
			
			process_rs232_data();
			
		}
	}
}