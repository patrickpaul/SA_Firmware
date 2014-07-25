void softboot();
void initialize_first_boot();

void default_device_config()
{
	for(int x = 0; x < 20; x++) {
		DEVICE_CONFIG.SERIAL[x] = 0xFF;
	}

	DEVICE_CONFIG.SERIAL[0] = 'N';
	DEVICE_CONFIG.SERIAL[1] = 'O';
	DEVICE_CONFIG.SERIAL[2] = 'N';
	DEVICE_CONFIG.SERIAL[3] = 'E';

	DEVICE_CONFIG.USBDETECT_ENABLE = 		DEFAULT_USBDETECT_ENABLE;
	DEVICE_CONFIG.DSP_VALUESEND_ENABLE = 	DEFAULT_DSP_VALUESEND_ENABLE;
	
	delay_ms(10);
	
	INTEEPROM_PUT(&DEVICE_CONFIG,sizeof(DEVICE_CONFIG),IEEPROM_DEVICE_CONFIG_LOC);


	read_flash_page_into_buffer(&PAGE_BUFFER_A,CURRENT_FLASH_PROGRAM,8);
	PAGE_BUFFER_A[57] = 0;
	write_buffer_to_flash_page(&PAGE_BUFFER_A,CURRENT_FLASH_PROGRAM,8);

}

void print_device_config()
{
	char name_buffer[20];

	memcpy(name_buffer,DEVICE_CONFIG.SERIAL,sizeof(name_buffer));

	fprintf(RS232,"[CONFIG] SERIAL = ");

	for(int y = 0; y < 20; y++) {
		if(name_buffer[y] == 0xFF) {
			break;
		}

		fputc(name_buffer[y],RS232);

	} 

	fprintf(RS232,"\r\n");
	fprintf(RS232,"[CONFIG] DSP_VALUESEND_ENABLE = %u\r\n",DEVICE_CONFIG.DSP_VALUESEND_ENABLE);
}

void device_boot()
{
	/* POWER STARTUP SEQUENCE */
	delay_ms(POWERUP_DELAY);
	
	fprintf(RS232,"Booting into main application built on ");
	fprintf(RS232,__DATE__);
	fprintf(RS232," ");
	fprintf(RS232,__TIME__);
	fprintf(RS232,"\r");

	fprintf(RS232,"Device firmware is v%u.%u%s\r",MAJOR_REVISION,MINOR_REVISION,REVISION_TEXT);
	delay_ms(10);

	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Reading DSP addresses from flash into memory... ");
	}

	FLASH_ADDR_READ();

	if(DEBUG) {
		fprintf(RS232,"Done!\r\n");
	}

	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Checking if EEPROM is configured... ");
	}

	int eeprom_preset_number = read_eeprom(IEEPROM_PRESET_LOC);

	//TODO - Re-implement
	if(eeprom_preset_number == 0xFF) {
		if(DEBUG) {
			fprintf(RS232,"NO PRESET IN EEPROM, GOING TO DEFAULT\r\n");
		}
		//switch_flash_program(DEFAULT_PRESET);
		CURRENT_FLASH_PROGRAM = DEFAULT_PRESET;
		write_eeprom(IEEPROM_PRESET_LOC,CURRENT_FLASH_PROGRAM);
	} else {
		if(DEBUG) {
			fprintf(RS232,"BOOTING FROM STORED PRESET - %U\r\n",eeprom_preset_number);
		}
		//switch_flash_program(eeprom_preset_number);
		CURRENT_FLASH_PROGRAM = eeprom_preset_number;
	}

	delay_ms(10);

	int programmed_flag = read_eeprom(IEEPROM_FLAG_LOC);

	INTEEPROM_GET(&DEVICE_CONFIG,sizeof(device_configuration),IEEPROM_DEVICE_CONFIG_LOC);
	delay_ms(10);

	if(DEBUG) {
		print_device_config();
	}
	if(programmed_flag == 0xFF) {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Starting first boot routine\r\n");
		}

		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Saving default device properties...");
		}
		default_device_config();

		if(DEBUG) {
			fprintf(RS232,"Done!\r\n");
		}

		
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] New device config below...\r\n");
			print_device_config();
		}
		write_eeprom(IEEPROM_FLAG_LOC,0x01);
		delay_ms(10);
	}

	
	
	
	/* INIT RS232 volumes and mutes */

	rs232_premix_vol[0] = 1;
	rs232_premix_vol[1] = 1;
	rs232_premix_vol[2] = 1;
	rs232_premix_vol[3] = 1;

	rs232_premix_mute[0] = 0;
	rs232_premix_mute[1] = 0;
	rs232_premix_mute[2] = 0;
	rs232_premix_mute[3] = 0;

	rs232_output_vol[0] = 1;
	rs232_output_vol[1] = 1;
	rs232_output_vol[2] = 1;
	rs232_output_vol[3] = 1;

	rs232_output_mute[0] = 0;
	rs232_output_mute[1] = 0;
	rs232_output_mute[2] = 0;
	rs232_output_mute[3] = 0;


}

void softboot()
{
	delay_ms(50);
	
	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Pulling DSP reset LOW\r\n");
	}

	output_low(PIN_DSP_nRESET);

	delay_ms(50);

	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Pulling DSP reset HIGH\r\n");
	}

	output_high(PIN_DSP_nRESET);// DSP Reset
	
	delay_ms(50);
	
	if(DEVICE_CONFIG.DSP_VALUESEND_ENABLE)
	{
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Sending DSP values from program %u\r\n",CURRENT_FLASH_PROGRAM);
		}
		
		dsp_mute_outputs();

		send_flash_program_to_dsp_buffered(CURRENT_FLASH_PROGRAM);

		dsp_unmute_outputs();
		

		delay_ms(100);

	} else {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] NOT sending DSP values\r\n");
		}
	}

	update_phantom_power();

	


}

void setup_interrupts()
{
	enable_interrupts(GLOBAL);
	enable_interrupts(INT_RDA2);

	if(DEVICE_CONFIG.USBDETECT_ENABLE == 0) {
		IS_USB_CONNECTED = true;
		disable_interrupts(INT_EXT1); 
	} else {
		// Check initial plug state
		if(input(PIN_B1)) {
			if(DEBUG){
				fprintf(RS232,"[DEBUG] Initial state of USB is high. Setting IS_USB_CONNECTED to true\r\n");
			}
			IS_USB_CONNECTED = true;
			ext_int_edge(1,H_TO_L); 
		} else {
			if(DEBUG){
				fprintf(RS232,"[DEBUG] Initial state of USB is low. Setting IS_USB_CONNECTED to false\r\n");
			}
			ext_int_edge(1,L_TO_H); 
		}

		clear_interrupt(INT_EXT1); 
   		enable_interrupts(INT_EXT1);

	
	}
}


void setup_peripherals()
{

	setup_adc( ADC_CLOCK_INTERNAL );

	setup_adc_ports( sAN0 | sAN9 );

	set_adc_channel(0);

	setup_timer_0(T0_INTERNAL|T0_DIV_64);

	setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);

	setup_timer_3(T3_DISABLED | T3_DIV_BY_1);
   	setup_timer_4(T4_DISABLED,0,1);
   	setup_timer_5(T5_DISABLED | T5_DIV_BY_1);
   	setup_timer_6(T6_DISABLED,0,1);

	setup_wdt(WDT_OFF); 

}


