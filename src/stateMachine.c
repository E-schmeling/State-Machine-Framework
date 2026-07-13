
#include "stateMachine.h"

uint8_t init_state_machine(state_machine_t *stateMachine, state_t *states, substate_t *substates, uint8_t state_count, uint8_t substate_count)
{
    if (stateMachine == NULL || states == NULL)
    {
        return 1; // Error: Null pointer provided
    }

    if (state_count == 0)
    {
        return 2; // Error: No states provided
    }
    for (uint8_t i = 0; i < state_count; i++)
    {
        if (states[i].state_id != i)
        {
            return 3; // Error: State IDs are not in the correct order
        }
    }
    stateMachine->states = states;
    stateMachine->state_count = state_count;

    if (substates == NULL && substate_count != 0)
    {
        return 4; // Error: Null pointer to substates provided but substate_count is not zero
    }

    for (uint8_t i = 0; i < substate_count; i++)
    {
        if (substates[i].substate_id != i)
        {
            return 5; // Error: Substate IDs are not in the correct order
        }
    }
    stateMachine->substates = substates;
    stateMachine->substate_count = substate_count;

    // Check init state and init substate are valid
    if (stateMachine->states[0].exit != NULL || stateMachine->states[0].loop != NULL)
    {
        return 6; // Error: Init state should not have exit or loop functions
    }

    if (stateMachine->substate_count != 0)
    {
        // State machine can only have states, so if there are no substates, this is a valid path so must handle this.
        if (stateMachine->substates[0].exit != NULL || stateMachine->substates[0].loop != NULL)
        {
            return 7; // Error: Init substate should not have exit or loop functions
        }

        stateMachine->current_substate = &substates[0].substate_id;
    }
    else
    {
        stateMachine->current_substate = NULL; // No substates available this technically leaves it in the init_substate, but this needs to be valid behaviour.
    }

    stateMachine->current_state = &states[0].state_id;

    if (stateMachine->states[0].enter != NULL)
    {
        uint8_t ret = stateMachine->states[0].enter();
        if (ret != 0)
        {
            return 8; // Error: Enter function of init state failed
        }
    }

    if (stateMachine->substate_count != 0 && stateMachine->substates[0].enter != NULL)
    {
        uint8_t ret = stateMachine->substates[0].enter();
        if (ret != 0)
        {
            return 9; // Error: Enter function of init substate failed
        }
    }

    stateMachine->is_initialised = true;
    return 0; // Success
}

uint8_t transition_to(state_machine_t *sm, state_t *new_state, substate_t *new_substate)
{

    if (sm == NULL)
    {
        return 1; // Error: Null pointer to state machine provided
    }

    if (sm->is_initialised == false)
    {
        return 2; // Error: State machine not initialised
    }

    if (new_state == NULL)
    {
        return 3; // Error: Null pointer to new state provided
    }

    if (*(sm->current_state) == new_state->state_id &&
        ((sm->substate_count == 0 && new_substate == NULL) ||
         (sm->substate_count != 0 && new_substate != NULL && *(sm->current_substate) == new_substate->substate_id)))
    {
        // Already in the desired state and substate, no transition needed.
        return 0; // Success
    }
    if (new_state->state_id >= sm->state_count)
    {
        return 4; // Error: New state ID is out of bounds
    }
    if (new_substate != NULL && new_substate->substate_id >= sm->substate_count)
    {
        return 5; // Error: New substate ID is out of bounds
    }

    if (sm->current_substate == NULL && new_substate == NULL && sm->substate_count == 0)
    {
        // State only machine, no substates.
        // Handling State only transition.

        uint8_t ret = 0;
        if (sm->states[*(sm->current_state)].exit != NULL)
        {
            ret = sm->states[*(sm->current_state)].exit();
            if (ret != 0)
            {
                return 0b00010000 + ret; // Error: Exit function of current state failed
            }
        }

        if (new_state->enter != NULL)
        {
            ret = new_state->enter();
            if (ret != 0)
            {
                return 0b00100000 + ret; // Error: Enter function of new state failed
            }
        }

        *(sm->current_state) = new_state->state_id;
        return 0; // Success
    }
    else if (sm->current_substate == NULL || new_substate == NULL || sm->substate_count == 0)
    {
        return 6; // Error: State only machine is configured incorrectly,
    }
    else
    {
        // State machine with substates, handle transition with substates.
        if (new_substate->parent_state_id != new_state->state_id)
        {
            return 7; // Error: New substate does not belong to the new state
        }

        uint8_t ret = 0;
        if (sm->substates[*(sm->current_substate)].exit != NULL)
        {
            ret = sm->substates[*(sm->current_substate)].exit();
            if (ret != 0)
            {
                return 0b01000000 + ret; // Error: Exit function of current substate failed
            }
        }
        if (*(sm->current_state) != new_state->state_id) // If state does not change, we don't need to call the exit/enter function pair of the transition.
        {
            if (sm->states[*(sm->current_state)].exit != NULL)
            {
                ret = sm->states[*(sm->current_state)].exit();
                if (ret != 0)
                {
                    return 0b00010000 + ret; // Error: Exit function of current state failed
                }
            }

            if (new_state->enter != NULL)
            {
                ret = new_state->enter();
                if (ret != 0)
                {
                    return 0b00100000 + ret; // Error: Enter function of new state failed
                }
            }
        }

        if (new_substate->enter != NULL)
        {
            ret = new_substate->enter();
            if (ret != 0)
            {
                return 0b10000000 + ret; // Error: Enter function of new substate failed
            }
        }

        *(sm->current_state) = new_state->state_id;
        *(sm->current_substate) = new_substate->substate_id;
        return 0; // Success
    }
}

uint8_t get_current_state(state_machine_t *sm, uint8_t *current_state, uint8_t *current_substate)
{
    if (sm == NULL)
    {
        return 1; // Error: Null pointer to state machine provided
    }
    if (sm->is_initialised == false)
    {
        return 2; // Error: State machine not initialised
    }
    if (current_state != NULL)
    {
        *current_state = *(sm->current_state);
    }
    if (current_substate != NULL)
    {
        *current_substate = (sm->current_substate != NULL) ? *(sm->current_substate) : 0;
    }
    return 0; // Success
}
