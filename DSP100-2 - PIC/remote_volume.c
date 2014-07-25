int32 get_AM_trim_channel(int ch)
{
	switch(ch) {
		case 0 :
			return AM_ANALOG1_TRIM;
		break;

		case 1 :
			return AM_ANALOG2_TRIM;
		break;

		case 2 : 
			return AM_ANALOG3_TRIM;
		break;
		
		case 3 :
			return AM_ANALOG4_TRIM;
		break;

		default :
			return 0;
		break;
	}
}

double discrete_vol_output(int ch,int new_vol)
{
	

	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 0;
			rs232_output_vol[i] = ((double)new_vol/100.0);
		
			
			send_dsp_command(get_AM_trim_channel(i),(int32)(rs232_output_vol[i]*2147483648.0));
		}

		return rs232_output_vol[0]; // They will all be the same. So just return the volume of CH1
	} else {

		rs232_output_mute[ch-1] = 0;
		rs232_output_vol[ch-1] = ((double)new_vol/100.0);
	
		if(DEBUG) {
			fprintf(RS232,"Discrete volume for %u to %g\r\n",ch-1,rs232_output_vol[ch-1]);
		}

		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(rs232_output_vol[ch-1]*2147483648.0));

		return rs232_output_vol[ch-1]; // They will all be the same. So just return the volume of CH1
	}
	
}

int log_volume_up(int ch, int amount)
{

	double new_log_value = 0;

	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 0;
			rs232_log_output_vol_index[i] += amount;

			if(rs232_log_output_vol_index[i] > 60) {
				rs232_log_output_vol_index[i] = 60;
			}
			
			new_log_value = log_values[rs232_log_output_vol_index[i]];

			send_dsp_command(get_AM_trim_channel(i),(int32)(new_log_value*2147483648.0));

		}

		return rs232_log_output_vol_index[0]; // They will all be the same. So just return the volume of CH1

	} else {

		rs232_output_mute[ch-1] = 0;
		
		rs232_log_output_vol_index[ch-1] += amount;

		if(rs232_log_output_vol_index[ch-1] > 60) {
			rs232_log_output_vol_index[ch-1] = 60;
		}

	
		if(DEBUG) {
			//fprintf(RS232,"Setting log volume for %u to %u which is %.4f\r\n",ch-1,rs232_log_output_vol_index[ch-1],log_values[rs232_log_output_vol_index[ch-1]]);
		}

		new_log_value = log_values[rs232_log_output_vol_index[ch-1]];

		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(new_log_value*2147483648.0));

		return rs232_log_output_vol_index[ch-1]; // They will all be the same. So just return the volume of CH1
	}

}

int log_volume_down(int ch, int amount)
{

	double new_log_value = 0;

	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 0;

			if(rs232_log_output_vol_index[i] >= amount) {
				rs232_log_output_vol_index[i] -= amount;
			} else {
				rs232_log_output_vol_index[i] = 0;
			}
			
			 new_log_value = log_values[rs232_log_output_vol_index[i]];

			send_dsp_command(get_AM_trim_channel(i),(int32)(new_log_value*2147483648.0));
		}

		return rs232_log_output_vol_index[0]; // They will all be the same. So just return the volume of CH1

	} else {

		rs232_output_mute[ch-1] = 0;
		
		if(rs232_log_output_vol_index[ch-1] >= amount) {
			rs232_log_output_vol_index[ch-1] -= amount;
		} else {
			rs232_log_output_vol_index[ch-1] = 0;
		}

	
		if(DEBUG) {
			//fprintf(RS232,"Setting log volume for %u to %u which is %.4f\r\n",ch-1,rs232_log_output_vol_index[ch-1],log_values[rs232_log_output_vol_index[ch-1]]);
		}


		new_log_value = log_values[rs232_log_output_vol_index[ch-1]];

		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(new_log_value*2147483648.0));

		return rs232_log_output_vol_index[ch-1]; // They will all be the same. So just return the volume of CH1
	}

}


double discrete_log_volume(int ch,unsigned int new_vol)
{
	
	// Data has already been checked.
	double new_log_value = 0;

	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {

			rs232_output_mute[i] = 0;
			rs232_log_output_vol_index[i] = (60 - new_vol);

			new_log_value = log_values[rs232_log_output_vol_index[i]];

			send_dsp_command(get_AM_trim_channel(i),(int32)(new_log_value*2147483648.0));
		}

		return rs232_output_vol[0]; // They will all be the same. So just return the volume of CH1
	} else {

			rs232_output_mute[ch-1] = 0;
			rs232_log_output_vol_index[ch-1] = (60 - new_vol);

			new_log_value = log_values[rs232_log_output_vol_index[ch-1]];

			send_dsp_command(get_AM_trim_channel(ch-1),(int32)(new_log_value*2147483648.0));
	
		if(DEBUG) {
			fprintf(RS232,"Discrete log volume for %u to %u which is %.4f\r\n",ch-1,rs232_log_output_vol_index[ch-1],log_values[rs232_log_output_vol_index[ch-1]]);
		}

		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(new_log_value*2147483648.0));

		return rs232_output_vol[ch-1]; // They will all be the same. So just return the volume of CH1
	}
	
}



