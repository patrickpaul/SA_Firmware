char last_byte1,last_byte2,last_byte3,last_byte4,last_address;
int finished;
int temp_byte;
char name_buffer[20];
int x, y;

void send_error(char error_code)
{
	fputc(ERR_START,USB);
	fputc(error_code,USB);
	fputc(0x03,USB);
}

void process_usb_data()  {

	char start_char,command_char,dummy_char,byte1,byte2,byte3,byte4,channel;
	int16 addr_lsb, addr_msb;
	int16 final_address, last_address;


	/*if(is_streaming) {
		process_stream_byte();
		return;
	}
*/
	// Wait until we get a starting char. Escapes after timeout to allow program to continue processing

	start_char = fast_timed_getc();

	if(TIMEOUT_ERROR == true) {
		return;
	}
	
	/* THIS LIST MUST BE UPDATED WHENEVER WE ADD A NEW START CHARACTER */
	if(
		(start_char != 0x02) && // GENERAL
		(start_char != 0x04) && // WRITE_DSP_CONFIG_VALUE
		(start_char != 0x05) && // GET_DSP_CONFIG_VALUE
		(start_char != 0x07) && // SEND_DSP_VALUE_DEBUG
		(start_char != 0x08) && // READ_DSP_VALUE
		(start_char != 0x09) && // UTILITY
		(start_char != 0x10) && // FLASH_PROGRAM_ACTIONS
		(start_char != 0x12) && // READ_RS232_VALUE
		(start_char != 0x13) && // SET_RS232_VALUE
		(start_char != 0x14) && // SET_DEVICE_PROPERTY
		(start_char != 0x17) && // SEND_DSP_VALUE_DEBUG
		(start_char != 0x15)    // GET_DEVICE_PROPERTY
		)
	{
		send_error(ERR_INVALID_START);
		return;
	}


	if(start_char == 0x02) {
		goto GENERAL;
	}
	
	if(start_char == 0x04) {
		goto WRITE_DSP_CONFIG_VALUE;
	}

	if(start_char == 0x05) {
		goto GET_DSP_CONFIG_VALUE;
	}
	
	if(start_char == 0x07) {
		goto SEND_DSP_VALUE;
	}

	if(start_char == 0x08) {
		goto READ_DSP_VALUE;
	}

	//if(start_char == 0x09) {
		//goto UTILITY;
	//}

	if(start_char == 0x10) {
		goto FLASH_PROGRAM_ACTIONS;
	}
/*
	if(start_char == 0x11) {
		goto PHANTOM_POWER_ACTIONS;
	}
*/

	if(start_char == 0x12) {
		goto READ_RS232_VALUE;
	}

	if(start_char == 0x13) {
		goto SET_RS232_VALUE;
	}

	if(start_char == 0x14) {
		goto SET_DEVICE_PROPERTY;
	}

	if(start_char == 0x15) {
		goto GET_DEVICE_PROPERTY;
	}
	

	/* IF YOU ADD A NEW START CHARACTER, UPDATE THE VALID LIST ABOVE */


GENERAL:
	
		command_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_COMMAND_TIMEOUT);
			return;
		}

		dummy_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No end char. Start over.
			send_error(ERR_END_TIMEOUT);
			return;
		}

		if(dummy_char != 0x03) {
			// Ending char not 0x03
			send_error(ERR_END_INVALID);
			return;
		}

		switch(command_char)
		{
			case 0x01 :
				// RTS
				fputc(0x06,USB);
				fputc(0x01,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x04 :
				// DEVICE ID
				fputc(0x06,USB);
				fputc(0x04,USB);
				fputc(DEVICE_ID_MSB,USB);
				fputc(DEVICE_ID_LSB,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x05 :
				// SOFT REBOOT
				softboot();
				fputc(0x06,USB);
				fputc(0x05,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x07 :
				// Firmware Version

				fputc(0x06,USB);
				fputc(0x07,USB);
				fputc(MAJOR_REVISION,USB);
				fputc(MINOR_REVISION,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x08 :
				
				// TODO - Not yet implemented

				fputc(0x06,USB);
				fputc(0x08,USB);
				fputc(0x03,USB);
			break;

			case 0x09 :
				
				// TODO - Not yet implemented

				update_phantom_power();

				fputc(0x06,USB);
				fputc(0x09,USB);
				fputc(0x03,USB);
			break;


			case 0x10 :
				// DISABLE TIMERS

				SETUP_TIMER_0(RTCC_OFF);
				setup_timer_1(T1_DISABLED);

				fputc(0x06,USB);
				fputc(0x10,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x11 :
				// ENABLE TIMERS

				setup_timer_0(T0_INTERNAL|T0_DIV_64);
				setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);

				setup_interrupts();

				fputc(0x06,USB);
				fputc(0x11,USB);
				fputc(0x03,USB);
				return;
			break;


			case 0x20 :
				// Reboot for firmware update
				fputc(0x06,USB);
				fputc(0x20,USB);
				fputc(0x03,USB);
				reset_cpu();

			break;


			default :
				send_error(ERR_COMMAND_INVALID);
				return;
			break;
		}

WRITE_DSP_CONFIG_VALUE:

		addr_msb = timed_getc();

		if(timeout_error == true) {
			// Timed out. No address. Start over.
			send_error(ERR_ADDR_TIMEOUT);
			return;
		}

		addr_lsb = timed_getc();

		if(timeout_error == true) {
			// Timed out. No address. Start over.
			send_error(ERR_ADDR_TIMEOUT);
			return;
		}


		if(addr_msb > 0) {
			final_address = 0;
			final_address = addr_msb;
			final_address <<= 8;
			final_address |= addr_lsb;
		} else {
			final_address = addr_lsb;
		}

		//if((final_address >= 0) && (final_address <= num_dsp_values)) {

			// byte1 is MSB
			byte1 = fast_timed_getc();
			byte2 = fast_timed_getc();
			byte3 = fast_timed_getc();
			byte4 = fast_timed_getc();

			if(timeout_error == true) {
				// Timed out on one of the bytes
				fputc(0x15,USB);
				fputc(ERR_DATA_TIMEOUT,USB);
				fputc(0x03,USB);
				return;
			}	
			
			dummy_char = timed_getc();
	
			if(timeout_error == true) {
				// Timed out. No command. Start over.
				fputc(0x15,USB);
				fputc(ERR_END_TIMEOUT,USB);
				fputc(0x03,USB);
				return;
			}
	
			if(dummy_char != 0x03) {
				// Ending char not 0x03
				fputc(0x15,USB);
				fputc(ERR_END_INVALID,USB);
				fputc(0x03,USB);
				return;
			}
			
			last_address = final_address;
			last_byte1 = byte1;
			last_byte2 = byte2;
			last_byte3 = byte3;
			last_byte4 = byte4;

			read_flash_page_into_buffer(&PAGE_BUFFER_A,CURRENT_FLASH_PROGRAM,addr_index_to_page_index(final_address));

			int32 new_dsp_value = 0x00000000 | byte1;
			new_dsp_value = new_dsp_value << 8;
			new_dsp_value = new_dsp_value | byte2;
			new_dsp_value = new_dsp_value << 8;
			new_dsp_value = new_dsp_value | byte3;
			new_dsp_value = new_dsp_value << 8;
			new_dsp_value = new_dsp_value | byte4;


			if(final_address < num_dsp_values) {
				send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,READ_CONFIG_ADDRESS(final_address),new_dsp_value);
			}
			PAGE_BUFFER_A[addr_index_to_buffer_index(final_address)] = new_dsp_value;

			write_buffer_to_flash_page(&PAGE_BUFFER_A,CURRENT_FLASH_PROGRAM,addr_index_to_page_index(final_address));

			// Send ACK
			fputc(0x06,USB);
			fputc(addr_msb,USB);
			fputc(addr_lsb,USB);
			fputc(0x03,USB);	
			return;

		//} else {
		//	// Invalid address
		//	send_error(ERR_ADDR_INVALID);
		//	return;
		//}

GET_DSP_CONFIG_VALUE:

		addr_msb = timed_getc();

		if(timeout_error == true) {
			// Timed out. No address. Start over.
			send_error(ERR_ADDR_TIMEOUT);
			return;
		}

		//printf("Got address 1 %u\r\n",addr_index);

		addr_lsb = timed_getc();

		if(timeout_error == true) {
			// Timed out. No address. Start over.
			send_error(ERR_ADDR_TIMEOUT);
			return;
		}

		//printf("Got address 2 %u\r\n",addr_index);

		if(addr_lsb == 255) {
			final_address = 0;
			final_address += addr_msb;
			final_address += addr_lsb;
		} else {
			final_address = addr_lsb;
		}

		dummy_char = timed_getc();


		if(timeout_error == true) {
			// Timed out. No end char. Start over.
			send_error(ERR_END_TIMEOUT);
			return;
		}
		
		if(dummy_char != 0x03) {
			// Ending char not 0x03
			send_error(ERR_END_INVALID);
			return;
		}

		if((final_address >= 0) && (final_address <= num_dsp_values)) {

			// TODO - Re-implement
			//int32 value = READ_CONFIG_VALUE(final_address);
	
			int32 value = 0;

			char byte4 = value & 0xFF;
			value = value >> 8;
		
			char byte3 = value & 0xFF;
			value = value >> 8;
			
			char byte2 = value & 0xFF;
			char byte1 = value >> 8;
		
			fputc(0x06,USB);
			fputc(addr_msb,USB);
			fputc(addr_lsb,USB);
			fputc(byte1,USB);
			fputc(byte2,USB);
			fputc(byte3,USB);
			fputc(byte4,USB);
			fputc(0x03,USB);
			return;
	
		} else {
			// Invalid address
			send_error(ERR_ADDR_INVALID);
			return;
		}

	// END GET_VALUE label

SEND_DSP_VALUE:

		byte addr_byte1,addr_byte2,addr_byte3,addr_byte4;
		byte val_byte1,val_byte2,val_byte3,val_byte4;

		addr_byte1 = fast_timed_getc();
		addr_byte2 = fast_timed_getc();
		addr_byte3 = fast_timed_getc();
		addr_byte4 = fast_timed_getc();

		val_byte1 = fast_timed_getc();
		val_byte2 = fast_timed_getc();
		val_byte3 = fast_timed_getc();
		val_byte4 = fast_timed_getc();

		if(timeout_error == true) {
			// Timed out on one of the bytes
			fputc(0x15,USB);
			fputc(0x17,USB);
			fputc(0x03,USB);
			return;
		}	
		
		dummy_char = timed_getc();

		if(timeout_error == true) {
			// Timed out. No command. Start over.
			fputc(0x15,USB);
			fputc(ERR_END_TIMEOUT,USB);
			fputc(0x03,USB);
			return;
		}

		if(dummy_char != 0x03) {
			// Ending char not 0x03
			fputc(0x15,USB);
			fputc(0x13,USB);
			fputc(0x03,USB);
			return;
		}

		

		int32 debug_address = 0x00000000 | addr_byte1;
		debug_address = debug_address << 8;
		debug_address = debug_address | addr_byte2;
		debug_address = debug_address << 8;
		debug_address = debug_address | addr_byte3;
		debug_address = debug_address << 8;
		debug_address = debug_address | addr_byte4;

		int32 debug_value = 0x00000000 | val_byte1;
		debug_value = debug_value << 8;
		debug_value = debug_value | val_byte2;
		debug_value = debug_value << 8;
		debug_value = debug_value | val_byte3;
		debug_value = debug_value << 8;
		debug_value = debug_value | val_byte4;
			
		send_dsp_command(debug_address,debug_value);

		fputc(0x06);
		fputc(0x07);
		fputc(0x03);


		return;

READ_DSP_VALUE:

		byte1 = fast_timed_getc();
		byte2 = fast_timed_getc();
		byte3 = fast_timed_getc();
		byte4 = fast_timed_getc();

		if(timeout_error == true) {
			// Timed out on one of the bytes
			fputc(0x15,USB);
			fputc(0x17,USB);
			fputc(0x03,USB);
			return;
		}	
		
		dummy_char = timed_getc();

		if(timeout_error == true) {
			// Timed out. No command. Start over.
			fputc(0x15,USB);
			fputc(ERR_END_TIMEOUT,USB);
			fputc(0x03,USB);
			return;
		}

		if(dummy_char != 0x03) {
			// Ending char not 0x03
			fputc(0x15,USB);
			fputc(0x13,USB);
			fputc(0x03,USB);
			return;
		}

		int32 address = 0x00000000 | byte1;
		address = address << 8;
		address = address | byte2;
		address = address << 8;
		address = address | byte3;
		address = address << 8;
		address = address | byte4;
			
		read_dsp_and_send_to_usb(address);

		return;



FLASH_PROGRAM_ACTIONS:

		command_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_COMMAND_TIMEOUT);
			return;
		}

		if(command_char == 0x04 || command_char == 0x05 || command_char == 0x09 || command_char == 0x11) {
			addr_msb = timed_getc();
			addr_lsb = timed_getc();
		} else {
			temp_byte = timed_getc();

		}
	
		if(timeout_error == true) {
			// Timed out. Couldn't read on/off. Start over.
			send_error(ERR_DATA_TIMEOUT);
			return;
		}
		
	
		

		char stream_size_msb,stream_size_lsb;

		if(command_char == 0x11) {
			stream_size_msb = timed_getc();
			stream_size_lsb = timed_getc();
		}	

		dummy_char = timed_getc();

		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_END_TIMEOUT);
			return;
		}

		switch(command_char) {

			case 0x01 :
				// SWITCH ACTIVE PROGRAM
				switch_flash_program(temp_byte);
				fputc(0x06,USB);
				fputc(0x01,USB);
				fputc(temp_byte,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x02 :
				// SAVE ACTIVE PROGRAM

				save_flash_program();

				fputc(0x06,USB);
				fputc(0x02,USB);
				fputc(temp_byte,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x04 :

				// SAVE ACTIVE SECTOR

				fputc(0x06,USB);
				fputc(0x05,USB);
				fputc(addr_msb,USB);
				fputc(addr_lsb,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x05 :

				FLASH_COPY_PROGRAM(addr_msb,addr_lsb);

				fputc(0x06,USB);
				fputc(0x05,USB);
				fputc(addr_msb,USB);
				fputc(addr_lsb,USB);
				fputc(0x03,USB);
				return;
			break;


			case 0x08 :

				// GET ACTIVE PROGRAM INDEX

				fputc(0x06,USB);
				fputc(0x08,USB);
				fputc(CURRENT_FLASH_PROGRAM,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x09 :

				// STREAM PROGRAM BLOCK TO USB

				read_flash_page_into_buffer(&PAGE_BUFFER_A,addr_msb,addr_lsb);

				fputc(0x06,USB);
				fputc(0x09,USB);
				fputc(addr_msb,USB);
				fputc(addr_lsb,USB);

				write_buffer_to_stream(&PAGE_BUFFER_A);

				fputc(0x03,USB);
				return;
			break;

			case 0x11 :
				
				
				int16 stream_size = 0;
		
				//fprintf(RS232,"Stream size MSB = %x, Stream size LSB = %x\r\n",stream_size_msb,stream_size_lsb);
				stream_size = stream_size | stream_size_msb;
				stream_size <<= 8;
				stream_size = stream_size | stream_size_lsb;

				/*if(data_available_usb()) {
					fprintf(RS232,"Data still available on USB...\r\n");
				} else {
					fprintf(RS232,"NO data available on USB...\r\n");
				}
*/
				// initiate_stream(int target_program, int target_page, int16 num_bytes)
				//initiate_stream(addr_msb,addr_lsb,stream_size);
				perform_stream(addr_msb,addr_lsb,stream_size);
				return;
				

			break;

			default :
				// Invalid utility command
				send_error(ERR_COMMAND_INVALID);
				return;
			break;

		}

READ_RS232_VALUE:
	
		command_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_COMMAND_TIMEOUT);
			return;
		}

		channel = timed_getc();

		if(timeout_error == true) {
			// Timed out. No end char. Start over.
			send_error(ERR_RS232_CH_TIMEOUT);
			return;
		}

		// TODO - this is zero based but use NUM_CHANNELS later
		if(channel > 4) {
			send_error(ERR_RS232_CH_INVALID);
			return;
		}

		dummy_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No end char. Start over.
			send_error(ERR_END_TIMEOUT);
			return;
		}

		if(dummy_char != 0x03) {
			// Ending char not 0x03
			send_error(ERR_END_INVALID);
			return;
		}

		switch(command_char)
		{
			case 0x01 :
				// MUTE STATUS
				fputc(0x06,USB);
				fputc(rs232_log_output_vol_index[channel-1],USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x02 :
				// VOL STATUS
				fputc(0x06,USB);
				fputc(((int)(rs232_log_output_vol_index[channel-1])),USB);
				fputc(0x03,USB);
				return;
			break;


			default :
				send_error(ERR_COMMAND_INVALID);
				return;
			break;
		}

SET_RS232_VALUE:


		command_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_COMMAND_TIMEOUT);
			return;
		}

		channel = timed_getc();

		if(timeout_error == true) {
			// Timed out. No end char. Start over.
			send_error(ERR_RS232_CH_TIMEOUT);
			return;
		}

		// TODO - this is zero based but use NUM_CHANNELS later
		if(channel > 4) {
			send_error(ERR_RS232_CH_INVALID);
			return;
		}

		dummy_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No end char. Start over.
			send_error(ERR_END_TIMEOUT);
			return;
		}

		if(dummy_char != 0x03) {
			// Ending char not 0x03
			send_error(ERR_END_INVALID);
			return;
		}

		switch(command_char)
		{
			case 0x00 :
				// SET MUTE OFF
				
				if(rs232_output_mute[channel-1] == 1) {
					mute_toggle_output(channel);
				}

				fputc(0x06,USB);
				fputc(0x00,USB);
				fputc(0x03,USB);
				return;
			break;

				case 0x01 :
				// SET MUTE ON
				
				if(rs232_output_mute[channel-1] == 0) {
					mute_toggle_output(channel);
				}

				fputc(0x06,USB);
				fputc(0x01,USB);
				fputc(0x03,USB);
				return;
			break;

		
			case 0x02 :
				// SET MUTE TOGGLE
				
				mute_toggle_output(channel);
				fputc(0x06,USB);
				fputc(0x02,USB);
				fputc(0x03,USB);
				return;
			break;

			case 0x03 :
				// RESET VOLUME
				
				discrete_vol_output(channel,100);
				fputc(0x06,USB);
				fputc(0x03,USB);
				fputc(0x03,USB);
				return;
			break;


			default :
				send_error(ERR_COMMAND_INVALID);
				return;
			break;
		}

