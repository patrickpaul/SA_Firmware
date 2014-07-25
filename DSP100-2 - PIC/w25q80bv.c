#define W25Q80BV_PAGE_LEN     		256  // in bytes
#define W25Q80BV_PAGES_PER_SECTOR	16

#define W25Q80BV_SECTOR_LEN			W25Q80BV_PAGE_LEN*W25Q80BV_PAGES_PER_SECTOR
#define W25Q80BV_SECTORS_PER_BLOCK	16

#define W25Q80BV_BLOCK_LEN			W25Q80BV_SECTOR_LEN*W25Q80BV_SECTORS_PER_BLOCK
  	
#define W25Q80BV_NUM_BLOCKS			16
#define W25Q80BV_NUM_SECTORS		W25Q80BV_NUM_BLOCKS*W25Q80BV_SECTORS_PER_BLOCK
#define W25Q80BV_NUM_PAGES    		W25Q80BV_NUM_SECTORS*W25Q80BV_PAGES_PER_SECTOR
#define W25Q80BV_NUM_BYTES    		W25Q80BV_NUM_BLOCKS*W25Q80BV_BLOCK_LEN

#define W25Q80BV_WRITE_ENABLE 0x06
#define W25Q80BV_CHIP_ERASE   0xC7
#define W25Q80BV_SECTOR_ERASE 0x20
#define W25Q80BV_READ_STATUS1 0x05
#define W25Q80BV_PAGE_PROGRAM 0x02
#define W25Q80BV_DEVICE_ID    0xAB
#define W25Q80BV_UNIQUE_ID    0x4B

#define W25Q80BV_STATUS_BUSY  0x01

#define W25Q80BV_READ 0x03

#define W25Q80BV_DEVICE_ID_RES  0x13 /* Expected device_id for W25Q80BV */

unsigned int32 page_address(unsigned int32 block_index, unsigned int32 sector_index, unsigned int32 page_index)
{
	unsigned int32 return_address = (page_index*W25Q80BV_PAGE_LEN) + (sector_index*W25Q80BV_SECTOR_LEN) + (block_index*W25Q80BV_BLOCK_LEN);	
	return return_address;
}

unsigned int32 sector_address(unsigned int32 block_index, unsigned int32 sector_index)
{
	unsigned int32 return_address = (sector_index*W25Q80BV_SECTOR_LEN) + (block_index*W25Q80BV_BLOCK_LEN);	
	return return_address;
}

unsigned int32 sector_address(unsigned int32 block_index)
{
	unsigned int32 return_address = (block_index*W25Q80BV_BLOCK_LEN);	
	return return_address;
}


int flash_get_device_id()
{
	int data = 0;

    output_low(FLASH_CS);
	spi_xfer(W25Q80BV_DEVICE_ID);
	
	data = spi_xfer(0x00);
	data = spi_xfer(0x00);
	data = spi_xfer(0x00);

	data = spi_xfer(0xFF);

	output_high(FLASH_CS);

	return data;
}

short verify_device_id()
{
	if(flash_get_device_id() == W25Q80BV_DEVICE_ID_RES) {
		return 1;
	} else {
		return 0;
	}
}

int flash_get_status()
{
	int value = 0;
	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_READ_STATUS1);
    value = spi_xfer(0x00);
    output_high(FLASH_CS);
	
	return value;
}

void flash_wait_while_busy()
{
	while ((flash_get_status() & W25Q80BV_STATUS_BUSY))
	{
	}
}

void flash_write_enable()
{
	flash_wait_while_busy();
	output_low(FLASH_CS);
	spi_xfer(0x06);
    output_high(FLASH_CS);
}

void flash_chip_erase()
{
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] Starting chip erase...\r\n");
		}
        int device_id = 0;

        device_id = 0;
        while(device_id != W25Q80BV_DEVICE_ID_RES)
        {
                device_id = flash_get_device_id();
        }

        flash_write_enable();
        flash_wait_while_busy();
		output_low(PIN_C0);
        output_low(FLASH_CS);
        spi_xfer(W25Q80BV_CHIP_ERASE);
        output_high(FLASH_CS);
		
		while (flash_get_status() & W25Q80BV_STATUS_BUSY)
		{
		}
		output_high(PIN_C0);
		if(DEBUG) {
			fprintf(RS232,"Done!\r\n");
		}
}

