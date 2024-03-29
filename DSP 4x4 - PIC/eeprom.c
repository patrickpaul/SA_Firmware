#byte INTCON=0xFF2 //Change for a 16 chip 
#bit INT_GIE=INTCON.7 


void write_int16_eeprom(int16 address, int16 data)
{
   int8 i;

   for(i = 0; i < 2; ++i)
   {
     write_eeprom(address + i, *((int8 *)(&data) + i));
   }
}


// Purpose:    Read a 16 bit number from internal eeprom
// Inputs:     An eeprom address
// Outputs:    The 16 bit number read from internal eeprom
int16 read_int16_eeprom(int16 address)
{
   int8  i;
   int16 data;

   for(i = 0; i < 2; ++i)
   {
     *((int8 *)(&data) + i) = read_eeprom(address + i);
   }

   return(data);
}


void INTEEPROM_GET(int *ptr,int16 num,int16 addr) { 
   int16 count; 
   int1 int_enabled; 
   int_enabled=INT_GIE; 
   for (count=0;count<num;count++) 
   { 
      disable_interrupts(global); 
      ptr[count]=read_int16_eeprom(addr+count); 
      if (int_enabled) enable_interrupts(global); 
   } 
} 

void INTEEPROM_PUT(int *ptr,int16 num,int16 addr) { 
   int16 count; 
   int1 int_enabled; 
   int_enabled= INT_GIE; 
   for (count=0;count<num;count++) 
   { 
      disable_interrupts(global); 
      //WRITE_EEPROM 
		write_int16_eeprom(addr+count,ptr[count]);
		delay_ms(3);
      if (int_enabled) enable_interrupts(global); 
   }
} 


void INTEEPROM_GET8(int *ptr,int16 num,int16 addr) { 
   int16 count; 
   int1 int_enabled; 
   int_enabled=INT_GIE; 
   for (count=0;count<num;count++) 
   { 
      disable_interrupts(global); 
      ptr[count]=read_eeprom(addr+count); 
      if (int_enabled) enable_interrupts(global); 
   } 
} 

void INTEEPROM_PUT8(int *ptr,int16 num,int16 addr) { 
   int16 count; 
   int1 int_enabled; 
   int_enabled= INT_GIE; 
   for (count=0;count<num;count++) 
   { 
      disable_interrupts(global); 
      //WRITE_EEPROM 
		write_eeprom(addr+count,ptr[count]);
		delay_ms(3);
      if (int_enabled) enable_interrupts(global); 
   }
} 

