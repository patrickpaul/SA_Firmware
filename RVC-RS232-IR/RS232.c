int timeout_error;

char timed_getc() {

	long timeout;

	timeout_error = FALSE;
	timeout = 0;

	while(!kbhit()&&(++timeout<50000)) { // half a second
		delay_us(10); // this polls at 10x the 9600 baud rate
	}

	if(kbhit()) {
		timeout_error = FALSE;
		return(getc());
	} else {
		timeout_error = TRUE;
		return(0);
	}
}

int get_serial_command()  { 
	int valid_command;
	int is_error;
	char command_char;
	char data_char1;
	char end_char;
	
	char start_char = timed_getc();

	if(TIMEOUT_ERROR == true) {
		return 0x50; // return ERR_START_TIMEOUT;
	}

	if(start_char != COMMAND_START_BYTE) { 
		return 0; // return ERR_START_INVALID; 
	}

	
	valid_command = 0;
	is_error = 0;
	
	command_char = timed_getc();

	if(TIMEOUT_ERROR == true) {
		return 0; // return ERR_COMMAND_TIMEOUT;
	}

	switch(command_char) {

		case VOL_START_BYTE :

			data_char1 = timed_getc();

			if(TIMEOUT_ERROR == true) {
				return 0; // return ERR_DATA_TIMEOUT;
			}
	
			if(data_char1 == VOL_UP_BYTE) { //u
				valid_command = COMMAND_VOL_UP;
			} else if(data_char1 == VOL_DOWN_BYTE) { //d
				valid_command = COMMAND_VOL_DOWN; // vol_down
			} else if(data_char1 == VOL_DOWN_BYTE_SMALL) {
				is_small_step = 1;
				valid_command = COMMAND_VOL_DOWN;
			} else if(data_char1 == VOL_UP_BYTE_SMALL) {
				is_small_step = 1;
				valid_command = COMMAND_VOL_UP;
			} else if(data_char1 == STATUS_BYTE) { //S
				valid_command = COMMAND_VOL_STATUS;
			} else {
				return 0; // return ERR_DATA_INVALID;
			}
				
		break;

		case VOL_DISCRETE_START :
	
			data_char1 = timed_getc();

			if(TIMEOUT_ERROR == true) {
				return 0; // return ERR_DATA_TIMEOUT;
			}

			int new_volume = data_char1;
			if((new_volume < 0) || (new_volume > 100)) {
				return 0; // return ERR_DATA_INVALID;
			} else {
				valid_command = COMMAND_VOL_DISCRETE;
				command_data = new_volume;
			}

		break;

		case MUTE_START_BYTE:

			data_char1 = timed_getc();

			if(TIMEOUT_ERROR == true) {
				return 0; // return ERR_DATA_TIMEOUT;
			}

			if(data_char1 == MUTE_TOGGLE_BYTE) { // M
				valid_command = COMMAND_MUTE_TOGGLE; // Mute toggle
			}  else if (data_char1 == MUTE_FORCEMUTE_BYTE) {
				valid_command = COMMAND_FORCE_MUTE;
			} else if (data_char1 == MUTE_FORCEUNMUTE_BYTE) {
				valid_command = COMMAND_FORCE_UNMUTE;
			} else if(data_char1 == STATUS_BYTE) { //S
				valid_command = COMMAND_MUTE_STATUS; // mute status
			} else {
				return 0; // return ERR_DATA_INVALID;
			}

		break;

		case DEBUG_START_BYTE :

			data_char1 = timed_getc();

			if(TIMEOUT_ERROR == true) {
				return 0; // return ERR_DATA_TIMEOUT;
			}

			if(data_char1 == DEBUG_GET_VERSION)	{
				valid_command = COMMAND_GET_VERSION;
			} else {
				return 0; // return ERR_DATA_INVALID;
			}

		break;

		default:
			return 0; // return ERR_COMMAND_INVALID;
		break;
	}


	end_char = timed_getc();

	if(TIMEOUT_ERROR == true) {
		return 0; // return ERR_END_TIMEOUT;
	}

	if(end_char == COMMAND_END_BYTE) {
		return valid_command;
	} else {
		return 0; // return ERR_END_INVALID;
	}
}
