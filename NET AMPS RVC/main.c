/********************************
Program Description: Code for Cobranet Amp's RVC input using ADC
Author: Patrick Paul
Company: Stewart Audio (c)2011
Date: 12/12/11
Rev: 1.1

All code copyright (c)2012 Stewart Audio. All rights reserved.

Changelog:
1.0 - Initial Release
1.1 - Added upper limit on ADC reading. After 240/255 (94%) it'll set to max

********************************/

#include <12F683.h> 
#fuses NOWDT, INTRC_IO, NOCPD, NOPROTECT, MCLR, NOPUT 
#use delay (clock=8000000)
#USE I2C(master, sda=PIN_A5, scl=PIN_A4)

void set_digital_pot(int data) {

	i2c_start();
	i2c_write(0x50);
	i2c_write(0xAF);
	i2c_write(data);
	i2c_stop();

}

void main() 
{ 
    
   	//setup_oscillator(OSC_8MHZ);  
   	setup_adc(ADC_CLOCK_INTERNAL);
   	setup_adc_ports(sAN1);
	set_adc_channel(1);
	setup_comparator(NC_NC);
	int16 rvc_value = 0;

	int pot_value;
	float pot_math;

   setup_vref(FALSE);

   while (1) 
   {
		rvc_value = read_adc();
		delay_us(20);
		

		if(rvc_value < 10) {
			pot_value = 64;
		} else if(rvc_value > 240) {
			pot_value = 0;
		} else {
			pot_value = (int)(65.84-(0.2582*rvc_value));
		}

		set_digital_pot(pot_value);
		delay_ms(20);	
   } 
} 