#define BOOTLOADER_PIC18F46K22
//#define BOOTLOADER_PIC18F8722


/* ------------------------------------------------------------------------- */
/* BOOTLOADER_PIC18F46K22 Bootloader                                                      */
/* ------------------------------------------------------------------------- */
#ifdef BOOTLOADER_PIC18F46K22

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


#endif /* #ifdef BOOTLOADER_PIC18F458 */