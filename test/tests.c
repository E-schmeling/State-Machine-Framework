#include "../src/stateMachine.h"
#include "testSupport.h"
#include <stdio.h>
#include <stddef.h>


typedef uint8_t (*test_Func)(void);
typedef struct
{
    test_Func fn;
    char msg[48];
} test;


/**=========================================
 *   Test Functions
 * =========================================
 */
uint8_t test_CorrectInitialisationWithSubStates(void);
uint8_t test_InitFailsWhenInitStateHasLoop(void);
uint8_t test_InitFailsWhenInitSubstateHasExit(void);
uint8_t test_TransitionWithinSameStateOnlyTouchesSubstates(void);
uint8_t test_TransitionToNewStateRunsExitEnterSequence(void);



test tests[] =
    {
        {test_CorrectInitialisationWithSubStates, "CorrectInitialisationWithSubStates"},
        {test_InitFailsWhenInitStateHasLoop, "InitFailsWhenInitStateHasLoop"},
        {test_InitFailsWhenInitSubstateHasExit, "InitFailsWhenInitSubstateHasExit"},
        {test_TransitionWithinSameStateOnlyTouchesSubstates, "TransitionWithinSameStateOnlyTouchesSubstates"},
        {test_TransitionToNewStateRunsExitEnterSequence, "TransitionToNewStateRunsExitEnterSequence"},
};

int main(void)
{
    printf("Starting state machine tests...");
    bool results[sizeof(tests) / sizeof(test)];
    for (int i = 0; i < sizeof(tests) / sizeof(test); i++)
    {
        // run test
        uint8_t err = tests[i].fn();
        // cleanMemoryUp();

        results[i] = (err == 0);
        if (err != 0)
        {
            printf("Test %d failed: %s with error code %d\n", i, tests[i].msg, err);
        }
    }
    printf("\n\n\n");
    for (int i = 0; i < sizeof(tests) / sizeof(test); i++)
    {
        if (results[i] == false)
        {
            printf("\t[FAIL] \t %s\n", tests[i].msg);
        }
        else
        {
            printf("\t[PASS] \t %s\n", tests[i].msg);
        }
    }
    return 0;
}

uint8_t test_CorrectInitialisationWithSubStates(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    typedef enum
    {
        SUBSTATE_INIT = 0,
        SUBSTATE_ONE,
        SUBSTATE_COUNT
    } substate_id_t;

    func_setAllToZero();

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    uint8_t err = init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT);
    
    return err;
}

uint8_t test_InitFailsWhenInitStateHasLoop(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    typedef enum
    {
        SUBSTATE_INIT = 0,
        SUBSTATE_ONE,
        SUBSTATE_COUNT
    } substate_id_t;

    func_setAllToZero();

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, func_addFiveToX, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    uint8_t err = init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT);

    if (err != 6)
    {
        return 1;
    }

    return 0;
}

uint8_t test_InitFailsWhenInitSubstateHasExit(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    typedef enum
    {
        SUBSTATE_INIT = 0,
        SUBSTATE_ONE,
        SUBSTATE_COUNT
    } substate_id_t;

    func_setAllToZero();

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, func_addFiveToX},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    uint8_t err = init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT);

    if (err != 7)
    {
        return 1;
    }

    return 0;
}

uint8_t test_TransitionWithinSameStateOnlyTouchesSubstates(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ACTIVE,
        STATE_COUNT
    } state_id_t;

    typedef enum
    {
        SUBSTATE_INIT = 0,
        SUBSTATE_ONE,
        SUBSTATE_TWO,
        SUBSTATE_COUNT
    } substate_id_t;

    func_setAllToZero();

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ACTIVE, func_addFiveToX, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ACTIVE, NULL, NULL, func_setYToX},
            {SUBSTATE_TWO, STATE_ACTIVE, func_addOneToY, NULL, NULL},
        };

    state_machine_t sm;
    uint8_t err = init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT);
    if (err != 0)
    {
        return err;
    }

    err = transition_to(&sm, &states[STATE_ACTIVE], &substates[SUBSTATE_ONE]);
    if (err != 0)
    {
        return err;
    }

    err = transition_to(&sm, &states[STATE_ACTIVE], &substates[SUBSTATE_TWO]);
    if (err != 0)
    {
        return err;
    }

    if (get_x() != 5 || get_y() != 6 || get_z() != 0)
    {
        return 1;
    }

    return 0;
}

uint8_t test_TransitionToNewStateRunsExitEnterSequence(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ALPHA,
        STATE_BETA,
        STATE_COUNT
    } state_id_t;

    typedef enum
    {
        SUBSTATE_INIT = 0,
        SUBSTATE_ALPHA,
        SUBSTATE_BETA,
        SUBSTATE_COUNT
    } substate_id_t;

    func_setAllToZero();

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ALPHA, func_addFiveToX, NULL, func_addFiveToX},
            {STATE_BETA, func_setZToY, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ALPHA, STATE_ALPHA, NULL, NULL, func_setYToX},
            {SUBSTATE_BETA, STATE_BETA, func_addOneToY, NULL, NULL},
        };

    state_machine_t sm;
    uint8_t err = init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT);
    if (err != 0)
    {
        return err;
    }

    err = transition_to(&sm, &states[STATE_ALPHA], &substates[SUBSTATE_ALPHA]);
    if (err != 0)
    {
        return err;
    }

    err = transition_to(&sm, &states[STATE_BETA], &substates[SUBSTATE_BETA]);
    if (err != 0)
    {
        return err;
    }

    if (get_x() != 10 || get_y() != 6 || get_z() != 5)
    {
        return 1;
    }

    return 0;
}