SET_DEVICE_PROPERTY:	

		command_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_COMMAND_TIMEOUT);
			return;
		}

		unsigned int new_value = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. Couldn't read on/off. Start over.
			send_error(ERR_DATA_TIMEOUT);
			return;
		}
	
		unsigned int new_value2;

		if(command_char == 0x11 || command_char == 0x12) {

			// SETTING SLEEP_SECONDS OR SLEEP_HOLDTIME
			// THESE ARE 16 BIT SO WE NEED TWO CHARS
			
			new_value2 = timed_getc();

			if(timeout_error == true) {
			// Timed out. Couldn't read on/off. Start over.
				send_error(ERR_DATA_TIMEOUT);
				return;
			}
		}
		
		dummy_char = timed_getc();
		
		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_END_TIMEOUT);
			return;
		}
		
		int perform_eeprom_save = 0;
		
		int16 lsb,msb;

		switch(command_char) {

			case 0x01 :
				// SETTING AMP MODE
				
				if(new_value>2) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.AMP_MODE = new_value;
				perform_eeprom_save = 1;
			break;
			
			case 0x02 :
				// SETTING 70V MODE
				
				if(new_value>1) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.IS_70V = new_value;
				perform_eeprom_save = 1;
			break;
			
			case 0x03 :
				// CALIBRATING ADC_MIN
				
				int new_min = ADC_calibrate_min(1);
				fputc(0x06,USB);
				fputc(0x03,USB);
				fputc(new_min,USB);
				fputc(0x03,USB);
				perform_eeprom_save = 0;
				return;
			break;
			
			case 0x04 :
				// CALIBRATING ADC_MAX
				
				int new_max = ADC_calibrate_max(1);

				fputc(0x06,USB);
				fputc(0x04,USB);
				fputc(new_max,USB);
				fputc(0x03,USB);
				perform_eeprom_save = 0;
				return;
			break;
			
			case 0x05 :
				// SETTING RVC_ENABLE
				
				if(new_value>1) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.RVC_ENABLE = new_value;
				perform_eeprom_save = 1;
			break;
			
			case 0x06 :
				// SETTING USBDETECT_ENABLE
				
				if(new_value>1) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.USBDETECT_ENABLE = new_value;
				perform_eeprom_save = 1;
			break;
			
			case 0x07 :
				// SETTING AMPBOOT_DELAY_ENABLE
				
				if(new_value>1) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.AMPBOOT_DELAY_ENABLE = new_value;
				perform_eeprom_save = 1;
			break;
			
			case 0x08 :
				// SETTING PS_PIN_ENABLE
				
				if(new_value>1) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.PS_PIN_ENABLE = new_value;
				perform_eeprom_save = 1;
			break;
			
			case 0x09 :
				// SETTING DSP_VALUESEND_ENABLE
				
				if(new_value>1) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.DSP_VALUESEND_ENABLE = new_value;
				perform_eeprom_save = 1;
			break;

			case 0x10 :
				// SETTING SLEEP_ENABLE
				
				if(new_value>1) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.SLEEP_ENABLE = new_value;
				perform_eeprom_save = 1;
			break;

			case 0x11 :
				// SETTING SLEEP_SECONDS
				
				lsb = (int16)new_value;
				msb = (int16)new_value2;

				int16 new_sleep_seconds = (msb<<8) | (lsb);

				if(new_sleep_seconds<DEVICE_CONFIG.SLEEP_HOLDTIME) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.SLEEP_SECONDS = new_sleep_seconds;
				perform_eeprom_save = 1;
			break;

			case 0x12 :
				// SETTING SLEEP_HOLDTIME
				
				lsb = (int16)new_value;
				msb = (int16)new_value2;

				int16 new_sleep_holdtime = (msb<<8) | (lsb);
				//fprintf(RS232,"LSB: %ld, MSB: %ld, INT16 %ld\r\n",lsb, msb, new_sleep_holdtime);

				if(new_sleep_holdtime>DEVICE_CONFIG.SLEEP_SECONDS) {
					send_error(ERR_DEVICE_CONFIG_INVALID);
					return;
				}
	
				DEVICE_CONFIG.SLEEP_HOLDTIME = new_sleep_holdtime;
				perform_eeprom_save = 1;
			break;

			case 0x13 :
				// SETTING SERIAL NUMBER
			
				finished = false;

				for(x = 0; x < 20; x++) {
					DEVICE_CONFIG.SERIAL[x] = 0xFF;
				}


				int16 char_receive_count = 0;

				while((char_receive_count < 20)	&& (timeout_error == false)&& (finished == false))
				{
					temp_byte = timed_getc();
					//temp_byte = fgetc(USB);
					if(temp_byte == 0x0A) {
						finished = true;
					} else {
						DEVICE_CONFIG.SERIAL[char_receive_count] = temp_byte;	

					}
					char_receive_count++;
				
				}

				if(!finished) {
					dummy_char = timed_getc();
					
					if(timeout_error == true) {
						// Timed out. No command. Start over.
						fputc(0x15,USB);
						fputc(ERR_END_TIMEOUT,USB);
						fputc(0x03,USB);
						return;
					}
					
					if(dummy_char != 0x03) {
						// Ending char not 0x03
						fputc(0x15,USB);
						fputc(0x12,USB);
						fputc(0x03,USB);
						return;
						
					}
				}

				perform_eeprom_save = 1;

			break;
			
			default :
				// Invalid utility command
				send_error(ERR_COMMAND_INVALID);
				return;
			break;
		}

		if(perform_eeprom_save == 1) {
			INTEEPROM_PUT(&DEVICE_CONFIG,sizeof(DEVICE_CONFIG),100);
			delay_ms(10);

			fputc(0x06,USB);
			fputc(command_char,USB);
			fputc(new_value,USB);
			fputc(0x03,USB);

			return;
		}

