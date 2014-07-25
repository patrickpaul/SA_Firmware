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

	DEVICE_CONFIG.AMP_MODE = 				DEFAULT_AMP_MODE;
	DEVICE_CONFIG.IS_70V = 					DEFAULT_IS_70V;

	DEVICE_CONFIG.ADC_CALIBRATION_MIN = 	DEFAULT_ADC_CALIBRATION_MIN;
	DEVICE_CONFIG.ADC_CALIBRATION_MAX = 	DEFAULT_ADC_CALIBRATION_MAX;

	DEVICE_CONFIG.RVC_ENABLE = 				DEFAULT_RVC_ENABLE;
	DEVICE_CONFIG.USBDETECT_ENABLE = 		DEFAULT_USBDETECT_ENABLE;
	DEVICE_CONFIG.AMPBOOT_DELAY_ENABLE = 	DEFAULT_AMPBOOT_DELAY_ENABLE;
	DEVICE_CONFIG.PS_PIN_ENABLE = 			DEFAULT_PS_PIN_ENABLE;
	DEVICE_CONFIG.DSP_VALUESEND_ENABLE = 	DEFAULT_DSP_VALUESEND_ENABLE;
	
	DEVICE_CONFIG.SLEEP_ENABLE		= 		DEFAULT_SLEEP_ENABLE;
	DEVICE_CONFIG.SLEEP_SECONDS		= 		DEFAULT_SLEEP_SECONDS;
	DEVICE_CONFIG.SLEEP_HOLDTIME	= 		DEFAULT_SLEEP_HOLDTIME;
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

	

	if(DEVICE_CONFIG.AMP_MODE == 0) {
		fprintf(RS232,"[CONFIG] AMP_MODE = 4CH\r\n");
	} else if(DEVICE_CONFIG.AMP_MODE == 1) {
		fprintf(RS232,"[CONFIG] AMP_MODE = 2CH\r\n");
	} else {
		fprintf(RS232,"[CONFIG] AMP_MODE = 1CH\r\n");
	}

	
	fprintf(RS232,"[CONFIG] IS_70V = %u\r\n",DEVICE_CONFIG.IS_70V);

	fprintf(RS232,"[CONFIG] ADC_CALIBRATION_MIN = %f\r\n",DEVICE_CONFIG.ADC_CALIBRATION_MIN);
	fprintf(RS232,"[CONFIG] ADC_CALIBRATION_MAX = %f\r\n",DEVICE_CONFIG.ADC_CALIBRATION_MAX);

	fprintf(RS232,"[CONFIG] RVC_ENABLE = %u\r\n",DEVICE_CONFIG.RVC_ENABLE);
	fprintf(RS232,"[CONFIG] USBDETECT_ENABLE = %u\r\n",DEVICE_CONFIG.USBDETECT_ENABLE);
	fprintf(RS232,"[CONFIG] AMPBOOT_DELAY_ENABLE = %u\r\n",DEVICE_CONFIG.AMPBOOT_DELAY_ENABLE);
	fprintf(RS232,"[CONFIG] PS_PIN_ENABLE = %u\r\n",DEVICE_CONFIG.PS_PIN_ENABLE);
	fprintf(RS232,"[CONFIG] DSP_VALUESEND_ENABLE = %u\r\n",DEVICE_CONFIG.DSP_VALUESEND_ENABLE);
	fprintf(RS232,"[CONFIG] SLEEP_ENABLE = %u\r\n",DEVICE_CONFIG.SLEEP_ENABLE);
	fprintf(RS232,"[CONFIG] SLEEP_SECONDS = %ld\r\n",DEVICE_CONFIG.SLEEP_SECONDS);
	fprintf(RS232,"[CONFIG] SLEEP_HOLDTIME = %ld\r\n",DEVICE_CONFIG.SLEEP_HOLDTIME);

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
		//initialize_first_boot();


		write_eeprom(IEEPROM_FLAG_LOC,0x01);
		delay_ms(10);
	}	
	/* INIT RS232 volumes and mutes */


}

