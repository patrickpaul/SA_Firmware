int get_serial_command()  { 
	char c,d,e; 
	int valid_command;
	int is_error;

	// Wait for start byte 
	while (c != COMMAND_START_BYTE) { 
		c = getc(); 
	}

	valid_command = 0;
	is_error = 0;
	
	while ((valid_command == 0) && (is_error == 0)) {
		c = getc();
		if(c == VOL_START_BYTE) { //v
			d = getc();
			if(d == VOL_UP_BYTE) { //u
				valid_command = COMMAND_VOL_UP;
			} else if(d == VOL_DOWN_BYTE) { //d
				valid_command = COMMAND_VOL_DOWN; // vol_down
			} else if(d == VOL_DOWN_BYTE_SMALL) {
				is_small_step = 1;
				valid_command = COMMAND_VOL_DOWN;
			} else if(d == VOL_UP_BYTE_SMALL) {
				is_small_step = 1;
				valid_command = COMMAND_VOL_UP;
			} else if(d == STATUS_BYTE) { //S
				valid_command = COMMAND_VOL_STATUS;
			} else {
				is_error = 1;
			}
		} else if(c == VOL_DISCRETE_START) { // V
			d = getc();

			//int new_volume = toint(d);
			int new_volume = d;
			if((new_volume < 0) || (new_volume > 100)) {
				is_error = 1;
			} else {
				valid_command = COMMAND_VOL_DISCRETE;
				command_data = new_volume;
			}
		} else if(c == MUTE_START_BYTE) { // m
			d = getc();

			if(d == MUTE_TOGGLE_BYTE) { // M
				valid_command = COMMAND_MUTE_TOGGLE; // Mute toggle
			}  else if (d == MUTE_FORCEMUTE_BYTE) {
				valid_command = COMMAND_FORCE_MUTE;
			} else if (d == MUTE_FORCEUNMUTE_BYTE) {
				valid_command = COMMAND_FORCE_UNMUTE;
			} else if(d == STATUS_BYTE) { //S
				valid_command = COMMAND_MUTE_STATUS; // mute status
			} else {
				is_error = 1;
			}
		} else if(c == DEBUG_START_BYTE) { // D
			d = getc();

			if(d == DEBUG_GET_VERSION)	{
				valid_command = COMMAND_GET_VERSION;
			} else {
				is_error = 1;
			}
		} else {
			is_error = 1;
		}
	}

	if(is_error == 1) {
		return 0;
	} else {
		e = getc();
		if(e == COMMAND_END_BYTE) {
			return valid_command;
		} else {
			return 0;
		}
	}
}