void flash_sector_erase(unsigned int32 block_index, unsigned int32 sector_index)
{
        int device_id = 0;

		unsigned int32 starting_address = page_address(block_index,sector_index,0);

        device_id = 0;
        while(device_id != W25Q80BV_DEVICE_ID_RES)
        {
                device_id = flash_get_device_id();
        }

        flash_write_enable();
        flash_wait_while_busy();
        output_low(FLASH_CS);
        spi_xfer(W25Q80BV_SECTOR_ERASE);
		spi_xfer((starting_address & 0xFF0000) >> 16);
		spi_xfer((starting_address & 0xFF00) >> 8);
		spi_xfer(starting_address & 0xFF);
        output_high(FLASH_CS);

		while (flash_get_status() & W25Q80BV_STATUS_BUSY)
		{
		}

}

int flash_write_full_page(int *ptr,unsigned int32 block_index, unsigned int32 sector_index, unsigned int32 page_index)
{
	unsigned int32 starting_address = page_address(block_index,sector_index,page_index);

	flash_write_enable();
	flash_wait_while_busy();

	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_PAGE_PROGRAM);
	spi_xfer((starting_address & 0xFF0000) >> 16);
	spi_xfer((starting_address & 0xFF00) >> 8);
	spi_xfer(starting_address & 0xFF);

	unsigned int rolling_checksum = 0;

	for (int16 i = 0; i < 256; i++)
	{
		spi_xfer(ptr[i]);
		rolling_checksum += ptr[i];
	}
	
	output_high(FLASH_CS);
	flash_wait_while_busy();

	return rolling_checksum;
}





void flash_read_full_page(int *ptr,unsigned int32 block_index, unsigned int32 sector_index, unsigned int32 page_index)
{
	unsigned int32 starting_address = page_address(block_index,sector_index,page_index);

	flash_write_enable();
	flash_wait_while_busy();

	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_READ);
	spi_xfer((starting_address & 0xFF0000) >> 16);
	spi_xfer((starting_address & 0xFF00) >> 8);
	spi_xfer(starting_address & 0xFF);

	for (int16 i = 0; i < 256; i++)
	{
		ptr[i] = spi_xfer(0x00);
	}

	output_high(FLASH_CS);
	flash_wait_while_busy();
}

void flash_read_bytes(int *ptr, int16 number_of_bytes, unsigned int32 block_index, unsigned int32 sector_index, unsigned int32 page_index)
{
	unsigned int32 starting_address = page_address(block_index,sector_index,page_index);

	flash_write_enable();
	flash_wait_while_busy();

	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_READ);
	spi_xfer((starting_address & 0xFF0000) >> 16);
	spi_xfer((starting_address & 0xFF00) >> 8);
	spi_xfer(starting_address & 0xFF);

	for (int16 i = 0; i < number_of_bytes; i++)
	{
		ptr[i] = spi_xfer(0x00);
	}

	output_high(FLASH_CS);
	flash_wait_while_busy();
}

void flash_write_bytes(int *ptr, int16 number_of_bytes, unsigned int32 block_index, unsigned int32 sector_index, unsigned int32 page_index)
{
	int32 starting_address = 0;
	int16 value_counter = 0;
	
	flash_sector_erase(block_index,sector_index);

	starting_address = page_address(block_index,sector_index,page_index);

	flash_write_enable();
	flash_wait_while_busy();
	
	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_PAGE_PROGRAM);
	spi_xfer((starting_address & 0xFF0000) >> 16);
	spi_xfer((starting_address & 0xFF00) >> 8);
	spi_xfer(starting_address & 0xFF);
		
	for (value_counter = 0; value_counter < number_of_bytes; value_counter++)
	{
		spi_xfer(ptr[value_counter]);
	}

	output_high(FLASH_CS);

	flash_wait_while_busy();
}

