#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "customheaders\bmpreadclass.h"
using namespace std;
string GetExePath();

int main(int argc, char** argv)
{
	class bmp_read file1;
	
	ifstream openfile;
	string initialpath = GetExePath();
	string currentpicture1= "/Import/import00";
	string currentpicture2= "/Import/import0";
	string currentpicture3= "/Import/import";
	
	string currentpicture1exp= "/Export/export00";
	string currentpicture2exp= "/Export/export0";
	string currentpicture3exp= "/Export/export";
	
	string currentpictureconcat = "";
	
	string currentpictureconcat_export="";
	
	char stringtochar[1000];
	char stringtocharexp[1000];
	int picturecounter = 0;
	int numberoffilesopen = 0;
	string format = ".bmp";
	string expformat = ".h";
	cout << endl;
	
	cout << "main argument total: "<<argc;

	for(picturecounter = 1; picturecounter < 1000; picturecounter++)
	{
		switch(picturecounter)
		{
		case 1 ... 9:
		
			currentpictureconcat = initialpath+currentpicture1 + to_string(picturecounter)+format;
			//cout <<currentpictureconcat<<endl; 
			break;
		case 10 ... 99:
			currentpictureconcat = initialpath+currentpicture2 + to_string(picturecounter)+format;
			//cout <<currentpictureconcat<<endl; 
			break;
		case 100 ... 999:
			currentpictureconcat = initialpath+currentpicture3 + to_string(picturecounter)+format;
			//cout <<currentpictureconcat<<endl; 
			break;
		}
		strcpy(stringtochar, currentpictureconcat.c_str());
		openfile.open(stringtochar);
		
		if (openfile.is_open())
		{
			numberoffilesopen++;
			//cout << "file is open"<<endl;
		}
		else
		{
			numberoffilesopen = numberoffilesopen;
			//cout << "file not opened!"<<endl;
		}
		openfile.close(); //close the file already..
		
	}
	cout << endl << "number of files detected: " <<numberoffilesopen<<endl;
	cout << "file conversion starting now."<<endl;
	currentpictureconcat = ""; //reinitializing?
	for(int i = 1; i <=numberoffilesopen;i++)
	{
		switch(i)
		{
		case 1 ... 9:
			currentpictureconcat = initialpath+currentpicture1 + to_string(i)+format;
			currentpictureconcat_export = initialpath+currentpicture1exp + to_string(i) + expformat;
			//cout <<endl<<currentpictureconcat<<endl; 
			break;
		case 10 ... 99:
			currentpictureconcat = initialpath+currentpicture2 + to_string(i)+format;
			currentpictureconcat_export = initialpath+currentpicture2exp + to_string(i) + expformat;
			//cout <<endl<<currentpictureconcat<<endl; 
			break;
		case 100 ... 999:
			currentpictureconcat = initialpath+currentpicture3 + to_string(i)+format;
			currentpictureconcat_export = initialpath+currentpicture3exp + to_string(i) + expformat;
			//cout <<endl<<currentpictureconcat<<endl; 
			break;
		}
		strcpy(stringtochar, currentpictureconcat.c_str());
		strcpy(stringtocharexp,currentpictureconcat_export.c_str());
		
		file1.open(stringtochar);// making string "constant" on the fly with (char *) "STRING"
		file1.read(stringtochar);
		file1.displayinfo();
		file1.convert();
		file1.exporttofile(stringtocharexp, 0, i); // (filename, flag, filenumber)
		file1.close();	
	}
	if(numberoffilesopen<20)
	{
		int i = numberoffilesopen+1;
		for(int i=numberoffilesopen+1; i <= 20; i++)
		{
			//cout << "files open: " << i << endl;
			switch(i)
			{
			case 1 ... 9:
				//currentpictureconcat = initialpath+currentpicture1 + to_string(i)+format;
				currentpictureconcat_export = initialpath+currentpicture1exp + to_string(i) + expformat;
				cout <<endl<<"No additional pictures detected. Empty header file created:";
				cout <<endl<<currentpictureconcat_export<<endl; 
				break;
			case 10 ... 99:
				//currentpictureconcat = initialpath+currentpicture2 + to_string(i)+format;
				currentpictureconcat_export = initialpath+currentpicture2exp + to_string(i) + expformat;
				cout <<endl<<"No additional pictures detected. Empty header file created:";
				cout <<endl<<currentpictureconcat_export<<endl; 
				break;
			case 100 ... 999:
				//currentpictureconcat = initialpath+currentpicture3 + to_string(i)+format;
				currentpictureconcat_export = initialpath+currentpicture3exp + to_string(i) + expformat;
				cout <<endl<<"No additional pictures detected. Empty header file created:";
				cout <<endl<<currentpictureconcat_export<<endl; 
				break;
			}
			strcpy(stringtocharexp,currentpictureconcat_export.c_str());
			
			file1.exporttofile(stringtocharexp, 1, i); // (filename, flag, filenumber)
			
		}
		
	}
	else
	{
		// do nothing....
	}
	

//cout <<endl<<endl<< GetExePath();

//	while(1)
//	{
//	}
	return 0;

}
string GetExeFileName()
{
  char buffer[MAX_PATH];
  GetModuleFileName( NULL, buffer, MAX_PATH );
  return string(buffer);
}

string GetExePath() 
{
  string f = GetExeFileName();
  return f.substr(0, f.find_last_of( "/\\" ));
}