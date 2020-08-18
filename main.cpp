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
string initialpath = GetExePath();
int numberoffilesopen = 0;

int main(int argc, char** argv)
{
	class bmp_read file1;
	
	ifstream openfile;
	
	//support to read up to 999 files... 001,002,003...999
	string currentpicture1= "/Import/import00";
	string currentpicture2= "/Import/import0";
	string currentpicture3= "/Import/import";
		
	string exportfilepath= "/Export/";
	
	string currentpictureconcat = "";	
	string exportfilepath_concat="";

	
	char stringtochar[1000];
	char strtocharexp[1000];
	int picturecounter = 0;
	
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
			break;
		case 10 ... 99:
			currentpictureconcat = initialpath+currentpicture2 + to_string(picturecounter)+format;
			break;
		case 100 ... 999:
			currentpictureconcat = initialpath+currentpicture3 + to_string(picturecounter)+format;
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
	
	exportfilepath_concat = initialpath+exportfilepath+"export"+expformat;
	strcpy(strtocharexp,exportfilepath_concat.c_str());
	
	file1.createexportfile(strtocharexp);
	
	file1.generate_runpictureprogram_function(); // THIS LINE OF CODE GENERATES A FUNCTION IN EXPORT.H FILE
	
	for(int i = 1; i <=numberoffilesopen;i++)
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
		
		file1.open(stringtochar);// making string "constant" on the fly with (char *) "STRING"
		file1.read(stringtochar);
		file1.displayinfo();
		file1.convert();
		file1.exporttofile(strtocharexp,0,i); // (filename, flag, filenumber)
		file1.closeinputfiles();	
	}
	
		if(numberoffilesopen<20)
	{
		int i = numberoffilesopen+1;
		for(int i=numberoffilesopen+1; i <= 20; i++)
		{
		file1.exporttofile(strtocharexp,1,i); // (filename, flag, filenumber)
		}
		
	}
	
	file1.closeoutputfile();

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