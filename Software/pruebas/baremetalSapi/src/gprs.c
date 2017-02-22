#include "gprs.h"
#include "sapi.h"
#include <string.h>

uint8_t gprsResponseFlag = 1; // 1 -> OK 2 -> > enviar 3 -> error
uint8_t gprsResponseString[256];
uint8_t stringOne[56];
uint8_t stringTwo[56];
uint8_t stringThree[56];
uint8_t stringAEnviar[256];

//Enumerativo para el control de los estados posibles del módem GPRS
enum gprsState
{
  INIT,
  SENDING,
  READING,
  IDLE
};

enum gprsSendState {
  STRING,
  ACTION
};

enum gprsState actualState = IDLE;
enum gprsSendState sendState = IDLE;

void GPRS_mef(uint8_t* pas, uint8_t* lat, uint8_t* lng) {
  uartWriteString(UART_USB, (uint8_t*)" GPRS - ENVIAR - - - - - - - - -  \n");
  if ( actualState == IDLE ) {
    uartWriteString( UART_USB, (uint8_t*)" - GPRS - ENVIAR - INICIANDO - \n");
    gprsResponseString[0]='\0';
    stringAEnviar[0]='\0';
    uint8_t aux;

    strcat(stringAEnviar, stringOne);
    strcat(stringAEnviar, pas);
    strcat(stringAEnviar, stringTwo);
    strcat(stringAEnviar, lat);
    strcat(stringAEnviar, stringThree);
    strcat(stringAEnviar, lng);
    strcat(stringAEnviar, (uint8_t*)"}");

    uartWriteString( UART_USB, stringAEnviar);
    uartWriteString( UART_USB, (uint8_t*)"\n");

    uartWriteString(UART_485, (uint8_t*)"AT+HTTPDATA=50,2000\r");

    actualState = SENDING;
    sendState = STRING;
  }
  else if ( actualState == SENDING ) {
    if ( sendState == STRING ) {
      uartWriteString( UART_USB, (uint8_t*)" - GPRS - ENVIAR - STRING - \n");
      uartWriteString( UART_485, stringAEnviar);
      sendState = ACTION;
    }
    else if ( sendState == ACTION ) {
      uartWriteString( UART_USB, (uint8_t*)" - GPRS - ENVIAR - ACTION - FIN \n");
      uartWriteString(UART_485, (uint8_t*)"AT+HTTPACTION=1\r");
      actualState = IDLE;
    }
  }

  // GPRS_leerRespuesta();
}

void GPRS_leerRespuesta(){
  actualState = READING;
  uartWriteString( UART_USB, gprsResponseString);
  uartWriteString( UART_USB, (uint8_t*)"\n");
  gprsResponseString[0]='\0';
  actualState = IDLE;
}

