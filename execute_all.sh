#!/bin/bash
clear
echo "Hello User!"
echo "Cleaning object files and hex files!"
echo `make clean`
echo "."
echo ". ."
echo ". . ."
echo "Cleaning complete!"
echo "Cleaning header files!"
echo `rm -rf Export/*.h`
echo "."
echo ". ."
echo ". . ."
echo "Cleaning complete!"
./main.exe
echo

while true
do
	read -p "Would you like to continue? Type \"y\" and press enter:" USERINPUT
	if [[ $USERINPUT == "y" ]]
	then
	{
		break
	}
	else
	{
	echo "Wrong input!"
	}
	fi
done
echo
echo `make compile; make program`


