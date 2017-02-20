#include "sapi.h"

// Respuesta de la UART
extern uint8_t gprsResponseString[256];

// Inicialización
void GPRS_init(void);

// Es una máquina de estados con 3 estados
// Este metodo se encarga de recibir los parametros, ejecutar el codigo necesario segun el estado y a su vez de actualizar el estado de la MEF
// Para finalizar el envío de datos se debe llamar a esta función tres veces, con al menos 50 ms de tiempo entre llamada y llamada
// En la primer llamada los parametros son tomados, en las restantes dos llamadas los parametros son ignorados
// Para iniciar un nuevo envío se debe asegurar de haber pasado al menos 2 segundos luego de las ultimas 3 llamadas
void GPRS_mef(uint8_t* pas, uint8_t* lat, uint8_t* lng);

// Metodo de debugging para leer la respuesta (luego de imprimir limpia la respuesta)
void GPRS_leerRespuesta();

// Usado en el GPRS_init (no darle bola)
uint8_t esperaRespuesta();