void default_addr()
{
	WRITE_CONFIG_ADDRESS(0, PREGAIN_CH1);     	// PREGAIN_CH1
	WRITE_CONFIG_ADDRESS(1, PREGAIN_MUTE_CH1);  // PREGAIN_MUTE_CH1
	WRITE_CONFIG_ADDRESS(2, PREGAIN_CH2);     	// PREGAIN_CH2
	WRITE_CONFIG_ADDRESS(3, PREGAIN_MUTE_CH2);  // PREGAIN_MUTE_CH2
	WRITE_CONFIG_ADDRESS(4, PREGAIN_CH3);     	// PREGAIN_CH3
	WRITE_CONFIG_ADDRESS(5, PREGAIN_MUTE_CH3);  // PREGAIN_MUTE_CH3
	WRITE_CONFIG_ADDRESS(6, PREGAIN_CH4);     	// PREGAIN_CH4
	WRITE_CONFIG_ADDRESS(7, PREGAIN_MUTE_CH4);  // PREGAIN_MUTE_CH4
	WRITE_CONFIG_ADDRESS(8, PREGAIN_CH5);     	// PREGAIN_CH5
	WRITE_CONFIG_ADDRESS(9, PREGAIN_MUTE_CH5);  // PREGAIN_MUTE_CH5
	WRITE_CONFIG_ADDRESS(10, PREGAIN_CH6);     	// PREGAIN_CH6
	WRITE_CONFIG_ADDRESS(11, PREGAIN_MUTE_CH6); // PREGAIN_MUTE_CH6
	WRITE_CONFIG_ADDRESS(12, PREGAIN_CH7);     	// PREGAIN_CH7
	WRITE_CONFIG_ADDRESS(13, PREGAIN_MUTE_CH7); // PREGAIN_MUTE_CH7
	WRITE_CONFIG_ADDRESS(14, PREGAIN_CH8);     	// PREGAIN_CH8
	WRITE_CONFIG_ADDRESS(15, PREGAIN_MUTE_CH8); // PREGAIN_MUTE_CH8

	WRITE_CONFIG_ADDRESS(16, PREMIX_CH1);     	// PREMIX_CH1
	WRITE_CONFIG_ADDRESS(17, PREMIX_MUTE_CH1);  // PREMIX_MUTE_CH1
	WRITE_CONFIG_ADDRESS(18, PREMIX_CH2);     	// PREMIX_CH2
	WRITE_CONFIG_ADDRESS(19, PREMIX_MUTE_CH2);  // PREMIX_MUTE_CH2
	WRITE_CONFIG_ADDRESS(20, PREMIX_CH3);     	// PREMIX_CH3
	WRITE_CONFIG_ADDRESS(21, PREMIX_MUTE_CH3);  // PREMIX_MUTE_CH3
	WRITE_CONFIG_ADDRESS(22, PREMIX_CH4);     	// PREMIX_CH4
	WRITE_CONFIG_ADDRESS(23, PREMIX_MUTE_CH4);  // PREMIX_MUTE_CH4
	WRITE_CONFIG_ADDRESS(24, PREMIX_CH5);     	// PREMIX_CH5
	WRITE_CONFIG_ADDRESS(25, PREMIX_MUTE_CH5);  // PREMIX_MUTE_CH5
	WRITE_CONFIG_ADDRESS(26, PREMIX_CH6);     	// PREMIX_CH6
	WRITE_CONFIG_ADDRESS(27, PREMIX_MUTE_CH6);  // PREMIX_MUTE_CH6
	WRITE_CONFIG_ADDRESS(28, PREMIX_CH7);     	// PREMIX_CH7
	WRITE_CONFIG_ADDRESS(29, PREMIX_MUTE_CH7);  // PREMIX_MUTE_CH7
	WRITE_CONFIG_ADDRESS(30, PREMIX_CH8);     	// PREMIX_CH8
	WRITE_CONFIG_ADDRESS(31, PREMIX_MUTE_CH8);  // PREMIX_MUTE_CH8

	WRITE_CONFIG_ADDRESS(32, TRIM_CH1);     	// TRIM_CH1
	WRITE_CONFIG_ADDRESS(33, TRIM_MUTE_CH1);    // TRIM_MUTE_CH1
	WRITE_CONFIG_ADDRESS(34, TRIM_CH2);     	// TRIM_CH2
	WRITE_CONFIG_ADDRESS(35, TRIM_MUTE_CH2);    // TRIM_MUTE_CH2
	WRITE_CONFIG_ADDRESS(36, TRIM_CH3);     	// TRIM_CH3
	WRITE_CONFIG_ADDRESS(37, TRIM_MUTE_CH3);    // TRIM_MUTE_CH3
	WRITE_CONFIG_ADDRESS(38, TRIM_CH4);     	// TRIM_CH4
	WRITE_CONFIG_ADDRESS(39, TRIM_MUTE_CH4);     // TRIM_MUTE_CH4

	WRITE_CONFIG_ADDRESS(40, OUTPUTGAIN_CH1);     // OUTPUTGAIN_CH1
	WRITE_CONFIG_ADDRESS(41, OUTPUT_MUTE_CH1);     // OUTPUT_MUTE_CH1
	WRITE_CONFIG_ADDRESS(42, OUTPUTGAIN_CH2);     // OUTPUTGAIN_CH2
	WRITE_CONFIG_ADDRESS(43, OUTPUT_MUTE_CH2);     // OUTPUT_MUTE_CH2
	WRITE_CONFIG_ADDRESS(44, OUTPUTGAIN_CH3);     // OUTPUTGAIN_CH3
	WRITE_CONFIG_ADDRESS(45, OUTPUT_MUTE_CH3);     // OUTPUT_MUTE_CH3
	WRITE_CONFIG_ADDRESS(46, OUTPUTGAIN_CH4);     // OUTPUTGAIN_CH4
	WRITE_CONFIG_ADDRESS(47, OUTPUT_MUTE_CH4);     // OUTPUT_MUTE_CH4

	WRITE_CONFIG_ADDRESS(48, INDUCKROUTER_SELECT0);     // INDUCKROUTER_SELECT0
	WRITE_CONFIG_ADDRESS(49, INDUCKROUTER_SELECT1);     // INDUCKROUTER_SELECT1
	WRITE_CONFIG_ADDRESS(50, INDUCKROUTER_SELECT2);     // INDUCKROUTER_SELECT2
	WRITE_CONFIG_ADDRESS(51, INDUCKROUTER_SELECT3);     // INDUCKROUTER_SELECT3
	WRITE_CONFIG_ADDRESS(52, INDUCKROUTER_SELECT4);     // INDUCKROUTER_SELECT4
	WRITE_CONFIG_ADDRESS(53, INDUCKROUTER_SELECT5);     // INDUCKROUTER_SELECT5
	WRITE_CONFIG_ADDRESS(54, INDUCKROUTER_SELECT6);     // INDUCKROUTER_SELECT6
	WRITE_CONFIG_ADDRESS(55, INDUCKROUTER_SELECT7);     // INDUCKROUTER_SELECT7
	WRITE_CONFIG_ADDRESS(56, OUTDUCKROUTER_SELECT0);     // OUTDUCKROUTER_SELECT0
	WRITE_CONFIG_ADDRESS(57, OUTDUCKROUTER_SELECT1);     // OUTDUCKROUTER_SELECT1
	WRITE_CONFIG_ADDRESS(58, OUTDUCKROUTER_SELECT2);     // OUTDUCKROUTER_SELECT2
	WRITE_CONFIG_ADDRESS(59, OUTDUCKROUTER_SELECT3);     // OUTDUCKROUTER_SELECT3
	WRITE_CONFIG_ADDRESS(60, OUTDUCKROUTER_SELECT4);     // OUTDUCKROUTER_SELECT4
	WRITE_CONFIG_ADDRESS(61, OUTDUCKROUTER_SELECT5);     // OUTDUCKROUTER_SELECT5
	WRITE_CONFIG_ADDRESS(62, OUTDUCKROUTER_SELECT6);     // OUTDUCKROUTER_SELECT6
	WRITE_CONFIG_ADDRESS(63, OUTDUCKROUTER_SELECT7);     // OUTDUCKROUTER_SELECT7
	WRITE_CONFIG_ADDRESS(64, DUCKER_THRESHOLD);     // DUCKER_THRESHOLD
	WRITE_CONFIG_ADDRESS(65, DUCKER_HOLD);     // DUCKER_HOLD
	WRITE_CONFIG_ADDRESS(66, DUCKER_DEPTH);     // DUCKER_DEPTH
	WRITE_CONFIG_ADDRESS(67, DUCKER_ATTACK);     // DUCKER_ATTACK
	WRITE_CONFIG_ADDRESS(68, DUCKER_RELEASE);     // DUCKER_RELEASE
	WRITE_CONFIG_ADDRESS(69, DUCKER_BYPASS);     // DUCKER_BYPASS

	WRITE_CONFIG_ADDRESS(70, IN_1_1_FILTER_B0);     // IN_1_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(71, IN_1_1_FILTER_B1);     // IN_1_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(72, IN_1_1_FILTER_B2);     // IN_1_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(73, IN_1_1_FILTER_MINUSA1);     // IN_1_1_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(74, IN_1_1_FILTER_MINUSA2);     // IN_1_1_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(75, IN_1_2_FILTER_B0);     // IN_1_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(76, IN_1_2_FILTER_B1);     // IN_1_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(77, IN_1_2_FILTER_B2);     // IN_1_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(78, IN_1_2_FILTER_MINUSA1);     // IN_1_2_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(79, IN_1_2_FILTER_MINUSA2);     // IN_1_2_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(80, IN_1_3_FILTER_B0);     // IN_1_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(81, IN_1_3_FILTER_B1);     // IN_1_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(82, IN_1_3_FILTER_B2);     // IN_1_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(83, IN_1_3_FILTER_MINUSA1);     // IN_1_3_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(84, IN_1_3_FILTER_MINUSA2);     // IN_1_3_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(85, IN_2_1_FILTER_B0);     // IN_2_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(86, IN_2_1_FILTER_B1);     // IN_2_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(87, IN_2_1_FILTER_B2);     // IN_2_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(88, IN_2_1_FILTER_MINUSA1);     // IN_2_1_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(89, IN_2_1_FILTER_MINUSA2);     // IN_2_1_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(90, IN_2_2_FILTER_B0);     // IN_2_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(91, IN_2_2_FILTER_B1);     // IN_2_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(92, IN_2_2_FILTER_B2);     // IN_2_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(93, IN_2_2_FILTER_MINUSA1);     // IN_2_2_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(94, IN_2_2_FILTER_MINUSA2);     // IN_2_2_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(95, IN_2_3_FILTER_B0);     // IN_2_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(96, IN_2_3_FILTER_B1);     // IN_2_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(97, IN_2_3_FILTER_B2);     // IN_2_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(98, IN_2_3_FILTER_MINUSA1);     // IN_2_3_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(99, IN_2_3_FILTER_MINUSA2);     // IN_2_3_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(100, IN_3_1_FILTER_B0);     // IN_3_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(101, IN_3_1_FILTER_B1);     // IN_3_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(102, IN_3_1_FILTER_B2);     // IN_3_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(103, IN_3_1_FILTER_MINUSA1);     // IN_3_1_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(104, IN_3_1_FILTER_MINUSA2);     // IN_3_1_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(105, IN_3_2_FILTER_B0);     // IN_3_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(106, IN_3_2_FILTER_B1);     // IN_3_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(107, IN_3_2_FILTER_B2);     // IN_3_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(108, IN_3_2_FILTER_MINUSA1);     // IN_3_2_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(109, IN_3_2_FILTER_MINUSA2);     // IN_3_2_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(110, IN_3_3_FILTER_B0);     // IN_3_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(111, IN_3_3_FILTER_B1);     // IN_3_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(112, IN_3_3_FILTER_B2);     // IN_3_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(113, IN_3_3_FILTER_MINUSA1);     // IN_3_3_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(114, IN_3_3_FILTER_MINUSA2);     // IN_3_3_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(115, IN_4_1_FILTER_B0);     // IN_4_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(116, IN_4_1_FILTER_B1);     // IN_4_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(117, IN_4_1_FILTER_B2);     // IN_4_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(118, IN_4_1_FILTER_MINUSA1);     // IN_4_1_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(119, IN_4_1_FILTER_MINUSA2);     // IN_4_1_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(120, IN_4_2_FILTER_B0);     // IN_4_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(121, IN_4_2_FILTER_B1);     // IN_4_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(122, IN_4_2_FILTER_B2);     // IN_4_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(123, IN_4_2_FILTER_MINUSA1);     // IN_4_2_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(124, IN_4_2_FILTER_MINUSA2);     // IN_4_2_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(125, IN_4_3_FILTER_B0);     // IN_4_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(126, IN_4_3_FILTER_B1);     // IN_4_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(127, IN_4_3_FILTER_B2);     // IN_4_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(128, IN_4_3_FILTER_MINUSA1);     // IN_4_3_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(129, IN_4_3_FILTER_MINUSA2);     // IN_4_3_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(130, IN_5_1_FILTER_B0);     // IN_5_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(131, IN_5_1_FILTER_B1);     // IN_5_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(132, IN_5_1_FILTER_B2);     // IN_5_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(133, IN_5_1_FILTER_MINUSA1);     // IN_5_1_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(134, IN_5_1_FILTER_MINUSA2);     // IN_5_1_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(135, IN_5_2_FILTER_B0);     // IN_5_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(136, IN_5_2_FILTER_B1);     // IN_5_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(137, IN_5_2_FILTER_B2);     // IN_5_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(138, IN_5_2_FILTER_MINUSA1);     // IN_5_2_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(139, IN_5_2_FILTER_MINUSA2);     // IN_5_2_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(140, IN_5_3_FILTER_B0);     // IN_5_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(141, IN_5_3_FILTER_B1);     // IN_5_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(142, IN_5_3_FILTER_B2);     // IN_5_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(143, IN_5_3_FILTER_MINUSA1);     // IN_5_3_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(144, IN_5_3_FILTER_MINUSA2);     // IN_5_3_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(145, IN_6_1_FILTER_B0);     // IN_6_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(146, IN_6_1_FILTER_B1);     // IN_6_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(147, IN_6_1_FILTER_B2);     // IN_6_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(148, IN_6_1_FILTER_MINUSA1);     // IN_6_1_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(149, IN_6_1_FILTER_MINUSA2);     // IN_6_1_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(150, IN_6_2_FILTER_B0);     // IN_6_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(151, IN_6_2_FILTER_B1);     // IN_6_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(152, IN_6_2_FILTER_B2);     // IN_6_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(153, IN_6_2_FILTER_MINUSA1);     // IN_6_2_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(154, IN_6_2_FILTER_MINUSA2);     // IN_6_2_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(155, IN_6_3_FILTER_B0);     // IN_6_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(156, IN_6_3_FILTER_B1);     // IN_6_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(157, IN_6_3_FILTER_B2);     // IN_6_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(158, IN_6_3_FILTER_MINUSA1);     // IN_6_3_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(159, IN_6_3_FILTER_MINUSA2);     // IN_6_3_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(160, IN_7_1_FILTER_B0);     // IN_7_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(161, IN_7_1_FILTER_B1);     // IN_7_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(162, IN_7_1_FILTER_B2);     // IN_7_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(163, IN_7_1_FILTER_MINUSA1);     // IN_7_1_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(164, IN_7_1_FILTER_MINUSA2);     // IN_7_1_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(165, IN_7_2_FILTER_B0);     // IN_7_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(166, IN_7_2_FILTER_B1);     // IN_7_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(167, IN_7_2_FILTER_B2);     // IN_7_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(168, IN_7_2_FILTER_MINUSA1);     // IN_7_2_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(169, IN_7_2_FILTER_MINUSA2);     // IN_7_2_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(170, IN_7_3_FILTER_B0);     // IN_7_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(171, IN_7_3_FILTER_B1);     // IN_7_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(172, IN_7_3_FILTER_B2);     // IN_7_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(173, IN_7_3_FILTER_MINUSA1);     // IN_7_3_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(174, IN_7_3_FILTER_MINUSA2);     // IN_7_3_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(175, IN_8_1_FILTER_B0);     // IN_8_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(176, IN_8_1_FILTER_B1);     // IN_8_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(177, IN_8_1_FILTER_B2);     // IN_8_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(178, IN_8_1_FILTER_MINUSA1);     // IN_8_1_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(179, IN_8_1_FILTER_MINUSA2);     // IN_8_1_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(180, IN_8_2_FILTER_B0);     // IN_8_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(181, IN_8_2_FILTER_B1);     // IN_8_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(182, IN_8_2_FILTER_B2);     // IN_8_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(183, IN_8_2_FILTER_MINUSA1);     // IN_8_2_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(184, IN_8_2_FILTER_MINUSA2);     // IN_8_2_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(185, IN_8_3_FILTER_B0);     // IN_8_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(186, IN_8_3_FILTER_B1);     // IN_8_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(187, IN_8_3_FILTER_B2);     // IN_8_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(188, IN_8_3_FILTER_MINUSA1);     // IN_8_3_FILTER_MINUSA1
	WRITE_CONFIG_ADDRESS(189, IN_8_3_FILTER_MINUSA2);     // IN_8_3_FILTER_MINUSA2
	WRITE_CONFIG_ADDRESS(190, CH1COMP_THRESHOLD);     // CH1COMP_THRESHOLD
	WRITE_CONFIG_ADDRESS(191, CH1COMP_KNEE);     // CH1COMP_KNEE
	WRITE_CONFIG_ADDRESS(192, CH1COMP_RATIO);     // CH1COMP_RATIO
	WRITE_CONFIG_ADDRESS(193, CH1COMP_ATTACK);     // CH1COMP_ATTACK
	WRITE_CONFIG_ADDRESS(194, CH1COMP_RELEASE);     // CH1COMP_RELEASE
	WRITE_CONFIG_ADDRESS(195, CH1COMP_BYPASS);     // CH1COMP_BYPASS
	WRITE_CONFIG_ADDRESS(196, CH2COMP_THRESHOLD);     // CH2COMP_THRESHOLD
	WRITE_CONFIG_ADDRESS(197, CH2COMP_KNEE);     // CH2COMP_KNEE
	WRITE_CONFIG_ADDRESS(198, CH2COMP_RATIO);     // CH2COMP_RATIO
	WRITE_CONFIG_ADDRESS(199, CH2COMP_ATTACK);     // CH2COMP_ATTACK
	WRITE_CONFIG_ADDRESS(200, CH2COMP_RELEASE);     // CH2COMP_RELEASE
	WRITE_CONFIG_ADDRESS(201, CH2COMP_BYPASS);     // CH2COMP_BYPASS
	WRITE_CONFIG_ADDRESS(202, CH3COMP_THRESHOLD);     // CH3COMP_THRESHOLD
	WRITE_CONFIG_ADDRESS(203, CH3COMP_KNEE);     // CH3COMP_KNEE
	WRITE_CONFIG_ADDRESS(204, CH3COMP_RATIO);     // CH3COMP_RATIO
	WRITE_CONFIG_ADDRESS(205, CH3COMP_ATTACK);     // CH3COMP_ATTACK
	WRITE_CONFIG_ADDRESS(206, CH3COMP_RELEASE);     // CH3COMP_RELEASE
	WRITE_CONFIG_ADDRESS(207, CH3COMP_BYPASS);     // CH3COMP_BYPASS
	WRITE_CONFIG_ADDRESS(208, CH4COMP_THRESHOLD);     // CH4COMP_THRESHOLD
	WRITE_CONFIG_ADDRESS(209, CH4COMP_KNEE);     // CH4COMP_KNEE
	WRITE_CONFIG_ADDRESS(210, CH4COMP_RATIO);     // CH4COMP_RATIO
	WRITE_CONFIG_ADDRESS(211, CH4COMP_ATTACK);     // CH4COMP_ATTACK
	WRITE_CONFIG_ADDRESS(212, CH4COMP_RELEASE);     // CH4COMP_RELEASE
	WRITE_CONFIG_ADDRESS(213, CH4COMP_BYPASS);     // CH4COMP_BYPASS
	WRITE_CONFIG_ADDRESS(214, CH5COMP_THRESHOLD);     // CH5COMP_THRESHOLD
	WRITE_CONFIG_ADDRESS(215, CH5COMP_KNEE);     // CH5COMP_KNEE
	WRITE_CONFIG_ADDRESS(216, CH5COMP_RATIO);     // CH5COMP_RATIO
	WRITE_CONFIG_ADDRESS(217, CH5COMP_ATTACK);     // CH5COMP_ATTACK
	WRITE_CONFIG_ADDRESS(218, CH5COMP_RELEASE);     // CH5COMP_RELEASE
	WRITE_CONFIG_ADDRESS(219, CH5COMP_BYPASS);     // CH5COMP_BYPASS
	WRITE_CONFIG_ADDRESS(220, CH6COMP_THRESHOLD);     // CH6COMP_THRESHOLD
	WRITE_CONFIG_ADDRESS(221, CH6COMP_KNEE);     // CH6COMP_KNEE
	WRITE_CONFIG_ADDRESS(222, CH6COMP_RATIO);     // CH6COMP_RATIO
	WRITE_CONFIG_ADDRESS(223, CH6COMP_ATTACK);     // CH6COMP_ATTACK
	WRITE_CONFIG_ADDRESS(224, CH6COMP_RELEASE);     // CH6COMP_RELEASE
	WRITE_CONFIG_ADDRESS(225, CH6COMP_BYPASS);     // CH6COMP_BYPASS
	WRITE_CONFIG_ADDRESS(226, CH7COMP_THRESHOLD);     // CH7COMP_THRESHOLD
	WRITE_CONFIG_ADDRESS(227, CH7COMP_KNEE);     // CH7COMP_KNEE
	WRITE_CONFIG_ADDRESS(228, CH7COMP_RATIO);     // CH7COMP_RATIO
	WRITE_CONFIG_ADDRESS(229, CH7COMP_ATTACK);     // CH7COMP_ATTACK
	WRITE_CONFIG_ADDRESS(230, CH7COMP_RELEASE);     // CH7COMP_RELEASE
	WRITE_CONFIG_ADDRESS(231, CH7COMP_BYPASS);     // CH7COMP_BYPASS
	WRITE_CONFIG_ADDRESS(232, CH8COMP_THRESHOLD);     // CH8COMP_THRESHOLD
	WRITE_CONFIG_ADDRESS(233, CH8COMP_KNEE);     // CH8COMP_KNEE
	WRITE_CONFIG_ADDRESS(234, CH8COMP_RATIO);     // CH8COMP_RATIO
	WRITE_CONFIG_ADDRESS(235, CH8COMP_ATTACK);     // CH8COMP_ATTACK
	WRITE_CONFIG_ADDRESS(236, CH8COMP_RELEASE);     // CH8COMP_RELEASE
	WRITE_CONFIG_ADDRESS(237, CH8COMP_BYPASS);     // CH8COMP_BYPASS
	WRITE_CONFIG_ADDRESS(238, MIXER_SELECT0);     // MIXER_SELECT0
	WRITE_CONFIG_ADDRESS(239, MIXER_SELECT1);     // MIXER_SELECT1
	WRITE_CONFIG_ADDRESS(240, MIXER_SELECT2);     // MIXER_SELECT2
	WRITE_CONFIG_ADDRESS(241, MIXER_SELECT3);     // MIXER_SELECT3
	WRITE_CONFIG_ADDRESS(242, MIXER_SELECT4);     // MIXER_SELECT4
	WRITE_CONFIG_ADDRESS(243, MIXER_SELECT5);     // MIXER_SELECT5
	WRITE_CONFIG_ADDRESS(244, MIXER_SELECT6);     // MIXER_SELECT6
	WRITE_CONFIG_ADDRESS(245, MIXER_SELECT7);     // MIXER_SELECT7
	WRITE_CONFIG_ADDRESS(246, MIXER_SELECT8);     // MIXER_SELECT8
	WRITE_CONFIG_ADDRESS(247, MIXER_SELECT9);     // MIXER_SELECT9
	WRITE_CONFIG_ADDRESS(248, MIXER_SELECT10);     // MIXER_SELECT10
	WRITE_CONFIG_ADDRESS(249, MIXER_SELECT11);     // MIXER_SELECT11
	WRITE_CONFIG_ADDRESS(250, MIXER_SELECT12);     // MIXER_SELECT12
	WRITE_CONFIG_ADDRESS(251, MIXER_SELECT13);     // MIXER_SELECT13
	WRITE_CONFIG_ADDRESS(252, MIXER_SELECT14);     // MIXER_SELECT14
	WRITE_CONFIG_ADDRESS(253, MIXER_SELECT15);     // MIXER_SELECT15
	WRITE_CONFIG_ADDRESS(254, MIXER_SELECT16);     // MIXER_SELECT16
	WRITE_CONFIG_ADDRESS(255, MIXER_SELECT17);     // MIXER_SELECT17
	WRITE_CONFIG_ADDRESS(256, MIXER_SELECT18);     // MIXER_SELECT18
	WRITE_CONFIG_ADDRESS(257, MIXER_SELECT19);     // MIXER_SELECT19
	WRITE_CONFIG_ADDRESS(258, MIXER_SELECT20);     // MIXER_SELECT20
	WRITE_CONFIG_ADDRESS(259, MIXER_SELECT21);     // MIXER_SELECT21
	WRITE_CONFIG_ADDRESS(260, MIXER_SELECT22);     // MIXER_SELECT22
	WRITE_CONFIG_ADDRESS(261, MIXER_SELECT23);     // MIXER_SELECT23
	WRITE_CONFIG_ADDRESS(262, MIXER_SELECT24);     // MIXER_SELECT24
	WRITE_CONFIG_ADDRESS(263, MIXER_SELECT25);     // MIXER_SELECT25
	WRITE_CONFIG_ADDRESS(264, MIXER_SELECT26);     // MIXER_SELECT26
	WRITE_CONFIG_ADDRESS(265, MIXER_SELECT27);     // MIXER_SELECT27
	WRITE_CONFIG_ADDRESS(266, MIXER_SELECT28);     // MIXER_SELECT28
	WRITE_CONFIG_ADDRESS(267, MIXER_SELECT29);     // MIXER_SELECT29
	WRITE_CONFIG_ADDRESS(268, MIXER_SELECT30);     // MIXER_SELECT30
	WRITE_CONFIG_ADDRESS(269, MIXER_SELECT31);     // MIXER_SELECT31
	WRITE_CONFIG_ADDRESS(270, MIXER_SELECT32);     // MIXER_SELECT32
	WRITE_CONFIG_ADDRESS(271, MIXER_SELECT33);     // MIXER_SELECT33
	WRITE_CONFIG_ADDRESS(272, MIXER_SELECT34);     // MIXER_SELECT34
	WRITE_CONFIG_ADDRESS(273, MIXER_SELECT35);     // MIXER_SELECT35
	WRITE_CONFIG_ADDRESS(274, MIXER_SELECT36);     // MIXER_SELECT36
	WRITE_CONFIG_ADDRESS(275, MIXER_SELECT37);     // MIXER_SELECT37
	WRITE_CONFIG_ADDRESS(276, MIXER_SELECT38);     // MIXER_SELECT38
	WRITE_CONFIG_ADDRESS(277, MIXER_SELECT39);     // MIXER_SELECT39
	WRITE_CONFIG_ADDRESS(278, MIXER_SELECT40);     // MIXER_SELECT40
	WRITE_CONFIG_ADDRESS(279, MIXER_SELECT41);     // MIXER_SELECT41
	WRITE_CONFIG_ADDRESS(280, MIXER_SELECT42);     // MIXER_SELECT42
	WRITE_CONFIG_ADDRESS(281, MIXER_SELECT43);     // MIXER_SELECT43
	WRITE_CONFIG_ADDRESS(282, MIXER_SELECT44);     // MIXER_SELECT44
	WRITE_CONFIG_ADDRESS(283, MIXER_SELECT45);     // MIXER_SELECT45
	WRITE_CONFIG_ADDRESS(284, MIXER_SELECT46);     // MIXER_SELECT46
	WRITE_CONFIG_ADDRESS(285, MIXER_SELECT47);     // MIXER_SELECT47
	WRITE_CONFIG_ADDRESS(286, MIXER_SELECT48);     // MIXER_SELECT48
	WRITE_CONFIG_ADDRESS(287, MIXER_SELECT49);     // MIXER_SELECT49
	WRITE_CONFIG_ADDRESS(288, MIXER_SELECT50);     // MIXER_SELECT50
	WRITE_CONFIG_ADDRESS(289, MIXER_SELECT51);     // MIXER_SELECT51
	WRITE_CONFIG_ADDRESS(290, MIXER_SELECT52);     // MIXER_SELECT52
	WRITE_CONFIG_ADDRESS(291, MIXER_SELECT53);     // MIXER_SELECT53
	WRITE_CONFIG_ADDRESS(292, MIXER_SELECT54);     // MIXER_SELECT54
	WRITE_CONFIG_ADDRESS(293, MIXER_SELECT55);     // MIXER_SELECT55
	WRITE_CONFIG_ADDRESS(294, MIXER_SELECT56);     // MIXER_SELECT56
	WRITE_CONFIG_ADDRESS(295, MIXER_SELECT57);     // MIXER_SELECT57
	WRITE_CONFIG_ADDRESS(296, MIXER_SELECT58);     // MIXER_SELECT58
	WRITE_CONFIG_ADDRESS(297, MIXER_SELECT59);     // MIXER_SELECT59
	WRITE_CONFIG_ADDRESS(298, MIXER_SELECT60);     // MIXER_SELECT60
	WRITE_CONFIG_ADDRESS(299, MIXER_SELECT61);     // MIXER_SELECT61
	WRITE_CONFIG_ADDRESS(300, MIXER_SELECT62);     // MIXER_SELECT62
	WRITE_CONFIG_ADDRESS(301, MIXER_SELECT63);     // MIXER_SELECT63
	WRITE_CONFIG_ADDRESS(302, MIXER_SELECT64);     // MIXER_SELECT64
	WRITE_CONFIG_ADDRESS(303, MIXER_SELECT65);     // MIXER_SELECT65
	WRITE_CONFIG_ADDRESS(304, MIXER_SELECT66);     // MIXER_SELECT66
	WRITE_CONFIG_ADDRESS(305, MIXER_SELECT67);     // MIXER_SELECT67
	WRITE_CONFIG_ADDRESS(306, MIXER_SELECT68);     // MIXER_SELECT68
	WRITE_CONFIG_ADDRESS(307, MIXER_SELECT69);     // MIXER_SELECT69
	WRITE_CONFIG_ADDRESS(308, MIXER_SELECT70);     // MIXER_SELECT70
	WRITE_CONFIG_ADDRESS(309, MIXER_SELECT71);     // MIXER_SELECT71
	WRITE_CONFIG_ADDRESS(310, MIXER_SELECT72);     // MIXER_SELECT72
	WRITE_CONFIG_ADDRESS(311, MIXER_SELECT73);     // MIXER_SELECT73
	WRITE_CONFIG_ADDRESS(312, MIXER_SELECT74);     // MIXER_SELECT74
	WRITE_CONFIG_ADDRESS(313, MIXER_SELECT75);     // MIXER_SELECT75
	WRITE_CONFIG_ADDRESS(314, MIXER_SELECT76);     // MIXER_SELECT76
	WRITE_CONFIG_ADDRESS(315, MIXER_SELECT77);     // MIXER_SELECT77
	WRITE_CONFIG_ADDRESS(316, MIXER_SELECT78);     // MIXER_SELECT78
	WRITE_CONFIG_ADDRESS(317, MIXER_SELECT79);     // MIXER_SELECT79
	WRITE_CONFIG_ADDRESS(318, OUT_1_1_FILTER_B0);     // OUT_1_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(319, OUT_1_1_FILTER_B1);     // OUT_1_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(320, OUT_1_1_FILTER_B2);     // OUT_1_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(321, OUT_1_1_FILTER_NEGATIVEA1);     // OUT_1_1_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(322, OUT_1_1_FILTER_NEGATIVEA2);     // OUT_1_1_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(323, OUT_1_2_FILTER_B0);     // OUT_1_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(324, OUT_1_2_FILTER_B1);     // OUT_1_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(325, OUT_1_2_FILTER_B2);     // OUT_1_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(326, OUT_1_2_FILTER_NEGATIVEA1);     // OUT_1_2_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(327, OUT_1_2_FILTER_NEGATIVEA2);     // OUT_1_2_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(328, OUT_1_3_FILTER_B0);     // OUT_1_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(329, OUT_1_3_FILTER_B1);     // OUT_1_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(330, OUT_1_3_FILTER_B2);     // OUT_1_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(331, OUT_1_3_FILTER_NEGATIVEA1);     // OUT_1_3_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(332, OUT_1_3_FILTER_NEGATIVEA2);     // OUT_1_3_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(333, OUT_1_4_FILTER_B0);     // OUT_1_4_FILTER_B0
	WRITE_CONFIG_ADDRESS(334, OUT_1_4_FILTER_B1);     // OUT_1_4_FILTER_B1
	WRITE_CONFIG_ADDRESS(335, OUT_1_4_FILTER_B2);     // OUT_1_4_FILTER_B2
	WRITE_CONFIG_ADDRESS(336, OUT_1_4_FILTER_NEGATIVEA1);     // OUT_1_4_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(337, OUT_1_4_FILTER_NEGATIVEA2);     // OUT_1_4_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(338, OUT_1_5_FILTER_B0);     // OUT_1_5_FILTER_B0
	WRITE_CONFIG_ADDRESS(339, OUT_1_5_FILTER_B1);     // OUT_1_5_FILTER_B1
	WRITE_CONFIG_ADDRESS(340, OUT_1_5_FILTER_B2);     // OUT_1_5_FILTER_B2
	WRITE_CONFIG_ADDRESS(341, OUT_1_5_FILTER_NEGATIVEA1);     // OUT_1_5_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(342, OUT_1_5_FILTER_NEGATIVEA2);     // OUT_1_5_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(343, OUT_1_6_FILTER_B0);     // OUT_1_6_FILTER_B0
	WRITE_CONFIG_ADDRESS(344, OUT_1_6_FILTER_B1);     // OUT_1_6_FILTER_B1
	WRITE_CONFIG_ADDRESS(345, OUT_1_6_FILTER_B2);     // OUT_1_6_FILTER_B2
	WRITE_CONFIG_ADDRESS(346, OUT_1_6_FILTER_NEGATIVEA1);     // OUT_1_6_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(347, OUT_1_6_FILTER_NEGATIVEA2);     // OUT_1_6_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(348, OUT_2_1_FILTER_B0);     // OUT_2_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(349, OUT_2_1_FILTER_B1);     // OUT_2_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(350, OUT_2_1_FILTER_B2);     // OUT_2_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(351, OUT_2_1_FILTER_NEGATIVEA1);     // OUT_2_1_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(352, OUT_2_1_FILTER_NEGATIVEA2);     // OUT_2_1_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(353, OUT_2_2_FILTER_B0);     // OUT_2_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(354, OUT_2_2_FILTER_B1);     // OUT_2_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(355, OUT_2_2_FILTER_B2);     // OUT_2_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(356, OUT_2_2_FILTER_NEGATIVEA1);     // OUT_2_2_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(357, OUT_2_2_FILTER_NEGATIVEA2);     // OUT_2_2_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(358, OUT_2_3_FILTER_B0);     // OUT_2_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(359, OUT_2_3_FILTER_B1);     // OUT_2_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(360, OUT_2_3_FILTER_B2);     // OUT_2_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(361, OUT_2_3_FILTER_NEGATIVEA1);     // OUT_2_3_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(362, OUT_2_3_FILTER_NEGATIVEA2);     // OUT_2_3_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(363, OUT_2_4_FILTER_B0);     // OUT_2_4_FILTER_B0
	WRITE_CONFIG_ADDRESS(364, OUT_2_4_FILTER_B1);     // OUT_2_4_FILTER_B1
	WRITE_CONFIG_ADDRESS(365, OUT_2_4_FILTER_B2);     // OUT_2_4_FILTER_B2
	WRITE_CONFIG_ADDRESS(366, OUT_2_4_FILTER_NEGATIVEA1);     // OUT_2_4_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(367, OUT_2_4_FILTER_NEGATIVEA2);     // OUT_2_4_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(368, OUT_2_5_FILTER_B0);     // OUT_2_5_FILTER_B0
	WRITE_CONFIG_ADDRESS(369, OUT_2_5_FILTER_B1);     // OUT_2_5_FILTER_B1
	WRITE_CONFIG_ADDRESS(370, OUT_2_5_FILTER_B2);     // OUT_2_5_FILTER_B2
	WRITE_CONFIG_ADDRESS(371, OUT_2_5_FILTER_NEGATIVEA1);     // OUT_2_5_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(372, OUT_2_5_FILTER_NEGATIVEA2);     // OUT_2_5_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(373, OUT_2_6_FILTER_B0);     // OUT_2_6_FILTER_B0
	WRITE_CONFIG_ADDRESS(374, OUT_2_6_FILTER_B1);     // OUT_2_6_FILTER_B1
	WRITE_CONFIG_ADDRESS(375, OUT_2_6_FILTER_B2);     // OUT_2_6_FILTER_B2
	WRITE_CONFIG_ADDRESS(376, OUT_2_6_FILTER_NEGATIVEA1);     // OUT_2_6_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(377, OUT_2_6_FILTER_NEGATIVEA2);     // OUT_2_6_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(378, OUT_3_1_FILTER_B0);     // OUT_3_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(379, OUT_3_1_FILTER_B1);     // OUT_3_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(380, OUT_3_1_FILTER_B2);     // OUT_3_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(381, OUT_3_1_FILTER_NEGATIVEA1);     // OUT_3_1_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(382, OUT_3_1_FILTER_NEGATIVEA2);     // OUT_3_1_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(383, OUT_3_2_FILTER_B0);     // OUT_3_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(384, OUT_3_2_FILTER_B1);     // OUT_3_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(385, OUT_3_2_FILTER_B2);     // OUT_3_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(386, OUT_3_2_FILTER_NEGATIVEA1);     // OUT_3_2_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(387, OUT_3_2_FILTER_NEGATIVEA2);     // OUT_3_2_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(388, OUT_3_3_FILTER_B0);     // OUT_3_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(389, OUT_3_3_FILTER_B1);     // OUT_3_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(390, OUT_3_3_FILTER_B2);     // OUT_3_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(391, OUT_3_3_FILTER_NEGATIVEA1);     // OUT_3_3_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(392, OUT_3_3_FILTER_NEGATIVEA2);     // OUT_3_3_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(393, OUT_3_4_FILTER_B0);     // OUT_3_4_FILTER_B0
	WRITE_CONFIG_ADDRESS(394, OUT_3_4_FILTER_B1);     // OUT_3_4_FILTER_B1
	WRITE_CONFIG_ADDRESS(395, OUT_3_4_FILTER_B2);     // OUT_3_4_FILTER_B2
	WRITE_CONFIG_ADDRESS(396, OUT_3_4_FILTER_NEGATIVEA1);     // OUT_3_4_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(397, OUT_3_4_FILTER_NEGATIVEA2);     // OUT_3_4_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(398, OUT_3_5_FILTER_B0);     // OUT_3_5_FILTER_B0
	WRITE_CONFIG_ADDRESS(399, OUT_3_5_FILTER_B1);     // OUT_3_5_FILTER_B1
	WRITE_CONFIG_ADDRESS(400, OUT_3_5_FILTER_B2);     // OUT_3_5_FILTER_B2
	WRITE_CONFIG_ADDRESS(401, OUT_3_5_FILTER_NEGATIVEA1);     // OUT_3_5_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(402, OUT_3_5_FILTER_NEGATIVEA2);     // OUT_3_5_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(403, OUT_3_6_FILTER_B0);     // OUT_3_6_FILTER_B0
	WRITE_CONFIG_ADDRESS(404, OUT_3_6_FILTER_B1);     // OUT_3_6_FILTER_B1
	WRITE_CONFIG_ADDRESS(405, OUT_3_6_FILTER_B2);     // OUT_3_6_FILTER_B2
	WRITE_CONFIG_ADDRESS(406, OUT_3_6_FILTER_NEGATIVEA1);     // OUT_3_6_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(407, OUT_3_6_FILTER_NEGATIVEA2);     // OUT_3_6_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(408, OUT_4_1_FILTER_B0);     // OUT_4_1_FILTER_B0
	WRITE_CONFIG_ADDRESS(409, OUT_4_1_FILTER_B1);     // OUT_4_1_FILTER_B1
	WRITE_CONFIG_ADDRESS(410, OUT_4_1_FILTER_B2);     // OUT_4_1_FILTER_B2
	WRITE_CONFIG_ADDRESS(411, OUT_4_1_FILTER_NEGATIVEA1);     // OUT_4_1_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(412, OUT_4_1_FILTER_NEGATIVEA2);     // OUT_4_1_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(413, OUT_4_2_FILTER_B0);     // OUT_4_2_FILTER_B0
	WRITE_CONFIG_ADDRESS(414, OUT_4_2_FILTER_B1);     // OUT_4_2_FILTER_B1
	WRITE_CONFIG_ADDRESS(415, OUT_4_2_FILTER_B2);     // OUT_4_2_FILTER_B2
	WRITE_CONFIG_ADDRESS(416, OUT_4_2_FILTER_NEGATIVEA1);     // OUT_4_2_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(417, OUT_4_2_FILTER_NEGATIVEA2);     // OUT_4_2_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(418, OUT_4_3_FILTER_B0);     // OUT_4_3_FILTER_B0
	WRITE_CONFIG_ADDRESS(419, OUT_4_3_FILTER_B1);     // OUT_4_3_FILTER_B1
	WRITE_CONFIG_ADDRESS(420, OUT_4_3_FILTER_B2);     // OUT_4_3_FILTER_B2
	WRITE_CONFIG_ADDRESS(421, OUT_4_3_FILTER_NEGATIVEA1);     // OUT_4_3_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(422, OUT_4_3_FILTER_NEGATIVEA2);     // OUT_4_3_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(423, OUT_4_4_FILTER_B0);     // OUT_4_4_FILTER_B0
	WRITE_CONFIG_ADDRESS(424, OUT_4_4_FILTER_B1);     // OUT_4_4_FILTER_B1
	WRITE_CONFIG_ADDRESS(425, OUT_4_4_FILTER_B2);     // OUT_4_4_FILTER_B2
	WRITE_CONFIG_ADDRESS(426, OUT_4_4_FILTER_NEGATIVEA1);     // OUT_4_4_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(427, OUT_4_4_FILTER_NEGATIVEA2);     // OUT_4_4_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(428, OUT_4_5_FILTER_B0);     // OUT_4_5_FILTER_B0
	WRITE_CONFIG_ADDRESS(429, OUT_4_5_FILTER_B1);     // OUT_4_5_FILTER_B1
	WRITE_CONFIG_ADDRESS(430, OUT_4_5_FILTER_B2);     // OUT_4_5_FILTER_B2
	WRITE_CONFIG_ADDRESS(431, OUT_4_5_FILTER_NEGATIVEA1);     // OUT_4_5_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(432, OUT_4_5_FILTER_NEGATIVEA2);     // OUT_4_5_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(433, OUT_4_6_FILTER_B0);     // OUT_4_6_FILTER_B0
	WRITE_CONFIG_ADDRESS(434, OUT_4_6_FILTER_B1);     // OUT_4_6_FILTER_B1
	WRITE_CONFIG_ADDRESS(435, OUT_4_6_FILTER_B2);     // OUT_4_6_FILTER_B2
	WRITE_CONFIG_ADDRESS(436, OUT_4_6_FILTER_NEGATIVEA1);     // OUT_4_6_FILTER_NEGATIVEA1
	WRITE_CONFIG_ADDRESS(437, OUT_4_6_FILTER_NEGATIVEA2);     // OUT_4_6_FILTER_NEGATIVEA2
	WRITE_CONFIG_ADDRESS(438, CH1LIM_THRESHOLD);     // CH1LIM_THRESHOLD
	WRITE_CONFIG_ADDRESS(439, CH1LIM_KNEE);     // CH1LIM_KNEE
	WRITE_CONFIG_ADDRESS(440, CH1LIM_RATIO);     // CH1LIM_RATIO
	WRITE_CONFIG_ADDRESS(441, CH1LIM_ATTACK);     // CH1LIM_ATTACK
	WRITE_CONFIG_ADDRESS(442, CH1LIM_RELEASE);     // CH1LIM_RELEASE
	WRITE_CONFIG_ADDRESS(443, CH1LIM_BYPASS);     // CH1LIM_BYPASS
	WRITE_CONFIG_ADDRESS(444, CH2LIM_THRESHOLD);     // CH2LIM_THRESHOLD
	WRITE_CONFIG_ADDRESS(445, CH2LIM_KNEE);     // CH2LIM_KNEE
	WRITE_CONFIG_ADDRESS(446, CH2LIM_RATIO);     // CH2LIM_RATIO
	WRITE_CONFIG_ADDRESS(447, CH2LIM_ATTACK);     // CH2LIM_ATTACK
	WRITE_CONFIG_ADDRESS(448, CH2LIM_RELEASE);     // CH2LIM_RELEASE
	WRITE_CONFIG_ADDRESS(449, CH2LIM_BYPASS);     // CH2LIM_BYPASS
	WRITE_CONFIG_ADDRESS(450, CH3LIM_THRESHOLD);     // CH3LIM_THRESHOLD
	WRITE_CONFIG_ADDRESS(451, CH3LIM_KNEE);     // CH3LIM_KNEE
	WRITE_CONFIG_ADDRESS(452, CH3LIM_RATIO);     // CH3LIM_RATIO
	WRITE_CONFIG_ADDRESS(453, CH3LIM_ATTACK);     // CH3LIM_ATTACK
	WRITE_CONFIG_ADDRESS(454, CH3LIM_RELEASE);     // CH3LIM_RELEASE
	WRITE_CONFIG_ADDRESS(455, CH3LIM_BYPASS);     // CH3LIM_BYPASS
	WRITE_CONFIG_ADDRESS(456, CH4LIM_THRESHOLD);     // CH4LIM_THRESHOLD
	WRITE_CONFIG_ADDRESS(457, CH4LIM_KNEE);     // CH4LIM_KNEE
	WRITE_CONFIG_ADDRESS(458, CH4LIM_RATIO);     // CH4LIM_RATIO
	WRITE_CONFIG_ADDRESS(459, CH4LIM_ATTACK);     // CH4LIM_ATTACK
	WRITE_CONFIG_ADDRESS(460, CH4LIM_RELEASE);     // CH4LIM_RELEASE
	WRITE_CONFIG_ADDRESS(461, CH4LIM_BYPASS);     // CH4LIM_BYPASS

	WRITE_CONFIG_ADDRESS(462, DELAY_CH1);     // DELAY_CH1
	WRITE_CONFIG_ADDRESS(463, DELAY_BYPASS_CH1);     // DELAY_BYPASS_CH1
	WRITE_CONFIG_ADDRESS(464, DELAY_CH2);     // DELAY_CH2
	WRITE_CONFIG_ADDRESS(465, DELAY_BYPASS_CH2);     // DELAY_BYPASS_CH2
	WRITE_CONFIG_ADDRESS(466, DELAY_CH3);     // DELAY_CH3
	WRITE_CONFIG_ADDRESS(467, DELAY_BYPASS_CH3);     // DELAY_BYPASS_CH3
	WRITE_CONFIG_ADDRESS(468, DELAY_CH4);     // DELAY_CH4
	WRITE_CONFIG_ADDRESS(469, DELAY_BYPASS_CH4);     // DELAY_BYPASS_CH4
	
	WRITE_CONFIG_ADDRESS(470, BRIDGEROUTER_SELECT0);     // BRIDGEROUTER_SELECT0
	WRITE_CONFIG_ADDRESS(471, BRIDGEROUTER_SELECT1);     // BRIDGEROUTER_SELECT1
	WRITE_CONFIG_ADDRESS(472, BRIDGEROUTER_SELECT2);     // BRIDGEROUTER_SELECT2
	WRITE_CONFIG_ADDRESS(473, BRIDGEROUTER_SELECT3);     // BRIDGEROUTER_SELECT3
	WRITE_CONFIG_ADDRESS(474, GEN_PINK_GAIN);     // GEN_PINK_GAIN
	WRITE_CONFIG_ADDRESS(475, GEN_SINE_OMEGA);     // GEN_SINE_OMEGA
	WRITE_CONFIG_ADDRESS(476, GEN_SINE_GAIN);     // GEN_SINE_GAIN
	WRITE_CONFIG_ADDRESS(477, SEVENTYVHP_BYPASS);     // 70VHP_BYPASS
	WRITE_CONFIG_ADDRESS(478, MUTE_OUTPUTS);     // MUTE_OUTPUTS

}