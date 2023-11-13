/****************************************************************************************
 /*   Author: Abdalah Beshary
 /*   SWC   : Gsm_Programe.c
 /*	  Date  : 25/10/2023
 /*  Version: 1
 **************************************************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SYSTICK/STK_interface.h"
#include "../../MCAL/UART/UART_int.h"
#include "Gsm_interfac.h"

u8 Loginitudnal[11]={0};
u8 Latitude[11]={0};
u8 Longitude[8]={0}; // Changed from Logintude to Longitude
u8 latitude_c[8]={0}; // Added latitude_c array



void GSM_init(){
	// at command it will respond OK
	MUSART_vTransmitString(USART1,"AT\r\n");
	STK_voidSetBusyWait(5000);
	MUSART_vTransmitString(USART1,"AT+IPR=115200\r\n");


	//check to sim state
	MUSART_vTransmitString(USART1,"AT+CPIN?\r\n");
	STK_voidSetBusyWait(5000);

	MUSART_vTransmitString(USART1,"ATE0\r\n");
}

void GPS_init(){
	// power_on gps
	MUSART_vTransmitString(USART1,"AT+CGPSPWR=1\r\n");
	STK_voidSetBusyWait(5000);
	//COLD RESET FOR LOCATION
	MUSART_vTransmitString(USART1,"AT+CGPSRST=0\r\n");
	STK_voidSetBusyWait(5000);

}
void Send_SMS(void){
	//check sim card by

	u8  GPS_location[250];
	u8   GPS_sate_of_location[50];
	u8 real_state_message[16]="Location Not Fix";

	//check location not fix
	MUSART_vTransmitString(USART1,"AT+CGPSSTATUS?\r\n");
	STK_voidSetBusyWait(5000);
	MUSART_vTransmitString(USART1,"AT+CGPSSTATUS?\r\n");
	STK_voidSetBusyWait(5000);
	MUSART_vTransmitString(USART1,"AT+CGPSSTATUS?\r\n");

	MUSART_u8ReceivesGsm_string(USART1,GPS_sate_of_location, 0);
	u8 counter=0;
	u8 i=0;


	// request of location
	MUSART_vTransmitString(USART1,"AT+CGPSINF=0\r\n"); //CIPGSMLOC
	//recive lcoation
	MUSART_u8ReceivesGsm_string(USART1,GPS_location, 0);

	get_poistion(GPS_location);
	// change from ddmm.mmmmmm to degree and minuites
	ddmmtodegree();
	//CHECK THS MESSAGE IS NOT EMPTY
	MUSART_vTransmitString(USART1,(u8*)"AT+CSMP=17,167,0,0\r\n");
	STK_voidSetBusyWait(5000);
	//CHECK THAT SMS IT CAN SED
	MUSART_vTransmitString(USART1,(u8*)"AT+CMGF=1\r\n");
	STK_voidSetBusyWait(5000);
	//SEND MESSAGE
	MUSART_vTransmitString(USART1,(u8*)"AT+CMGS=\"+201141438886\"\r\n");  
	STK_voidSetBusyWait(5000);
	//send content of message location of location with message say help.
	MUSART_vTransmitString(USART1,"https://www.google.com/maps?q=");
	for(int counter=0;counter<9;counter++){

		MUSART_vTransmitByteSynch(USART1,Loginitudnal[counter]);
	}
	MUSART_vTransmitByteSynch(USART1,',');
	for( counter=0;counter<9;counter++){

		MUSART_vTransmitByteSynch(USART1,Latitude[counter]);
	}


	MUSART_vTransmitString(USART1,"\r\n");


	STK_voidSetBusyWait(10000);

	//command after send message is important
	MUSART_vTransmitString(USART1,"\x1A");
	STK_voidSetBusyWait(5000);



}

void SMS(void){

	u8  GPS_location[250];
	u8   GPS_sate_of_location[50];
	u8 real_state_message[16]="Location Not Fix";
	//CHECK THS MESSAGE IS NOT EMPTY
	MUSART_vTransmitString(USART1,(u8*)"AT+CSMP=17,167,0,0\r\n");
	STK_voidSetBusyWait(5000);
	//CHECK THAT SMS IT CAN SED
	MUSART_vTransmitString(USART1,(u8*)"AT+CMGF=1\r\n");
	STK_voidSetBusyWait(5000);
	//SEND MESSAGE
	MUSART_vTransmitString(USART1,(u8*)"AT+CMGS=\"+201141438886\"\r\n");  
	STK_voidSetBusyWait(5000);
	//send content of message location of location with message say help.
	MUSART_vTransmitString(USART1,"Emergency!!! Driver Fatigue Detected\r\n");
	MUSART_vTransmitString(USART1,"https://maps.app.goo.gl/JpNyjzGwrsayPUEx7?g_st=iw");

	MUSART_vTransmitString(USART1,"\r\n");
	STK_voidSetBusyWait(10000);

	//command after send message is important
	MUSART_vTransmitString(USART1,"\x1A");
	STK_voidSetBusyWait(5000);



}

void Make_Call(void){

	//MAKE CALL FOR THIS NUMBER
	MUSART_vTransmitString(USART1,"ATD+201141926991;\r\n");  //201141926991 201005326822
	MUSART_vTransmitString(USART1,"ATD+201141926991;\r\n");  //201141926991 201005326822
	MUSART_vTransmitString(USART1,"ATD+201141926991;\r\n");  //201141926991 201005326822

	//closed call AFTER SPECIFIC TIME

	STK_voidSetBusyWait(9000000);
	//MUSART_vTransmitString(USART1,"ATH\r\n");


}


void get_poistion(u8 * position){

	u8 counter=0;
	u8 k=0,m=0;
	for(u8 i=0;i<40;i++){

		if(position[i]==','){
			counter++;
		}

		if(counter==1){

			Loginitudnal[k]=position[i+1];
			k++;
		}
		else if(counter==2){

			Latitude[m]=position[i+1];
			m++;
		}
		else if(counter==3){

			break;
		}
	}



}

//
void intToString(u8 value, u8* str, u8 digits) {
	for (u8 i = digits; i > 0; i--) {
		str[i - 1] = (value % 10) + '0';
		value /= 10;
	}
}

// Function to convert a floating-point value to a string
void floatToString(f32 value, u8* str, u8 integerDigits, u8 fractionalDigits) {
	u8 integerPart = (u8)value;
	f32 fractionalPart = value - integerPart;

	intToString(integerPart, str, integerDigits);

	if (fractionalDigits > 0) {
		str[integerDigits] = '.';

		for (u8 i = 0; i < fractionalDigits; i++) {
			fractionalPart *= 10;
			str[integerDigits + 1 + i] = (u8)fractionalPart + '0';
			fractionalPart -= (u8)fractionalPart;
		}
	}
}

void ddmmtodegree(void) {
	u8 degree = 0;
	u8 i = 0;
	f32 minutes = 0.0;
	// u8 Longitude[8]={0}; // Changed from Logintude to Longitude
	//u8 latitude_c[8]={0}; // Added latitude_c array

	degree = (Loginitudnal[0] - '0') * 10 + (Loginitudnal[1] - '0');
	minutes = (Loginitudnal[2] - '0') * 10 + (Loginitudnal[3] - '0');
	minutes += (Loginitudnal[5] - '0') / 10.0 + (Loginitudnal[6] - '0') / 100.0 + (Loginitudnal[7] - '0') / 100000.0;

	// Calculate degrees and minutes
	f32 total_minutes = minutes / 60.0;
	f32 final_degree = degree + total_minutes;

	// Convert to string and store in Longitude
	floatToString(final_degree, Longitude, 2, 6);
	if(Latitude[1]!='.'){
		degree = (Latitude[0] - '0') * 10 + (Latitude[1] - '0');
		minutes = (Latitude[2] - '0') * 10 + (Latitude[3] - '0');
		minutes += (Latitude[5] - '0') / 10.0 + (Latitude[6] - '0') / 100.0 + (Latitude[7] - '0') / 100000.0;

		// Calculate degrees and minutes for latitude
		total_minutes = minutes / 60.0;
		final_degree = degree + total_minutes;

		// Convert to string and store in latitude_c
		floatToString(final_degree, latitude_c, 2, 6);
	}
	// Copy the converted strings back to the global arrays
	for (i = 0; i < 8; i++) {
		Loginitudnal[i] = Longitude[i];
		Latitude[i] = latitude_c[i];
	}
}

