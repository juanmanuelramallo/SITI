#include "sAPI.h"
#include "string.h"
#define LENGTH_FIELDS 14
#define LENGTH_TYPE 5
#define LENGTH_UTC 9
#define LENGTH_LATITUDE 10
#define LENGTH_NS 1
#define LENGTH_EO 1
#define LENGTH_LONGITUDE 11


//Enumerativo para el control de los estados posibles para el tratamiento de la trama NMEA GPS
enum gpsFrameState 
{
	frameInit,
	frameType,
	frameUtcTime,
	frameLatitude,
	frameNS,
	frameLongitude,
	frameEO

};

//Agrupamiento de variables de datos de la trama GPS
struct gpsFrameData
{
	uint8_t type[LENGTH_FIELDS];
	uint8_t utcTime[LENGTH_FIELDS];
	uint8_t latitude[LENGTH_FIELDS];
	uint8_t ns;
	uint8_t longitude[LENGTH_FIELDS];
	uint8_t eo;
}gpsData;

//Datos de coordenadas expresadas sin ceros iniciales de la forma: lat = GGMM,MMMMM y lon = GGGMM,MMMMM
//Se le sacan los ceros iniciales, en caso que hayan por ubidots. Los minutos se deben interpretar como
//grados para usar en google maps (grados decimales), aunque hay varias formas, siendo esta la mas sencilla
//para enviar por la UART evitando convertir y desconvertir varias veces
struct gpsCoordinatesUbidots
{
	uint8_t latitude[LENGTH_FIELDS];
	uint8_t longitude[LENGTH_FIELDS];
}gpsCoordinates;

// inicializar estructura

//Variable que contiene un dato recibido por el GPS
uint8_t gpsCharacterReceived;

//Variable unica que indica el indice para la obtencion de los datos
uint8_t gpsFrameIndex;

//Agrupamiento de flags de control
struct gpsFrameFlags
{
	uint8_t characterReceived;		//flagGPS		
	uint8_t ready;	
}gpsFlags;

//Variable enumerativa para control de estado de la tama GPS
enum gpsFrameState state = frameInit;

//Procedimiento que permite inicializar variable de recepcion del GPS
void gpsFrameCharacterReceivedInit(){
	gpsCharacterReceived = '\0';
}

//Procedimiento que permite inicializar los flags de control
void gpsFrameFlagsInit(){
	gpsFlags.characterReceived = 0;
	gpsFlags.ready = 0;
}

//Procedimiento que permite inicializar un campo individual de datos del GPS
void gpsFrameFieldInit(char* frameField){

	int i = 0;
	for (i = 0; i <strlen(frameField); ++i)
	{
		frameField[i] = '\0';
	}

}

//Procedimiento que permite inicializar los datos del GPS
void gpsFrameVarInit(){
	
	gpsFrameFieldInit((char*)gpsData.type);	
	gpsFrameFieldInit((char*)gpsData.utcTime);	
	gpsFrameFieldInit((char*)gpsData.latitude);	
	gpsData.ns = '\0';	
	gpsFrameFieldInit((char*)gpsData.longitude);	
	gpsData.eo = '\0';
	gpsFrameIndex = 0;

}

//Procedimiento que setea el caracter recivido de la interrupcion
void gpsSetCharacterReceived(uint8_t frameCharacter){
	gpsCharacterReceived = frameCharacter;
}

//Procedimiento de lectura del caracter que se recive de la interrupcion
uint8_t gpsReadCharacterReceived(){
	return gpsCharacterReceived;
}

//Procedimiento de lectura del flag de recepcion de caracter
uint8_t gpsReadFlagCharacterReceived(){
	return gpsFlags.characterReceived;
}

//Procedimineto que setea del flag de caracter recibido
void gpsSetFlagCharacterReceived(){
	gpsFlags.characterReceived = 1;
}

//Procedimiento que limpia el flag de caracter recivido
void gpsClearFlagCharacterReceived(){
	gpsFlags.characterReceived = 0;
}

//Procedimiento de lectura del flag de trama obtenida
uint8_t gpsReadFlagReady(){
	return gpsFlags.ready;
}

//Procedimiento que setea el flag de trama obtenida
void gpsSetFlagReady(){
	gpsFlags.ready = 1;
}

