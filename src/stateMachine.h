/**
 * @file stateMachine.h
 * @brief State machine implementation in C.
 * @author ERS
 *
 * This module provides a basic framework for a state machine with enter, loop, and exit functions.
 * The state machine can handle both states and substates, allowing for hierarchical state management.
 * There is a maximum of 2^8 states and 2^8 substates, with the state and substate IDs being sequentially assigned starting from 0.
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/** =======================================================================
 *  Routine Defines
 *  =======================================================================
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>



 
/** =======================================================================
 *  Public Type Definitions
 *  =======================================================================
 */

/**
 * @brief Function pointer type for state functions (enter, loop, exit).
 * 
 * @return Return code indicating the result of the function execution. 0 indicates success, non-zero indicates an error.
 *         These errors have a maximum value of 15, so they can be combined with the error codes of the state machine 
 *          functions to provide more context.
 */
typedef uint8_t (*state_func_t)(void);

/**
 * @brief Represents a state in the state machine.
 * 
 * - 'state_id' is the unique identifier for the state
 * - 'enter'    is a function pointer to the enter function of the state
 * - 'loop'     is a function pointer to the loop function of the state
 * - 'exit'     is a function pointer to the exit function of the state
 */
typedef struct
{
    uint8_t state_id;
    
    state_func_t enter;
    state_func_t loop;
    state_func_t exit;
} state_t;

/**
 * @brief Represents a substate in the state machine.
 * 
 * - 'substate_id'     is the unique identifier for the substate
 * - 'parent_state_id' is the ID of the parent state
 * - 'enter'           is a function pointer to the enter function of the substate
 * - 'loop'            is a function pointer to the loop function of the substate
 * - 'exit'            is a function pointer to the exit function of the substate
 */
typedef struct
{
    uint8_t substate_id;
    
    uint8_t parent_state_id;

    state_func_t enter;
    state_func_t loop;
    state_func_t exit;
} substate_t;

/**
 * @brief Represents the state machine.
 * 
 * - 'current_state'     is a pointer to the current state ID
 * - 'current_substate'  is a pointer to the current substate ID
 * - 'states'            is a pointer to the array of states
 * - 'substates'         is a pointer to the array of substates
 * - 'state_count'       is the number of states in the states array
 * - 'substate_count'    is the number of substates in the substates array
 * - 'is_initialised'    indicates whether the state machine has been initialised
 */
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



/** =======================================================================
 *  Public Function Definitions
 *  =======================================================================
 */
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
 *          0:                  Success
 *          1:                  Error: Null pointer provided
 *          2:                  Error: No states provided
 *          3:                  Error: State IDs are not in the correct order
 *          4:                  Error: Null pointer to substates provided but substate_count is not zero
 *          5:                  Error: Substate IDs are not in the correct order
 *          6:                  Error: Init state should not have exit or loop functions
 *          7:                  Error: Init substate should not have exit or loop functions
 *          8:                  Error: Substate with ID 0 should be the only substate with parent_state_id 0
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

#endif // STATE_MACHINE_H