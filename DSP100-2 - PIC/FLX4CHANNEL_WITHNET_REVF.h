
/** 'MIXER' **/
#define MIXER_hold_count  0x0001   /*signed integer*/
#define MIXER_ramp  0x0002   /*signed 1.31 format*/
#define MIXER_send_gain_0  0x0003   /*signed 3.29 format*/
#define MIXER_send_gain_1  0x0004   /*signed 3.29 format*/
#define MIXER_send_gain_2  0x0005   /*signed 3.29 format*/
#define MIXER_send_gain_3  0x0006   /*signed 3.29 format*/
#define MIXER_send_gain_4  0x0007   /*signed 3.29 format*/
#define MIXER_send_gain_5  0x0008   /*signed 3.29 format*/
#define MIXER_send_gain_6  0x0009   /*signed 3.29 format*/
#define MIXER_send_gain_7  0x000a   /*signed 3.29 format*/
#define MIXER_send_gain_8  0x000b   /*signed 3.29 format*/
#define MIXER_send_gain_9  0x000c   /*signed 3.29 format*/
#define MIXER_send_gain_10  0x000d   /*signed 3.29 format*/
#define MIXER_send_gain_11  0x000e   /*signed 3.29 format*/
#define MIXER_send_gain_12  0x000f   /*signed 3.29 format*/
#define MIXER_send_gain_13  0x0010   /*signed 3.29 format*/
#define MIXER_send_gain_14  0x0011   /*signed 3.29 format*/
#define MIXER_send_gain_15  0x0012   /*signed 3.29 format*/
#define MIXER_send_gain_16  0x0013   /*signed 3.29 format*/
#define MIXER_send_gain_17  0x0014   /*signed 3.29 format*/
#define MIXER_send_gain_18  0x0015   /*signed 3.29 format*/
#define MIXER_send_gain_19  0x0016   /*signed 3.29 format*/
#define MIXER_send_gain_20  0x0017   /*signed 3.29 format*/
#define MIXER_send_gain_21  0x0018   /*signed 3.29 format*/
#define MIXER_send_gain_22  0x0019   /*signed 3.29 format*/
#define MIXER_send_gain_23  0x001a   /*signed 3.29 format*/
#define MIXER_send_gain_24  0x001b   /*signed 3.29 format*/
#define MIXER_send_gain_25  0x001c   /*signed 3.29 format*/
#define MIXER_send_gain_26  0x001d   /*signed 3.29 format*/
#define MIXER_send_gain_27  0x001e   /*signed 3.29 format*/
#define MIXER_send_gain_28  0x001f   /*signed 3.29 format*/
#define MIXER_send_gain_29  0x0020   /*signed 3.29 format*/
#define MIXER_send_gain_30  0x0021   /*signed 3.29 format*/
#define MIXER_send_gain_31  0x0022   /*signed 3.29 format*/
#define MIXER_send_gain_32  0x0023   /*signed 3.29 format*/
#define MIXER_send_gain_33  0x0024   /*signed 3.29 format*/
#define MIXER_send_gain_34  0x0025   /*signed 3.29 format*/
#define MIXER_send_gain_35  0x0026   /*signed 3.29 format*/
#define MIXER_send_gain_36  0x0027   /*signed 3.29 format*/
#define MIXER_send_gain_37  0x0028   /*signed 3.29 format*/
#define MIXER_send_gain_38  0x0029   /*signed 3.29 format*/
#define MIXER_send_gain_39  0x002a   /*signed 3.29 format*/
#define MIXER_send_gain_40  0x002b   /*signed 3.29 format*/
#define MIXER_send_gain_41  0x002c   /*signed 3.29 format*/
#define MIXER_send_gain_42  0x002d   /*signed 3.29 format*/
#define MIXER_send_gain_43  0x002e   /*signed 3.29 format*/
#define MIXER_send_gain_44  0x002f   /*signed 3.29 format*/
#define MIXER_send_gain_45  0x0030   /*signed 3.29 format*/
#define MIXER_send_gain_46  0x0031   /*signed 3.29 format*/
#define MIXER_send_gain_47  0x0032   /*signed 3.29 format*/
#define MIXER_clips_0  0x0033   /*READ-ONLY: signed integer*/
#define MIXER_clips_1  0x0034   /*READ-ONLY: signed integer*/
#define MIXER_clips_2  0x0035   /*READ-ONLY: signed integer*/
#define MIXER_clips_3  0x0036   /*READ-ONLY: signed integer*/
#define MIXER_clips_4  0x0037   /*READ-ONLY: signed integer*/
#define MIXER_clips_5  0x0038   /*READ-ONLY: signed integer*/

