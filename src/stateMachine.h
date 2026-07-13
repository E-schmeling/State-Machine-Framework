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
 *          0: Success
 *          1: Error: Null pointer provided
 *          2: Error: No states provided
 *          3: Error: State IDs are not in the correct order
 *          4:                  Error: Null pointer to substates provided but substate_count is not zero
 *          5:                  Error: Substate IDs are not in the correct order
 *          6:                  Error: Init state should not have exit or loop functions
 *          7:                  Error: Init substate should not have exit or loop functions
 *          0b00010000 + ret:   Error: Enter function of init state failed (ret is the return value of the enter function)
 *          0b00100000 + ret:   Error: Enter function of init substate failed (ret is the return value of the enter function)
 * 
 */
uint8_t init_state_machine(state_machine_t* stateMachine, state_t* states, substate_t* substates, uint8_t state_count, uint8_t substate_count);



/**
 * @brief Transitions the state machine to a new state and substate.
 * 
 * @param sm Pointer to the state machine
 * @param new_state Pointer to the new state to transition to.
 * @param new_substate Pointer to the new substate to transition to.
 * 
 * @return Return Codes:
 *          0:                  Success
 *          1:                  Error: Null pointer to state machine provided
 *          2:                  Error: State machine not initialised
 *          3:                  Error: Null pointer to new state provided
 *          4:                  Error: New state ID is out of bounds
 *          5:                  Error: New substate ID is out of bounds
 *          6:                  Error: State only machine is configured incorrectly
 *          7:                  Error: New substate does not belong to the new state
 *          0b00010000 + ret:   Error: Exit function of current state failed (ret is the return value of the exit function)
 *          0b00100000 + ret:   Error: Enter function of new state failed (ret is the return value of the enter function)
 *          0b01000000 + ret:   Error: Exit function of current substate failed (ret is the return value of the exit function)
 *          0b10000000 + ret:   Error: Enter function of new substate failed (ret is the return value of the enter function)
 */

uint8_t transition_to(state_machine_t *sm, state_t *new_state, substate_t *new_substate);

/**
 * @brief Runs the state machine by executing the loop functions of the current state and substate.
 * 
 * @param sm Pointer to the state machine
 * @param new_state Pointer to the new state to transition to.
 * @param new_substate Pointer to the new substate to transition to.
 * 
 * @return Return Codes:
 *          0:                  Success
 *          1:                  Error: Null pointer to state machine provided
 *          2:                  Error: State machine not initialised
 *          3:                  Error: Current state is NULL
 *          4:                  Error: Current state ID is out of bounds
 *          5:                  Error: Current substate is NULL but substates are defined
 *          6:                  Error: Current substate ID is out of bounds
 *          7:                  Error: Current substate is set but no substates are defined
 *          0b00010000 + ret:   Error: Loop function of current state failed (ret is the return value of the loop function)
 *          0b00100000 + ret:   Error: Loop function of current substate failed (ret is the return value of the loop function)
 * 
 */
uint8_t run_state_machine(state_machine_t *sm);


/**
 * @brief Gets the current state and substate of the state machine.
 * 
 * @param sm Pointer to the state machine
 * @param current_state Pointer to a variable to store the current state ID (can be NULL
 * if not needed)
 * @param current_substate Pointer to a variable to store the current substate ID (can
 * be NULL if not needed)
 * 
 * @return Return Codes:
 *          0: Success
 *          1: Error: Null pointer to state machine provided
 *          2: Error: State machine not initialised
 */
uint8_t get_current_state(state_machine_t *sm, uint8_t *current_state, uint8_t *current_substate);