/* DEBUG STUFF */

void flash_print_page(unsigned int32 block_index, unsigned int32 sector_index, unsigned int32 page_index)
{
	int32 starting_address = page_address(block_index,sector_index,page_index);
	unsigned int data = 0;
	flash_wait_while_busy();

	//starting_address = 0;
	fprintf(RS232,"\r\nPrinting flash at starting address (%u,%u,%u) %lu\r\n",block_index,sector_index,page_index,starting_address);

	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_READ);
	spi_xfer((starting_address & 0xFF0000) >> 16);
	spi_xfer((starting_address & 0xFF00) >> 8);
	spi_xfer(starting_address & 0xFF);

	for (int16 i = 0; i < 256; i++)
	{
		data = spi_xfer(0x00);
		printf("%x",data);

		if((i % 4) == 3) {
			printf(" ");
		}

		if((i % 32) == 31) {
			printf("\r\n");
		}
	}
	output_high(FLASH_CS);
}


int flash_page_checksum(unsigned int32 block_index, unsigned int32 sector_index, unsigned int32 page_index)
{
	unsigned int32 starting_address = page_address(block_index,sector_index,page_index);
	unsigned int data = 0;
	flash_wait_while_busy();

	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_READ);
	spi_xfer((starting_address & 0xFF0000) >> 16);
	spi_xfer((starting_address & 0xFF00) >> 8);
	spi_xfer(starting_address & 0xFF);

	unsigned int rolling_checksum = 0;

	for (int16 i = 0; i < 256; i++)
	{
		data = spi_xfer(0x00);
		rolling_checksum += data;
	}
	output_high(FLASH_CS);

	return rolling_checksum;
}

/*
void FLASH_PROGRAM_WRITE(int program_index) { 
   

    // This function will write the current DSP_CONFIG in memory to the program at index program_index

	int *ptr = 0;

	ptr = &DSP_CONFIG;

	//fprintf(RS232,"Sizeof DSP_CONFIG is %lu\r\n",sizeof(DSP_CONFIG));
	//fprintf(RS232,"Sizeof DSP_CONFIG.TEST_VALUES is %lu\r\n",sizeof(DSP_CONFIG.TEST_VALUES));
	int16 value_counter = 0;

	int32 starting_address = 0;

	int16 test_val = 0;

	int16 value_in_sector_counter = 0;
	for(int sector_counter = 0; sector_counter < 8; sector_counter++) {
		
		flash_sector_erase(program_index,sector_counter);
		//fprintf(RS232,"Status1: %x\r\n",flash_get_status());
		//delay_ms(40);
		//fprintf(RS232,"Status2: %x\r\n",flash_get_status());
		//ptr = &DSP_CONFIG.TEST_VALUES[0];
		starting_address = page_address(program_index,sector_counter,0);
		flash_write_enable();
		flash_wait_while_busy();

			
		output_low(FLASH_CS);
		spi_xfer(W25Q80BV_PAGE_PROGRAM);
		spi_xfer((starting_address & 0xFF0000) >> 16);
		spi_xfer((starting_address & 0xFF00) >> 8);
		spi_xfer(starting_address & 0xFF);
		
		for (value_in_sector_counter = 0; value_in_sector_counter < 256; value_in_sector_counter++)
		{
			spi_xfer(ptr[value_counter]);
			test_val++;
			value_counter++;
		}
		
		output_high(FLASH_CS);

		flash_wait_while_busy();
	}
}
*/
/*
void FLASH_PROGRAM_READ(int program_index)
{
	int *ptr = 0;

	ptr = &DSP_CONFIG;

	int32 starting_address = 0;

	int16 value_counter = 0;

	int data = 0;

	for(int sector_counter = 0; sector_counter < 8; sector_counter++) {

		starting_address = page_address(program_index,sector_counter,0);

		output_low(FLASH_CS);
		spi_xfer(W25Q80BV_READ);
		spi_xfer((starting_address & 0xFF0000) >> 16);
		spi_xfer((starting_address & 0xFF00) >> 8);
		spi_xfer(starting_address & 0xFF);
	
		for (int16 i = 0; i < 256; i++)
		{
			data = spi_xfer(0x00);
			ptr[value_counter] = data;
			value_counter++;

			//fprintf(RS232,"%x||",data);
		}

		output_high(FLASH_CS);
	}
}
*/
void FLASH_ADDR_WRITE(int block_index) { 
   

   // This function will write the current DSP_CONFIG in memory to the program at index program_index

	int *ptr = 0;

	ptr = &DSP_ADDR;

	//fprintf(RS232,"Sizeof DSP_CONFIG is %lu\r\n",sizeof(DSP_CONFIG));
	//fprintf(RS232,"Sizeof DSP_CONFIG.TEST_VALUES is %lu\r\n",sizeof(DSP_CONFIG.TEST_VALUES));

	int16 value_counter = 0;

	int32 starting_address = 0;

	int16 test_val = 0;

	int16 value_in_sector_counter = 0;
	for(int sector_counter = 0; sector_counter < NUM_ADDRESS_PAGES; sector_counter++) {
		
		flash_sector_erase(block_index,sector_counter);
		starting_address = page_address(block_index,sector_counter,0);
		flash_write_enable();
		flash_wait_while_busy();

			
		output_low(FLASH_CS);
		spi_xfer(W25Q80BV_PAGE_PROGRAM);
		spi_xfer((starting_address & 0xFF0000) >> 16);
		spi_xfer((starting_address & 0xFF00) >> 8);
		spi_xfer(starting_address & 0xFF);
		
		for (value_in_sector_counter = 0; value_in_sector_counter < 256; value_in_sector_counter++)
		{
			//spi_xfer(value_counter);
			spi_xfer(ptr[value_counter]);
			test_val++;
			value_counter++;
		}
		
		output_high(FLASH_CS);

		flash_wait_while_busy();

		//fprintf(RS232,"Wrote %lu bytes\r\n",test_val);
		
	}
}


