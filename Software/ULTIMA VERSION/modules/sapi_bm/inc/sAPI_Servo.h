/* Copyright 2016, Ian Olivieri
 * Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
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

/* Date: 2016-02-10 */

#ifndef SAPI_SERVO_H_
#define SAPI_SERVO_H_

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros and definitions]=================================*/

/*==================[typedef]================================================*/

typedef enum{
   ENABLE_SERVO_TIMERS, DISABLE_SERVO_TIMERS,
   ENABLE_SERVO_OUTPUT, DISABLE_SERVO_OUTPUT
} ServoConfig_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*
 * @Brief: Initializes the servo peripheral
 * @param  uint8_t servoNumber
 * @param  uint8_t config
 * @return bool_t true (1) if config it is ok
 * @IMPORTANT:   this function uses Timer 1, 2 and 3 to generate the servo signals, so
 *   they won't be available to use.
 */
bool_t servoConfig( uint8_t servoNumber, uint8_t config );

/*
 * @brief:   Tells if the servo is currently active, and its position
 * @param:   servoNumber:   ID of the servo, from 0 to 8
 * @param:   value:   value of the servo, from 0 to 180
 * @return:   position (1 ~ SERVO_TOTALNUMBER), 0 if the element was not found.
 */
uint8_t servoIsAttached( uint8_t servoNumber);

/*
 * @brief: read the value of the servo
 * @param:   servoNumber:   ID of the servo, from 0 to 8
 * @return: value of the servo (0 ~ 180).
 *   If an error ocurred, return = EMPTY_POSITION = 255
 */
uint8_t servoRead( uint8_t servoNumber);

/*
 * @brief: change the value of the servo
 * @param:   servoNumber:   ID of the servo, from 0 to 8
 * @param:   value:   value of the servo, from 0 to 180
 * @return: True if the value was successfully changed, False if not.
 */
bool_t servoWrite( uint8_t servoNumber, uint8_t angle );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* SAPI_SERVO_H_ */
