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
#define PLAIN_VALUE_PAGES_OFFSET	8	
#define NUM_ADDRESS_PAGES			4
#define IOLABEL_PAGE				11

#define DEFAULT_ADDR_BLOCK			14
#define DEFAULT_VALUE_BLOCK			15

long int AUDIODETECT_HOLDTIME_SECONDS = 2;


#define DELAY_POWERUP			100
#define DELAY_AMP_MODE_SETTLE	1000
#define DELAY_DSP_RESET_SETTLE	50

unsigned int RVC_NOISE_FLOOR = 0; // Higher the number the fewer the subdivisions

/* store in EEPROM */

const int DEBUG = 0;

double DEFAULT_ADC_CALIBRATION_MIN	= 30.0;
double DEFAULT_ADC_CALIBRATION_MAX	= 240.0;

int DEFAULT_AMP_MODE = 1; // 0 = 4CH, 1 = 2CH, 2 = 1CH
int DEFAULT_IS_70V = 1;

int DEFAULT_RVC_ENABLE = 1;
int DEFAULT_USBDETECT_ENABLE = 1;
int DEFAULT_AMPBOOT_DELAY_ENABLE = 1;
int DEFAULT_PS_PIN_ENABLE = 0;
int DEFAULT_DSP_VALUESEND_ENABLE = 1;
int DEFAULT_SLEEP_ENABLE = 0;
int16 DEFAULT_SLEEP_SECONDS = 65;
int16 DEFAULT_SLEEP_HOLDTIME = 60;

#define DEVICE_ID_MSB	0
#define DEVICE_ID_LSB	0x1E

typedef struct {
	
	int AMP_MODE;
	int IS_70V;
	
	double ADC_CALIBRATION_MIN;
	double ADC_CALIBRATION_MAX;

	
	int RVC_ENABLE;
	int USBDETECT_ENABLE;
	int AMPBOOT_DELAY_ENABLE;
	int PS_PIN_ENABLE;
	int DSP_VALUESEND_ENABLE;
	int SLEEP_ENABLE;
	int16 SLEEP_SECONDS;
	int16 SLEEP_HOLDTIME;
	char SERIAL[20];
} device_configuration;

device_configuration DEVICE_CONFIG;

	