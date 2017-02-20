/* Copyright 2015-2016, Eric Pernia.
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

/* Date: 2015-09-23 */

/*==================[inclusions]=============================================*/

#include "chip.h"
#include "sAPI_DataTypes.h"
#include "sAPI_Timer.h"

#include "sAPI_Tick.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/* This global variable holds the tick count */
volatile tick_t tickCounter;
volatile tick_t tickRateMS;
volatile sAPI_FuncPtr_t tickHookFunction = sAPI_NullFuncPtr;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* Tick rate configuration 1 to 50 ms */
bool_t tickConfig(tick_t tickRateMSvalue, sAPI_FuncPtr_t tickHook ) {

   bool_t ret_val = 1;
   tick_t tickRateHz = 0;

   if( tickHook ){
      tickHookFunction = tickHook;
   }

   if( (tickRateMSvalue >= 1) && (tickRateMSvalue <= 50) ){

		tickRateMS = tickRateMSvalue;

      /*
      tickRateHz = 1000 => 1000 ticks per second =>  1 ms tick
      tickRateHz =  200 =>  200 ticks per second =>  5 ms tick
      tickRateHz =  100 =>  100 ticks per second => 10 ms tick
      tickRateHz =   20 =>   20 ticks per second => 50 ms tick
      */
      tickRateHz = 1000 / tickRateMSvalue;

      /* Init SysTick interrupt, tickRateHz ticks per second */
      SysTick_Config( SystemCoreClock / tickRateHz);
   }
   else{
      /* Error, tickRateMS variable not in range (1 <= tickRateMS <= 50) */
      ret_val = 0;
   }

   return ret_val;
}


/* Read Tick Counter */
tick_t tickRead( void ) {
   return tickCounter;
}


/* Write Tick Counter */
void tickWrite( tick_t ticks ) {
   tickCounter = ticks;
}

/*==================[ISR external functions definition]======================*/

__attribute__ ((section(".after_vectors")))

/* SysTick Timer ISR Handler */
void SysTick_Handler(void) {
   tickCounter++;

	/* Execute Tick Hook function */
	(* tickHookFunction )( 0 );
}

/*==================[end of file]============================================*/
