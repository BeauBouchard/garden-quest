UINT8 i;

void fadein(){
	wait_vbl_done();
	// its changing the palette for the background switching each colour in the palette to white step by step
	// dont need to start at all back as will have been set that by fadeout
	for(i=1; i != 4; i++){
		switch(i){
			case 1:
				BGP_REG = 0xFE;
				break;
			case 2:
				BGP_REG = 0xF9;
				break;
			case 3:
				BGP_REG = 0xE4;
				break;											
		}
		delay(100);
	}	
}

void fadeout(){
	wait_vbl_done();	
	for(i = 0; i != 4; i++){
		switch(i){
			case 0:
				BGP_REG = 0xE4;
				break;
			case 1:
				BGP_REG = 0xF9;
				break;
			case 2:
				BGP_REG = 0xFE;
				break;
			case 3:
				BGP_REG = 0xFF;
				break;												
		}
		delay(100);
	}	
}

// blank sprite
const unsigned char BackgroundData[1] =
{
	0x00
};

