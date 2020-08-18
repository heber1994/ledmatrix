#ifndef bmpreadclass_h
#define bmpreadclass_h

using namespace std;
extern int numberoffilesopen;
extern string initialpath;
class bmp_read{

private:
	
public:

uint8_t brightness; //modify this variable in case the brightness of the matrix changes. this will modify the way the picture is packed and stored.
uint8_t width_data_address; //
uint8_t height_data_address; //
uint8_t picture_data_start_address; //

volatile uint8_t width;
volatile uint8_t height;
volatile uint8_t start_add;

unsigned char info[54];			//retains header file info.
unsigned char buffer1[259254];	//this limits size of buffer to a 240 by 360 pixel picture or any dimension where (width x height x 3) + 54 is less than 259,254.
unsigned char buffer3[129600];	//packed data. size is limited to a 240 by 360 pixel picture ((240*360)/8)*12 = 129,600
ifstream openbmpfile;
ofstream exporthexdata;

//default constructor
	bmp_read()
	{
	 width_data_address=0x15;
	 height_data_address=0x19;
	 picture_data_start_address = 0xA;
	 brightness = 12;	//modify this variable in case the brightness of the matrix changes. this will modify the way the picture is packed and stored.

	}

	void open(char filelocation[])
	{
		memset(info,0,sizeof(info));
		openbmpfile.open(filelocation);
		
		if (openbmpfile.is_open())
		{
			cout << endl<<"File opened successfully!";
		}
		else
		{
			cout << "cannot locate file!";
		}
		
		for(int loop = 0; loop<54; loop++)
		{
		info[loop] = openbmpfile.get()+0x00;		//all characters are copied to info[loop]
		}
	
	
	width = info[width_data_address-0]+info[width_data_address-1]+info[width_data_address-2]+info[width_data_address-3]+0;
	height = info[height_data_address-0]+info[height_data_address-1]+info[height_data_address-2]+info[height_data_address-3]+0;
	start_add = info[picture_data_start_address]+0;
		
		memset(buffer1,0,sizeof(buffer1)); // initialize buffer1 
		for(int i=0; i<(width*height*3);i++)
		{
			buffer1[i] = openbmpfile.get();
			// cout << hex << buffer1[i]+0<<" ";   -> cout used for debugging purposes
		}
		cout << dec;
	
	openbmpfile.close();
	}

	void read(char filelocation[])
	{	cout << endl;
		cout << "file location: " << filelocation;
	}
	
	void convert()
	{
	int loop_limit = width*height;
	unsigned char buffer2[loop_limit];
	//unsigned char buffer3[(loop_limit)/8]; //buffer 3 is the final buffer that holds packet data, ready to be exported
	unsigned char temporary;
	//for loop designed to extract picture data. data repeats 3 times. we only need 1 set of data, not 3 sets.
	
	memset(buffer2,0,sizeof(buffer2));
		for(int i = 0; i < loop_limit;i++)
		{
			buffer2[i] = buffer1[(i*3)]+0; //jump data pointers by increments of 3. start address not included since file is still open and will resume from last read address 54.
		}
	
		for(int i = 0; i < loop_limit;i++)
		{
			
		temporary = ((buffer2[i]+0)/31)+0;	//adding + 0 to let compiler know we want HEX value, not ASCII value.
			//cout << temporary + 0 << " ";
			switch (temporary)
			{
			//max brightness in the LED Matrix is set to 12 (array with 12 elements which only range 0-11 is accessible)
			//this switch case code makes brightness changes sharper.
			
			case 0:
			temporary = 0; break;
			case 1:
			temporary = 1; break;
			case 2:
			temporary = 2; break;
			case 3:
			temporary = 3; break;
			case 4:
			temporary = 4; break;
			case 5:
			temporary = 6; break;
			case 6:
			temporary = 8; break;
			case 7:
			temporary = 10; break;
			case 8:
			temporary = 11; break;
			}
		//cout << temporary + 0 << " ";
		buffer2[i] = temporary; //changing values of buffer2 from ASCII to HEX/48

		}
		
		uint8_t binarybuffer[width*height][brightness];
		memset(binarybuffer,0,sizeof(binarybuffer));
		
		for(int i = 0; i < (loop_limit)/8;i++)
		{
			for(int i1=0;i1<8;i1++)
			{
				for(int i2=0;i2<=buffer2[(i*8)+i1];i2++)
				{
					binarybuffer[(i*8)+i1][i2] = 1<<i1;
				}
			}
		}
		memset(buffer3,0,sizeof(buffer3));
			for(int i1 = 0; i1<(loop_limit)/8;i1++)
			{
				for(int i2=0;i2<12;i2++)
				{
					for(int i3 = 0; i3<8; i3++)
					{
					buffer3[i1*12+i2] |=binarybuffer[(i1*8)+i3][i2];
					}				
				}					
			}		
	}

