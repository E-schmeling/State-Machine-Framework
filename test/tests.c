#include "../src/stateMachine.h"
#include "testSupport.h"
#include <stdio.h>
#include <stddef.h>

typedef uint8_t (*test_Func)(void);
typedef struct
{
    test_Func fn;
    char msg[96];
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
uint8_t test_Init01_ValidStateOnlyInitialization(void);
uint8_t test_Init02_StateMachinePointerNull(void);
uint8_t test_Init03_StatesPointerNull(void);
uint8_t test_Init04_ZeroStatesProvided(void);
uint8_t test_Init05_StateIdsOutOfOrder(void);
uint8_t test_Init06_InitStateLoopNotAllowed(void);
uint8_t test_Init07_InitStateExitNotAllowed(void);
uint8_t test_Init08_InitStateEnterFailure(void);
uint8_t test_Init09_TransitionNullStateMachine(void);
uint8_t test_Init10_ValidStateAndSubstateInitialization(void);
uint8_t test_Init11_NullSubstatesWhenCountNonZero(void);
uint8_t test_Init12_SubstateIdsOutOfOrder(void);
uint8_t test_Init13_InitSubstateLoopNotAllowed(void);
uint8_t test_Init14_InitSubstateExitNotAllowed(void);
uint8_t test_Init15_InitSubstateEnterFailure(void);
uint8_t test_Init16_InvalidParentOnNonZeroSubstateZeroRule(void);
uint8_t test_Trans01_UninitialisedMachine(void);
uint8_t test_Trans02_NullNewState(void);
uint8_t test_Trans03_NewStateOutOfBounds(void);
uint8_t test_Trans04_NoOpSameState(void);
uint8_t test_Trans05_StateChangeRunsExitThenEnter(void);
uint8_t test_Trans06_NullStateMachine(void);
uint8_t test_Trans07_UninitialisedMachine(void);
uint8_t test_Trans08_NullNewState(void);
uint8_t test_Trans09_NewStateOutOfBounds(void);
uint8_t test_Trans10_NewSubstateOutOfBounds(void);
uint8_t test_Trans11_MismatchedParentPair(void);
uint8_t test_Trans12_NoOpSameStateAndSubstate(void);
uint8_t test_Trans13_SameStateSubstateChange(void);
uint8_t test_Trans14_StateChangeFullTransition(void);
uint8_t test_TransNum01_StateOnlyNoOpSameState(void);
uint8_t test_TransNum02_StateOnlyStateChangeUpdatesCurrentState(void);
uint8_t test_TransNum03_StateOnlyStateChangeRunsExitAndEnter(void);
uint8_t test_TransNum04_SubstateNoOpSameStateAndSubstate(void);
uint8_t test_TransNum05_SubstateSameStateSwitchesSubstateOnly(void);
uint8_t test_TransNum06_SubstateStateChangeRunsFullTransition(void);
uint8_t test_Run01_ValidStateOnlyLoop(void);
uint8_t test_Run02_NullStateMachine(void);
uint8_t test_Run03_UninitialisedMachine(void);
uint8_t test_Run04_NullCurrentStatePointer(void);
uint8_t test_Run05_CurrentStateOutOfBounds(void);
uint8_t test_Run06_CurrentSubstateSetWithoutSubstates(void);
uint8_t test_Get01_ValidStateOnlyCurrentState(void);
uint8_t test_Get02_NullStateMachine(void);
uint8_t test_Get03_UninitialisedMachine(void);
uint8_t test_Run07_ValidStateAndSubstateLoops(void);
uint8_t test_Run08_NullCurrentSubstateWithSubstates(void);
uint8_t test_Run09_CurrentSubstateOutOfBounds(void);
uint8_t test_Get04_ValidStateAndSubstateCurrentState(void);
uint8_t test_Get05_NullCurrentStateOutput(void);
uint8_t test_Get06_NullCurrentSubstateOutput(void);



test tests[] =
    {
        {test_CorrectInitialisationWithSubStates, "CorrectInitialisationWithSubStates"},
        {test_InitFailsWhenInitStateHasLoop, "InitFailsWhenInitStateHasLoop"},
        {test_InitFailsWhenInitSubstateHasExit, "InitFailsWhenInitSubstateHasExit"},
        {test_TransitionWithinSameStateOnlyTouchesSubstates, "TransitionWithinSameStateOnlyTouchesSubstates"},
        {test_TransitionToNewStateRunsExitEnterSequence, "TransitionToNewStateRunsExitEnterSequence"},
        {test_Init01_ValidStateOnlyInitialization, "Init01_ValidStateOnlyInitialization"},
        {test_Init02_StateMachinePointerNull, "Init02_StateMachinePointerNull"},
        {test_Init03_StatesPointerNull, "Init03_StatesPointerNull"},
        {test_Init04_ZeroStatesProvided, "Init04_ZeroStatesProvided"},
        {test_Init05_StateIdsOutOfOrder, "Init05_StateIdsOutOfOrder"},
        {test_Init06_InitStateLoopNotAllowed, "Init06_InitStateLoopNotAllowed"},
        {test_Init07_InitStateExitNotAllowed, "Init07_InitStateExitNotAllowed"},
        {test_Init08_InitStateEnterFailure, "Init08_InitStateEnterFailure"},
        {test_Init09_TransitionNullStateMachine, "Init09_TransitionNullStateMachine"},
        {test_Init10_ValidStateAndSubstateInitialization, "Init10_ValidStateAndSubstateInitialization"},
        {test_Init11_NullSubstatesWhenCountNonZero, "Init11_NullSubstatesWhenCountNonZero"},
        {test_Init12_SubstateIdsOutOfOrder, "Init12_SubstateIdsOutOfOrder"},
        {test_Init13_InitSubstateLoopNotAllowed, "Init13_InitSubstateLoopNotAllowed"},
        {test_Init14_InitSubstateExitNotAllowed, "Init14_InitSubstateExitNotAllowed"},
        {test_Init15_InitSubstateEnterFailure, "Init15_InitSubstateEnterFailure"},
        {test_Init16_InvalidParentOnNonZeroSubstateZeroRule, "Init16_InvalidParentOnNonZeroSubstateZeroRule"},
        {test_Trans01_UninitialisedMachine, "Trans01_UninitialisedMachine"},
        {test_Trans02_NullNewState, "Trans02_NullNewState"},
        {test_Trans03_NewStateOutOfBounds, "Trans03_NewStateOutOfBounds"},
        {test_Trans04_NoOpSameState, "Trans04_NoOpSameState"},
        {test_Trans05_StateChangeRunsExitThenEnter, "Trans05_StateChangeRunsExitThenEnter"},
        {test_Trans06_NullStateMachine, "Trans06_NullStateMachine"},
        {test_Trans07_UninitialisedMachine, "Trans07_UninitialisedMachine"},
        {test_Trans08_NullNewState, "Trans08_NullNewState"},
        {test_Trans09_NewStateOutOfBounds, "Trans09_NewStateOutOfBounds"},
        {test_Trans10_NewSubstateOutOfBounds, "Trans10_NewSubstateOutOfBounds"},
        {test_Trans11_MismatchedParentPair, "Trans11_MismatchedParentPair"},
        {test_Trans12_NoOpSameStateAndSubstate, "Trans12_NoOpSameStateAndSubstate"},
        {test_Trans13_SameStateSubstateChange, "Trans13_SameStateSubstateChange"},
        {test_Trans14_StateChangeFullTransition, "Trans14_StateChangeFullTransition"},
        {test_TransNum01_StateOnlyNoOpSameState, "TransNum01_StateOnlyNoOpSameState"},
        {test_TransNum02_StateOnlyStateChangeUpdatesCurrentState, "TransNum02_StateOnlyUpdatesCurrentState"},
        {test_TransNum03_StateOnlyStateChangeRunsExitAndEnter, "TransNum03_StateOnlyStateChangeRunsExitAndEnter"},
        {test_TransNum04_SubstateNoOpSameStateAndSubstate, "TransNum04_SubstateNoOpSameStateAndSubstate"},
        {test_TransNum05_SubstateSameStateSwitchesSubstateOnly, "TransNum05_SubstateSameStateSwitchesSubstateOnly"},
        {test_TransNum06_SubstateStateChangeRunsFullTransition, "TransNum06_SubstateStateChangeRunsFullTransition"},
        {test_Run01_ValidStateOnlyLoop, "Run01_ValidStateOnlyLoop"},
        {test_Run02_NullStateMachine, "Run02_NullStateMachine"},
        {test_Run03_UninitialisedMachine, "Run03_UninitialisedMachine"},
        {test_Run04_NullCurrentStatePointer, "Run04_NullCurrentStatePointer"},
        {test_Run05_CurrentStateOutOfBounds, "Run05_CurrentStateOutOfBounds"},
        {test_Run06_CurrentSubstateSetWithoutSubstates, "Run06_CurrentSubstateSetWithoutSubstates"},
        {test_Get01_ValidStateOnlyCurrentState, "Get01_ValidStateOnlyCurrentState"},
        {test_Get02_NullStateMachine, "Get02_NullStateMachine"},
        {test_Get03_UninitialisedMachine, "Get03_UninitialisedMachine"},
        {test_Run07_ValidStateAndSubstateLoops, "Run07_ValidStateAndSubstateLoops"},
        {test_Run08_NullCurrentSubstateWithSubstates, "Run08_NullCurrentSubstateWithSubstates"},
        {test_Run09_CurrentSubstateOutOfBounds, "Run09_CurrentSubstateOutOfBounds"},
        {test_Get04_ValidStateAndSubstateCurrentState, "Get04_ValidStateAndSubstateCurrentState"},
        {test_Get05_NullCurrentStateOutput, "Get05_NullCurrentStateOutput"},
        {test_Get06_NullCurrentSubstateOutput, "Get06_NullCurrentSubstateOutput"},
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
        func_setAllToZero();
        results[i] = (err == 0);
        if (err != 0)
        {
            printf("\nTest %d failed: %s with error code %d", i, tests[i].msg, err);
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

uint8_t test_Init01_ValidStateOnlyInitialization(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    uint8_t err = init_state_machine(&sm, states, NULL, STATE_COUNT, 0);
    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;

    if (err != 0)
    {
        return err;
    }

    if (sm.is_initialised != true || sm.current_substate != NULL)
    {
        return 1;
    }

    err = get_current_state(&sm, &current_state, &current_substate);
    if (err != 0)
    {
        return err;
    }

    if (current_state != STATE_INIT || current_substate != 0)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Init02_StateMachinePointerNull(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    if (init_state_machine(NULL, states, NULL, STATE_COUNT, 0) != 1)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Init03_StatesPointerNull(void)
{
    if (init_state_machine(NULL, NULL, NULL, 0, 0) != 1)
    {
        return 1;
    }

    state_machine_t sm;
    if (init_state_machine(&sm, NULL, NULL, 0, 0) != 1)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Init04_ZeroStatesProvided(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, 0, 0) != 2)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Init05_StateIdsOutOfOrder(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_BROKEN = 2,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_BROKEN, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 3)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Init06_InitStateLoopNotAllowed(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, func_addFiveToX, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 6)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Init07_InitStateExitNotAllowed(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, func_addFiveToX},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 6)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Init08_InitStateEnterFailure(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, func_failOne, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 17)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Init09_TransitionNullStateMachine(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    if (transition_to(NULL, &states[STATE_ONE], NULL) != 1)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Trans01_UninitialisedMachine(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm = {0};
    if (transition_to(&sm, &states[STATE_ONE], NULL) != 2)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Trans02_NullNewState(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, NULL, NULL) != 3)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Trans03_NewStateOutOfBounds(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_t bad_state = {2, NULL, NULL, NULL};

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &bad_state, NULL) != 4)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Trans04_NoOpSameState(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, func_setAllToOne, NULL, NULL},
            {STATE_ONE, NULL, NULL, func_addFiveToX},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &states[STATE_ONE], NULL) != 0)
    {
        return 2;
    }
    if (get_x() != 1)
    {
        return 3;
    }

    if (transition_to(&sm, &states[STATE_ONE], NULL) != 0)
    {
        return 4;
    }
    if (get_x() != 1)
    {
        return 5;
    }

    return 0;
}

uint8_t test_Trans05_StateChangeRunsExitThenEnter(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_TWO,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, func_setAllToOne, NULL, NULL},
            {STATE_ONE, NULL, NULL, func_setYToX},
            {STATE_TWO, func_addFiveToX, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &states[STATE_ONE], NULL) != 0)
    {
        return 2;
    }

    if (transition_to(&sm, &states[STATE_TWO], NULL) != 0)
    {
        return 3;
    }

    if (get_x() != 6 || get_y() != 1)
    {
        return 4;
    }

    return 0;
}

