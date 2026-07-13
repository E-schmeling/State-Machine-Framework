#include <Arduino.h>
#include "stateMachine.c"


// Must use Format. 
// System will init into state_id_t = 0,
// System will perform checks around STATE_COUNT.
// System Init can have a Enterence function but will not allow a loop or exit function. 
// as soon the state machine inits successfully, use transition_to(state, substate) --
// to go to the default state and substate.
// 
// there is a max number of states and substates due to the uint8_t type.
// that limit is 255 states and 255 substates.

typedef enum
{
    STATE_INIT = 0,
    STATE_PRELAUNCH,
    STATE_INFLIGHT,
    STATE_RECOVERY,
    
    STATE_COUNT
} state_id_t;

typedef enum
{
    SUBSTATE_INIT = 0,
    
    SUBSTATE_PRELAUNCH_IDLE,
    SUBSTATE_PRELAUNCH_ARMED,
    SUBSTATE_PRELAUNCH_CHECKS,

    SUBSTATE_INFLIGHT_ASCENT,
    SUBSTATE_INFLIGHT_COAST,
    SUBSTATE_INFLIGHT_APOGEE,
    SUBSTATE_INFLIGHT_DESCENT,
    SUBSTATE_INFLIGHT_LANDED,

    SUBSTATE_RECOVERY_IDLE,

    SUBSTATE_COUNT
} substate_id_t;

state_machine_t stateMachine;

state_t states[STATE_COUNT] = 
{
    {STATE_INIT, NULL, NULL, NULL},
    {STATE_PRELAUNCH, NULL, NULL, NULL},
    {STATE_INFLIGHT, NULL, NULL, NULL},
    {STATE_RECOVERY, NULL, NULL, NULL}
};

substate_t substates[SUBSTATE_COUNT] = 
{
    {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
    {SUBSTATE_PRELAUNCH_IDLE, STATE_PRELAUNCH, NULL, NULL, NULL},
    {SUBSTATE_PRELAUNCH_ARMED, STATE_PRELAUNCH, NULL, NULL, NULL},
    {SUBSTATE_PRELAUNCH_CHECKS, STATE_PRELAUNCH, NULL, NULL, NULL},
    {SUBSTATE_INFLIGHT_ASCENT, STATE_INFLIGHT, NULL, NULL, NULL},
    {SUBSTATE_INFLIGHT_COAST, STATE_INFLIGHT, NULL, NULL, NULL},
    {SUBSTATE_INFLIGHT_APOGEE, STATE_INFLIGHT, NULL, NULL, NULL},
    {SUBSTATE_INFLIGHT_DESCENT, STATE_INFLIGHT, NULL, NULL, NULL},
    {SUBSTATE_INFLIGHT_LANDED, STATE_INFLIGHT, NULL, NULL, NULL},
    {SUBSTATE_RECOVERY_IDLE, STATE_RECOVERY, NULL, NULL, NULL}
};


void setup()
{
    init_state_machine(&stateMachine, states, substates, STATE_COUNT, SUBSTATE_COUNT);



    // put your setup code here, to run once:
}

void loop()
{
    // put your main code here, to run repeatedly:
}
