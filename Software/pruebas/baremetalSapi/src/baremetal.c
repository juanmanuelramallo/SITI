/* Copyright 2014, 2015 Mariano Cerdeiro
* Copyright 2014, Pablo Ridolfi
* Copyright 2014, Juan Cecconi
* Copyright 2014, Gustavo Muro
* All rights reserved.
*
* This file is part of CIAA Firmware.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

/** \brief Bare Metal example source file
**
** This is a mini example of the CIAA Firmware.
**
**/

/** \addtogroup CIAA_Firmware CIAA Firmware
** @{ */
/** \addtogroup Examples CIAA Firmware Examples
** @{ */
/** \addtogroup Baremetal Bare Metal example source file
** @{ */

/*
* Initials     Name
* ---------------------------
*
*/

/*
* modification history (new versions first)
* -----------------------------------------------------------
* yyyymmdd v0.0.1 initials initial version
*/

/*==================[inclusions]=============================================*/
#include "baremetal.h"       /* <= own header */
#include "sAPI.h"
#include "gps.h"
#include "gprs.h"

// #ifndef CPU
// #error CPU shall be defined
// #endif
// #if (lpc4337 == CPU)
// #include "chip.h"
// #elif (mk60fx512vlq15 == CPU)
// #else
// #endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
*
* This is the main entry point of the software.
*
* \returns 0
*
* \remarks This function never returns. Return value is only to avoid compiler
*          warnings or errors.
*/
#define FACTOR 0.25

static uint8_t uartBuff[10];
//static uint8_t uartBuff2[10];
uint8_t contador;
uint8_t contadorString[3];

bool_t flag20seg;
bool_t flag5ms;
bool_t flagDatos;
bool_t flag3seg;

/*==================[internal data definition]==============================*/
typedef struct {

	uint16_t puntoMedio;
	uint16_t umbralAlto;
	uint16_t umbralBajo;

	tick_t flancoAsc;
	tick_t flancoDes;
	tick_t periodo;
	tick_t comienzoPeriodo;

	uint16_t muestraAct;
	uint16_t muestraAnt;

} Canal;


/*==================[internal functions definition]==========================*/