// Validates that state and substate initialization succeeds with the expected initial current IDs.
uint8_t test_Init10_ValidStateAndSubstateInitialization(void)
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
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;
    if (get_current_state(&sm, &current_state, &current_substate) != 0)
    {
        return 2;
    }

    if (current_state != STATE_INIT || current_substate != SUBSTATE_INIT)
    {
        return 3;
    }

    return 0;
}

// Validates that a non-zero substate count rejects a null substate array.
uint8_t test_Init11_NullSubstatesWhenCountNonZero(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 1) != 4)
    {
        return 1;
    }

    return 0;
}

// Validates that substate IDs must be declared in order.
uint8_t test_Init12_SubstateIdsOutOfOrder(void)
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
        SUBSTATE_BROKEN = 2,
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
            {SUBSTATE_BROKEN, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 5)
    {
        return 1;
    }

    return 0;
}

// Validates that the init substate cannot define a loop hook.
uint8_t test_Init13_InitSubstateLoopNotAllowed(void)
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
            {SUBSTATE_INIT, STATE_INIT, NULL, func_addFiveToX, NULL},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 7)
    {
        return 1;
    }

    return 0;
}

// Validates that the init substate cannot define an exit hook.
uint8_t test_Init14_InitSubstateExitNotAllowed(void)
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
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 7)
    {
        return 1;
    }

    return 0;
}