void FLASH_ADDR_READ()
{
	int *ptr = 0;

	ptr = &DSP_ADDR;

	int32 starting_address = 0;

	int16 value_counter = 0;

	int data = 0;

	for(int sector_counter = 0; sector_counter < NUM_ADDRESS_PAGES; sector_counter++) {

		starting_address = page_address(DEFAULT_ADDR_BLOCK,sector_counter,0);

		output_low(FLASH_CS);
		spi_xfer(W25Q80BV_READ);
		spi_xfer((starting_address & 0xFF0000) >> 16);
		spi_xfer((starting_address & 0xFF00) >> 8);
		spi_xfer(starting_address & 0xFF);
	
		for (int16 i = 0; i < 256; i++)
		{
			data = spi_xfer(0x00);
			ptr[value_counter] = data;
			value_counter++;
			
		}

		output_high(FLASH_CS);
	}
}

/*
void PRINT_READ_PROGRAM()
{

// This function will write the current DSP_CONFIG in memory to the program at index program_index

	int *ptr = 0;

	ptr = &DSP_CONFIG;

	//fprintf(RS232,"Sizeof DSP_CONFIG is %lu\r\n",sizeof(DSP_CONFIG));
	//fprintf(RS232,"Sizeof DSP_CONFIG.TEST_VALUES is %lu\r\n",sizeof(DSP_CONFIG.TEST_VALUES));
	int16 value_counter = 0;

	int16 value_in_sector_counter = 0;
	for(int sector_counter = 0; sector_counter < 8; sector_counter++) {
		
		for (value_in_sector_counter = 0; value_in_sector_counter < 256; value_in_sector_counter++)
		{
			printf("%x",ptr[value_counter]);

			if((value_in_sector_counter % 4) == 3) {
				printf(" ");
			}
	
			if((value_in_sector_counter % 32) == 31) {
				printf("\r\n");
			}

			value_counter++;
	
		}
	}	
}
*/
void PRINT_READ_ADDR()
{

// This function will write the current DSP_CONFIG in memory to the program at index program_index

	int *ptr = 0;

	ptr = &DSP_ADDR;

	//fprintf(RS232,"Sizeof DSP_CONFIG is %lu\r\n",sizeof(DSP_CONFIG));
	//fprintf(RS232,"Sizeof DSP_CONFIG.TEST_VALUES is %lu\r\n",sizeof(DSP_CONFIG.TEST_VALUES));
	int16 value_counter = 0;

	int16 value_in_sector_counter = 0;
	for(int sector_counter = 0; sector_counter < NUM_ADDRESS_PAGES; sector_counter++) {
		
		for (value_in_sector_counter = 0; value_in_sector_counter < 256; value_in_sector_counter++)
		{
			printf("%x",ptr[value_counter]);

			if((value_in_sector_counter % 4) == 3) {
				printf(" ");
			}
	
			if((value_in_sector_counter % 32) == 31) {
				printf("\r\n");
			}

			value_counter++;
	
		}
	}	
}


