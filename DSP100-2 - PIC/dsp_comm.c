BYTE dsp_read_buffer[8];

void i2c_write_4byte(int32 fourBytes) {

      int byte4 = fourBytes & 0xFF;
      fourBytes = fourBytes >> 8;
   
      int byte3 = fourBytes & 0xFF;
      fourBytes = fourBytes >> 8;
   
      int byte2 = fourBytes & 0xFF;
   
      int byte1 = fourBytes >> 8;
   
      i2c_write(byte1);
      i2c_write(byte2); 
      i2c_write(byte3);
      i2c_write(byte4);
   
}

void reset_dsp() {

	output_high(PIN_DSP_nRESET);
	delay_ms(200);
	output_low(PIN_DSP_nRESET);
	delay_ms(200);
	output_high(PIN_DSP_nRESET);
}


void send_dsp_command(int32 address, int32 command) {

   i2c_start();
   i2c_write(DSP_I2C_ADDRESS);
   i2c_write_4byte(address);
   i2c_write_4byte(command);
   i2c_stop();

}


void send_dsp_message(int32 message) {

   i2c_start();
   i2c_write(DSP_I2C_ADDRESS);
   i2c_write_4byte(message);
   i2c_stop();
}

void send_prefixed_dsp_command(int16 address_prefix, int16 address_suffix, int32 command) {

   i2c_start();
   i2c_write(DSP_I2C_ADDRESS);

   int32 address = address_prefix;
   address <<= 16;
   address |= address_suffix;
   i2c_write_4byte(address);
   i2c_write_4byte(command);
   i2c_stop();

}

int read_dsp_int_prefixed(int16 address_prefix,int16 address_suffix)
{
	i2c_start();

	int32 address = address_prefix;
   	address <<= 16;
   	address |= address_suffix;

	i2c_write(DSP_I2C_ADDRESS);
	i2c_write_4byte(address);
	i2c_stop();

	delay_ms(1);

	if(input(PIN_DSP_IRQ) == 0) {

		i2c_start();

		if(i2c_write(0x81) == 0) {

			for(int i = 0; i < 8; i++) {
				if(i == 7) {
					dsp_read_buffer[i] = i2c_read(0);;
				} else {
					dsp_read_buffer[i] = i2c_read();
				}

				delay_ms(1);
			}
		}

		i2c_stop();
	} else {
		fprintf(RS232,"IRQ never goes low");
	}

	return dsp_read_buffer[7];
}


void read_dsp_and_send_to_usb(int32 address)
{
	i2c_start();

	i2c_write(DSP_I2C_ADDRESS);
	i2c_write_4byte(address);
	i2c_stop();

	delay_ms(1);

	if(input(PIN_DSP_IRQ) == 0) {

		i2c_start();

		if(i2c_write(0x81) == 0) {

			for(int i = 0; i < 8; i++) {
				if(i == 7) {
					dsp_read_buffer[i] = i2c_read(0);
				} else {
					dsp_read_buffer[i] = i2c_read();
				}

				delay_us(100);
			}
	
			fputc(0x06,USB);
			//delay_ms(1);
			for(int x = 4; x < 8; x++) {
				fputc(dsp_read_buffer[x],USB);
				//delay_ms(1);
			}
			//delay_ms(1);
			fputc(0x03,USB);
			delay_ms(1);
		}

		i2c_stop();
	} else {
		//fprintf(RS232,"IRQ never goes low");
	}
}

void read_dsp_and_send_to_rs232(int32 address)
{
	i2c_start();

	i2c_write(DSP_I2C_ADDRESS);
	i2c_write_4byte(address);
	i2c_stop();

	delay_ms(1);

	if(input(PIN_DSP_IRQ) == 0) {

		i2c_start();

		if(i2c_write(0x81) == 0) {

			for(int i = 0; i < 8; i++) {
				if(i == 7) {
					dsp_read_buffer[i] = i2c_read(0);;
				} else {
					dsp_read_buffer[i] = i2c_read();
				}

				delay_ms(1);
			}
	
			fprintf(RS232,"Read:");
			for(int x = 4; x < 8; x++) {
				fputc(dsp_read_buffer[x],RS232);
			}
			fprintf(RS232,"\r\n");
		}

		i2c_stop();
	} else {
		fprintf(RS232,"IRQ never goes low");
	}
}
void read_unsolicited_DSP_message()
{
		i2c_start();

		if(i2c_write(0x81) == 0) {

			for(int i = 0; i < 8; i++) {
				if(i == 7) {
					dsp_read_buffer[i] = i2c_read(0);;
				} else {
					dsp_read_buffer[i] = i2c_read();
				}

				delay_us(100);
			}
			for(int x = 0; x < 8; x++) {
				fputc(dsp_read_buffer[x],RS232);
			}
			fprintf(RS232,"\r\n");
		}

		i2c_stop();

}

void load_dsp_values() {

/*
	for(int16 i = 0; i <= num_dsp_values; i++) {
		send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,READ_CONFIG_ADDRESS(i),READ_CONFIG_VALUE(i));
		//delay_ms(2);	
	}
*/
}

void dsp_mute_outputs()
{
	send_dsp_command(AM_MASTERGAIN,0x00000000);
}

void dsp_unmute_outputs()
{
	send_dsp_command(AM_MASTERGAIN,0x08000000);
}

void send_flash_program_to_dsp_buffered(int prog_index)
{
	int16 overall_counter = 0;

	for(int sector_counter = 0; sector_counter < 8; sector_counter++) {

		read_flash_page_into_buffer(&PAGE_BUFFER_A,prog_index,sector_counter);

		for(int i = 0; i < 64; i++) {
			if(PAGE_BUFFER_A[i] == 0xFFFFFFFF) {
				break;
			}

			if(READ_CONFIG_ADDRESS(overall_counter) == BRIDGEROUTER_SELECT0) {
				overall_counter++;
				continue;	
			}

			if(READ_CONFIG_ADDRESS(overall_counter) == BRIDGEROUTER_SELECT1) {
				overall_counter++;
				continue;	
			}

			if(READ_CONFIG_ADDRESS(overall_counter) == BRIDGEROUTER_SELECT2) {
				overall_counter++;
				continue;	
			}

			if(READ_CONFIG_ADDRESS(overall_counter) == BRIDGEROUTER_SELECT3) {
				overall_counter++;
				continue;	
			}


			send_prefixed_dsp_command(DSP_ADDRESS_WRITE_PREFIX,READ_CONFIG_ADDRESS(overall_counter),PAGE_BUFFER_A[i]);
			overall_counter++;
		}

		
	}
}