/** 'MIXER_OUT_METER' **/
#define MIXER_OUT_METER_coeff_rms  0x0039   /*signed 1.31 format*/
#define MIXER_OUT_METER_coeff_peak  0x003a   /*signed 1.31 format*/
#define MIXER_OUT_METER_hold_count  0x003b   /*signed integer*/
#define MIXER_OUT_METER_infinite_peak_hold  0x003c   /*signed integer*/
#define MIXER_OUT_METER_ms_0  0x003d   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_0  0x003e   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_hold_0  0x003f   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_hold_0  0x0040   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_1  0x0041   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_1  0x0042   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_hold_1  0x0043   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_hold_1  0x0044   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_2  0x0045   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_2  0x0046   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_hold_2  0x0047   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_hold_2  0x0048   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_3  0x0049   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_3  0x004a   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_hold_3  0x004b   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_hold_3  0x004c   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_4  0x004d   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_4  0x004e   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_hold_4  0x004f   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_hold_4  0x0050   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_5  0x0051   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_5  0x0052   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_ms_hold_5  0x0053   /*READ-ONLY: signed 1.31 format*/
#define MIXER_OUT_METER_pk_hold_5  0x0054   /*READ-ONLY: signed 1.31 format*/

/** 'PREMIX_METER' **/
#define PREMIX_METER_coeff_rms  0x0055   /*signed 1.31 format*/
#define PREMIX_METER_coeff_peak  0x0056   /*signed 1.31 format*/
#define PREMIX_METER_hold_count  0x0057   /*signed integer*/
#define PREMIX_METER_infinite_peak_hold  0x0058   /*signed integer*/
#define PREMIX_METER_ms_0  0x0059   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_0  0x005a   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_hold_0  0x005b   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_hold_0  0x005c   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_1  0x005d   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_1  0x005e   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_hold_1  0x005f   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_hold_1  0x0060   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_2  0x0061   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_2  0x0062   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_hold_2  0x0063   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_hold_2  0x0064   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_3  0x0065   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_3  0x0066   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_hold_3  0x0067   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_hold_3  0x0068   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_4  0x0069   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_4  0x006a   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_hold_4  0x006b   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_hold_4  0x006c   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_5  0x006d   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_5  0x006e   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_ms_hold_5  0x006f   /*READ-ONLY: signed 1.31 format*/
#define PREMIX_METER_pk_hold_5  0x0070   /*READ-ONLY: signed 1.31 format*/

/** 'COMP_OUT_METER' **/
#define COMP_OUT_METER_coeff_rms  0x0071   /*signed 1.31 format*/
#define COMP_OUT_METER_coeff_peak  0x0072   /*signed 1.31 format*/
#define COMP_OUT_METER_hold_count  0x0073   /*signed integer*/
#define COMP_OUT_METER_infinite_peak_hold  0x0074   /*signed integer*/
#define COMP_OUT_METER_ms_0  0x0075   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_0  0x0076   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_hold_0  0x0077   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_hold_0  0x0078   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_1  0x0079   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_1  0x007a   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_hold_1  0x007b   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_hold_1  0x007c   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_2  0x007d   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_2  0x007e   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_hold_2  0x007f   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_hold_2  0x0080   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_3  0x0081   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_3  0x0082   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_hold_3  0x0083   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_hold_3  0x0084   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_4  0x0085   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_4  0x0086   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_hold_4  0x0087   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_hold_4  0x0088   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_5  0x0089   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_5  0x008a   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_ms_hold_5  0x008b   /*READ-ONLY: signed 1.31 format*/
#define COMP_OUT_METER_pk_hold_5  0x008c   /*READ-ONLY: signed 1.31 format*/

/** 'COMP_IN_METER' **/
#define COMP_IN_METER_coeff_rms  0x008d   /*signed 1.31 format*/
#define COMP_IN_METER_coeff_peak  0x008e   /*signed 1.31 format*/
#define COMP_IN_METER_hold_count  0x008f   /*signed integer*/
#define COMP_IN_METER_infinite_peak_hold  0x0090   /*signed integer*/
#define COMP_IN_METER_ms_0  0x0091   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_0  0x0092   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_hold_0  0x0093   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_hold_0  0x0094   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_1  0x0095   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_1  0x0096   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_hold_1  0x0097   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_hold_1  0x0098   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_2  0x0099   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_2  0x009a   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_hold_2  0x009b   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_hold_2  0x009c   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_3  0x009d   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_3  0x009e   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_hold_3  0x009f   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_hold_3  0x00a0   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_4  0x00a1   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_4  0x00a2   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_hold_4  0x00a3   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_hold_4  0x00a4   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_5  0x00a5   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_5  0x00a6   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_ms_hold_5  0x00a7   /*READ-ONLY: signed 1.31 format*/
#define COMP_IN_METER_pk_hold_5  0x00a8   /*READ-ONLY: signed 1.31 format*/

