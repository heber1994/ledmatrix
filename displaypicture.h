#ifndef displaypicture_h
#define displaypicture_h

//#include "export.h"

extern volatile uint8_t matrix1[12][12];
extern volatile uint8_t matrix2[12][12];
extern volatile uint8_t matrix3[12][12];

void displaypicture(uint8_t picnumber, uint8_t heightinpixels, uint8_t cycles, uint8_t speed)
{
int photoloop1,photoloop2;
int shift;
int cyclelimit;
uint8_t loopforeachpicture;
uint8_t trueorfalse; //0 for false, 1 for true.. haha

	switch(picnumber)
	{
		case 1:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash1[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash1[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash1[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 2:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash2[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash2[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash2[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 3:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash3[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash3[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash3[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}	
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 4:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash4[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash4[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash4[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}	
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 5:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash5[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash5[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash5[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 6:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash6[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash6[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash6[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 7:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash7[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash7[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash7[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 8:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash8[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash8[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash8[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 9:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash9[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash9[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash9[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 10:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash10[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash10[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash10[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 11:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash11[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash11[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash11[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 12:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash12[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash12[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash12[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 13:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash13[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash13[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash13[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 14:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash14[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash14[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash14[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 15:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash15[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash15[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash15[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 16:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash16[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash16[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash16[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 17:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash17[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash17[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash17[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 18:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash18[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash18[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash18[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 19:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash19[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash19[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash19[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		case 20:
			shift = (heightinpixels-12)*3;
			cyclelimit = (shift/3)*2;
			trueorfalse=0;
			for(loopforeachpicture=0;loopforeachpicture<((cyclelimit*cycles)+1);loopforeachpicture++){
				for(photoloop1=0;photoloop1<12;photoloop1++){
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix1[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash20[0+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix2[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash20[1+shift+(3*photoloop1)][photoloop2]));}
					for(photoloop2=0;photoloop2<12;photoloop2++){
					matrix3[photoloop1][photoloop2] = pgm_read_byte(&(storetoflash20[2+shift+(3*photoloop1)][photoloop2]));}
				}
				if(shift==(heightinpixels-12)*3){trueorfalse=1;}		
				if(trueorfalse){shift = shift-3;}
				else{shift = shift+3;}	
				if(shift==0){trueorfalse=0;}
				delay_ms(speed);
			}
			break;
		
	}
	
}

#endif