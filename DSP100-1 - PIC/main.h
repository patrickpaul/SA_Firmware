#include <STDLIB.H>

// VERSION INFO
int MAJOR_REVISION = 1;
int MINOR_REVISION = 0;
char REVISION_TEXT[20] = "-DSP100-1";

// USEFUL DEFINES
#define hi(x) (*((int8*)&x+1)) 
#define ON     0x00000001
#define OFF    0x00000000

// Used for eeprom.c
#define interrupt_enabled(x)  !!(*(make8(x,1) | 0xF00) & make8(x,0)) 

// EEPROM DEFINES
#use I2C(MASTER, SDA=PIN_C3, SCL=PIN_C2)

#define EEPROM_ADDRESS long int 
#define EEPROM_SIZE   (128*8*8) 

// RS232 DEFINES

#use rs232(baud=19200,parity=N,xmit=PIN_USB_TX,rcv=PIN_USB_RX,bits=8,errors,stream=USB,FORCE_SW)
#use rs232(baud=9600,parity=N,xmit=PIN_RS232_TX,rcv=PIN_RS232_RX,bits=8,errors, stream=RS232)

#define FLASH_CS	PIN_D2

#use SPI(DO = PIN_D4, DI = PIN_D1, CLK = PIN_D0,BITS = 8,MSB_FIRST, SAMPLE_RISE) 

int IS_USB_CONNECTED;


// DSP DEFINES
#define DSP_I2C_ADDRESS 0x80

// MEMORY DEFINES
int CURRENT_FLASH_PROGRAM = 0;

#define PAGE_SIZE  64 
#define NUM_PAGES 9
#define TOTAL_ARRAY_SIZE (PAGE_SIZE*NUM_PAGES)

int32 PAGE_BUFFER_A[PAGE_SIZE];


/* VARIABLES FOR RVC */
unsigned int last_adc = 0;
unsigned int current_adc = 0;

int is_muted = 0;
int pin_in_mute_state = 0;


/* VARIABLES FOR SLEEP TIMER */
int16 sleepseconds;
int16 sleeptimeout_seconds = 10;

int is_in_sleep = 0;
int sleep_timer_active = 0;

typedef struct {
	int16 ADDRESSES_1[PAGE_SIZE];
	int16 ADDRESSES_2[PAGE_SIZE];
	int16 ADDRESSES_3[PAGE_SIZE];
	int16 ADDRESSES_4[PAGE_SIZE];
	int16 ADDRESSES_5[PAGE_SIZE];
	int16 ADDRESSES_6[PAGE_SIZE];
	int16 ADDRESSES_7[PAGE_SIZE];
	int16 ADDRESSES_8[PAGE_SIZE];
} dsp_addresses;

dsp_addresses DSP_ADDR;









