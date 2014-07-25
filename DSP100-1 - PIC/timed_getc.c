//timed_getc.c
int timeout_error;

short data_available_usb()
{
	return kbhit(USB);


}
char timed_getc() {

	long timeout;

	timeout_error = FALSE;
	timeout = 0;

	while(!kbhit(USB)&&(++timeout<50000)) { // half a second
		delay_us(5); // this polls at 10x the 9600 baud rate
	}

	if(kbhit()) {
		timeout_error = FALSE;
		return(fgetc(USB));
	} else {
		timeout_error = TRUE;
		return(0);
	}
}

char fast_timed_getc() {

	long timeout;

	timeout_error = FALSE;
	timeout = 0;

	while(!kbhit(USB)&&(++timeout<10000)) { // tenth of a second
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

char slow_timed_getc() {

	long timeout;

	timeout_error = FALSE;
	timeout = 0;

	while(!kbhit(USB)&&(++timeout<20000)) { // fifth of a second
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