// Validates that an init substate enter failure is propagated back to the caller.
uint8_t test_Init15_InitSubstateEnterFailure(void)
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
            {SUBSTATE_INIT, STATE_INIT, func_failSeven, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 34)
    {
        return 1;
    }

    return 0;
}

// Validates the parent-state rule for non-zero substates.
uint8_t test_Init16_InvalidParentOnNonZeroSubstateZeroRule(void)
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
            {SUBSTATE_ONE, STATE_INIT, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 8)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Trans06_NullStateMachine(void)
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

    if (transition_to(NULL, &states[STATE_ONE], &substates[SUBSTATE_ONE]) != 1)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Trans07_UninitialisedMachine(void)
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

    state_machine_t sm = {0};
    if (transition_to(&sm, &states[STATE_ONE], &substates[SUBSTATE_ONE]) != 2)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Trans08_NullNewState(void)
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
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, NULL, &substates[SUBSTATE_ONE]) != 3)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Trans09_NewStateOutOfBounds(void)
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

    state_t bad_state = {2, NULL, NULL, NULL};

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &bad_state, &substates[SUBSTATE_ONE]) != 4)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Trans10_NewSubstateOutOfBounds(void)
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

    substate_t bad_substate = {2, STATE_ONE, NULL, NULL, NULL};

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &states[STATE_ONE], &bad_substate) != 5)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Trans11_MismatchedParentPair(void)
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
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &states[STATE_ONE], &substates[SUBSTATE_INIT]) != 7)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Trans12_NoOpSameStateAndSubstate(void)
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
            {STATE_ONE, func_addFiveToX, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &states[STATE_ONE], &substates[SUBSTATE_ONE]) != 0)
    {
        return 2;
    }

    if (transition_to(&sm, &states[STATE_ONE], &substates[SUBSTATE_ONE]) != 0)
    {
        return 3;
    }

    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;
    if (get_current_state(&sm, &current_state, &current_substate) != 0)
    {
        return 4;
    }

    if (current_state != STATE_ONE || current_substate != SUBSTATE_ONE)
    {
        return 5;
    }

    if (get_x() != 5)
    {
        return 6;
    }

    return 0;
}

