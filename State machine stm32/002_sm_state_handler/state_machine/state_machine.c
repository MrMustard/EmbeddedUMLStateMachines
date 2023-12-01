/*
 * state_machine.c
 *
 *  Created on: 30 oct. 2023
 *      Author: el_gl
 */

#include "main.h"
#include "lcd.h"
#include "state_machine.h"
#include "stdlib.h"
#include "stdio.h"

extern lcd_t lcd_1;
/*STATE MACHINE FUNCTIONS */

/*initialitaion of the object and state machine*/
void protimer_init(protimer_t *const mobj)
{
	event_t ee;
	ee.sig =ENTRY;
	//mobj->active_State =STATE_IDLE;
	mobj->active_State = STATE_IDLE;
	mobj->pro_time=0;
	(*mobj->active_State)(mobj,&ee);//jump to IDLE

}

/*state machine function*/

/*states:
 * STATE_IDLE,
 * STATE_TIME_SET,
 * STATE_COUNTDOWN,
 * STATE_PAUSE,
 * STATE_STAT
 *
 *
 *
 *
 * The state machine will return the status of the event, it will be:
 *
 * 		EVENT_HANDLED,
		EVENT_IGNORED,
		EVENT_TRANSITION
 * */
event_status_t protimer_state_machine(protimer_t *const mobj, event_t const *const e)
{


}

/*state handlers of the state  machine
 * note: the double const on event structure of do inmutable the address of the pointer and the data of the*/

 event_status_t protimer_state_handler_IDLE(protimer_t *const mobj, event_t const * const e)
{
	//put both internal and external events
	switch(e->sig)
	{

		case ENTRY:
		{

		mobj->curr_time=0;
		mobj->elapsed_time =0;
		display_time(&lcd_1, 0);
		display_message(&lcd_1, "Set", 0, 0);
		display_message(&lcd_1, "Time", 0, 1);
		return EVENT_HANDLED;
		}//end of entry

		case EXIT:
		{
			//display_clear(&lcd_1);
			lcd_clear(&lcd_1);
			return EVENT_HANDLED;

		}//end of exit

		//if we receive the event inc_time we will take a transition
		case INC_TIME:
		{
			mobj->curr_time+=60;
			mobj->active_State = STATE_TIME_SET;
			return EVENT_TRANSITION;

		}//end of INC_TIME


		case START_PAUSE:
		{

			mobj->active_State=STATE_STAT;
			return EVENT_TRANSITION;

		}//end of start_pause


		case TIME_TICK:
		{
			if( ((protimer_tick_event_t * )(e))->ss==5)
			{
				do_beep();
				return EVENT_HANDLED;

			}//end if

			return EVENT_IGNORED;

		}//end of time_tick


	}//end of switch

	return EVENT_IGNORED;
}
 event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj,event_t const *const e) {
	switch (e->sig) {
	case ENTRY: {

		display_time(&lcd_1, mobj->curr_time);
		return EVENT_HANDLED;
	}
	case EXIT: {
		display_clear(&lcd_1);
		return EVENT_HANDLED;

	}
	case INC_TIME: {

		mobj->curr_time += 60;
		display_time(&lcd_1, mobj->curr_time);
		return EVENT_HANDLED;
	}
	case DEC_TIME: {
		if (mobj->curr_time >= 60) {
			mobj->curr_time -= 60;
			display_time(&lcd_1, mobj->curr_time);
			return EVENT_HANDLED;
		}

		return EVENT_IGNORED;
	}
	case ABRT:
	{

		mobj->active_State = STATE_IDLE;
		return EVENT_TRANSITION;
	}

	case START_PAUSE: {
		if (mobj->curr_time >= 60)
		{
			mobj->active_State = STATE_COUNTDOWN;
			return EVENT_TRANSITION;
		}
		return EVENT_IGNORED;
	}

	} //end of switch

	return EVENT_IGNORED;
}
 event_status_t protimer_state_handler_COUNTDOWN(protimer_t  *const mobj, event_t const *const e)
{
	switch(e->sig)
	{

	case EXIT:
	{
		mobj->pro_time += mobj->elapsed_time;
		mobj->elapsed_time=0;
		return EVENT_HANDLED;
	}
	case TIME_TICK:
	{
		if(((protimer_tick_event_t*)(e))->ss ==10)
		{
			--mobj->curr_time;
			++mobj->elapsed_time;
			display_time(&lcd_1, mobj->curr_time);
			if(!mobj->curr_time)
			{
				for(uint8_t counter=0; counter<=10; counter++)
				{
					HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, GPIO_PIN_SET);
					HAL_Delay(25);
					HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, GPIO_PIN_RESET);
					HAL_Delay(25);
				}


				mobj->active_State=STATE_IDLE;

			 return EVENT_TRANSITION;
			}

			return EVENT_HANDLED;
		}
		return EVENT_IGNORED;

	}


	case START_PAUSE:
	{
		mobj->active_State =STATE_PAUSE;
		return EVENT_TRANSITION;

	}

	case ABRT:
	{

		mobj->active_State = STATE_IDLE;
		return EVENT_TRANSITION;
	}

	}//end of switch

	return EVENT_IGNORED;
}
 event_status_t protimer_state_handler_PAUSE(protimer_t  *const mobj, event_t const *const e)
{

	switch(e->sig)
	{

		case ENTRY:
		{
			display_message(&lcd_1, "paused", 5, 1);
			return EVENT_HANDLED;

		}
		case EXIT:
		{
			display_clear(&lcd_1);
			return EVENT_HANDLED;
		}
		case INC_TIME:
		{
			mobj->curr_time+=60;
			mobj->active_State=STATE_TIME_SET;
		}

		case DEC_TIME :
		{
			if(mobj->curr_time >= 60)
			{
				mobj->curr_time-=60;
				mobj->active_State=STATE_TIME_SET;
				return EVENT_TRANSITION;

			}
			return EVENT_IGNORED;
		}
		case START_PAUSE:
		{
			mobj->active_State=STATE_COUNTDOWN;
			return EVENT_TRANSITION;
		}
		case ABRT:
		{
			mobj->active_State=STATE_IDLE;
			return EVENT_TRANSITION;
		}


	}//end switch
	return EVENT_IGNORED;
}
 event_status_t protimer_state_handler_STAT(protimer_t  *const mobj, event_t const *const e)
{
	static uint8_t tick_count;

	switch(e->sig)
	{
		case ENTRY:
		{
			display_time(&lcd_1, mobj->pro_time);
			display_message(&lcd_1, "productive time", 1, 1);
			return EVENT_HANDLED;
		}

		case EXIT:
		{
			display_clear(&lcd_1);
			return EVENT_HANDLED;

		}
		case TIME_TICK:
		{
			if(++tick_count >=30)
			{
				tick_count=0;
				mobj->active_State=STATE_IDLE;
				return EVENT_TRANSITION;

			}

			return EVENT_IGNORED;

		}


	}//end switch


	return EVENT_IGNORED;

}