GET_DEVICE_PROPERTY:	

		command_char = timed_getc();
	
		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_COMMAND_TIMEOUT);
			return;
		}
		
		dummy_char = timed_getc();
		
		if(timeout_error == true) {
			// Timed out. No command. Start over.
			send_error(ERR_END_TIMEOUT);
			return;
		}

		switch(command_char) {

			case 0x01 :
				// GET AMPLIFIER MODE

				fputc(0x06);
				fputc(0x01);
				fputc(DEVICE_CONFIG.AMP_MODE);
				fputc(0x03);
				return;
			break;

			case 0x02 :
				// GET 70V MODE
				fputc(0x06);
				fputc(0x02);
				fputc(DEVICE_CONFIG.IS_70V);
				fputc(0x03);
				return;
			break;

			case 0x03 :
				// GET ADC_MIN
				fputc(0x06);
				fputc(0x03);
				fputc((int)DEVICE_CONFIG.ADC_CALIBRATION_MIN);
				fputc(0x03);
				return;
			break;

			case 0x04 :
				// GET ADC_MAX
				fputc(0x06);
				fputc(0x04);
				fputc((int)DEVICE_CONFIG.ADC_CALIBRATION_MAX);
				fputc(0x03);
				return;
			break;

			case 0x05 :
				// GET RVC_ENABLE
				fputc(0x06);
				fputc(0x05);
				fputc(DEVICE_CONFIG.RVC_ENABLE);
				fputc(0x03);
				return;
			break;

			case 0x06 :
				// GET USBDETECT
				fputc(0x06);
				fputc(0x06);
				fputc(DEVICE_CONFIG.USBDETECT_ENABLE);
				fputc(0x03);
				return;
			break;

			case 0x07 :
				// GET AMPBOOT
				fputc(0x06);
				fputc(0x07);
				fputc(DEVICE_CONFIG.AMPBOOT_DELAY_ENABLE);
				fputc(0x03);
				return;
			break;
	
			case 0x08 :
				// GET PS_PIN
				fputc(0x06);
				fputc(0x08);
				fputc(DEVICE_CONFIG.PS_PIN_ENABLE);
				fputc(0x03);
				return;
			break;

			case 0x09 :
				// DSP_VALUESEND
				fputc(0x06);
				fputc(0x09);
				fputc(DEVICE_CONFIG.DSP_VALUESEND_ENABLE);
				fputc(0x03);
				return;
			break;

			case 0x10 :
				// SLEEP_ENABLE
				fputc(0x06);
				fputc(0x10);
				fputc(DEVICE_CONFIG.SLEEP_ENABLE);
				fputc(0x03);
				return;
			break;

			case 0x11 :
				// SLEEP_SECONDS
				fputc(0x06);
				fputc(0x11);
				fprintf(USB,"%ld",DEVICE_CONFIG.SLEEP_SECONDS);
				fputc(0x0A);
				return;
			break;

			case 0x12 :
				// SLEEP_HOLDTIME
				fputc(0x06);
				fputc(0x12);
				fprintf(USB,"%ld",DEVICE_CONFIG.SLEEP_HOLDTIME);
				fputc(0x03);
				return;
			break;
	
			case 0x13 :
				// SERIAL NUMBER
				memcpy(name_buffer,DEVICE_CONFIG.SERIAL,sizeof(name_buffer));

				fputc(0x06);
				fputc(0x13);

				for(y = 0; y < 20; y++) {
					if(name_buffer[y] == 0xFF) {
						break;
					}
			
					fputc(name_buffer[y],USB);
				}

				fputc(0x03);
				return;
			break;

			case 0x14 :
				// GET CURRENT RVC

				int current_adc = read_adc();

				double percentage = RVC_to_decibel(current_adc);

				fputc(0x16);
				fputc(0x14);
				fputc(current_adc);
				fputc((int)percentage);
				fputc(0x03);
				return;
			break;
			
			default :
				// Invalid utility command
				send_error(ERR_COMMAND_INVALID);
				return;
			break;
		}

	// How did we get here? Should be impossible.. Let's send an error though...
	// Someone probably forgot a return statement above... D'oh!


	fputc(0x15,USB);
	fputc(ERR_UNKNOWN,USB);
	fputc(0x03,USB);
	return;
}