//Procedimiento que limpia el flag de trama obtenida
void gpsClearFlagReady(){
	gpsFlags.ready = 0;
}

//Procedimiento de lectura de la latitud
uint8_t* gpsReadLatitude(){
	return gpsData.latitude;
}

//Procedimiento de lectura de la longitud
uint8_t* gpsReadLongitude(){
	return gpsData.longitude;
}

uint8_t* gpsReadLatitudeUbidots(){

	int degreeInt;

	uint8_t degree[10];
	uint8_t minutes[9];

	degree[0] = gpsData.latitude[1];
	degree[1] = gpsData.latitude[2];
	degree[2] = '\0';

	degreeInt = atoi(degree);

	gpsFrameFieldInit((char*)degree);

	if(gpsData.eo == 'W'){
		degreeInt = degreeInt*(-1);
	}

	itoa(degreeInt, degree, 10);

	minutes[0] = gpsData.latitude[3];
	minutes[1] = gpsData.latitude[4];
	minutes[2] = gpsData.latitude[5];
	minutes[3] = gpsData.latitude[6];
	minutes[4] = gpsData.latitude[7];
	minutes[5] = gpsData.latitude[8];
	minutes[6] = gpsData.latitude[9];
	minutes[7] = gpsData.latitude[10];
	minutes[8] = '\0';

	strcpy(gpsCoordinates.latitude, gpsData.latitude[0]);
	strcat(gpsCoordinates.latitude, degree);
	strcat(gpsCoordinates.latitude, minutes);

	return gpsCoordinates.latitude;
}

uint8_t* gpsReadLongitudeUbidots(){	

	int degreeInt;

	uint8_t degree[4];
	uint8_t minutes[9];

	degree[0] = gpsData.longitude[1];
	degree[1] = gpsData.longitude[2];
	degree[2] = gpsData.longitude[3];
	degree[3] = '\0';

	degreeInt = atoi(degree);

	if(gpsData.ns == 'S'){
		degreeInt = degreeInt*(-1);
	}

	gpsFrameFieldInit((char*)degree);

	itoa(degreeInt, degree, 10);

	minutes[0] = gpsData.longitude[4];
	minutes[1] = gpsData.longitude[5];
	minutes[2] = gpsData.longitude[6];
	minutes[3] = gpsData.longitude[7];
	minutes[4] = gpsData.longitude[8];
	minutes[5] = gpsData.longitude[9];
	minutes[6] = gpsData.longitude[10];
	minutes[7] = gpsData.longitude[11];
	minutes[8] = '\0';

	strcpy(gpsCoordinates.longitude, degree);
	strcat(gpsCoordinates.longitude, minutes);

	return gpsCoordinates.longitude;
}

uint8_t gpsValidateCharacter(uint8_t character){

	if ((('a' <= character) && (character <= 'z')) || (('A' <= character) && (character <= 'Z')) || (('0' <= character) && (character <= '9')) || (character == '.') || (character == ',') || (character == '$') || (character == '*') || (character == '\n') || (character == '\r')){
		return 1;
	}

	return 0;
}

