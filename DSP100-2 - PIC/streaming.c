// streaming.c

#define NIBBLE_SIZE 32

/* VARIABLES FOR STREAMING */
byte STREAMING_BUFFER[256];

byte STREAM_NIBBLE_BUFFER[32];

int16 streaming_buffer_index = 0;
int16 bytes_in_stream = 0;

int16 num_bytes_added = 0;

int stream_target_program = 0;
int stream_target_page = 0;

short is_streaming = 0;

int16 total_bytes_so_far = 0;

unsigned int nibble_crc = 0;

unsigned int verified_bytes = 0;
int nibble_index = 0; // 0-31 (local in STREAM_NIBBLE_BUFFER)


void flush_nibble_buffer() {

	streaming_buffer_index = 0;
	for(int j = 0; j < 32; j++) {
		STREAM_NIBBLE_BUFFER[j] = 0xFF;
	}

}


void flush_stream_buffer() {

	streaming_buffer_index = 0;

	for(int16 i = 0; i < 256; i++) {
		STREAMING_BUFFER[i] = 0xFF;
	}

	for(int j = 0; j < 32; j++) {
		STREAM_NIBBLE_BUFFER[j] = 0xFF;
	}

}




int calc_crc_int(int *Buffer, int16 Len) 
{ 
   int16 x; 
   int16 crc = 0xFFFF; 
   int return_int = 0;

   while(Len--) 
   { 
      x = make8(crc,1) ^ *Buffer++; 
      x ^= x>>4; 
      
      crc = (crc << 8) ^ (x << 12) ^ (x <<5) ^ x; 
   } 

	return_int = crc & 0xFF;

   	return return_int; 
} 





void clear_nibble()
{
	for(int n = 0; n < NIBBLE_SIZE; n++) {
		STREAM_NIBBLE_BUFFER[n] = 0xFF;
	}

	nibble_index = 0;
}

void add_nibble_to_buffer()
{
	for(int m = 0; m < NIBBLE_SIZE; m++) {
		STREAMING_BUFFER[verified_bytes++] = STREAM_NIBBLE_BUFFER[m];
	}

	nibble_index = 0;
}

void kill_stream()
{
	is_streaming = false;
	clear_nibble();
	flush_stream_buffer();
	streaming_buffer_index = 0;
	streaming_buffer_index = 0;
	nibble_index = 0;
	verified_bytes = 0;
	total_bytes_so_far = 0;

}

void print_stream_to_rs232()
{
	for(int i = 0; i < 32; i++) {
		fprintf(RS232,"%u ",STREAM_NIBBLE_BUFFER[i]);
	}

	char nibble_crc = calc_crc_int(STREAM_NIBBLE_BUFFER,sizeof(STREAM_NIBBLE_BUFFER));

	fprintf(RS232,"CRC = %u\r\n",nibble_crc);

	

}

void perform_stream(int target_program, int target_page, int16 num_bytes)
{
	

	char streamed_char;

	stream_target_program = target_program;
	stream_target_page = target_page;
	bytes_in_stream = num_bytes;

	streaming_buffer_index = 0;
	streaming_buffer_index = 0;
	nibble_index = 0;
	verified_bytes = 0;
	total_bytes_so_far = 0;

	num_bytes_added = 0;
	total_bytes_so_far = 0;


	is_streaming = true;
	flush_stream_buffer();

	fputc(0x06,USB);
	fputc(target_program,USB);
	fputc(target_page,USB);
	fputc(0x03,USB);

	int nibble_byte_counter = 0;

	for(int nibble_counter = 0; nibble_counter <8; nibble_counter++)
	{
		nibble_index = 0;

		for(nibble_byte_counter = 0; nibble_byte_counter < 32; nibble_byte_counter++) {

			streamed_char = timed_getc();
	
			total_bytes_so_far++;

			STREAM_NIBBLE_BUFFER[nibble_byte_counter] = streamed_char;	
		}
	
		if(TIMEOUT_ERROR == true) {

			if(DEBUG) {
				fprintf(RS232,"Timed out after having read %lu bytes\r\n",total_bytes_so_far);
				fprintf(RS232,"So far we have received: ");
				print_stream_to_rs232();
			}
			//send_error(ERR_COMMAND_TIMEOUT);
			kill_stream();
			return;
		} else {
			
			nibble_crc = calc_crc_int(STREAM_NIBBLE_BUFFER,sizeof(STREAM_NIBBLE_BUFFER));
			//fprintf(RS232,"GOT FULL NIBBLE. So far %lu. Sending %u CRC\r\n",total_bytes_so_far,nibble_crc);
			fputc(nibble_crc,USB);

			for(int x = 0; x < 32; x++) {
				STREAMING_BUFFER[num_bytes_added++] = STREAM_NIBBLE_BUFFER[x];
			}

			flush_nibble_buffer();
		}
	}

	write_buffer_to_flash_page(&STREAMING_BUFFER,target_program, target_page);

	fputc(0x06,USB);
	fputc(0x01,USB);
	fputc(target_program,USB);
	fputc(target_page,USB);
	fputc(0x03,USB);

}
