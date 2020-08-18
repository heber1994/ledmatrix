# ledmatrix
Code in C and C++ to convert low resolution pictures into packed header files to display low resolution images in an led matrix

Hello there! I decided to create a 24x12 LED Matrix to practice my programming skills! The longest part was designing and building the LED Matrix LED by LED, one at a time, and making the connections to shift registers! I used a barebone ATMEL ATMEGA32 Chip with a USBTiny programmer to burn the code into the chip.

After I was done with the matrix, I coded simple letters and sentences in C for AVR to test the matrix out. It then came to me, what if instead of displaying just letters and/or sentences I could display pictures? Thats when I started working on a C++ project that reads low resolution bmp files, saves the info in an array, does some calculations with the data and then exports the information in a header.h file. This header.h file can then be used with the code written in C.

So far there are 2 sections for this project:

1st section: Code written in C
,Objective: create code that interacts with the microcontroller, the shift registers and the LED Matrix.
Inputs: Text, words, header.h file pictures using a custom-made packing algorithm
Outputs: scrolling text, words and pictures on the LED Matrix!
Dependency: This code depends on the 2nd section of the project. without the 2nd section, all I could display is scrolling text messages on the LED Matrix.

2nd section: Code written in C++
,Objective: Generate header.h files from low resolution pictures using a custom-made packing algorithm.
Inputs: Pictures in .bmp file format, maximum width is 24, height has no limit, although I would not exceed 40 or 50 pixels in height (you can perform exploratory tests on this software and see what happens!)
Outputs: header.h files
Dependency: This code depends on pictures saved as bmp files. Without any bmp images, the pictures would not be generated!

I mentioned the two important sections. However, I also used makefiles and a bash script to kind of automate everything and start the file conversion process and the upload of the compiled C program (.hex file) by running one single command.

TO DO THIS PROJECT:
pre-requisites:
1) build a 24x12 LED Matrix using 8-bit shift registers and using an 8-bit microcontroller from AVR ATMEGA32 (schematics coming up soon! Everything is in my head)
2) Use a USBTiny programmer for SPI communications between the computer and the ATMEGA32 microcontroller
3) You must be either running linux and have gcc and gpp installed, avrdude, as well as makefile. (warning, the makefiles may need some updating if using linux!)
4) If you do not have linux, you can install cygwin on your windows pc, and install gcc, gpp, makefile, winavr and bash scripting.

avrdude can be replaced with winavr if you are running windows. avrdude/winavr allows programming hex files into microcontrollers.

TO RUN THE C++ PROGRAM (The program that generates h. header files):
1) open up a terminal/cygwin and nagivate to the folder /ledmatrix_project/version_1.1
2) locate the "Import" folder and add/delete/replace pictures. Remember, these pictures must be 24 pixels width and 40-50 pixels in height for best results.
3) locate the "Export" folder and delete all the header files. You can peak at the files. When the tool runs, it should generate new header files for you!
4) find main.exe in /ledmatrix_project/version_1.1 and just double click it. If you want to see some feedback, you can run the program within a terminal window.

TO RUN THE C PROGRAM (The program that compiles the source.c file, with all other headers for the AVR)
1) attach the USBTiny to a computer, then attach the SPI communications port to your microcontroller
2) if you executed the C++ program already, then open up a terminal and go to /ledmatrix_project/version_1.1
3) type in the terminal: make compile; make program
4) if you would like to generate everything, then open up a terminal and go to /ledmatrix_project/version_1.1
5) then, run execute_all.sh by typing: ./execute_all.sh
6) don't forget to add/delete pictures in the Import folder.



