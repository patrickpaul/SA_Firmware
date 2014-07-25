void update_phantom_power()
{
	read_flash_page_into_buffer(&PAGE_BUFFER_A,CURRENT_FLASH_PROGRAM,8);

	int32 phantom_mask = PAGE_BUFFER_A[54];

	output_bit(PIN_PHANTOM_CH1,bit_test(phantom_mask,0));
	output_bit(PIN_PHANTOM_CH2,bit_test(phantom_mask,1));
	output_bit(PIN_PHANTOM_CH3,bit_test(phantom_mask,2));
	output_bit(PIN_PHANTOM_CH4,bit_test(phantom_mask,3));

}