void GPRS_init(void){
  actualState = INIT;

  uint8_t aux;
  uartWriteString( UART_USB, (uint8_t*)"\n - - - INICIALIZACIÓN GPRS - - - \n");

  // {"pas": 0, "lat": 1234567890, "lng": 9876543210}
  // stringAEnviar  -> posicion 50: pasajero
  //                -> posicion 104: lat
  //                -> posicion 166: lng
  strcpy(stringOne,(uint8_t*)"{\"pas\": ");
  strcpy(stringTwo,(uint8_t*)", \"lat\": ");
  strcpy(stringThree,(uint8_t*)", \"lng\": ");
  strcpy(stringAEnviar,(uint8_t*)" ");
  gprsResponseString[0] = '\0';

  uartWriteString( UART_485, (uint8_t*)"AT\r");
  delay(60);
  esperaRespuesta();

  // // Ver si necesita poner PIN de la sim
  // uartWriteString( UART_485, (uint8_t*)"AT+CPIN?\r");
  // esperaRespuesta();

  // Ver intensidad de señal promedio 25
  uartWriteString( UART_485, (uint8_t*)"AT+CSQ\r");
  delay(60);
  esperaRespuesta();

  uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r");
  delay(60);
  // aux = esperaRespuesta();
  // while ( aux != 0 ){
  //   uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r");
  //   delay(60);
  //   aux = esperaRespuesta();
  // }

  // uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"APN\",\"wap.gprs.unifon.com.ar\"\r");
  uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"APN\",\"internet.movil\"\r");
  delay(60);
  aux = esperaRespuesta();
  while ( aux != 0 ){
    // uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"APN\",\"wap.gprs.unifon.com.ar\"\r");
    uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"APN\",\"internet.movil\"\r");
    delay(60);
    aux = esperaRespuesta();
  }

  // uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"USER\",\"wap\"\r");
  uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"USER\",\"internet\"\r");
  delay(60);
  aux = esperaRespuesta();
  while ( aux != 0 ){
    // uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"USER\",\"wap\"\r");
    uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"USER\",\"internet\"\r");
    delay(60);
    aux = esperaRespuesta();
  }

  // uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"PWD\",\"wap\"\r");
  uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"PWD\",\"internet\"\r");
  delay(60);
  aux = esperaRespuesta();
  while ( aux != 0 ){
    // uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"PWD\",\"wap\"\r");
    uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=3,1,\"PWD\",\"internet\"\r");
    delay(60);
    aux = esperaRespuesta();
  }

  // Activa estado gprs
  uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=1,1\r");
  delay(60);
  // aux = esperaRespuesta();
  // while( aux != 0){
  //   uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=1,1\r");
  //   delay(60);
  //   aux = esperaRespuesta();
  // }

  // Muestra ip asignada por ISP
  uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=2,1\r");
  delay(60);
  aux = esperaRespuesta();
  while( aux != 0){
    uartWriteString( UART_485, (uint8_t*)"AT+SAPBR=2,1\r");
    delay(60);
    aux = esperaRespuesta();
  }

  uartWriteString(UART_485, (uint8_t*)"AT+HTTPINIT\r");
  delay(60);
  // aux = esperaRespuesta();
  // while ( aux != 0 ) {
  //   uartWriteString(UART_485, (uint8_t*)"AT+HTTPINIT\r");
  //   delay(60);
  //   aux = esperaRespuesta();
  // }

  uartWriteString(UART_485, (uint8_t*)"AT+HTTPPARA=\"CID\",1\r");
  delay(60);
  // aux = esperaRespuesta();
  // while ( aux != 0 ) {
  //   uartWriteString(UART_485, (uint8_t*)"AT+HTTPPARA=\"CID\",1\r");
  //   delay(60);
  //   aux = esperaRespuesta();
  // }

  uartWriteString(UART_485, (uint8_t*)"AT+HTTPPARA=\"URL\",\"http://things.ubidots.com/api/v1.6/devices/ciaa/?token=4GOvwGlOzE9hfL9sKKeelcEhXO9z5h\"\r");
  delay(60);
  aux = esperaRespuesta();
  while ( aux != 0 ) {
    uartWriteString(UART_485, (uint8_t*)"AT+HTTPPARA=\"URL\",\"http://things.ubidots.com/api/v1.6/devices/ciaa/?token=4GOvwGlOzE9hfL9sKKeelcEhXO9z5h\"\r");
    delay(60);
    aux = esperaRespuesta();
  }

  uartWriteString(UART_485, (uint8_t*)"AT+HTTPPARA=\"CONTENT\",\"application/json\"\r");
  delay(60);
  aux = esperaRespuesta();
  while ( aux != 0 ) {
    uartWriteString(UART_485, (uint8_t*)"AT+HTTPPARA=\"CONTENT\",\"application/json\"\r");
    delay(60);
    aux = esperaRespuesta();
  }

  uartWriteString(UART_USB, (uint8_t*)" - - - GPRS INICIALIZADO - - -\n\n");
  actualState = IDLE;
}

uint8_t esperaRespuesta(){
  uartWriteString(UART_USB, (uint8_t*)"Esperando respuesta...\n");
  while(gprsResponseFlag == 0); // mientras no reciba caracter del modem
  gprsResponseFlag = 0;
  //Si el string de respuesta contiene un OK retorna 0
  if ( strstr(gprsResponseString, (uint8_t*)"DOWNLOAD") != NULL ){
    uartWriteString( UART_USB, (uint8_t*)gprsResponseString);
    uartWriteString( UART_USB, (uint8_t*)" --------------- DOWNLOAD\n");
    gprsResponseString[0] = '\0';
    return 0;
  }
  else if (strstr(gprsResponseString, (uint8_t*)"HTTPACTION: 1,200") != NULL){
    uartWriteString( UART_USB, (uint8_t*)gprsResponseString);
    uartWriteString( UART_USB, (uint8_t*)" --------------- HTTPACTION OK\n");
    gprsResponseString[0] = '\0';
    return 0;
  } else if (strstr(gprsResponseString, (uint8_t*)"CONNECT") != NULL){
    uartWriteString( UART_USB, gprsResponseString);
    uartWriteString( UART_USB, (uint8_t*)" --------------- CONNECTED\n");
    gprsResponseString[0] = '\0';
    // memset(gprsResponseString,0,strlen(gprsResponseString));
    return 0;
  } else if (strstr(gprsResponseString, (uint8_t*)"OK\r\n") != NULL){
    // Fin de respuesta
    uartWriteString( UART_USB, gprsResponseString);
    uartWriteString( UART_USB, (uint8_t*)"\n ------------- OK ENCONTRADO\n");
    gprsResponseString[0] = '\0';
    return 0;
    // Si la respuesta tiene error retorna 1
  } else if (strstr(gprsResponseString, (uint8_t*)"ERROR") != NULL){
    uartWriteString( UART_USB, gprsResponseString);
    uartWriteString( UART_USB, (uint8_t*)"\n ------------- ERROR \n");
    gprsResponseString[0] = '\0';
    return 1;
  } else if (strstr(gprsResponseString, (uint8_t*)">") != NULL){
    uartWriteString( UART_USB, gprsResponseString);
    uartWriteString( UART_USB, (uint8_t*)" --------------- SEND\n");
    gprsResponseString[0] = '\0';
    // memset(gprsResponseString,0,strlen(gprsResponseString));
    return 0;
  }

  return 2;
}
