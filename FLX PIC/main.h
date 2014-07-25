#include <STDLIB.H>

// VERSION INFO
int MAJOR_REVISION = 1;
int MINOR_REVISION = 3;
char REVISION_TEXT[20] = "d-FLX80-4";

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

#define RS232_BUFFER_SIZE 32
#define rs232_data_available (next_in!=next_out) 

int buffer_unread = 0;
BYTE RS232_BYTE1, RS232_BYTE2, RS232_BYTE3, RS232_BYTE4, RS232_BYTE5;
BYTE buffer[RS232_BUFFER_SIZE];
BYTE next_in = 0;
BYTE next_out = 0;

double rs232_premix_vol[4];
int rs232_premix_mute[4];

double rs232_output_vol[4];
int rs232_output_mute[4];

int rs232_log_output_vol_index[4];

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

double log_values[61] = {
	0.0000,0.0011,0.0013,0.0014,0.0016,0.0018,
	0.0020,0.0022,0.0025,0.0028,0.0032,0.0035,
	0.0040,0.0045,0.0050,0.0056,0.0063,0.0071,
	0.0079,0.0089,0.0100,0.0112,0.0126,0.0141,
	0.0158,0.0178,0.0200,0.0224,0.0251,0.0282,
	0.0316,0.0355,0.0398,0.0447,0.0501,0.0562,
	0.0631,0.0708,0.0794,0.0891,0.1000,0.1122,
	0.1259,0.1413,0.1585,0.1778,0.1995,0.2239,
	0.2512,0.2818,0.3162,0.3548,0.3981,0.4467,
	0.5012,0.5623,0.6310,0.7079,0.7943,0.8913,
	1.0000};

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