uint8_t test_Trans13_SameStateSubstateChange(void)
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
        SUBSTATE_TWO,
        SUBSTATE_COUNT
    } substate_id_t;

    func_setAllToZero();

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, NULL, func_addOneToY},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, func_setYToX, NULL, func_addFourToZ},
            {SUBSTATE_TWO, STATE_ONE, func_subFiveFromZ, NULL, func_addOneToY},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &states[STATE_ONE], &substates[SUBSTATE_ONE]) != 0)
    {
        return 2;
    }

    if (transition_to(&sm, &states[STATE_ONE], &substates[SUBSTATE_TWO]) != 0)
    {
        return 3;
    }

    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;
    if (get_current_state(&sm, &current_state, &current_substate) != 0)
    {
        return 4;
    }

    if (current_state != STATE_ONE || current_substate != SUBSTATE_TWO)
    {
        return 5;
    }

    if (get_x() != 5 || get_y() != 5 || (int32_t)get_z() != -1)
    {
        return 6;
    }

    return 0;
}

uint8_t test_Trans14_StateChangeFullTransition(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_TWO,
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
            {STATE_ONE, func_addFiveToX, NULL, func_addOneToY},
            {STATE_TWO, func_addFourToZ, NULL, func_subFiveFromZ},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, func_setYToX, NULL, func_addFourToZ},
            {SUBSTATE_TWO, STATE_TWO, func_setZToY, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_to(&sm, &states[STATE_ONE], &substates[SUBSTATE_ONE]) != 0)
    {
        return 2;
    }

    if (transition_to(&sm, &states[STATE_TWO], &substates[SUBSTATE_TWO]) != 0)
    {
        return 3;
    }

    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;
    if (get_current_state(&sm, &current_state, &current_substate) != 0)
    {
        return 4;
    }

    if (current_state != STATE_TWO || current_substate != SUBSTATE_TWO)
    {
        return 5;
    }

    if (get_x() != 5 || get_y() != 6 || get_z() != 6)
    {
        return 6;
    }

    return 0;
}