// Funcion para convertir un valor numérico en una cadena de texto
char* itoa(int value, char* result, int base) {
 // check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

 // Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

/*
Función que calcula el promedio de 10 muestras. Recibe:
-Canal: indica el canal del adc que se debe leer
  1 (CH1, asociado a AI0)
  2 (CH2, asociado a AI1)
-Nivel: indica si se debe calcular el promedio en nivel alto o bajo
  HIGH: nivel alto
  LOW: nivel bajo
*/
float promedio( uint8_t canal , uint8_t nivel  )
{
	uint8_t uartBuff[10];
float     promedio;    // Promedio de las "N - 1" muestras leidas
uint16_t  N = 0;       // Numero de muestras leidas
uint16_t  muestra;     // Muestra leida
uint8_t   i;           // Variable indice

delay_t delay1;
delayConfig( &delay1, 50 );

// Establece una salida en nivel alto o bajo segun corresponda
if( nivel == HIGH )
  pwmWrite( PWM6, 255 );    // GPIO 8
else
  pwmWrite( PWM6, 0 );    // GPIO 8

while( !delayRead( &delay1 ) );

// Lee la primera muestra
if( canal == 1 )
	muestra = analogRead( AI0 );
else
	muestra = analogRead( AI1 );

N++;
promedio = muestra;


// Promedia las lecturas de las 9 muestras restantes
for( i = 0 ; i < 10 ; i++ ){
	if( canal == 1 )
		muestra = analogRead( AI0 );
	else
		muestra = analogRead( AI1 );

	N++;
	promedio = ((float) 1/N)*((N-1)*promedio + muestra);
}

return promedio;
}


void procesaLectura( Canal *ptrCanal )
{
// Si se lee una muestra con nivel definido en el canal
	if( ptrCanal->muestraAct > ptrCanal->umbralAlto || ptrCanal->muestraAct < ptrCanal->umbralBajo ){
		if( ptrCanal->muestraAct < ptrCanal->umbralBajo && ptrCanal->muestraAnt > ptrCanal->umbralAlto ){
			ptrCanal->flancoDes = tickRead();
			uartWriteString( UART_USB, (uint8_t*)"CHx: Flanco de bajada\n\r" );
		}
		if( ptrCanal->muestraAct > ptrCanal->umbralAlto && ptrCanal->muestraAnt < ptrCanal->umbralBajo ){
			ptrCanal->flancoAsc = tickRead();
			uartWriteString( UART_USB, (uint8_t*)"CHx: Flanco de subida\n\r" );
		}
		if( ptrCanal->flancoAsc > 0 && ptrCanal->flancoDes > 0){
			ptrCanal->periodo = (ptrCanal->flancoAsc - ptrCanal->flancoDes)*5;
			ptrCanal->comienzoPeriodo = ptrCanal->flancoDes;
			ptrCanal->flancoAsc = ptrCanal->flancoDes = 0;

			uartWriteString( UART_USB, (uint8_t*)"CHx: PULSO (" );
			itoa( ptrCanal->periodo, uartBuff, 10 );
			uartWriteString( UART_USB, uartBuff );
			uartWriteString( UART_USB, (uint8_t*)" ms)\n\r" );
		}
		ptrCanal->muestraAnt = ptrCanal->muestraAct;
	}

}

void cuentaPasajero( Canal *ptrCanal1 , Canal *ptrCanal2 )
{
	int64_t diferenciaFlancos;

// Si algo atravesó los dos sensores
	if( ptrCanal1->periodo > 0 && ptrCanal2->periodo > 0 ){

		diferenciaFlancos = ptrCanal1->comienzoPeriodo - ptrCanal2->comienzoPeriodo;
		diferenciaFlancos = diferenciaFlancos*5;

  // Si lo que atravesó los sensores es una persona (inserte AA aquí)
		if( ptrCanal1->periodo > 100 && ptrCanal2->periodo > 100 )
			if( diferenciaFlancos > 0 ){
				uartWriteString( UART_USB, (uint8_t*)"PERSONA: Ascenso de pasajero\n\r" );
				contador++;
			}
			else {
				uartWriteString( UART_USB, (uint8_t*)"PERSONA: Descenso de pasajero\n\r" );
				if (contador > 0) {
					contador--;
				} else {
					uartWriteString( UART_USB, (uint8_t*)"NO HAY PASAJEROS PARA RESTAR\r\n");
				}
			}

			ptrCanal1->periodo = ptrCanal2->periodo = 0;

		}
	}

	void determinarUmbral( Canal *ptrCanal , uint8_t numCanal )
	{
// Calcular los umbrales para cada canal como:
		ptrCanal->puntoMedio = ( (float) ( promedio(numCanal,HIGH) + 0*promedio(numCanal,LOW) ) )/2;

		ptrCanal->umbralAlto = ptrCanal->puntoMedio + FACTOR*( float ) ptrCanal->puntoMedio;
		ptrCanal->umbralBajo = ptrCanal->puntoMedio - FACTOR*( float ) ptrCanal->puntoMedio;


	}

	/* FUNCION que se ejecuta cada vezque ocurre un Tick. */
bool_t sendCounter( void *ptr ){

   static uint16_t tickCounter = 0;

	 tickCounter++;
	 flag5ms = true;
	 // considerando la config actual de cada 1ms
   if( tickCounter == 4000 ){
      flag20seg = true;
   }
	 if( tickCounter % 600 == 0){
		 flag3seg = true;
	 }

	 // si pasaron mas de 5 segundos
	 // restablecer el tickcounter
	 if ( tickCounter == 4000 ){
		 tickCounter = 0;
	 }

   return 1;
}


	int main(void)
	{
/* perform the needed initialization here */
/* Inicializar la placa */
		boardConfig();

/* Inicializar el conteo de Ticks con resolución de 1ms, sin tickHook */
		tickConfig( 5, sendCounter );

/* Inicializar DigitalIO */
		digitalConfig( 0, ENABLE_DIGITAL_IO );

/* Configuración de pines de entrada para Teclas de la CIAA-NXP */
		digitalConfig( TEC1, INPUT );
		digitalConfig( TEC2, INPUT );
		digitalConfig( TEC3, INPUT );
		digitalConfig( TEC4, INPUT );

/* Configuración de pines de salida para Leds de la CIAA-NXP */
		digitalConfig( LEDR, OUTPUT );
		digitalConfig( LEDG, OUTPUT );
		digitalConfig( LEDB, OUTPUT );
		digitalConfig( LED1, OUTPUT );
		digitalConfig( LED2, OUTPUT );
		digitalConfig( LED3, OUTPUT );

/* Inicializar UART_USB a 115200 baudios */
		uartConfig( UART_USB, 115200 );
		uartConfig( UART_232, 9600 );
		uartConfig( UART_485, 9600 );

digitalConfig( CTOUT7, OUTPUT );         // Establece GPIO2 como salida

analogConfig( ENABLE_ANALOG_INPUTS );    // Inicializar AnalogIO

pwmConfig( 0,    ENABLE_PWM_TIMERS );    // Activar los timers
pwmConfig( PWM6, ENABLE_PWM_OUTPUT );   // Ver en sAPI_PWM.c que hay 11 PWMs: el PWM6 se reserva para GPIO8

/* VARIABLES LOCALES */
Canal CH1;
Canal CH2;

// Valores iniciales
CH1.flancoAsc = 0;
CH1.flancoDes = 0;
CH1.periodo = 0;

CH2.flancoAsc = 0;
CH2.flancoDes = 0;
CH1.periodo = 0;

determinarUmbral( &CH1 , 1 );
determinarUmbral( &CH2 , 2 );

pwmWrite( PWM6, 255);    // gpio 8

/* SECCION PRINCIPAL */

// Delay para tener mejor visualizacion de la salida
delay_t delay1;
delayConfig( &delay1, 5 );

while( !delayRead( &delay1 ) );

CH1.muestraAnt = analogRead( AI0 );
CH2.muestraAnt = analogRead( AI1 );

// delay(3000);

// uartWriteString( UART_USB, (uint8_t*)"\n\r ============================================================== \n\r" );
// uartWriteString( UART_USB, (uint8_t*)"\n\rComienza simulacion\n\r SALTAR GPRS INIT \r\n" );

// GPRS_init();
// delay(100);

uint8_t veces = 0;
// strcpy(contadorString, (uint8_t*)"5");

bool_t flagSending = false;

while(1) {
/* add your code here */
	if( flag5ms ){

		CH1.muestraAct = analogRead( AI0 );
		procesaLectura( &CH1 );

		CH2.muestraAct = analogRead( AI1 );
		procesaLectura( &CH2 );

		cuentaPasajero( &CH1 , &CH2 );

		// uartWriteString(UART_USB, (uint8_t*)"Lectura CH1: ");
		// itoa(CH1.muestraAct, contadorString, 10);
		// uartWriteString(UART_USB, (uint8_t*)contadorString);
		// uartWriteString(UART_USB, (uint8_t*)"\t");
		// itoa(CH1.puntoMedio, contadorString, 10);
		// uartWriteString(UART_USB, (uint8_t*)contadorString);
		// uartWriteString(UART_USB, (uint8_t*)"\t");
		//
		// itoa(CH2.muestraAct, contadorString, 10);
		// uartWriteString(UART_USB, (uint8_t*)"Lectura CH2: ");
		// uartWriteString(UART_USB, (uint8_t*)contadorString);
		// uartWriteString(UART_USB, (uint8_t*)"\t");
		// itoa(CH2.puntoMedio, contadorString, 10);
		// uartWriteString(UART_USB, (uint8_t*)contadorString);
		// uartWriteString(UART_USB, (uint8_t*)"\n");

		flag5ms = false;
	}

	if (flag20seg) {
		itoa(contador, contadorString, 10);
		uartWriteString(UART_USB, (uint8_t*)"CONTADOR: ");
		uartWriteString(UART_USB, (uint8_t*)contadorString);
		uartWriteString(UART_USB, (uint8_t*)"\n");
		uartWriteString(UART_USB, (uint8_t*)"GPS: LAT -> ");
		uartWriteString(UART_USB, (uint8_t*)gpsReadLatitudeUbidots());
		uartWriteString(UART_USB, (uint8_t*)" - LNG -> ");
		uartWriteString(UART_USB, (uint8_t*)gpsReadLongitudeUbidots());
		uartWriteString(UART_USB, (uint8_t*)"\n");
	}

	if(gpsReadFlagCharacterReceived()){
		gpsClearFlagCharacterReceived();
		gpsFrameParse(gpsReadCharacterReceived());
	}

	if (gpsReadFlagReady()){
			//imprime los datos obtenidos
			flagDatos = true;
			gpsClearFlagReady();
			// gpsVarPrint();
			itoa(contador, contadorString, 10);
			//uartWriteString( UART_USB, (uint8_t*)"Cantidad pasajeros: ");
			//uartWriteString( UART_USB, (uint8_t*)contadorString);
			uartWriteByte(UART_USB,'\n');
			uartWriteByte(UART_USB,'\r');
	}

	if (flag20seg) {
		// GPRS_mef(contadorString, gpsReadLatitudeUbidots(), gpsReadLongitudeUbidots());
		veces++;
		flag20seg = false;
		flag3seg = false;
		flagSending = true;
		// GPRS_leerRespuesta();
	}

	if (flag3seg) {
		itoa(contador, contadorString, 10);
		uartWriteString( UART_USB, (uint8_t*)"Contador pasajero: ");
		uartWriteString( UART_USB, (uint8_t*)contadorString);
		uartWriteString( UART_USB, (uint8_t*)"\n");
		flag3seg = false;
	}

	// if (flag3seg && flagSending) {
	// 	if (veces < 3) {
	// 		GPRS_mef(contadorString, gpsReadLatitudeUbidots(), gpsReadLongitudeUbidots());
	// 		veces++;
	// 		GPRS_leerRespuesta();
	// 	} else {
	// 		flagSending = false;
	// 		veces = 0;
	// 		GPRS_leerRespuesta();
	// 	}
	// 	flag3seg = false;
	// }

	// GPRS_leerRespuesta();

//uartWriteString(UART_USB, (uint8_t*)"FIN DEL WHILE ***********************************\n\n\r");

}
uartWriteString(UART_USB, (uint8_t*)"FIN DEL PROGRAMA ***********************************\n\n\n");

/* Nunca debe pasar por aca */
return 0;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