/** 'DUCKER_METER' **/
#define DUCKER_METER_coeff_rms  0x00a9   /*signed 1.31 format*/
#define DUCKER_METER_coeff_peak  0x00aa   /*signed 1.31 format*/
#define DUCKER_METER_hold_count  0x00ab   /*signed integer*/
#define DUCKER_METER_infinite_peak_hold  0x00ac   /*signed integer*/
#define DUCKER_METER_ms_0  0x00ad   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_0  0x00ae   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_hold_0  0x00af   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_hold_0  0x00b0   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_1  0x00b1   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_1  0x00b2   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_hold_1  0x00b3   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_hold_1  0x00b4   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_2  0x00b5   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_2  0x00b6   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_hold_2  0x00b7   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_hold_2  0x00b8   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_3  0x00b9   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_3  0x00ba   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_hold_3  0x00bb   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_hold_3  0x00bc   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_4  0x00bd   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_4  0x00be   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_hold_4  0x00bf   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_hold_4  0x00c0   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_5  0x00c1   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_5  0x00c2   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_ms_hold_5  0x00c3   /*READ-ONLY: signed 1.31 format*/
#define DUCKER_METER_pk_hold_5  0x00c4   /*READ-ONLY: signed 1.31 format*/

/** 'INPUT_METER2' **/
#define INPUT_METER2_coeff_rms  0x00c5   /*signed 1.31 format*/
#define INPUT_METER2_coeff_peak  0x00c6   /*signed 1.31 format*/
#define INPUT_METER2_hold_count  0x00c7   /*signed integer*/
#define INPUT_METER2_infinite_peak_hold  0x00c8   /*signed integer*/
#define INPUT_METER2_ms_0  0x00c9   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_0  0x00ca   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_hold_0  0x00cb   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_hold_0  0x00cc   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_1  0x00cd   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_1  0x00ce   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_hold_1  0x00cf   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_hold_1  0x00d0   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_2  0x00d1   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_2  0x00d2   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_hold_2  0x00d3   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_hold_2  0x00d4   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_3  0x00d5   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_3  0x00d6   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_hold_3  0x00d7   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_hold_3  0x00d8   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_4  0x00d9   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_4  0x00da   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_hold_4  0x00db   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_hold_4  0x00dc   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_5  0x00dd   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_5  0x00de   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_ms_hold_5  0x00df   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER2_pk_hold_5  0x00e0   /*READ-ONLY: signed 1.31 format*/

/** 'INPUT_METER' **/
#define INPUT_METER_coeff_rms  0x00e1   /*signed 1.31 format*/
#define INPUT_METER_coeff_peak  0x00e2   /*signed 1.31 format*/
#define INPUT_METER_hold_count  0x00e3   /*signed integer*/
#define INPUT_METER_infinite_peak_hold  0x00e4   /*signed integer*/
#define INPUT_METER_ms_0  0x00e5   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_0  0x00e6   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_hold_0  0x00e7   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_hold_0  0x00e8   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_1  0x00e9   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_1  0x00ea   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_hold_1  0x00eb   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_hold_1  0x00ec   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_2  0x00ed   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_2  0x00ee   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_hold_2  0x00ef   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_hold_2  0x00f0   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_3  0x00f1   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_3  0x00f2   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_hold_3  0x00f3   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_hold_3  0x00f4   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_4  0x00f5   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_4  0x00f6   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_hold_4  0x00f7   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_hold_4  0x00f8   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_5  0x00f9   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_5  0x00fa   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_ms_hold_5  0x00fb   /*READ-ONLY: signed 1.31 format*/
#define INPUT_METER_pk_hold_5  0x00fc   /*READ-ONLY: signed 1.31 format*/

/** 'BRIDGE_METER' **/
#define BRIDGE_METER_coeff_rms  0x00fd   /*signed 1.31 format*/
#define BRIDGE_METER_coeff_peak  0x00fe   /*signed 1.31 format*/
#define BRIDGE_METER_hold_count  0x00ff   /*signed integer*/
#define BRIDGE_METER_infinite_peak_hold  0x0100   /*signed integer*/
#define BRIDGE_METER_ms_0  0x0101   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_pk_0  0x0102   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_ms_hold_0  0x0103   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_pk_hold_0  0x0104   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_ms_1  0x0105   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_pk_1  0x0106   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_ms_hold_1  0x0107   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_pk_hold_1  0x0108   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_ms_2  0x0109   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_pk_2  0x010a   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_ms_hold_2  0x010b   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_pk_hold_2  0x010c   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_ms_3  0x010d   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_pk_3  0x010e   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_ms_hold_3  0x010f   /*READ-ONLY: signed 1.31 format*/
#define BRIDGE_METER_pk_hold_3  0x0110   /*READ-ONLY: signed 1.31 format*/