/*************************************event dispatcher***********************************************/
void protimer_event_dispatcher(protimer_t *const mobj, event_t *const e)
{

	event_status_t status;
	  protimer_state_t source, target;

	  source = mobj->active_State;
	  status = (*mobj->active_State)(mobj,e);

	  if(status == EVENT_TRANSITION){
	    target = mobj->active_State;
	    event_t ee;
	    //1. run the exit action for the source state
	    ee.sig = EXIT;
	   (*source)(mobj,&ee);

	    //2. run the entry action for the target state
	    ee.sig = ENTRY;
	    (*target)(mobj,&ee);
	  }

}

/*tick event dispatcher for every 100 ms*/

void protimer_tick_event_dispatcher(protimer_t *const mobj, event_t *const e)
{
	static protimer_tick_event_t te;
	static uint32_t current_time=0;

	if(HAL_GetTick()-current_time >=100)
	{
		current_time=HAL_GetTick();
		te.super.sig=TIME_TICK;//indicamos que ya existio un evento de tick
		if(++te.ss>10)
		{

			te.ss=1;


		}

		protimer_event_dispatcher(mobj, &te.super);

	}//end if




}


/*Button debouncing*/

uint8_t button_deboucing(uint8_t btn_pad_value)
{
	static button_state_t btn_sm_state=NOT_PRESSED;
	static uint32_t curr_time=0;

	switch(btn_sm_state)
	{
	case NOT_PRESSED:
	{
		if(btn_pad_value )
		{
			btn_sm_state=BOUNCE;
			curr_time=HAL_GetTick();
		}

		break;
	}
	case BOUNCE:
	{
		if(HAL_GetTick()-curr_time>=100)
		{
			//50ms has passed
			if(btn_pad_value)
			{
				btn_sm_state=PRESSED;
				return btn_pad_value;
			}
			else
			{

				btn_sm_state=NOT_PRESSED;
			}
		}

		break;
	}

	case PRESSED:
	{

		if(!btn_pad_value)
		{
			btn_sm_state=BOUNCE;
			curr_time=HAL_GetTick();
		}

	}

	default:

		btn_sm_state=NOT_PRESSED;
		break;

	}//END SWITCH


	return button_not_pressed;
}

/*Read button function*/
uint8_t button_read()
{
	uint8_t btn_var=0,b1,b2,b3,b4,b5;

	b1=HAL_GPIO_ReadPin(button_1_GPIO_Port, button_1_Pin);
	b2=HAL_GPIO_ReadPin(button_2_GPIO_Port, button_2_Pin);
	b3=HAL_GPIO_ReadPin(button_3_GPIO_Port, button_3_Pin);


	btn_var=((b3<<2)|(b2<<1)|b1);



	btn_var=button_deboucing(btn_var);

	return btn_var;
}

/*helper functions
 *
 * note: the static keyword in a function declaration its for the scope is limited to the source code file in which it is define
 *
 * */

 void do_beep(void)
{
	HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, GPIO_PIN_SET);
	HAL_Delay(25);
	HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, GPIO_PIN_RESET);
}

/*functions for the lcd using in the state machine*/
 void display_clear(lcd_t * const lcd)
{

	 lcd_clear(lcd);

}
 void display_message(lcd_t * const lcd,char *str,uint8_t c,uint8_t r)
{
	 lcd_set_cursor(lcd, r, c);
	 lcd_print_string(lcd, str);
}
 void display_time(lcd_t * const lcd,uint32_t time)
{
	 char buffer[20];
	 uint16_t m =time/60;
	 uint8_t s = time % 60;

	 sprintf(buffer,"%03d:%02d",m,s);
	 lcd_set_cursor(lcd, 0, 5);
	 lcd_print_string(lcd, buffer);

}