// Validates that the integer-based transition API keeps a state-only machine on the same state without calling hooks.
uint8_t test_TransNum01_StateOnlyNoOpSameState(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    if (transition_toNum(&sm, STATE_INIT, 0) != 0)
    {
        return 2;
    }

    uint8_t current_state = 0xFF;
    if (get_current_state(&sm, &current_state, NULL) != 0)
    {
        return 3;
    }

    if (current_state != STATE_INIT)
    {
        return 4;
    }

    return 0;
}

// Validates that the integer-based transition API can move a state-only machine to a new state.
uint8_t test_TransNum02_StateOnlyStateChangeUpdatesCurrentState(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    if (transition_toNum(&sm, STATE_ONE, 0) != 0)
    {
        return 2;
    }

    uint8_t current_state = 0xFF;
    if (get_current_state(&sm, &current_state, NULL) != 0)
    {
        return 3;
    }

    if (current_state != STATE_ONE)
    {
        return 4;
    }

    return 0;
}

// Validates that the integer-based transition API still runs exit and enter hooks in state-only mode.
uint8_t test_TransNum03_StateOnlyStateChangeRunsExitAndEnter(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_TWO,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, func_setAllToOne, NULL, NULL},
            {STATE_ONE, NULL, NULL, func_addFiveToX},
            {STATE_TWO, func_addOneToY, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    if (transition_toNum(&sm, STATE_ONE, 0) != 0)
    {
        return 2;
    }

    if (transition_toNum(&sm, STATE_TWO, 0) != 0)
    {
        return 3;
    }

    uint8_t current_state = 0xFF;
    if (get_current_state(&sm, &current_state, NULL) != 0)
    {
        return 4;
    }

    if (current_state != STATE_TWO)
    {
        return 5;
    }

    if (get_x() != 6 || get_y() != 2 || get_z() != 1)
    {
        return 6;
    }

    return 0;
}

