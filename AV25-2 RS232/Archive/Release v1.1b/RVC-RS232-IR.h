/*
NOTE - THIS IS THE AV25-2 VERSION!!!
*/
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOPUT                    //No Power Up Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOPROTECT                //Code not protected from reading

#use delay(clock=20000000)
#define LED PIN_A1
#define DELAY 500

#use rs232(baud=9600,parity=N,xmit=PIN_B2,rcv=PIN_B1,bits=8,errors)
// DIGITAL POT (MICROCHIP MCP41010

#define SPI_ENABLE PIN_B6       
#define DPOT_SCLK PIN_B5       
#define DPOT_MOSI PIN_B4

#define DPOT_COMMAND 0x11 //Specific to Microchip MCP41010

#define POT_MAX 255 
#define POT_MIN 0


#define VERSION_MAJOR 1
#define VERSION_MINOR 1


// VOLUME CONFIGURATION IN DECIBELS

unsigned int VOL_MUTE = 0;
unsigned int VOL_MIN = 0;
unsigned int VOL_MAX = 100;
unsigned int VOL_BIG_STEP = 10; // MUST BE A MULTIPLE OF 5 AND DIVIDE INTO 100 OR THINGS BREAK!
unsigned int VOL_SMALL_STEP = 5;
signed int command_data = 0;


// COMMANDS

#define COMMAND_START_BYTE 		0x02 // ASCII Start of Text
#define COMMAND_END_BYTE 		0x03 // ASCII End of text

#define VOL_START_BYTE 			0x76 // v
#define VOL_UP_BYTE 			0x75 // u
#define VOL_UP_BYTE_SMALL		0x74
#define VOL_DOWN_BYTE 			0x64 // d
#define VOL_DOWN_BYTE_SMALL		0x63
#define VOL_DISCRETE_START 		0x56 // V

#define MUTE_START_BYTE 		0x6D // m
#define MUTE_TOGGLE_BYTE 		0x4D // M
#define MUTE_FORCEMUTE_BYTE 	0x79 // y
#define MUTE_FORCEUNMUTE_BYTE 	0x6E // n

#define DEBUG_START_BYTE		0x44 //	D
#define DEBUG_GET_VERSION		0x56 // V

#define STATUS_BYTE 0x53 // S (sent after VOL_START_BYTE or MUTE_START_BYTE)

#define COMMAND_MAX_LENGTH 4 // INCLUDING END_BYTE

// COMMAND LIST FOR INTERNAL USE ONLY

#define COMMAND_VOL_UP			0x01
#define COMMAND_VOL_DOWN		0x02
#define COMMAND_VOL_DISCRETE	0x03
#define COMMAND_VOL_STATUS		0x04

#define COMMAND_MUTE_TOGGLE		0x05
#define COMMAND_FORCE_MUTE		0x06
#define COMMAND_FORCE_UNMUTE	0x07
#define COMMAND_MUTE_STATUS		0x08

#define COMMAND_GET_VERSION		0x09


// DEBUG VERBOSE MODE

#define DEBUG 0
#define DEBUG_IR 0


// INFRARED

#define IR_INPUT PIN_B0                // Pin IR received connected to (must be an interrupt)
#define IR_STATUS (!input(IR_INPUT))   // Invert the signal from the IR receiver

unsigned int current_volume = 0; // in dB
unsigned int current_pot_setting = 0;
signed int muted_volume = 0;
int is_muted = 0;
int startup_flag = 1;
int is_small_step = 0;
int get_IR_command(void);
int get_serial_command(void);

typedef struct {
   int8 address;
   int8 command;
   int8 state;
} IR_struct;

IR_struct IR;
