
void set_digital_pot (int data) {

   /* Software SPI implementation */

   BYTE i; 
   BYTE cmd[2];
   
   cmd[0] = data; // Integer representation of volume to set (0-254)
   cmd[1] = DPOT_COMMAND; // Specific command byte for target chip

   output_high(SPI_ENABLE); // Should already be high
   output_low(DPOT_SCLK); // Should already be low
   delay_ms(1); 
   
   output_low(SPI_ENABLE); // Bring low to enable
   delay_ms(1);
   
   for(i=1;i<=16;++i) { 
      output_bit(DPOT_MOSI, shift_left(cmd,2,0)); // Shifts out a single bit (16-bits total)

      output_high(DPOT_SCLK); 
      delay_us(2); 
      output_low(DPOT_SCLK); 
   }
   
   output_high(SPI_ENABLE); 
   output_low(DPOT_MOSI); 
   output_low(DPOT_SCLK); 
}

int volume_to_nearest_five() {
	
	int return_int = 0;
	if(current_volume % 5 == 0) {
		return current_volume;
	}

	if(current_volume == 0) {
		return_int = 0;
	} else if(current_volume > 0 && current_volume <= 5) {
		return_int = 5;
	} else if (current_volume > 5 && current_volume <= 10) {
		return_int = 10;
	} else if (current_volume > 10 && current_volume <= 15) {
		return_int = 15;
	} else if (current_volume > 15 && current_volume <= 20) {
		return_int = 20;
	} else if (current_volume > 20 && current_volume <= 25) {
		return_int = 25;
	} else if (current_volume > 25 && current_volume <= 30) {
		return_int = 30;
	} else if (current_volume > 30 && current_volume <= 35) {
		return_int = 35;
	} else if (current_volume > 35 && current_volume <= 40) {
		return_int = 40;
	} else if (current_volume > 40 && current_volume <= 45) {
		return_int = 45;
	} else if (current_volume > 45 && current_volume <= 50) {
		return_int = 50;
	} else if (current_volume > 50 && current_volume <= 55) {
		return_int = 55;
	} else if (current_volume > 55 && current_volume <= 60) {
		return_int = 60;
	} else if (current_volume > 60 && current_volume <= 65) {
		return_int = 65;
	} else if (current_volume > 65 && current_volume <= 70) {
		return_int = 70;
	} else if (current_volume > 70 && current_volume <= 75) {
		return_int = 75;
	} else if (current_volume > 75 && current_volume <= 80) {
		return_int = 80;
	} else if (current_volume > 80 && current_volume <= 85) {
		return_int = 85;
	} else if (current_volume > 85 && current_volume <= 90) {
		return_int = 90;
	} else if (current_volume > 90 && current_volume <= 95) {
		return_int = 95;
	} else if (current_volume > 95 && current_volume <= 100) {
		return_int = 100;
	}

	return return_int;

}

void saveAndSetVol() {

	unsigned int log_index = 0;
	int eeprom_volume = 0;
	int eeprom_mute = 0;

	log_index = current_volume / 5;
	// Calculated in Excel with (255 - (255 * POWER(VOL_PERCENT, 3.3))
	// Actual formula is (255 - (255 * VOL_PERCENT^3.3))
	// !!CHANGED 7/7/11 to have 10% be about 1.5V due to the diode dropout..
	// New formula is (255 - (26 + 229*VOL_PERCENT^3.3))
	//  --> ALSO WRITTEN AS (255 - (26 + 229 * POWER(VOL_PERCENT, 3.3))

	unsigned int shaped_pot_values[21] = {255,205,205,205,204,203,201,199,195,190,184,175,165,156,142,126,107,85,60,32,0};

	current_pot_setting = shaped_pot_values[log_index];

	if(DEBUG) {
		//printf("Setting volume to [POT]%u : [CV]%u\n\r",current_pot_setting,current_volume);
	}

	if(startup_flag == 1) {
	// IF THIS IS STARTING UP.. VOLUME WILL FADE IN. HIGH VOLUME WILL TAKE ABOUT HALF A SECOND
	unsigned int x = 255;

		while(x > current_pot_setting) {
			
			x -= 5;
			if(x < current_pot_setting) {
				x = current_pot_setting;
			}

			set_digital_pot(x); // Finally set the digital pot
			delay_ms(10);

			
		}

		startup_flag = 0;
	} else {

		set_digital_pot(current_pot_setting); // Finally set the digital pot
		//set_digital_pot(current_volume); 	
		if(is_muted == 1) {
			eeprom_volume = muted_volume;
		} else {
			eeprom_volume = current_volume;
		}

		write_eeprom(10,eeprom_volume); // Save volume in EEPROM for power cycle
		eeprom_mute = is_muted;
		write_eeprom(12,eeprom_mute); // Save volume in EEPROM for power cycle

	}


	putc(COMMAND_START_BYTE);
	putc(VOL_START_BYTE);
	putc(current_volume);
	putc(COMMAND_END_BYTE);
	
}

void vol_discrete() {
	
	// ADD A CHECK HERE BUT IT IS CURRENTLY DONE IN RS232.c
	current_volume = command_data;
	current_volume = volume_to_nearest_five();
	saveAndSetVol();

}

void vol_up() {
	
	if(is_muted == 1) {
		is_muted = 0;
		current_volume = muted_volume;
	}
	if(is_small_step == 1) {
		if((current_volume + VOL_SMALL_STEP) >= VOL_MAX) {
			current_volume = VOL_MAX;
		} else {
			current_volume += VOL_SMALL_STEP;
		}

		is_small_step = 0;
	} else {
		if((current_volume + VOL_BIG_STEP) >= VOL_MAX) {
			current_volume = VOL_MAX;
		} else {
			current_volume += VOL_BIG_STEP;
		}
	}
   
	saveAndSetVol();
}

void vol_down() {
	
	if(is_muted == 1) {
		is_muted = 0;
		current_volume = muted_volume;
	}

	if(is_small_step == 1) {
		if(current_volume < VOL_SMALL_STEP) {
			current_volume = VOL_MIN;
		} else {
			current_volume -= VOL_SMALL_STEP;
		}

		is_small_step = 0;
	} else {
		if(current_volume < VOL_BIG_STEP) {
			current_volume = VOL_MIN;
		} else {
			current_volume -= VOL_BIG_STEP;
		}
	}
   
	saveAndSetVol();
}

void mute_forcemute() {
	if(is_muted) {
		//if(DEBUG) { printf("ALREADY MUTED\n\r"); }
		return;
	}
	//if(DEBUG) { printf("Mute ON\n\r"); }
	is_muted = 1;
   	muted_volume = current_volume;
	current_volume = VOL_MUTE;
	saveAndSetVol();
}

void mute_forceunmute() {
	if(!is_muted) {
		//if(DEBUG) { printf("ALREADY UNMUTED\n\r"); }
		return;
	}
	//if(DEBUG) { printf("Mute OFF\n\r"); }
	is_muted = 0;
   	current_volume = muted_volume;
	saveAndSetVol();
}

void mute_toggle() {

	if(is_muted) {
		//if(DEBUG) { printf("MUTE OFF\n\r"); }
		is_muted = 0;
   		current_volume = muted_volume;
 	} else {
		//if(DEBUG) { printf("MUTE ON\n\r"); }
		is_muted = 1;
   		muted_volume = current_volume;
		current_volume = VOL_MUTE;
	}
	  	
	saveAndSetVol();

   	
}