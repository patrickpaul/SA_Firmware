// File DSP4x4_CONFIG.h

#define POWERUP_DELAY	200

#define IEEPROM_PRESET_LOC	0x10
#define IEEPROM_DEVICE_CONFIG_LOC 0x64
#define IEEPROM_FLAG_LOC 0x20

#define FLASH_PHANTOM_LOC 0x200

#define NUM_PRESETS			10
#define DEFAULT_PRESET		0

long int num_dsp_values = 478; // Not a define since the software will automatically change this if necessary

#define NUM_PRESET_PAGES			12
#define NUM_DSP_VALUE_PAGES			8		
#define NUM_PLAIN_VALUE_PAGES		4
#define PLAIN_VALUE_PAGES_OFFSET	9	
#define NUM_ADDRESS_PAGES			4
#define IOLABEL_PAGE				11

#define DEFAULT_ADDR_BLOCK			14
#define DEFAULT_VALUE_BLOCK			15

/* store in EEPROM */

const int DEBUG = 0;


int DEFAULT_USBDETECT_ENABLE = 1;
int DEFAULT_DSP_VALUESEND_ENABLE = 1;

#define DEVICE_ID_MSB	0
#define DEVICE_ID_LSB	0x14


typedef struct {
	
	int USBDETECT_ENABLE;
	int DSP_VALUESEND_ENABLE;
	char SERIAL[20];
} device_configuration;

device_configuration DEVICE_CONFIG;
	