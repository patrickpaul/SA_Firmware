// ADC

double ADC_to_percentage(unsigned int read_value)
{
	if(read_value < DEVICE_CONFIG.ADC_CALIBRATION_MIN) {

		if(DEBUG) {
			fprintf(RS232,"[DEBUG] ADC %u, DSP  Minimum\r\n",read_value);
		}

		return 0;
	} else if(read_value > DEVICE_CONFIG.ADC_CALIBRATION_MAX) {
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] ADC %u, DSP  Maximum\r\n",read_value);
		}
		return 1.0;
	} else {
		double percentage = ((((double)read_value)-DEVICE_CONFIG.ADC_CALIBRATION_MIN)/(DEVICE_CONFIG.ADC_CALIBRATION_MAX-DEVICE_CONFIG.ADC_CALIBRATION_MIN));
		if(DEBUG) {
			fprintf(RS232,"[DEBUG] ADC %u, PERC %g, SENT_VALUE %lx \r\n",read_value,percentage,((int32)(percentage*2147483648.0)) );
		}
		return percentage;
	}
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