// Validates that the integer-based transition API keeps the same state/substate pair unchanged in substate mode.
uint8_t test_TransNum04_SubstateNoOpSameStateAndSubstate(void)
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
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_toNum(&sm, STATE_INIT, SUBSTATE_INIT) != 0)
    {
        return 2;
    }

    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;
    if (get_current_state(&sm, &current_state, &current_substate) != 0)
    {
        return 3;
    }

    if (current_state != STATE_INIT || current_substate != SUBSTATE_INIT)
    {
        return 4;
    }

    return 0;
}

// Validates that the integer-based transition API can switch substates without changing the parent state.
uint8_t test_TransNum05_SubstateSameStateSwitchesSubstateOnly(void)
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
        SUBSTATE_TWO,
        SUBSTATE_COUNT
    } substate_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, func_addOneToY},
            {SUBSTATE_TWO, STATE_ONE, func_addFourToZ, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_toNum(&sm, STATE_ONE, SUBSTATE_ONE) != 0)
    {
        return 2;
    }

    if (transition_toNum(&sm, STATE_ONE, SUBSTATE_TWO) != 0)
    {
        return 3;
    }

    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;
    if (get_current_state(&sm, &current_state, &current_substate) != 0)
    {
        return 4;
    }

    if (current_state != STATE_ONE || current_substate != SUBSTATE_TWO)
    {
        return 5;
    }

    if (get_y() != 1 || get_z() != 4)
    {
        return 6;
    }

    return 0;
}

// Validates that the integer-based transition API performs the full exit/enter sequence when changing state and substate.
uint8_t test_TransNum06_SubstateStateChangeRunsFullTransition(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_TWO,
        STATE_COUNT
    } state_id_t;

    typedef enum
    {
        SUBSTATE_INIT = 0,
        SUBSTATE_ONE,
        SUBSTATE_TWO,
        SUBSTATE_COUNT
    } substate_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, NULL, func_addOneToY},
            {STATE_TWO, func_addFourToZ, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, func_setYToX, NULL, func_subFiveFromZ},
            {SUBSTATE_TWO, STATE_TWO, func_setZToY, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (transition_toNum(&sm, STATE_ONE, SUBSTATE_ONE) != 0)
    {
        return 2;
    }

    if (transition_toNum(&sm, STATE_TWO, SUBSTATE_TWO) != 0)
    {
        return 3;
    }

    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;
    if (get_current_state(&sm, &current_state, &current_substate) != 0)
    {
        return 4;
    }

    if (current_state != STATE_TWO || current_substate != SUBSTATE_TWO)
    {
        return 5;
    }

    if (get_x() != 5 || get_y() != 6 || get_z() != 6)
    {
        return 6;
    }

    return 0;
}

uint8_t test_Run01_ValidStateOnlyLoop(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_TWO,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, func_addOneToY, NULL},
            {STATE_TWO, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }
    if (transition_to(&sm, &states[STATE_ONE], NULL) != 0)
    {
        return 2;
    }
    if (run_state_machine(&sm) != 0)
    {
        return 3;
    }
    if (get_x() != 5)
    {
        return 4;
    }

    return 0;
}