//Procedimiento que permite parsear los datos de la trama GPS
void gpsFrameParse(uint8_t frameCharacter){
	
	if (gpsValidateCharacter(frameCharacter)){
		
		switch(state)
		{
			case (frameInit):

			if (frameCharacter == '$')
			{
				gpsFrameVarInit();
				state = frameType;
			}

			break;

			case (frameType):

			if (frameCharacter == ',')		//llego aca hasta que encontre el nombre del protocolo, como por ejemplo GPGGA
			{

				if (strcmp((char *)gpsData.type,"GPGGA") == 0)		//si es GPGGA paso al campo UTC
				{
					gpsFrameIndex = 0;
					state = frameUtcTime;
				}
				else			//si no es GPGGA vuelvo a ver el siguiente protocolo
				{
					state = frameInit;		
				}
			}
			else
			{				//hasta no terminar de llenar el campo del nombre del protocolo
				if (gpsFrameIndex >= LENGTH_TYPE)
				{
					state = frameInit;
				}
				gpsData.type[gpsFrameIndex] = frameCharacter;
				gpsFrameIndex++;
			}	 

			break;

			case (frameUtcTime):

			if (frameCharacter == ',')		//si termino el campo UTC, paso al campo latitud
			{
				gpsFrameIndex = 1;
				state = frameLatitude;
			}
			else			//hasta no terminar el campo UTC, acumulo en el campo los valores
			{
				if (gpsFrameIndex >= LENGTH_UTC)
				{
					state = frameInit;
				}
				gpsData.utcTime[gpsFrameIndex] = frameCharacter;
				gpsFrameIndex++;
			}

			break;

			case (frameLatitude):

			if (frameCharacter == ',')			//si termino el campo latitud paso al campo norte sur
			{
				gpsFrameIndex = 0;
				state = frameNS;
			}	
			else			//voy llenando el campo latitud
			{
				if (gpsFrameIndex >= LENGTH_LATITUDE + 1)
				{
					state = frameInit;
				}
				gpsData.latitude[gpsFrameIndex] = frameCharacter;
				gpsFrameIndex++;
			}

			break;

			case (frameNS):

			if (frameCharacter == ',')			//paso al campo longitud
			{
				gpsFrameIndex = 1;
				state = frameLongitude;
			}		
			else			//lleno el campo norte/sur		
			{
				if (gpsFrameIndex >= LENGTH_NS)
				{
					state = frameInit;
				}				
				gpsData.ns = frameCharacter;

				if(frameCharacter == 'N'){
					gpsData.latitude[0] = '+';
				}else{
					gpsData.latitude[0] = '-';	
				}
			}

			break;

			case (frameLongitude):

			if (frameCharacter == ',')			//paso al campo Este/Oeste
			{
				gpsFrameIndex = 0;
				state = frameEO;
			}
			else				//voy llenando el campo longitud
			{
				if (gpsFrameIndex >= LENGTH_LONGITUDE + 1)
				{
					state = frameInit;
				}
				gpsData.longitude[gpsFrameIndex] = frameCharacter;
				gpsFrameIndex++;
			}

			break;

			case (frameEO):
			if (frameCharacter == ',')			//vuelvo al principio
			{
				//Para seguir procesando datos no olvidar inicializar el indice
				//gpsFrameIndex = 0;
				state = frameInit;
				gpsFlags.ready = 1;
			}
			else		//lleno el campo este/oeste
			{
				if (gpsFrameIndex >= LENGTH_EO)
				{
					state = frameInit;
				}
				gpsData.eo = frameCharacter;

				if(frameCharacter == 'E'){
					gpsData.longitude[0]='+';
				}else{
					gpsData.longitude[0]='-';
				}
			}

			break;
		}
	}
	else{

		state = frameInit;

	}

}

//Procedimiento que permite ver en pantalla los datos obtenidos de la trama GPS
void gpsVarPrint(){

	uartWriteString(UART_USB, (uint8_t *)"=====================================");
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');

	uartWriteString(UART_USB, (uint8_t *)"Tipo de trama: ");
	uartWriteString(UART_USB, gpsData.type);
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');

	uartWriteString(UART_USB, (uint8_t *)"Hora UTC: ");
	uartWriteString(UART_USB, gpsData.utcTime);
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');

	uartWriteString(UART_USB, (uint8_t *)"Latitud: ");
	uartWriteString(UART_USB, gpsData.latitude);
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r'); 

	uartWriteString(UART_USB, (uint8_t *)"Longitud: ");
	uartWriteString(UART_USB, gpsData.longitude);
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');

	uartWriteString(UART_USB, (uint8_t *)"Norte/Sur: ");
	uartWriteByte(UART_USB, gpsData.ns);
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');

	uartWriteString(UART_USB, (uint8_t *)"Este/Oeste: ");
	uartWriteByte(UART_USB, gpsData.eo);
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');

	uartWriteString(UART_USB, (uint8_t *)"Latitud Grados: ");
	uartWriteString(UART_USB, gpsReadLatitudeUbidots());
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');

	uartWriteString(UART_USB, (uint8_t *)"Longitud Grados: ");
	uartWriteString(UART_USB, gpsReadLongitudeUbidots());
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');


	uartWriteString(UART_USB, (uint8_t *)"=====================================");
	uartWriteByte(UART_USB, '\n');
	uartWriteByte(UART_USB, '\r');
}