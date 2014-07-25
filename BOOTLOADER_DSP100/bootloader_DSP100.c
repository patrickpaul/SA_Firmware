#include <18LF46K22.h>
#device adc=8

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES WDT128                	//Watch Dog Timer uses 1:128 Postscale
#FUSES HSM                   	//High speed Osc, medium power 4MHz-16MHz
#FUSES NOPLLEN               	//4X HW PLL disabled, 4X PLL enabled in software
#FUSES PUT                   	//Power Up Timer
#FUSES NOBROWNOUT            	//No brownout reset
#FUSES WDT_SW                	//No Watch Dog Timer, enabled in Software
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST               	//Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=14745600)

#include "types.h"


/* enable the following line to support lower case charachters in HEX file */
//#define BOOTLOADER_HEX_LOWERCASE

/* the following line enables the checksum check, disable to decrease the */
/* bootloader size */
#define BOOTLOADER_HEX_CHECKSUM

/* ------------------------------------------------------------------------- */
/* Intel HEX file record types                                               */
/* ------------------------------------------------------------------------- */
#define HEX_DATA_REC        0   /* data record */
#define HEX_EOF_REC         1   /* end of file record */
#define HEX_EXTADDR_REC     4   /* extened linear address record */


/* ------------------------------------------------------------------------- */
/* Intel HEX file section start offsets                                      */
/* ------------------------------------------------------------------------- */
#define HEX_LEN_START       1   /* start of record length */
#define HEX_ADDR_START      3   /* start of address */
#define HEX_TYPE_START      7   /* start of record type */
#define HEX_DATA_START      9   /* start of data */

#define HEX_HEADER_LEN      4   /* lenght of lenght-, address- and type field in byte */

#define HEX_LINE_LEN_MAX    50  /* maximum length a line in the HEX file */


#define ACK                 0x06    /* positive acknowledge (ACK) */
#define NAK                 0x15    /* negative acknowledge (NAK) */


/* ------------------------------------------------------------------------- */
/* Bootloader Address Mapping                                                */
/* ------------------------------------------------------------------------- */
#define BOOTLOADER_START        0x2A 
#define BOOTLOADER_END          0x3FF + 0x400 
#define RESET_VECTOR            0x400 + 0x400  
#define INTERRUPT_VECTOR_LOW    0x418 + 0x400  
#define INTERRUPT_VECTOR_HIGH   0x408 + 0x400  
#define APPLICATION_START       RESET_VECTOR 

#ORG BOOTLOADER_START, BOOTLOADER_END auto=0 default 

#define PIN_USB_BOOT_TX			PIN_C5
#define PIN_USB_BOOT_RX			PIN_C4	
#define PIN_PHANTOM_ENABLE		PIN_D5


/* USB configuration */
#use rs232(baud=57600,parity=N,xmit=PIN_USB_BOOT_TX,rcv=PIN_USB_BOOT_RX,bits=8,errors,stream=USB_BOOT,FORCE_SW)


/* ========================================================================= */
/* get_hexbyte                                                               */
/* returns byte representation of 2 ASCII characters pointed to by *hex      */
/* ========================================================================= */
uint8 get_hexbyte(uint8 *hex)
{
    uint8 i;
    uint8 ret = 0;
    uint8 ch;
    
    for (i=0; i < 2; i++)
    {
        /* take care of HEX files where lower case letters are used */
        #ifdef BOOTLOADER_HEX_LOWERCASE
        ch = toupper(*hex);
        #else
        ch = *hex;
        #endif
        
        /* convert character to integer value */
        if (ch >= 'A')
        {
            ch = ch - 'A' + 10;
        }
        else
        {
            ch = ch - '0';
        }
        ret = (ret << 4) | ch;
        hex++;
    }
    
    return (ret);
}


/* ========================================================================= */
/* check_checksum                                                            */
/* calculates checksum for the received Intel HEX file line                  */
/* return: 0 = checksum ok                                                   */
/*         1 = checksum error                                                */
/* ========================================================================= */
#ifdef BOOTLOADER_HEX_CHECKSUM
uint8 check_checksum(uint8 *hex, uint8 reclen)
{
    uint8 checksum = 0;
    uint8 i;

    // add all byte values, incl. checksum!
    for (i=0; i <= (reclen + HEX_HEADER_LEN); i++)
    {
        checksum += get_hexbyte(hex);
        hex += 2;
    }

    // checksum is zero if checksum is correct
    return (checksum);
}
#endif /* BOOTLOADER_HEX_CHECKSUM */


