
#include "main.h"
/*El primner paso es crear el pesudo estado de init la incializacion de la maquina de estados
La funcion recibe como parametro la estructura de la apliacion principal */
void protimer_init(protimer_t *mobj)
{

mobj->active_state =IDLE; // Inicializamos el objeto en el estado de IDLE
mobj->pro_timer = 0;

} 