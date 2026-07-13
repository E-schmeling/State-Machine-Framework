#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



typedef uint8_t (*state_func_t)(void);

typedef struct
{
    uint8_t state_id;
    
    state_func_t enter;
    state_func_t loop;
    state_func_t exit;


} state_t;

typedef struct
{
    uint8_t substate_id;
    
    uint8_t parent_state_id;

    state_func_t enter;
    state_func_t loop;
    state_func_t exit;

} substate_t;


typedef struct
{
    uint8_t* current_state;
    uint8_t* current_substate;
    
    state_t* states;
    substate_t* substates;

    uint8_t state_count;
    uint8_t substate_count;

    bool is_initialised;
} state_machine_t;




/** @brief initialises the state machine with the provided states and substates. 
 * 
 * Based on this format, the state machine needs to include an init state and an init substate. each of these can have an enter function. 
 * 
 * @param stateMachine Pointer to the state machine to initialise
 * @param states Pointer to the array of states
 * @param substates Pointer to the array of substates
 * @param state_count Number of states in the states array
 * @param substate_count Number of substates in the substates array
 * 
 * @return Return Codes:
 *              0: Success

 * 
 */
uint8_t init_state_machine(state_machine_t* stateMachine, state_t* states, substate_t* substates, uint8_t state_count, uint8_t substate_count);