/** 'OUTPUT_METER' **/
#define OUTPUT_METER_coeff_rms  0x0111   /*signed 1.31 format*/
#define OUTPUT_METER_coeff_peak  0x0112   /*signed 1.31 format*/
#define OUTPUT_METER_hold_count  0x0113   /*signed integer*/
#define OUTPUT_METER_infinite_peak_hold  0x0114   /*signed integer*/
#define OUTPUT_METER_ms_0  0x0115   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_pk_0  0x0116   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_ms_hold_0  0x0117   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_pk_hold_0  0x0118   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_ms_1  0x0119   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_pk_1  0x011a   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_ms_hold_1  0x011b   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_pk_hold_1  0x011c   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_ms_2  0x011d   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_pk_2  0x011e   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_ms_hold_2  0x011f   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_pk_hold_2  0x0120   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_ms_3  0x0121   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_pk_3  0x0122   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_ms_hold_3  0x0123   /*READ-ONLY: signed 1.31 format*/
#define OUTPUT_METER_pk_hold_3  0x0124   /*READ-ONLY: signed 1.31 format*/

/** 'DELAY_METER' **/
#define DELAY_METER_coeff_rms  0x0125   /*signed 1.31 format*/
#define DELAY_METER_coeff_peak  0x0126   /*signed 1.31 format*/
#define DELAY_METER_hold_count  0x0127   /*signed integer*/
#define DELAY_METER_infinite_peak_hold  0x0128   /*signed integer*/
#define DELAY_METER_ms_0  0x0129   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_pk_0  0x012a   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_ms_hold_0  0x012b   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_pk_hold_0  0x012c   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_ms_1  0x012d   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_pk_1  0x012e   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_ms_hold_1  0x012f   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_pk_hold_1  0x0130   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_ms_2  0x0131   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_pk_2  0x0132   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_ms_hold_2  0x0133   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_pk_hold_2  0x0134   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_ms_3  0x0135   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_pk_3  0x0136   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_ms_hold_3  0x0137   /*READ-ONLY: signed 1.31 format*/
#define DELAY_METER_pk_hold_3  0x0138   /*READ-ONLY: signed 1.31 format*/

/** 'LIM_OUT_METER' **/
#define LIM_OUT_METER_coeff_rms  0x0139   /*signed 1.31 format*/
#define LIM_OUT_METER_coeff_peak  0x013a   /*signed 1.31 format*/
#define LIM_OUT_METER_hold_count  0x013b   /*signed integer*/
#define LIM_OUT_METER_infinite_peak_hold  0x013c   /*signed integer*/
#define LIM_OUT_METER_ms_0  0x013d   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_pk_0  0x013e   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_ms_hold_0  0x013f   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_pk_hold_0  0x0140   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_ms_1  0x0141   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_pk_1  0x0142   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_ms_hold_1  0x0143   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_pk_hold_1  0x0144   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_ms_2  0x0145   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_pk_2  0x0146   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_ms_hold_2  0x0147   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_pk_hold_2  0x0148   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_ms_3  0x0149   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_pk_3  0x014a   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_ms_hold_3  0x014b   /*READ-ONLY: signed 1.31 format*/
#define LIM_OUT_METER_pk_hold_3  0x014c   /*READ-ONLY: signed 1.31 format*/

/** 'LIM_IN_METER' **/
#define LIM_IN_METER_coeff_rms  0x014d   /*signed 1.31 format*/
#define LIM_IN_METER_coeff_peak  0x014e   /*signed 1.31 format*/
#define LIM_IN_METER_hold_count  0x014f   /*signed integer*/
#define LIM_IN_METER_infinite_peak_hold  0x0150   /*signed integer*/
#define LIM_IN_METER_ms_0  0x0151   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_pk_0  0x0152   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_ms_hold_0  0x0153   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_pk_hold_0  0x0154   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_ms_1  0x0155   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_pk_1  0x0156   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_ms_hold_1  0x0157   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_pk_hold_1  0x0158   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_ms_2  0x0159   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_pk_2  0x015a   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_ms_hold_2  0x015b   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_pk_hold_2  0x015c   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_ms_3  0x015d   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_pk_3  0x015e   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_ms_hold_3  0x015f   /*READ-ONLY: signed 1.31 format*/
#define LIM_IN_METER_pk_hold_3  0x0160   /*READ-ONLY: signed 1.31 format*/

/** 'TRIM_METER' **/
#define TRIM_METER_coeff_rms  0x0161   /*signed 1.31 format*/
#define TRIM_METER_coeff_peak  0x0162   /*signed 1.31 format*/
#define TRIM_METER_hold_count  0x0163   /*signed integer*/
#define TRIM_METER_infinite_peak_hold  0x0164   /*signed integer*/
#define TRIM_METER_ms_0  0x0165   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_pk_0  0x0166   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_ms_hold_0  0x0167   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_pk_hold_0  0x0168   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_ms_1  0x0169   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_pk_1  0x016a   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_ms_hold_1  0x016b   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_pk_hold_1  0x016c   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_ms_2  0x016d   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_pk_2  0x016e   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_ms_hold_2  0x016f   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_pk_hold_2  0x0170   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_ms_3  0x0171   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_pk_3  0x0172   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_ms_hold_3  0x0173   /*READ-ONLY: signed 1.31 format*/
#define TRIM_METER_pk_hold_3  0x0174   /*READ-ONLY: signed 1.31 format*/

