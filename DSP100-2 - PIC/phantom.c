void update_phantom_power()
{
	read_flash_page_into_buffer(&PAGE_BUFFER_A,CURRENT_FLASH_PROGRAM,8);

	int32 phantom_mask = PAGE_BUFFER_A[54];

	if((phantom_mask & 0x03) > 0) {
		output_high(PIN_PHANTOM_ENABLE);
	} else {
		output_low(PIN_PHANTOM_ENABLE);
	}


	output_bit(PIN_PHANTOM_CH1,bit_test(phantom_mask,0));
	output_bit(PIN_PHANTOM_CH2,bit_test(phantom_mask,1));

}
