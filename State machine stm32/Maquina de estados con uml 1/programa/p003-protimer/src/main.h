
#ifndef MAIN_H
#define MaAIN_H
#include <Arduino.h>



/*1.Dentro de main.h creamos las definiciones de estructuras y de nuestros eventos con enums*/

/*enum de señales de la aplicacion
Recordemos que las señales estan asociadas con los eventos 
*/
typedef enum 
{
INC_TIME, //SEÑAL DE INCREMENTAR TIEMPO
DEC_TIME, // SEÑAL DE DECREMENTAR TIEMPO
TIME_TICK,//SEÑAL DE TIME_TICK
START_PAUSE,//SEÑAL DE START Y PAUSA
ABRT,// SEÑAL DE ABORTAR
/*Señales de actividades internas*/
ENTRY, //SEÑAL A LA HORA DE ENTRAR A UN ESTADO
EXIT //  SEÑAL A LA HORA DE SALIR DE UN ESTADO

}protimer_signal_t;//creamos la varaible tipo protimer_signal



typedef enum
{
IDLE,//ESTADO DE INACTIVIDAD
TIME_SET,//ESTADO DE SELECCION DE TIEMPO
COUNT_DOWN, // ESTADO DE CUENTA REGRESIVA
PAUSE,// ESTADO DE PAUSA
STAT // ESTADO DE STATUS

}protimer_state_t;


/*La estructura de la aplicacion principal*/
typedef struct 
{
    //iicio de creacion de las varaibles de estado extendidas 
    uint32_t curr_time;
    uint32_t elapsed_time;
    uint32_t pro_timer;

    //fin de la creacion de varaibles de estado extendidas

    protimer_state_t active_state;//varaible de tipo protimer_state_t (varaible tipo estado) que define el estado activo

}protimer_t;


/*Creamos nuestra estrcutura de super evento
Todas las estrucutras de evento heredaran esta estrcutura de super eventop*/
typedef struct 
{
    uint8_t sig;//la señal que tendra el evento
}event_t;//creamos la estructura que sera de tipo event


/*Creamos nuestra estructura de eventos generados por el usuario
Recordemos que esta estrcutura heredara los parametros de la estructura evento, por lo que debemos de creart una varaible tipo evento*/
typedef struct 
{
event_t super;//creamos la varaible tipo evento y este será nuestro super evento

}protimer_user_event_t;

/*Creamos nuestra varaible de evento interno de tick 
Esta estructura tambien hereda los aprametros de event_t pero tambien tendra sus propios atibutos*/

typedef struct 
{
    event_t super;//creamos varaible de super estado
    uint8_t ss;//variable de parametro interno sub second
}protimer_tick_event_t;


/*Creamos la deficniion de la funcion de inicializacion del objeto de l;a maquina de estados.*/
void protimer_init(protimer_t *mobj);


#endif