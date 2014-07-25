// presets.c

void softboot();

void save_flash_program()
{
	//FLASH_PROGRAM_WRITE(CURRENT_PRESET);
}

void switch_flash_program(int new_index)
{
	CURRENT_FLASH_PROGRAM = new_index;

	softboot();

	write_eeprom(IEEPROM_PRESET_LOC,CURRENT_FLASH_PROGRAM);

	delay_ms(5);
}