void FLASH_COPY_PROGRAM(int from_index, int to_index)
{

	fprintf(RS232,"\r\nCopying program from %u to %u ... ",from_index,to_index);
	//fprintf(RS232,"Sizeof DSP_CONFIG.TEST_VALUES is %lu\r\n",sizeof(DSP_CONFIG.TEST_VALUES));
	int32 read_starting_address = 0;
	int32 write_starting_address = 0;
	
	int read_data = 0;

	for(int sector_counter = 0; sector_counter < NUM_PRESET_PAGES; sector_counter++) {

		flash_sector_erase(to_index,sector_counter);

		write_starting_address = page_address(to_index,sector_counter,0);
		read_starting_address = page_address(from_index,sector_counter,0);

		

		for (int16 i = 0; i < 256; i++)
		{
			output_low(FLASH_CS);
			spi_xfer(W25Q80BV_READ);
			spi_xfer((read_starting_address & 0xFF0000) >> 16);
			spi_xfer((read_starting_address & 0xFF00) >> 8);
			spi_xfer(read_starting_address & 0xFF);
		
			read_data = spi_xfer(0x00);

			output_high(FLASH_CS);

			flash_wait_while_busy();

			flash_write_enable();
			flash_wait_while_busy();

			output_low(FLASH_CS);
			spi_xfer(W25Q80BV_PAGE_PROGRAM);
			spi_xfer((write_starting_address & 0xFF0000) >> 16);
			spi_xfer((write_starting_address & 0xFF00) >> 8);
			spi_xfer(write_starting_address & 0xFF);

			spi_xfer(read_data);

			output_high(FLASH_CS);

			flash_wait_while_busy();

			read_starting_address++;
			write_starting_address++;

			//fprintf(RS232,"%x||",read_data);
		}
	}

	fprintf(RS232,"DONE!\r\n");
}

void FLASH_COMPARE_PROGRAM(int a_index, int b_index)
{

	fprintf(RS232,"\r\Comparing programs %u and %u ... ",a_index,b_index);

	int32 compare_a_starting_address = 0;
	int32 compare_b_starting_address = 0;
	
	int read_data_a = 0;
	int read_data_b = 0;

	int errors_found = 0;

	for(int sector_counter = 0; sector_counter < NUM_PRESET_PAGES; sector_counter++) {


		compare_a_starting_address = page_address(a_index,sector_counter,0);
		compare_b_starting_address = page_address(b_index,sector_counter,0);

		

		for (int16 i = 0; i < 256; i++)
		{
			output_low(FLASH_CS);
			spi_xfer(W25Q80BV_READ);
			spi_xfer((compare_a_starting_address & 0xFF0000) >> 16);
			spi_xfer((compare_a_starting_address & 0xFF00) >> 8);
			spi_xfer(compare_a_starting_address & 0xFF);
		
			read_data_a = spi_xfer(0x00);

			output_high(FLASH_CS);

			flash_wait_while_busy();


			output_low(FLASH_CS);
			spi_xfer(W25Q80BV_READ);
			spi_xfer((compare_b_starting_address & 0xFF0000) >> 16);
			spi_xfer((compare_b_starting_address & 0xFF00) >> 8);
			spi_xfer(compare_b_starting_address & 0xFF);
		
			read_data_b = spi_xfer(0x00);

			output_high(FLASH_CS);

			flash_wait_while_busy();

			compare_a_starting_address++;
			compare_b_starting_address++;

			if(read_data_a != read_data_b) {
				fprintf(RS232,"[ERROR] found in sector %u at address %lu. A = %x, B = %x\r\n",sector_counter,i,read_data_a,read_data_b);
				errors_found++;
			} else {
				//fprintf(RS232,"%x == %x ",read_data_a,read_data_b);
				
			}
		}

		//fprintf(RS232,"Completed sector %u, %u errors found.\r\n",sector_counter,errors_in_sector);
	}

	fprintf(RS232,"%u errors found\r\n",errors_found);
}