	void createexportfile(char exportlocation[])
	{
		exporthexdata.open(exportlocation);
		exporthexdata << dec << "#ifndef export_h" <<endl;
		exporthexdata << "#define export_h" << endl;
	}
	
	void generate_runpictureprogram_function()
	{
	string currentpicture1= "/Import/import00";
	string currentpicture2= "/Import/import0";
	string currentpicture3= "/Import/import";	
	string currentpictureconcat = "";
	char stringtochar[1000];	
	string format = ".bmp";
		exporthexdata << endl << "extern void displaypicture(uint8_t picnumber, uint8_t heightinpixels, uint8_t cycles, uint8_t speed);"<<endl;
		exporthexdata << endl << "void runpictureprogram(){"<<endl;
		for(int i=1;i<=numberoffilesopen;i++)
		{
			switch(i)
			{
			case 1 ... 9:
				currentpictureconcat = initialpath+currentpicture1 + to_string(i)+format;
				break;
			case 10 ... 99:
				currentpictureconcat = initialpath+currentpicture2 + to_string(i)+format;
				break;
			case 100 ... 999:
				currentpictureconcat = initialpath+currentpicture3 + to_string(i)+format;
				break;
			}
		strcpy(stringtochar, currentpictureconcat.c_str());
		open(stringtochar); //open BMP file to read height!			
			//export data!
			exporthexdata << dec << "displaypicture(" << i << "," << (height+0) << ",2,20);"<<endl;			
		}
		exporthexdata << "}"<<endl<<endl;

	}
	void exporttofile(char exportlocation[], uint8_t flag, int filenumber)
	{
		if(flag == 0)
		{	
			exporthexdata << dec << "const uint8_t storetoflash"<< filenumber <<"[" <<(((width*height)/8)+0)<<"]["<<(brightness+0)<<"] PROGMEM = {"<<endl;
			
			///////
			for(int i1 = 0; i1<((width*height)/8);i1++)
			{
			exporthexdata << "{";
				for(int i2 = 0; i2<brightness-1; i2++)
				{
				exporthexdata << "0x"<< hex<<buffer3[(i1*12)+i2]+0 <<", ";
				}
				exporthexdata <<"0x"<< hex<<buffer3[(i1*12)+brightness-1]+0<<"},"<<endl;
			}
			exporthexdata<<"};"<<endl<<endl<<endl;
		}
		else if (flag == 1)
		{
			exporthexdata << dec << "const uint8_t storetoflash" << filenumber << "[1][1] PROGMEM = {"<<endl;
			exporthexdata << "{0x00}"<<endl;
			exporthexdata << "};"<<endl<<endl;
		}
	}
	
	void closeinputfiles()
	{
		openbmpfile.close();
		if (openbmpfile.is_open())
		{
			cout << endl << "files could not be closed.";
		}
		else
		{
			cout <<endl << "Input files have been closed successfully!."<<endl;
		}
		
	}
	
	void closeoutputfile()
	{
		exporthexdata << endl << "#endif";
		exporthexdata.close();
		if (exporthexdata.is_open())
		{
			cout << endl << "file could not be closed.";
		}
		else
		{
			cout <<endl << "program generated header file and closed used files."<<endl;
		}		
	}
	void displayinfo()
	{
		cout <<endl;
		cout << "width of picture is: "<< dec <<width+0 <<" pixels";
		cout <<endl;
		cout << "height of picture is: " << dec <<height+0<<" pixels";
	}	
	
};
#endif