void softboot()
{
	delay_ms(50);
	
	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Pulling DSP and Amp reset LOW\r\n");
	}

	// TODO - Mute transistors

	output_high(AUD_MUTE);

	output_low(PIN_DSP_nRESET);
	output_low(PIN_AMP_nRESET);

	if(DEVICE_CONFIG.PS_PIN_ENABLE) {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Enabling Power Supply\r\n");
		}	

		output_high(PIN_PSON);
	}

	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Muting DSP Output (NOT YET IMPLEMENTED)\r\n");
	}

	

	if(DEVICE_CONFIG.AMP_MODE == 0) {
		//4CH
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Putting amplifier into 4 CH mode\r\n");
		}
		output_low(PIN_AMP_M1);  // TI Chip - Mode Pin 1
		output_low(PIN_AMP_M2); // TI Chip - Mode Pin 2
		output_high(PIN_AMP_M3);  // TI Chip - Mode Pin 3
	}

	if(DEVICE_CONFIG.AMP_MODE == 1) {
		//2CH
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Putting amplifier into 2 CH mode\r\n");
		}
		output_low(PIN_AMP_M1);  // TI Chip - Mode Pin 1
		output_high(PIN_AMP_M2); // TI Chip - Mode Pin 2
		output_low(PIN_AMP_M3);  // TI Chip - Mode Pin 3
	}

	if(DEVICE_CONFIG.AMP_MODE == 2) {
		//1.2CH
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Putting amplifier into 1.2 CH mode\r\n");
		}
		output_high(PIN_AMP_M1);  // TI Chip - Mode Pin 1
		output_high(PIN_AMP_M2); // TI Chip - Mode Pin 2
		output_low(PIN_AMP_M3);  // TI Chip - Mode Pin 3
	}

	delay_ms(DELAY_AMP_MODE_SETTLE);

	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Pulling AMP reset HIGH\r\n");
	}

	output_high(PIN_AMP_nRESET);

	if(DEVICE_CONFIG.AMPBOOT_DELAY_ENABLE) {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Waiting for AMP ready....\r\n");
		}
		while(!input(PIN_AMP_READY)) {
	
		}
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] AMP is ready!\r\n");
		}
	}

	
	delay_ms(50);

	
	if(DEBUG) {
		fprintf(RS232,"[DEBUG] Pulling DSP reset HIGH\r\n");
	}

	output_high(PIN_DSP_nRESET);// DSP Reset
	
	delay_ms(DELAY_DSP_RESET_SETTLE);

	if(DEVICE_CONFIG.IS_70V == 0) {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Not a 70V amp. Disabling 100Hz HP Filter\r\n");
		}

		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,SEVENTYVHP_BYPASS,0x00000001);
	}
		

	if(DEVICE_CONFIG.AMP_MODE == 0) {
		//4CH
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Putting DSP into 4 CH mode\r\n");
		}

		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT0,0x00000001);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT1,0x00000002);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT2,0x00000003);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT3,0x00000004);
	}

	if(DEVICE_CONFIG.AMP_MODE == 1) {
		//2CH
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Putting DSP into 2 CH mode\r\n");
		}

		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT0,0x00000001);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT1,0x00000001);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT2,0x00000003);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT3,0x00000003);
	}

	if(DEVICE_CONFIG.AMP_MODE == 2) {
		//1.2CH
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Putting DSP into 1.2 CH mode\r\n");
		}

		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT0,0x00000001);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT1,0x00000001);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT2,0x00000003);
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,BRIDGEROUTER_SELECT3,0x00000004);
	}

	
	if(DEVICE_CONFIG.DSP_VALUESEND_ENABLE)
	{
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Sending DSP values from program %u\r\n",CURRENT_FLASH_PROGRAM);
		}
		
		dsp_mute_outputs();

		send_flash_program_to_dsp_buffered(CURRENT_FLASH_PROGRAM);

		// We will have an RVC value to read. Keep this muted. We'll unmute later
		if(DEVICE_CONFIG.RVC_ENABLE != 1) {
			dsp_unmute_outputs();
		}

		delay_ms(100);

	} else {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] NOT sending DSP values\r\n");
		}
	}

	if(DEVICE_CONFIG.RVC_ENABLE == 1) {

		pin_in_mute_state = !input(PIN_AMP_nMUTE);
	
		set_adc_channel(0);
		delay_us(10);
		current_adc = read_adc();
		
		if(pin_in_mute_state) {
			is_muted = true;
			send_dsp_command(AM_ANALOG1_TRIM,0x00000000);
			send_dsp_command(AM_ANALOG2_TRIM,0x00000000);
			send_dsp_command(AM_ANALOG3_TRIM,0x00000000);
			send_dsp_command(AM_ANALOG4_TRIM,0x00000000);
			set_timer1(15550);
			clear_interrupt(INT_TIMER1);
	
			if(DEBUG) {
				fprintf(RS232,"[DEBUG] Startup RVC - Muted\r\n");
			}
		} else {
			double dsp_value = RVC_to_dsp_value(current_adc);

			send_dsp_command(AM_ANALOG1_TRIM,(int32)(dsp_value*2147483648.0));
			send_dsp_command(AM_ANALOG2_TRIM,(int32)(dsp_value*2147483648.0));
			send_dsp_command(AM_ANALOG3_TRIM,(int32)(dsp_value*2147483648.0));
			send_dsp_command(AM_ANALOG4_TRIM,(int32)(dsp_value*2147483648.0));

			if(DEBUG) {
				fprintf(RS232,"[DEBUG] Startup RVC - ADC = %u, Value = %.4f\r\n",current_adc,dsp_value);
			}

		}

		dsp_unmute_outputs();

	} else {
		if(DEBUG) {
				fprintf(RS232,"[DEBUG] DEVICE_CONFIG.RVC_ENABLE == 0\r\n");
		}
	}


	output_low(AUD_MUTE);

	update_phantom_power();

}