int addr_index_to_page_index(int16 addr_index) {
	return (int)(addr_index / PAGE_SIZE);
}

int addr_index_to_buffer_index(int16 addr_index) {
	return (int)(addr_index % PAGE_SIZE);
}

void read_flash_page_into_buffer(int *ptr,int program_index, int page_index) 
{
	int32 starting_address = 0;
	int data = 0;

	starting_address = page_address(program_index,page_index,0);

	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_READ);
	spi_xfer((starting_address & 0xFF0000) >> 16);
	spi_xfer((starting_address & 0xFF00) >> 8);
	spi_xfer(starting_address & 0xFF);
	
	for (int16 i = 0; i < 256; i++)
	{
		data = spi_xfer(0x00);
		ptr[i] = data;
	}

	output_high(FLASH_CS);
}


void write_buffer_to_flash_page(int *ptr,int program_index, int page_index) 
{
	int32 starting_address = 0;
	int16 value_counter = 0;
	
	flash_sector_erase(program_index,page_index);

	starting_address = page_address(program_index,page_index,0);

	flash_write_enable();
	flash_wait_while_busy();
	
	output_low(FLASH_CS);
	spi_xfer(W25Q80BV_PAGE_PROGRAM);
	spi_xfer((starting_address & 0xFF0000) >> 16);
	spi_xfer((starting_address & 0xFF00) >> 8);
	spi_xfer(starting_address & 0xFF);
		
	for (value_counter = 0; value_counter < 256; value_counter++)
	{
		spi_xfer(ptr[value_counter]);
	}

	output_high(FLASH_CS);

	flash_wait_while_busy();
}

void write_buffer_to_stream(int *ptr, int is_usb_stream = 1) 
{
	for (int16 value_counter = 0; value_counter < 256; value_counter++)
	{
		if(is_usb_stream == 1) {
			fputc(ptr[value_counter],USB);
		} else {
			fputc(ptr[value_counter],RS232);
		}
	}	
}

void print_buffer_to_stream(int *ptr, int is_usb_stream = 1) 
{
	for (int16 value_counter = 0; value_counter < 256; value_counter++)
	{
		if(is_usb_stream == 1) {
			fprintf(USB,"%x",ptr[value_counter]);
		} else {
			fprintf(RS232,"%x",ptr[value_counter]);

			if((value_counter % 4) == 3) {
				fprintf(RS232," ");	
			}

			if((value_counter % 32) == 31) {
				fprintf(RS232,"\r\n");	
			}
		}
	}	
}


void print_flash_page_buffer(int *ptr)
{
	int16 value_counter = 0;

	int16 value_in_sector_counter = 0;

		for (value_in_sector_counter = 0; value_in_sector_counter < 256; value_in_sector_counter++)
		{
			printf("%x",ptr[value_counter]);

			if((value_in_sector_counter % 4) == 3) {
				printf(" ");
			}
	
			if((value_in_sector_counter % 32) == 31) {
				printf("\r\n");
			}

			value_counter++;
	
		}
}