/** 'PROCESSING' **/
#define PROCESSING_hold_count_24dB_Gain  0x0175   /*signed integer*/
#define PROCESSING_clip_0_24dB_Gain  0x0176   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_1_24dB_Gain  0x0177   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_2_24dB_Gain  0x0178   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_3_24dB_Gain  0x0179   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_4_24dB_Gain  0x017a   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_5_24dB_Gain  0x017b   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_6_24dB_Gain  0x017c   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_7_24dB_Gain  0x017d   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_8_24dB_Gain  0x017e   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_9_24dB_Gain  0x017f   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_10_24dB_Gain  0x0180   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_11_24dB_Gain  0x0181   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_12_24dB_Gain  0x0182   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_13_24dB_Gain  0x0183   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_14_24dB_Gain  0x0184   /*READ-ONLY: signed integer*/
#define PROCESSING_clip_15_24dB_Gain  0x0185   /*READ-ONLY: signed integer*/

/** 'CH4LIM' **/
#define CH4LIM_threshold  0x0186   /*signed 9.23 format*/
#define CH4LIM_knee_size  0x0187   /*signed 9.23 format*/
#define CH4LIM_dsp_compress_ratio  0x0188   /*signed 1.31 format*/
#define CH4LIM_dsp_attack_coef  0x0189   /*signed 1.31 format*/
#define CH4LIM_dsp_release_coef  0x018a   /*signed 1.31 format*/
#define CH4LIM_dsp_bypass  0x018b   /*signed integer*/
#define CH4LIM_region  0x018c   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH4LIM_gain_reduction  0x018d   /*READ-ONLY: signed 1.31 format*/

/** 'CH3LIM' **/
#define CH3LIM_threshold  0x018e   /*signed 9.23 format*/
#define CH3LIM_knee_size  0x018f   /*signed 9.23 format*/
#define CH3LIM_dsp_compress_ratio  0x0190   /*signed 1.31 format*/
#define CH3LIM_dsp_attack_coef  0x0191   /*signed 1.31 format*/
#define CH3LIM_dsp_release_coef  0x0192   /*signed 1.31 format*/
#define CH3LIM_dsp_bypass  0x0193   /*signed integer*/
#define CH3LIM_region  0x0194   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH3LIM_gain_reduction  0x0195   /*READ-ONLY: signed 1.31 format*/

/** 'CH2LIM' **/
#define CH2LIM_threshold  0x0196   /*signed 9.23 format*/
#define CH2LIM_knee_size  0x0197   /*signed 9.23 format*/
#define CH2LIM_dsp_compress_ratio  0x0198   /*signed 1.31 format*/
#define CH2LIM_dsp_attack_coef  0x0199   /*signed 1.31 format*/
#define CH2LIM_dsp_release_coef  0x019a   /*signed 1.31 format*/
#define CH2LIM_dsp_bypass  0x019b   /*signed integer*/
#define CH2LIM_region  0x019c   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH2LIM_gain_reduction  0x019d   /*READ-ONLY: signed 1.31 format*/

/** 'CH1LIM' **/
#define CH1LIM_threshold  0x019e   /*signed 9.23 format*/
#define CH1LIM_knee_size  0x019f   /*signed 9.23 format*/
#define CH1LIM_dsp_compress_ratio  0x01a0   /*signed 1.31 format*/
#define CH1LIM_dsp_attack_coef  0x01a1   /*signed 1.31 format*/
#define CH1LIM_dsp_release_coef  0x01a2   /*signed 1.31 format*/
#define CH1LIM_dsp_bypass  0x01a3   /*signed integer*/
#define CH1LIM_region  0x01a4   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH1LIM_gain_reduction  0x01a5   /*READ-ONLY: signed 1.31 format*/

/** 'CH6COMP' **/
#define CH6COMP_threshold  0x01a6   /*signed 9.23 format*/
#define CH6COMP_knee_size  0x01a7   /*signed 9.23 format*/
#define CH6COMP_dsp_compress_ratio  0x01a8   /*signed 1.31 format*/
#define CH6COMP_dsp_attack_coef  0x01a9   /*signed 1.31 format*/
#define CH6COMP_dsp_release_coef  0x01aa   /*signed 1.31 format*/
#define CH6COMP_dsp_bypass  0x01ab   /*signed integer*/
#define CH6COMP_region  0x01ac   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH6COMP_gain_reduction  0x01ad   /*READ-ONLY: signed 1.31 format*/