uint8_t test_Run02_NullStateMachine(void)
{
    if (run_state_machine(NULL) != 1)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Run03_UninitialisedMachine(void)
{
    state_machine_t sm = {0};
    if (run_state_machine(&sm) != 2)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Run04_NullCurrentStatePointer(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    sm.current_state = NULL;
    if (run_state_machine(&sm) != 3)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Run05_CurrentStateOutOfBounds(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    *sm.current_state = STATE_COUNT;
    if (run_state_machine(&sm) != 4)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Run06_CurrentSubstateSetWithoutSubstates(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, NULL, NULL},
        };

    uint8_t fake_substate = 0;
    state_machine_t sm;
    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    sm.current_substate = &fake_substate;
    if (run_state_machine(&sm) != 7)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Get01_ValidStateOnlyCurrentState(void)
{
    typedef enum
    {
        STATE_INIT = 0,
        STATE_ONE,
        STATE_COUNT
    } state_id_t;

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    uint8_t current_state = 0xFF;

    if (init_state_machine(&sm, states, NULL, STATE_COUNT, 0) != 0)
    {
        return 1;
    }

    if (get_current_state(&sm, &current_state, NULL) != 0)
    {
        return 2;
    }

    if (current_state != STATE_INIT)
    {
        return 3;
    }

    return 0;
}

uint8_t test_Get02_NullStateMachine(void)
{
    uint8_t current_state = 0xFF;
    if (get_current_state(NULL, &current_state, NULL) != 1)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Get03_UninitialisedMachine(void)
{
    state_machine_t sm = {0};
    uint8_t current_state = 0xFF;
    if (get_current_state(&sm, &current_state, NULL) != 2)
    {
        return 1;
    }

    return 0;
}

uint8_t test_Run07_ValidStateAndSubstateLoops(void)
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

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, func_addOneToY, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, func_addFourToZ, func_subFiveFromZ, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }
    if (transition_to(&sm, &states[STATE_ONE], &substates[SUBSTATE_ONE]) != 0)
    {
        return 2;
    }
    if (run_state_machine(&sm) != 0)
    {
        return 3;
    }
    if (get_x() != 5 || get_y() != 1 || (int32_t)get_z() != -1)
    {
        return 4;
    }

    return 0;
}

uint8_t test_Run08_NullCurrentSubstateWithSubstates(void)
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

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    sm.current_substate = NULL;
    if (run_state_machine(&sm) != 5)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Run09_CurrentSubstateOutOfBounds(void)
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

    state_t states[STATE_COUNT] =
        {
            {STATE_INIT, NULL, NULL, NULL},
            {STATE_ONE, func_addFiveToX, NULL, NULL},
        };

    substate_t substates[SUBSTATE_COUNT] =
        {
            {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
            {SUBSTATE_ONE, STATE_ONE, NULL, NULL, NULL},
        };

    state_machine_t sm;
    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    *sm.current_substate = SUBSTATE_COUNT;
    if (run_state_machine(&sm) != 6)
    {
        return 2;
    }

    return 0;
}

uint8_t test_Get04_ValidStateAndSubstateCurrentState(void)
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
    uint8_t current_state = 0xFF;
    uint8_t current_substate = 0xFF;

    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (get_current_state(&sm, &current_state, &current_substate) != 0)
    {
        return 2;
    }

    if (current_state != STATE_INIT || current_substate != SUBSTATE_INIT)
    {
        return 3;
    }

    return 0;
}

uint8_t test_Get05_NullCurrentStateOutput(void)
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
    uint8_t current_substate = 0xFF;

    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (get_current_state(&sm, NULL, &current_substate) != 0)
    {
        return 2;
    }

    if (current_substate != SUBSTATE_INIT)
    {
        return 3;
    }

    return 0;
}

uint8_t test_Get06_NullCurrentSubstateOutput(void)
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
    uint8_t current_state = 0xFF;

    if (init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT) != 0)
    {
        return 1;
    }

    if (get_current_state(&sm, &current_state, NULL) != 0)
    {
        return 2;
    }

    if (current_state != STATE_INIT)
    {
        return 3;
    }

    return 0;
}
