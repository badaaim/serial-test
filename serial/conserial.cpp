// File: conserial.cpp
// Description: Serial communication console program for Windows and Linux
// WebSite: http://cool-emerald.blogspot.sg/2017/05/serial-port-programming-in-c-with.html
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye
// build executable: g++ conserial.cpp ceSerial.cpp -o conserial_COM6.exe -std=c++11

#include <stdio.h>
#include "ceSerial.h"
using namespace std;
using namespace ce;

int main()
{
#ifdef ceWINDOWS
	ceSerial com("\\\\.\\COM50",115200,8,'N',1); // Windows
#else
	ceSerial com("/dev/ttyS0",9600,8,'N',1); // Linux
#endif

	printf("Opening port %s.\r\n",com.GetPort().c_str());
	if (com.Open() == 0) {
		printf("OK.\n");
	}
	else {
		printf("Error.\n");
		return 1;
	}

	bool successFlag;
	printf("Writing.\r\n");
	unsigned int sequenceCount = 50;
	char s[]="AT+PH=569,9430,1,\r\n"; 
	for (unsigned short i = 1; i <= sequenceCount; i++) {
		successFlag=com.Write(s); // write string
	}
	//successFlag=com.WriteChar('!'); // write a character

	printf(s);
	//ceSerial::Delay(3000); // delay to wait for a character

	printf("Reading.\r\n");
	char c=com.ReadChar(successFlag); // read a char
	if(successFlag) printf("Rx: %c\r\n",c);

	printf("Closing port %s.\r\n",com.GetPort().c_str());
	com.Close();
	return 0;
}