/** 'CH5COMP' **/
#define CH5COMP_threshold  0x01ae   /*signed 9.23 format*/
#define CH5COMP_knee_size  0x01af   /*signed 9.23 format*/
#define CH5COMP_dsp_compress_ratio  0x01b0   /*signed 1.31 format*/
#define CH5COMP_dsp_attack_coef  0x01b1   /*signed 1.31 format*/
#define CH5COMP_dsp_release_coef  0x01b2   /*signed 1.31 format*/
#define CH5COMP_dsp_bypass  0x01b3   /*signed integer*/
#define CH5COMP_region  0x01b4   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH5COMP_gain_reduction  0x01b5   /*READ-ONLY: signed 1.31 format*/

/** 'CH4COMP' **/
#define CH4COMP_threshold  0x01b6   /*signed 9.23 format*/
#define CH4COMP_knee_size  0x01b7   /*signed 9.23 format*/
#define CH4COMP_dsp_compress_ratio  0x01b8   /*signed 1.31 format*/
#define CH4COMP_dsp_attack_coef  0x01b9   /*signed 1.31 format*/
#define CH4COMP_dsp_release_coef  0x01ba   /*signed 1.31 format*/
#define CH4COMP_dsp_bypass  0x01bb   /*signed integer*/
#define CH4COMP_region  0x01bc   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH4COMP_gain_reduction  0x01bd   /*READ-ONLY: signed 1.31 format*/

/** 'CH3COMP' **/
#define CH3COMP_threshold  0x01be   /*signed 9.23 format*/
#define CH3COMP_knee_size  0x01bf   /*signed 9.23 format*/
#define CH3COMP_dsp_compress_ratio  0x01c0   /*signed 1.31 format*/
#define CH3COMP_dsp_attack_coef  0x01c1   /*signed 1.31 format*/
#define CH3COMP_dsp_release_coef  0x01c2   /*signed 1.31 format*/
#define CH3COMP_dsp_bypass  0x01c3   /*signed integer*/
#define CH3COMP_region  0x01c4   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH3COMP_gain_reduction  0x01c5   /*READ-ONLY: signed 1.31 format*/

/** 'CH2COMP' **/
#define CH2COMP_threshold  0x01c6   /*signed 9.23 format*/
#define CH2COMP_knee_size  0x01c7   /*signed 9.23 format*/
#define CH2COMP_dsp_compress_ratio  0x01c8   /*signed 1.31 format*/
#define CH2COMP_dsp_attack_coef  0x01c9   /*signed 1.31 format*/
#define CH2COMP_dsp_release_coef  0x01ca   /*signed 1.31 format*/
#define CH2COMP_dsp_bypass  0x01cb   /*signed integer*/
#define CH2COMP_region  0x01cc   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH2COMP_gain_reduction  0x01cd   /*READ-ONLY: signed 1.31 format*/

/** 'CH1COMP' **/
#define CH1COMP_threshold  0x01ce   /*signed 9.23 format*/
#define CH1COMP_knee_size  0x01cf   /*signed 9.23 format*/
#define CH1COMP_dsp_compress_ratio  0x01d0   /*signed 1.31 format*/
#define CH1COMP_dsp_attack_coef  0x01d1   /*signed 1.31 format*/
#define CH1COMP_dsp_release_coef  0x01d2   /*signed 1.31 format*/
#define CH1COMP_dsp_bypass  0x01d3   /*signed integer*/
#define CH1COMP_region  0x01d4   /*READ-ONLY: signed integer signal indicator, 0 - below; 1 - knee; 2 - above*/
#define CH1COMP_gain_reduction  0x01d5   /*READ-ONLY: signed 1.31 format*/

/** 'Ducker' **/
#define Ducker_ramp_OUTDUCK_ROUTER  0x01d6   /*signed 1.31 format*/
#define Ducker_select_0_OUTDUCK_ROUTER  0x01d7   /*signed integer*/
#define Ducker_select_1_OUTDUCK_ROUTER  0x01d8   /*signed integer*/
#define Ducker_select_2_OUTDUCK_ROUTER  0x01d9   /*signed integer*/
#define Ducker_select_3_OUTDUCK_ROUTER  0x01da   /*signed integer*/
#define Ducker_select_4_OUTDUCK_ROUTER  0x01db   /*signed integer*/
#define Ducker_select_5_OUTDUCK_ROUTER  0x01dc   /*signed integer*/

/** 'DUCKER' **/
#define DUCKER_threshold  0x01dd   /*signed 9.23 format*/
#define DUCKER_dsp_hold_time  0x01de   /*signed integer*/
#define DUCKER_depth  0x01df   /*signed 9.23 format*/
#define DUCKER_dsp_attack_coef  0x01e0   /*signed 1.31 format*/
#define DUCKER_dsp_release_coef  0x01e1   /*signed 1.31 format*/
#define DUCKER_dsp_bypass  0x01e2   /*signed integer*/
#define DUCKER_indicator  0x01e3   /*READ-ONLY: signed integer*/

