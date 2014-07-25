/*void WRITE_CONFIG_BOTH(int16 index, int16 address, int32 value)
{
	if(index > num_dsp_values) {
		num_dsp_values = index;
	}

	if(index < PAGE_SIZE)
  	{ 
   		DSP_ADDR.ADDRESSES_1[index] = address;
		DSP_CONFIG.VALUES_1[index] = value;  
  	} else if(index < (PAGE_SIZE * 2))
  	{ 
   		DSP_ADDR.ADDRESSES_2[index - (PAGE_SIZE*1)] = address;
		DSP_CONFIG.VALUES_2[index - (PAGE_SIZE*1)] = value;  
  	}  else if(index < (PAGE_SIZE * 3))
  	{ 
   		DSP_ADDR.ADDRESSES_3[index - (PAGE_SIZE*2)] = address;   
		DSP_CONFIG.VALUES_3[index - (PAGE_SIZE*2)] = value;   
  	}  else if(index < ((PAGE_SIZE*4)))
  	{ 
   		DSP_ADDR.ADDRESSES_4[index - (PAGE_SIZE*3)] = address;   
		DSP_CONFIG.VALUES_4[index - (PAGE_SIZE*3)] = value;   
  	} else if(index < ((PAGE_SIZE*5)))
  	{ 
   		DSP_ADDR.ADDRESSES_5[index - (PAGE_SIZE*4)] = address;   
		DSP_CONFIG.VALUES_5[index - (PAGE_SIZE*4)] = value;   
  	} else if(index < ((PAGE_SIZE*6)))
  	{ 
   		DSP_ADDR.ADDRESSES_6[index - (PAGE_SIZE*5)] = address;   
		DSP_CONFIG.VALUES_6[index - (PAGE_SIZE*5)] = value;   
  	} else if(index < ((PAGE_SIZE*7)))
  	{ 
   		DSP_ADDR.ADDRESSES_7[index - (PAGE_SIZE*6)] = address;   
		DSP_CONFIG.VALUES_7[index - (PAGE_SIZE*6)] = value;   
  	} else if(index < ((PAGE_SIZE*8)))
  	{ 
   		DSP_ADDR.ADDRESSES_8[index - (PAGE_SIZE*7)] = address;   
		//DSP_CONFIG.VALUES_8[index - (PAGE_SIZE*7)] = value;   
  	}

}
*/
void WRITE_CONFIG_ADDRESS(int16 index, int16 address)
{
	if(index > num_dsp_values) {
		num_dsp_values = index;
	}

	if(index < PAGE_SIZE)
  	{ 
   		DSP_ADDR.ADDRESSES_1[index] = address;
  	} else if(index < (PAGE_SIZE * 2))
  	{ 
   		DSP_ADDR.ADDRESSES_2[index - (PAGE_SIZE*1)] = address;
  	}  else if(index < (PAGE_SIZE * 3))
  	{ 
   		DSP_ADDR.ADDRESSES_3[index - (PAGE_SIZE*2)] = address; 
  	}  else if(index < ((PAGE_SIZE*4)))
  	{ 
   		DSP_ADDR.ADDRESSES_4[index - (PAGE_SIZE*3)] = address;  
  	} else if(index < ((PAGE_SIZE*5)))
  	{ 
   		DSP_ADDR.ADDRESSES_5[index - (PAGE_SIZE*4)] = address; 
  	} else if(index < ((PAGE_SIZE*6)))
  	{ 
   		DSP_ADDR.ADDRESSES_6[index - (PAGE_SIZE*5)] = address; 
  	} else if(index < ((PAGE_SIZE*7)))
  	{ 
   		DSP_ADDR.ADDRESSES_7[index - (PAGE_SIZE*6)] = address; 
  	} else if(index < ((PAGE_SIZE*8)))
  	{ 
   		DSP_ADDR.ADDRESSES_8[index - (PAGE_SIZE*7)] = address;   
  	}

}


int16 READ_CONFIG_ADDRESS(int16 index) 
{ 
	int16 retval; 

	if(index < PAGE_SIZE)
  	{ 
   		retval = DSP_ADDR.ADDRESSES_1[index];
  	} else if(index < (PAGE_SIZE * 2))
  	{ 
   		retval = DSP_ADDR.ADDRESSES_2[index - (PAGE_SIZE*1)];
  	}  else if(index < (PAGE_SIZE * 3))
  	{ 
   		retval = DSP_ADDR.ADDRESSES_3[index - (PAGE_SIZE*2)];
  	}  else if(index < ((PAGE_SIZE*4)))
  	{ 
   		retval = DSP_ADDR.ADDRESSES_4[index - (PAGE_SIZE*3)];
  	} else if(index < ((PAGE_SIZE*5)))
  	{ 
   		retval = DSP_ADDR.ADDRESSES_5[index - (PAGE_SIZE*4)];  
  	} else if(index < ((PAGE_SIZE*6)))
  	{ 
   		retval = DSP_ADDR.ADDRESSES_6[index - (PAGE_SIZE*5)];
  	} else if(index < ((PAGE_SIZE*7)))
  	{ 
   		retval = DSP_ADDR.ADDRESSES_7[index - (PAGE_SIZE*6)];
  	} else if(index < ((PAGE_SIZE*8)))
  	{ 
   		retval = DSP_ADDR.ADDRESSES_8[index - (PAGE_SIZE*7)];
  	}

	return(retval); 
}

/*
int32 READ_CONFIG_VALUE(int16 index) 
{ 
	int32 retval; 

	if(index < PAGE_SIZE)
  	{ 
   		retval = DSP_CONFIG.VALUES_1[index];  
  	} else if(index < (PAGE_SIZE + PAGE_SIZE))
  	{ 
   		retval = DSP_CONFIG.VALUES_2[index - PAGE_SIZE];  
  	}  else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{ 
   		retval = DSP_CONFIG.VALUES_3[index - PAGE_SIZE - PAGE_SIZE];  
  	}  else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{ 
   		retval = DSP_CONFIG.VALUES_4[index - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE];  
  	} else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{ 
   		retval = DSP_CONFIG.VALUES_5[index - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE- PAGE_SIZE];  
  	} else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{ 
   		retval = DSP_CONFIG.VALUES_6[index - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE];  
  	} else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{ 
   		retval = DSP_CONFIG.VALUES_7[index - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE];  
  	} else
  	{ 
   		retval = 0; 
  	} 

	return(retval); 
}

void WRITE_CONFIG_VALUE(int16 index, int32 value) 
{ 
	if(index < PAGE_SIZE)
  	{ 
		DSP_CONFIG.VALUES_1[index] = value;  
  	} else if(index < (PAGE_SIZE + PAGE_SIZE))
  	{ 
		DSP_CONFIG.VALUES_2[index - PAGE_SIZE] = value;  
  	}  else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{   
		DSP_CONFIG.VALUES_3[index - PAGE_SIZE - PAGE_SIZE] = value;   
  	}  else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{   
		DSP_CONFIG.VALUES_4[index - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE] = value;   
  	} else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{   
		DSP_CONFIG.VALUES_5[index - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE] = value;   
  	} else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{ 
		DSP_CONFIG.VALUES_6[index - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE] = value;   
  	} else if(index < (PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE + PAGE_SIZE))
  	{    
		DSP_CONFIG.VALUES_7[index - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE - PAGE_SIZE] = value;   
  	}
}

*/