/* ========================================================================= */
/* bootloader                                                                */
/* the bootloader itself.                                                    */
/* ========================================================================= */
void bootloader(void)
{
    uint32 addr;
    uint16 addr_low;
    uint8 addr_high = 0;
    uint8 reclen;
    uint8 rectype;
    uint8 idx;
    uint8 buffer[HEX_LINE_LEN_MAX];
    uint8 ch;
    bool hexend = 0;
    
    #if getenv("FLASH_ERASE_SIZE")>2
    uint16 next_addr = 0;
    #endif

    
    /* until end of HEX file */
    while(hexend == 0)
    {
        /* get one line of the HEX file via RS232 until we receive CR or */
        /* we reached the end of the buffer */
        idx = 0;
        do
        {
             /* get one byte */
             ch = fgetc(USB_BOOT);
             /* save to buffer */
             buffer[idx] = ch;
             /* increment buffer index */
             idx++;
        }
        while(ch != 0x0A);


        /* get record length */
        reclen = get_hexbyte(&buffer[HEX_LEN_START]);

        /* check for proper checksum */
        #ifdef BOOTLOADER_HEX_CHECKSUM
        if (check_checksum(&buffer[HEX_LEN_START], reclen) != 0)
        {
            /* checkum error - send negative acknowledge */
            fputc(NAK,USB_BOOT);
        }
        else
        #endif /* BOOTLOADER_HEX_CHECKSUM */
        {
            /* checkum ok */

            /* get address */
            addr_low = make16(get_hexbyte(&buffer[HEX_ADDR_START]),
                              get_hexbyte(&buffer[HEX_ADDR_START+2]));

            /* make 32 bit address */
            addr = make32(addr_high, addr_low);

            /* get record type */
            rectype = get_hexbyte(&buffer[HEX_TYPE_START]);
            
            if (rectype == HEX_DATA_REC)
            {
                /* only program code memory */
                if ((addr_high < 0x30) && (addr >= RESET_VECTOR))
                {
                    for (idx=0; idx < reclen; idx++)
                    {
                        buffer[idx] = get_hexbyte(&buffer[HEX_DATA_START+(idx*2)]);
                    }

                    #if getenv("FLASH_ERASE_SIZE") > getenv("FLASH_WRITE_SIZE")
                    #if defined(__PCM__)
                    if ((addr_low!=next_addr)&&(addr_low&(getenv("FLASH_ERASE_SIZE")-1)!=0))
                    #else
                    if ((addr_low!=next_addr)&&(addr_low&(getenv("FLASH_ERASE_SIZE")/2-1)!=0))
                    #endif
                        erase_program_eeprom(addr);
                    next_addr = addr_low + 1;
                    #endif
                    write_program_memory(addr, buffer, reclen);
                }
            }
            else if (rectype == HEX_EOF_REC)
            {
                hexend = 1;
            }
            else if (rectype == HEX_EXTADDR_REC)
            {
				//fprintf(RS232_BOOT,"Got extended address record\r\n");
                /* to save resources, only take lower byte - this */
                /* allows 24 bit addresses => enough for PIC18F */
                //addr_high = make16(get_hexbyte(&buffer[HEX_DATA_START]),
                //                   get_hexbyte(&buffer[HEX_DATA_START+2]));
                addr_high = get_hexbyte(&buffer[HEX_DATA_START+2]);
            }
            
            /* send positive acknowledge */
            fputc(ACK,USB_BOOT);
        }
    }
   
   //write_eeprom(0x05,0x00);
   
}


/* ========================================================================= */
/* application                                                               */
/* dummy application.                                                        */
/* ========================================================================= */
#ORG APPLICATION_START,APPLICATION_START+2
void application(void)
{
   	//write_eeprom(0x05,0x01);
   	while(1);
}


/* ========================================================================= */
/* main                                                                      */
/* checks if bootloader shall be invoked or if it shall start the            */
/* application program.                                                      */
/* ========================================================================= */
#ORG BOOTLOADER_START

int timeout_error;

char timed_getc() {

	int32 timeout;

	timeout_error = FALSE;
	timeout = 0;

	while(!kbhit(USB_BOOT)&&(++timeout<300000)) { // half a second
		delay_us(5); // this polls at 10x the 9600 baud rate
	}

	if(kbhit(USB_BOOT)) {
		timeout_error = FALSE;
		return(fgetc(USB_BOOT));
	} else {
		timeout_error = TRUE;
		return(0);
	}
}

void main()
{
    setup_adc(ADC_OFF);

	delay_us(50);

	output_low(PIN_PHANTOM_ENABLE);

	fprintf(USB_BOOT,"Startup!\r\n");

    char receive_char = timed_getc();


	if(receive_char == 0x55) {
		fputc(0x06,USB_BOOT);
		fputc(0x55,USB_BOOT);
		fputc(0x03,USB_BOOT);
        bootloader();
    }

    #asm
    goto RESET_VECTOR
    #endasm
}


/* ========================================================================= */
/* isr_low                                                                   */
/* remap interrupt vector low.                                               */
/* ========================================================================= */
#ORG 0x08, 0x17
void isr_high(void)
{
    #asm
    goto INTERRUPT_VECTOR_HIGH
    #endasm
}


/* ========================================================================= */
/* isr_high                                                                  */
/* remap interrupt vector high.                                              */
/* ========================================================================= */
#ORG 0x18, 0x29
void isr_low(void)
{
    #asm
    goto INTERRUPT_VECTOR_LOW
    #endasm
}
