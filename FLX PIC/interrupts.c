void disable_all_timers()
{
	clear_interrupt(INT_TIMER0);
	clear_interrupt(INT_TIMER1);
	SETUP_TIMER_0(RTCC_OFF);
	setup_timer_1(T1_DISABLED);
	clear_interrupt(INT_TIMER0);
	clear_interrupt(INT_TIMER1);
}

void enable_all_timers()
{

	clear_interrupt(INT_TIMER0);
	clear_interrupt(INT_TIMER1);
	setup_timer_0(T0_INTERNAL|T0_DIV_64);
	setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
	clear_interrupt(INT_TIMER0);
	clear_interrupt(INT_TIMER1);

	setup_interrupts();

}

// SLEEP TIMER is every 1 seconds
#INT_TIMER0
void SLEEPTIMER_ISR(void) 
{

	sleepseconds++;

	if(sleepseconds >= sleeptimeout_seconds) {
		sleepseconds = 0;
		// TIMEOUT ROUTINE HERE
		is_in_sleep = 1;
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] NO AUDIO FOR %ld SECONDS, AMPLIFIER NOW IN SLEEP MODE\r\n",sleeptimeout_seconds);
		}

		disable_interrupts(INT_TIMER0);
		clear_interrupt(INT_TIMER0);
		return;
	}

	set_timer0(7936);
	clear_interrupt(INT_TIMER0);
}

// REMOTE VOLUME CONTROL
#INT_TIMER1 
void RVCTIMER_ISR(void) 
{

	pin_in_mute_state = !input(PIN_AMP_nMUTE);
	
	set_adc_channel(0);
	delay_us(10);
	current_adc = read_adc();
	
	if(pin_in_mute_state && is_muted) {
		// Do nothing
		set_timer1(15550);
		clear_interrupt(INT_TIMER1);
	}

	

	if(pin_in_mute_state && !is_muted) {
		is_muted = true;
		send_dsp_command(AM_ANALOG1_TRIM,0x00000000);
		send_dsp_command(AM_ANALOG2_TRIM,0x00000000);
		send_dsp_command(AM_ANALOG3_TRIM,0x00000000);
		send_dsp_command(AM_ANALOG4_TRIM,0x00000000);
		set_timer1(15550);
		clear_interrupt(INT_TIMER1);

		if(DEBUG) {
			fprintf(RS232,"Mute pin brought low. Muting\r\n");
		}
	}

	unsigned int difference = 0;

	if(current_adc > last_adc) {
		difference = current_adc - last_adc;
	} else {
		difference = last_adc - current_adc;
	}

	if((!pin_in_mute_state && is_muted) || (difference > RVC_NOISE_FLOOR)) {

		
		double dsp_value = RVC_to_dsp_value(current_adc);

		
		if(current_adc < 30) {
			dsp_value = 0;
			if(DEBUG) {
				fprintf(RS232,"[DEBUG] ADC = %u, Value = 0.0000\r\n",current_adc);
			}	
		} else {
			if(DEBUG) {
				fprintf(RS232,"[DEBUG] ADC = %u, Value = %.4f\r\n",current_adc,dsp_value);
			}

		}

		//double percentage = ADC_to_percentage(current_adc);
		send_dsp_command(AM_ANALOG1_TRIM,(int32)(dsp_value*2147483648.0));
		send_dsp_command(AM_ANALOG2_TRIM,(int32)(dsp_value*2147483648.0));
		send_dsp_command(AM_ANALOG3_TRIM,(int32)(dsp_value*2147483648.0));
		send_dsp_command(AM_ANALOG4_TRIM,(int32)(dsp_value*2147483648.0));

		is_muted = 0;
		last_adc = current_adc;
		set_timer1(15550);
		clear_interrupt(INT_TIMER1);
	}  
}

// AUDIO DETECT FOR SLEEP MODE
#INT_EXT
void AUDIODETECT_ISR(void) 
{ 
   	disable_interrupts (INT_EXT);

	clear_interrupt(INT_EXT);
	

	if(input(PIN_B0)) {

		// Audio is now present
		//if(is_in_sleep) {
			is_in_sleep = 0;
			sleep_timer_active = 0;
			clear_interrupt(INT_TIMER0);
			disable_interrupts(INT_TIMER0);
			
			if(DEBUG) {
				fprintf(RS232,"[DEBUG] AUDIO DETECTED. NO LONGER IN SLEEP MODE\r\n");
			}

			// Now wait for it to go low again...

			
		//}

			ext_int_edge(0,H_TO_L); 
			
			enable_interrupts (INT_EXT);
			return;
	} else {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] NO AUDIO FOR %ld SECONDS, STARTING SLEEP TIMER\r\n",AUDIODETECT_HOLDTIME_SECONDS);
		}
		// Audio not detected for 1 minute.. start timer
		clear_interrupt(INT_TIMER0);

		sleepseconds = AUDIODETECT_HOLDTIME_SECONDS;
		set_timer0(7936);
		enable_interrupts(INT_TIMER0);
		sleep_timer_active = 1;
		is_in_sleep = 0;

		ext_int_edge(0,L_TO_H); 
		enable_interrupts (INT_EXT);
		return;
	}
}

// USB DETECTION
#INT_EXT1 
void USBDETECT_ISR(void) 
{ 

   	disable_interrupts (INT_EXT1);

	delay_us(100);

	if(input(PIN_B1)) {
		IS_USB_CONNECTED = true;
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] PIN_B1 is high. USB CONNECT EVENT. Triggering on H_TO_L.\r\n");
		}
		ext_int_edge(1,H_TO_L); 

		disable_all_timers();

	} else {
		IS_USB_CONNECTED = false;
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] PIN_B1 is low. USB DISCONNECT EVENT. Triggering on L_TO_H.\r\n");
		}
		ext_int_edge(1,L_TO_H); 

		enable_all_timers();
	}
	
	enable_interrupts(INT_EXT1);
	clear_interrupt(INT_EXT1);
} 