double vol_big_up_output(int ch)
{
	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 0;
			rs232_output_vol[i] += 0.1;
			if(rs232_output_vol[i] > 1) {
				rs232_output_vol[i] = 1;
			}
				
			send_dsp_command(get_AM_trim_channel(i),(int32)(rs232_output_vol[i]*2147483648.0));
		}

		return rs232_output_vol[0]; // Temporarily just return the first channel volume

	} else {
		rs232_output_mute[(ch-1)] = 0;
		rs232_output_vol[(ch-1)] += 0.1; // TODO - Change this to be a variable
		if(rs232_output_vol[(ch-1)] > 1) {
			rs232_output_vol[(ch-1)] = 1;
		}
		
		if(DEBUG) {
			fprintf(RS232,"Discrete volume for %u to %g\r\n",ch-1,rs232_output_vol[ch-1]);
		}

		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(rs232_output_vol[ch-1]*2147483648.0));

		return rs232_output_vol[(ch-1)];
	}
}

double vol_small_up_output(int ch)
{
	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 0;
			rs232_output_vol[i] += 0.05; // TODO - Change this to be a variable
			if(rs232_output_vol[i] > 1) {
				rs232_output_vol[i] = 1;
			}
				
			send_dsp_command(get_AM_trim_channel(i),(int32)(rs232_output_vol[i]*2147483648.0));
		}

		return rs232_output_vol[0]; // Temporarily just return the first channel volume

	} else {
		
		rs232_output_mute[(ch-1)] = 0;
		rs232_output_vol[(ch-1)] += 0.05;
		if(rs232_output_vol[(ch-1)] > 1) {
			rs232_output_vol[(ch-1)] = 1;
		}
	
		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(rs232_output_vol[ch-1]*2147483648.0));
		return rs232_output_vol[(ch-1)];
	}
}

double vol_big_down_output(int ch)
{
	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 0;
			if(rs232_output_vol[i] > 0.1) { // TODO - Change this to be a variable
				rs232_output_vol[i] -= 0.1; // TODO - Change this to be a variable
			} else {
				rs232_output_vol[i] = 0;
			}
				
			send_dsp_command(get_AM_trim_channel(i),(int32)(rs232_output_vol[i]*2147483648.0));
		}

		return rs232_output_vol[0]; // Temporarily just return the first channel volume

	} else {
		rs232_output_mute[(ch-1)] = 0;
		if(rs232_output_vol[(ch-1)] > 0.1) {
			rs232_output_vol[(ch-1)] -= 0.1;
		} else {
			rs232_output_vol[(ch-1)] = 0;
		}
	
		if(DEBUG) {
			fprintf(RS232,"Discrete volume for %u to %g\r\n",ch-1,rs232_output_vol[ch-1]);
		}

		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(rs232_output_vol[ch-1]*2147483648.0));

		return rs232_output_vol[(ch-1)];
	}
}

double vol_small_down_output(int ch)
{
	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 0;
			if(rs232_output_vol[i] > 0.05) { // TODO - Change this to be a variable
				rs232_output_vol[i] -= 0.05; // TODO - Change this to be a variable
			} else {
				rs232_output_vol[i] = 0;
			}
				
			send_dsp_command(get_AM_trim_channel(i),(int32)(rs232_output_vol[i]*2147483648.0));
		}

		return rs232_output_vol[0]; // Temporarily just return the first channel volume

	} else {
		
		rs232_output_mute[(ch-1)] = 0;
		if(rs232_output_vol[(ch-1)] > 0.05) {
			rs232_output_vol[(ch-1)] -= 0.05;
		} else {
			rs232_output_vol[(ch-1)] = 0;
		}
	
		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(rs232_output_vol[ch-1]*2147483648.0));

		return rs232_output_vol[ch];
	}
}

void mute_on_output(int ch)
{
	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 1;

			send_dsp_command(get_AM_trim_channel(i),0x00000000);
		}
	} else {
		rs232_output_mute[(ch-1)] = 1;
	
		send_dsp_command(get_AM_trim_channel(ch-1),0x00000000);
	}		
}

void mute_off_output(int ch)
{

	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = 0;
	
			send_dsp_command(get_AM_trim_channel(i),(int32)(rs232_output_vol[i]*2147483648.0));
		}
	} else {
		rs232_output_mute[(ch-1)] = 0;
	
		send_dsp_command(get_AM_trim_channel(ch-1),(int32)(rs232_output_vol[ch-1]*2147483648.0));
	}		
}

int mute_toggle_output(int ch)
{
	if(ch == 0) {
		
		for(int i = 0; i < 4; i++) {
			rs232_output_mute[i] = !rs232_output_mute[i];

			if(rs232_output_mute[i]) {
				send_dsp_command(get_AM_trim_channel(i),0x00000000);
			} else {
				send_dsp_command(get_AM_trim_channel(i),(int32)(rs232_output_vol[i]*2147483648.0));
			}
		
			
		}

		return rs232_output_mute[0];

	} else {
		rs232_output_mute[(ch-1)] = !rs232_output_mute[(ch-1)];

		if(rs232_output_mute[(ch-1)]) {
			send_dsp_command(get_AM_trim_channel(ch-1),0x00000000);	
		} else {
			send_dsp_command(get_AM_trim_channel(ch-1),(int32)(rs232_output_vol[ch-1]*2147483648.0));
		}
	
		return rs232_output_mute[(ch-1)];
	}
}