void setup_interrupts()
{
	if(DEVICE_CONFIG.RVC_ENABLE == 1) {

		set_timer1(15550);
		enable_interrupts(INT_TIMER1); 

		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Enabling RVC\r\n");
		}
	} else {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Disabling RVC\r\n");
		}
	}
	if(DEBUG) {
		fprintf(RS232,"[DEBUG]: Enabling global interrupts\r\n");
	}
	enable_interrupts(GLOBAL);

	
	enable_interrupts(INT_RDA2);
	
	

	disable_interrupts(INT_EXT); 

	if(DEVICE_CONFIG.SLEEP_ENABLE == 1) {
		// Sleep timer enabled.. check initial state
		if(DEBUG){
			fprintf(RS232,"[DEBUG] Sleep detect enabled... checking current state...");
		}

		if(input(PIN_AUDIODETECT)) {
			// We currently have audio
			if(DEBUG){
				fprintf(RS232,"AUDIO PRESENT\r\n");
				fprintf(RS232,"[DEBUG] Will disable sleep timer and wait for audiodetect to go low\r\n");
			}

				ext_int_edge(0,H_TO_L); 
				enable_interrupts(INT_EXT);
				disable_interrupts(INT_TIMER0);
				sleep_timer_active = 0;
				is_in_sleep = 0;
		} else {
			if(DEBUG){
				fprintf(RS232,"NO AUDIO PRESENT\r\n");
				fprintf(RS232,"[DEBUG] Will start sleep timer and wait for audiodetect to go high\r\n");
			}

			ext_int_edge(0,L_TO_H); 
			enable_interrupts(INT_EXT);

			set_timer0(7936);
			enable_interrupts(INT_TIMER0);
			sleep_timer_active = 1;
			is_in_sleep = 0;
				
		}				

	}

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
			IS_USB_CONNECTED = false;
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


