/*
 * state_machine.h
 *
 *  Created on: 30 oct. 2023
 *      Author: el_gl
 */

/*FOR STATE HANDLER WE HAVE TO CHANGE SOME CODE LINES
 * 1) remove the states enum
 * 2) ON the application structure we have to change the "uint8_t active state" to a function pointer varaible. rembmeber that the state handler will store the addres of the function\
 * 2.1)declarate the function pointer before the application the application struct*/

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_


//buttons signal definition

#define button_not_pressed 	0
#define button_start_pause 	4
#define button_dec_time 	2
#define button_inc_time		1
#define button_abrt			3
typedef enum
{

NOT_PRESSED,
BOUNCE,
PRESSED
}button_state_t;


/*signals of the application*/

typedef enum
{

INC_TIME,
DEC_TIME,
TIME_TICK,
START_PAUSE,
ABRT,
/*internal activity signals*/
ENTRY,
DO,
EXIT
}protimer_signal_t;


#define STATE_IDLE &protimer_state_handler_IDLE
#define STATE_TIME_SET &protimer_state_handler_TIME_SET
#define STATE_COUNTDOWN &protimer_state_handler_COUNTDOWN
#define STATE_PAUSE &protimer_state_handler_PAUSE
#define STATE_STAT &protimer_state_handler_STAT


typedef enum
{
		EVENT_HANDLED,
		EVENT_IGNORED,
		EVENT_TRANSITION

}event_status_t;

//forward declarations
struct protimer_tag;
struct event_tag;

typedef event_status_t (*protimer_state_t)(struct protimer_tag *const , struct event_tag  const * const );

/*main application structure*/

typedef struct protimer_tag
{
	uint32_t curr_time;
	uint32_t elapsed_time;
	uint32_t pro_time;
	protimer_state_t active_State;

}protimer_t;
/*generic (super)event structure*/

typedef struct event_tag
{
uint8_t sig;

}event_t;


/*for user generated events*/
typedef struct
{
event_t super;

}protimer_user_event_t;

/*for tick event*/

typedef struct
{
event_t super;
uint8_t ss;
}protimer_tick_event_t;




/*STATE MACHINE FUNCTIONS */

/*initialitaion of the object and state machine*/
void protimer_init(protimer_t *const mobj);

/*state machine function*/
event_status_t protimer_state_machine(protimer_t *const mobj, event_t const *const e);

/*state handlers of the state  machine
 * note: the double const on event structure of do inmutable the address of the pointer and the data of the*/

 event_status_t protimer_state_handler_IDLE(protimer_t *const mobj, event_t const * const e);
 event_status_t protimer_state_handler_TIME_SET(protimer_t  *const mobj, event_t const *const e);
 event_status_t protimer_state_handler_COUNTDOWN(protimer_t  *const mobj, event_t const *const e);
 event_status_t protimer_state_handler_PAUSE(protimer_t  *const mobj, event_t const *const e);
 event_status_t protimer_state_handler_STAT(protimer_t  *const mobj, event_t const *const e);

/*event dispatcher*/

void protimer_event_dispatcher(protimer_t *const mobj, event_t *const e);

/*tick event dispatcher for every 100 ms*/

void protimer_tick_event_dispatcher(protimer_t *const mobj, event_t *const e);

/*Button debouncing*/

uint8_t button_deboucing(uint8_t button_value);

//funcion para leer los botones
uint8_t button_read();
/*helper functions
 *
 * note: the static keyword in a function declaration its for the scope is limited to the source code file in which it is define
 *
 * */

 void do_beep(void);

/*functions for the lcd using in the state machine*/
 void display_clear(lcd_t * const lcd);
 void display_message(lcd_t * const lcd,char *str,uint8_t c,uint8_t r);
 void display_time(lcd_t * const lcd,uint32_t time);

#endif /* STATE_MACHINE_H_ */
