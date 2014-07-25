// ADC

double RVC_to_dsp_value(unsigned int read_value)
{
	return pow(10.0,(-60.0+(60.0*((read_value-30.0)/225.0)))/20.0);

}

double RVC_to_decibel(unsigned int read_value)
{
	return -60.0 + (60.0*((read_value-30.0)/225.0));
}


int ADC_calibrate_min(int is_usb = 0)
{
	set_adc_channel(0);
	delay_us(10);
	int current_adc = read_adc();
	
	if(DEBUG && (is_usb==0)) {
		fprintf(RS232,"[DEBUG] Read a value of %u, saving as new minimum...",current_adc);
	}
	DEVICE_CONFIG.ADC_CALIBRATION_MIN = (double)current_adc;

	INTEEPROM_PUT(&DEVICE_CONFIG,sizeof(DEVICE_CONFIG),100);
	delay_ms(10);

	if(DEBUG && (is_usb==0)) {
		fprintf(RS232,"[DEBUG] Done!\r\n");
	}

	return current_adc;
}

int ADC_calibrate_max(int is_usb = 0)
{
	set_adc_channel(0);
	delay_us(10);
	int current_adc = read_adc();

	if(DEBUG && (is_usb==0)) {
		fprintf(RS232,"[DEBUG] Read a value of %u, saving as new maximum...",current_adc);
	}
	DEVICE_CONFIG.ADC_CALIBRATION_MAX= (double)current_adc;

	INTEEPROM_PUT(&DEVICE_CONFIG,sizeof(DEVICE_CONFIG),100);
	delay_ms(10);

	if(DEBUG && (is_usb==0)) {
		fprintf(RS232,"[DEBUG] Done!\r\n");
	}

	return current_adc;
}