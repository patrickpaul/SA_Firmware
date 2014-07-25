#include <STDLIB.H>

// VERSION INFO
int MAJOR_REVISION = 3;
int MINOR_REVISION = 0;
char REVISION_TEXT[20] = "-DSP4x4";

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
BYTE RS232_BYTE1, RS232_BYTE2, RS232_BYTE3, RS232_BYTE4;
BYTE buffer[RS232_BUFFER_SIZE];
BYTE next_in = 0;
BYTE next_out = 0;

double rs232_premix_vol[4];
int rs232_premix_mute[4];

double rs232_output_vol[4];
int rs232_output_mute[4];

// DSP DEFINES
#define DSP_I2C_ADDRESS 0x80

// MEMORY DEFINES
int CURRENT_FLASH_PROGRAM = 0;

#define PAGE_SIZE  64 
#define NUM_PAGES 9
#define TOTAL_ARRAY_SIZE (PAGE_SIZE*NUM_PAGES)

int32 PAGE_BUFFER_A[PAGE_SIZE];

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









