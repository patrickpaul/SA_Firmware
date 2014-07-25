/* RS232 BUFFER */

int log_volume_index = 0;

#INT_RDA2
void serial_isr() {
   int t;
   buffer[next_in]=fgetc(RS232);
	buffer_unread++;
   t=next_in;
   next_in=(next_in+1) % RS232_BUFFER_SIZE;
   if(next_in==next_out)
     next_in=t;           // Buffer full!
}

BYTE bgetc() {
   BYTE c;

   c=buffer[next_out];
   next_out=(next_out+1) % RS232_BUFFER_SIZE;
   buffer_unread--;
	return(c);
}


void send_rs232_error(char error_code)
{
	fputc(0x12,RS232);
	fputc(error_code,RS232);
	fputc(0x0A,RS232);

	buffer_unread = 0;
	next_in = 0;
	next_out = 0;
}


void process_rs232_data()
{
	delay_ms(20);

	if(buffer_unread == 4 || buffer_unread == 5) {
		RS232_BYTE1 = bgetc();
		RS232_BYTE2 = bgetc();
		RS232_BYTE3 = bgetc();
		RS232_BYTE4 = bgetc();

		if(buffer_unread == 1) {
			RS232_BYTE5 = bgetc();
		} else {
			RS232_BYTE5 = 0xFF;
		}

		if(RS232_BYTE1 != 0x12)
		{
			if(DEBUG) {
				fprintf(RS232,"Bad RS232 command: %x %x %x %x %x\r",RS232_BYTE1,RS232_BYTE2,RS232_BYTE3,RS232_BYTE4,RS232_BYTE5);
			}

			send_rs232_error(ERR_INVALID_START);
			return;
		}

		switch(RS232_BYTE2) {

			case 0x01:
			case 0x55:
				// Volume up 10%
				
				vol_big_up_output(RS232_BYTE3);

				fputc(0x06,RS232);
				if(RS232_BYTE3 == 0) {
					fputc(((int)(rs232_output_vol[0]*100)),RS232);
				} else {
					fputc(((int)(rs232_output_vol[RS232_BYTE3-1]*100)),RS232);
				}
				fputc(0x0A,RS232);
				return;
			break;

			case 0x02:
			case 0x75:
				// Volume up 5%

				vol_small_up_output(RS232_BYTE3);

				fputc(0x06,RS232);
				if(RS232_BYTE3 == 0) {
					fputc(((int)(rs232_output_vol[0]*100)),RS232);
				} else {
					fputc(((int)(rs232_output_vol[RS232_BYTE3-1]*100)),RS232);
				}
				fputc(0x0A,RS232);
				return;
			break;

			case 0x04:
			case 0x44:
				// Volume down 10%

				vol_big_down_output(RS232_BYTE3);

				fputc(0x06,RS232);
				if(RS232_BYTE3 == 0) {
					fputc(((int)(rs232_output_vol[0]*100)),RS232);
				} else {
					fputc(((int)(rs232_output_vol[RS232_BYTE3-1]*100)),RS232);
				}
				fputc(0x0A,RS232);
				return;
			break;

			case 0x05:
			case 0x64:
				// Volume down 5%

				vol_small_down_output(RS232_BYTE3);

				fputc(0x06,RS232);
				if(RS232_BYTE3 == 0) {
					fputc(((int)(rs232_output_vol[0]*100)),RS232);
				} else {
					fputc(((int)(rs232_output_vol[RS232_BYTE3-1]*100)),RS232);
				}
				fputc(0x0A,RS232);
				return;
			break;

			case 0x06:
			case 0x56:
				// Discrete volume

				discrete_vol_output(RS232_BYTE3,RS232_BYTE4);

				fputc(0x06,RS232);
			
				if(RS232_BYTE3 == 0) {
					fputc(((int)(rs232_output_vol[0]*100)),RS232);
				} else {
					fputc(((int)(rs232_output_vol[RS232_BYTE3-1]*100)),RS232);
				}
				fputc(0x0A,RS232);
				return;
			break;

			case 0x07:
			case 0x42:
				// Volume Status

				fputc(0x06,RS232);
				fputc(((int)(rs232_output_vol[RS232_BYTE3-1]*100)),RS232);
				fputc(0x0A,RS232);
				return;
			break;

			case 0x08:
			case 0x4D:
				// Force mute on
				
				mute_on_output(RS232_BYTE3);
				fputc(0x06,RS232);
				fputc(0x01,RS232);
				fputc(0x0A,RS232);
				return;
			break;

			case 0x09:
			case 0x6D:
				// Force mute off
				
				mute_off_output(RS232_BYTE3);
				fputc(0x06,RS232);
				fputc(0x00,RS232);
				fputc(0x0A,RS232);
				return;
			break;

			case 0x10:
			case 0x54:
				// Toggle mute

				fputc(0x06,RS232);
				fputc(mute_toggle_output(RS232_BYTE3),RS232);
				fputc(0x0A,RS232);	
				return;
			break;

			case 0x11:
			case 0x43:
			// Mute status

				fputc(0x06,RS232);
				fputc(((int)(rs232_output_mute[RS232_BYTE3-1])),RS232);
				fputc(0x0A,RS232);
				return;
			break;

			case 0x12:
				// Change preset

				switch_flash_program(RS232_BYTE3);

				fputc(0x06,RS232);
				fputc(((int)CURRENT_FLASH_PROGRAM),RS232);
				fputc(0x0A,RS232);
				return;

			break;

			case 0x13:
			case 0x46:
				// Firmware version
				fprintf(RS232,"PIC firmware is v%u.%u%s\r",MAJOR_REVISION,MINOR_REVISION,REVISION_TEXT);
				return;
			break;

			case 0x14:
				// Softboot
				softboot();

			break;

			case 0x15 :
				reset_cpu();
			break;

			case 0x16:
				int return_log_vol_up = log_volume_up(RS232_BYTE3,RS232_BYTE4);
				fputc(0x06,RS232);
				fputc(60-return_log_vol_up,RS232);
				fputc(0x0A,RS232);
				return;
			break;

			case 0x17:
				int return_log_vol_down = log_volume_down(RS232_BYTE3,RS232_BYTE4);

				fputc(0x06,RS232);
				fputc(60-return_log_vol_down,RS232);
				fputc(0x0A,RS232);
				return;
			break;

			case 0x18:
			   	discrete_log_volume(RS232_BYTE3,RS232_BYTE4);
			break;

			case 0x19:
				// LOG VOLUME STATUS
				fputc(0x06,RS232);
				fputc(60-rs232_log_output_vol_index[RS232_BYTE3-1],RS232);
				fputc(0x0A,RS232);
				return;
			break;


		}
		
	} else {
		if(DEBUG) {
			fprintf(RS232,"ERR unknown. Buffer unread: %u, next_in = %u, next_out = %u, \r\n",buffer_unread,next_in,next_out);
			char temporary_byte = 0x00;

			for(int bleah = 0; bleah < buffer_unread; bleah++) {
				temporary_byte = bgetc();
				fprintf(RS232,"Byte %u: %x\r\n",bleah,temporary_byte);
			}
		}

		buffer_unread = 0;
		next_in = 0;
		next_out = 0;
		send_rs232_error(ERR_UNKNOWN);

		
	}
}