/** 'Ducker' **/
#define Ducker_ramp_INDUCK_ROUTER  0x01e4   /*signed 1.31 format*/
#define Ducker_select_0_INDUCK_ROUTER  0x01e5   /*signed integer*/
#define Ducker_select_1_INDUCK_ROUTER  0x01e6   /*signed integer*/
#define Ducker_select_2_INDUCK_ROUTER  0x01e7   /*signed integer*/
#define Ducker_select_3_INDUCK_ROUTER  0x01e8   /*signed integer*/
#define Ducker_select_4_INDUCK_ROUTER  0x01e9   /*signed integer*/
#define Ducker_select_5_INDUCK_ROUTER  0x01ea   /*signed integer*/

/** 'Bridging' **/
#define Bridging_ramp_BRIDGEROUTER  0x01eb   /*signed 1.31 format*/
#define Bridging_select_0_BRIDGEROUTER  0x01ec   /*signed integer*/
#define Bridging_select_1_BRIDGEROUTER  0x01ed   /*signed integer*/
#define Bridging_select_2_BRIDGEROUTER  0x01ee   /*signed integer*/
#define Bridging_select_3_BRIDGEROUTER  0x01ef   /*signed integer*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_4_6  0x01f0   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_4_6  0x01f1   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_4_6  0x01f2   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_4_6  0x01f3   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_4_6  0x01f4   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_4_5  0x01f5   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_4_5  0x01f6   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_4_5  0x01f7   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_4_5  0x01f8   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_4_5  0x01f9   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_4_4  0x01fa   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_4_4  0x01fb   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_4_4  0x01fc   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_4_4  0x01fd   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_4_4  0x01fe   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_3_6  0x01ff   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_3_6  0x0200   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_3_6  0x0201   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_3_6  0x0202   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_3_6  0x0203   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_3_5  0x0204   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_3_5  0x0205   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_3_5  0x0206   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_3_5  0x0207   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_3_5  0x0208   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_3_4  0x0209   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_3_4  0x020a   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_3_4  0x020b   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_3_4  0x020c   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_3_4  0x020d   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_2_6  0x020e   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_2_6  0x020f   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_2_6  0x0210   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_2_6  0x0211   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_2_6  0x0212   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_2_5  0x0213   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_2_5  0x0214   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_2_5  0x0215   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_2_5  0x0216   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_2_5  0x0217   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_2_4  0x0218   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_2_4  0x0219   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_2_4  0x021a   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_2_4  0x021b   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_2_4  0x021c   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_1_6  0x021d   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_1_6  0x021e   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_1_6  0x021f   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_1_6  0x0220   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_1_6  0x0221   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_1_5  0x0222   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_1_5  0x0223   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_1_5  0x0224   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_1_5  0x0225   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_1_5  0x0226   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_1_4  0x0227   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_1_4  0x0228   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_1_4  0x0229   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_1_4  0x022a   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_1_4  0x022b   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_4_3  0x022c   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_4_3  0x022d   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_4_3  0x022e   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_4_3  0x022f   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_4_3  0x0230   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_4_2  0x0231   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_4_2  0x0232   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_4_2  0x0233   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_4_2  0x0234   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_4_2  0x0235   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_4_1  0x0236   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_4_1  0x0237   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_4_1  0x0238   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_4_1  0x0239   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_4_1  0x023a   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_3_3  0x023b   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_3_3  0x023c   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_3_3  0x023d   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_3_3  0x023e   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_3_3  0x023f   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_3_2  0x0240   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_3_2  0x0241   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_3_2  0x0242   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_3_2  0x0243   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_3_2  0x0244   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_3_1  0x0245   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_3_1  0x0246   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_3_1  0x0247   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_3_1  0x0248   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_3_1  0x0249   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_2_3  0x024a   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_2_3  0x024b   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_2_3  0x024c   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_2_3  0x024d   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_2_3  0x024e   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_2_2  0x024f   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_2_2  0x0250   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_2_2  0x0251   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_2_2  0x0252   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_2_2  0x0253   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_2_1  0x0254   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_2_1  0x0255   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_2_1  0x0256   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_2_1  0x0257   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_2_1  0x0258   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_1_3  0x0259   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_1_3  0x025a   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_1_3  0x025b   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_1_3  0x025c   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_1_3  0x025d   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_1_2  0x025e   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_1_2  0x025f   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_1_2  0x0260   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_1_2  0x0261   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_1_2  0x0262   /*signed 2.30 format*/

/** 'Output_Filters' **/
#define Output_Filters_b_0_OUTFILTER_1_1  0x0263   /*signed 3.29 format*/
#define Output_Filters_b_1_OUTFILTER_1_1  0x0264   /*signed 3.29 format*/
#define Output_Filters_b_2_OUTFILTER_1_1  0x0265   /*signed 3.29 format*/
#define Output_Filters_minus_a_1_OUTFILTER_1_1  0x0266   /*signed 2.30 format*/
#define Output_Filters_minus_a_2_OUTFILTER_1_1  0x0267   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_6_3  0x0268   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_6_3  0x0269   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_6_3  0x026a   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_6_3  0x026b   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_6_3  0x026c   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_6_2  0x026d   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_6_2  0x026e   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_6_2  0x026f   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_6_2  0x0270   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_6_2  0x0271   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_6_1  0x0272   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_6_1  0x0273   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_6_1  0x0274   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_6_1  0x0275   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_6_1  0x0276   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_5_3  0x0277   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_5_3  0x0278   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_5_3  0x0279   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_5_3  0x027a   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_5_3  0x027b   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_5_2  0x027c   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_5_2  0x027d   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_5_2  0x027e   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_5_2  0x027f   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_5_2  0x0280   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_5_1  0x0281   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_5_1  0x0282   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_5_1  0x0283   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_5_1  0x0284   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_5_1  0x0285   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_3_3  0x0286   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_3_3  0x0287   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_3_3  0x0288   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_3_3  0x0289   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_3_3  0x028a   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_4_2  0x028b   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_4_2  0x028c   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_4_2  0x028d   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_4_2  0x028e   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_4_2  0x028f   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_4_1  0x0290   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_4_1  0x0291   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_4_1  0x0292   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_4_1  0x0293   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_4_1  0x0294   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_3_3  0x0295   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_3_3  0x0296   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_3_3  0x0297   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_3_3  0x0298   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_3_3  0x0299   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_3_2  0x029a   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_3_2  0x029b   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_3_2  0x029c   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_3_2  0x029d   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_3_2  0x029e   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_3_1  0x029f   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_3_1  0x02a0   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_3_1  0x02a1   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_3_1  0x02a2   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_3_1  0x02a3   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_2_3  0x02a4   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_2_3  0x02a5   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_2_3  0x02a6   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_2_3  0x02a7   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_2_3  0x02a8   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_2_2  0x02a9   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_2_2  0x02aa   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_2_2  0x02ab   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_2_2  0x02ac   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_2_2  0x02ad   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_2_1  0x02ae   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_2_1  0x02af   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_2_1  0x02b0   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_2_1  0x02b1   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_2_1  0x02b2   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_1_3  0x02b3   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_1_3  0x02b4   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_1_3  0x02b5   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_1_3  0x02b6   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_1_3  0x02b7   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_1_2  0x02b8   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_1_2  0x02b9   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_1_2  0x02ba   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_1_2  0x02bb   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_1_2  0x02bc   /*signed 2.30 format*/

/** 'Input_Filters' **/
#define Input_Filters_b_0_INFILTER_1_1  0x02bd   /*signed 3.29 format*/
#define Input_Filters_b_1_INFILTER_1_1  0x02be   /*signed 3.29 format*/
#define Input_Filters_b_2_INFILTER_1_1  0x02bf   /*signed 3.29 format*/
#define Input_Filters_minus_a_1_INFILTER_1_1  0x02c0   /*signed 2.30 format*/
#define Input_Filters_minus_a_2_INFILTER_1_1  0x02c1   /*signed 2.30 format*/

/** 'Output_Gain' **/
#define Output_Gain_enable_CH4OUTPUTGAIN  0x02c2   /*signed integer*/
#define Output_Gain_Gain_CH4OUTPUTGAIN  0x02c3   /*signed 9.23 format*/
#define Output_Gain_signal_invert_CH4OUTPUTGAIN  0x02c4   /*signed integer*/
#define Output_Gain_POST_SHIFT_BY_LEFT_CH4OUTPUTGAIN  0x02c5   /*signed integer*/

/** 'Output_Gain' **/
#define Output_Gain_enable_CH3OUTPUTGAIN  0x02c6   /*signed integer*/
#define Output_Gain_Gain_CH3OUTPUTGAIN  0x02c7   /*signed 9.23 format*/
#define Output_Gain_signal_invert_CH3OUTPUTGAIN  0x02c8   /*signed integer*/
#define Output_Gain_POST_SHIFT_BY_LEFT_CH3OUTPUTGAIN  0x02c9   /*signed integer*/

/** 'Output_Gain' **/
#define Output_Gain_enable_CH2OUTPUTGAIN  0x02ca   /*signed integer*/
#define Output_Gain_Gain_CH2OUTPUTGAIN  0x02cb   /*signed 9.23 format*/
#define Output_Gain_signal_invert_CH2OUTPUTGAIN  0x02cc   /*signed integer*/
#define Output_Gain_POST_SHIFT_BY_LEFT_CH2OUTPUTGAIN  0x02cd   /*signed integer*/

/** 'Output_Gain' **/
#define Output_Gain_enable_CH1OUTPUTGAIN  0x02ce   /*signed integer*/
#define Output_Gain_Gain_CH1OUTPUTGAIN  0x02cf   /*signed 9.23 format*/
#define Output_Gain_signal_invert_CH1OUTPUTGAIN  0x02d0   /*signed integer*/
#define Output_Gain_POST_SHIFT_BY_LEFT_CH1OUTPUTGAIN  0x02d1   /*signed integer*/
