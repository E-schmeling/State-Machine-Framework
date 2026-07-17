# State Machine Framework

A small state machine framework for embedded C systems.

This repository provides a compact state machine core written in C that supports both state-only operation and hierarchical state + substate operation. 

The framework lives in `src/stateMachine.c` and `src/stateMachine.h`. It handles initialisation, transitions, periodic execution, and current-state reporting. The test code in `test/` is written to the documented failure paths as well as the normal flow.

## Structure

- `src/stateMachine.h`: public API, type definitions, and documented return codes.
- `src/stateMachine.c`: core implementation.
- `test/tests.c`: raw C test suite.
- `test/testSupport.c` and `test/testSupport.h`: helper functions used by the tests.
- `test/stateMachine_test_matrix.csv`: matrix of expected coverage and function names.

## How to use

The framework is designed around a small set of rules:

- States and substates are stored in arrays.
- IDs must be sequential and start at `0`.
- State `0` is the init state.
- If substates are enabled, substate `0` is the init substate.
- The init state must not define `exit` or `loop`.
- The init substate must not define `exit` or `loop`.
- The first substate is treated specially and must be the only substate allowed to use `parent_state_id == 0`.

The minimal integration flow is:

1. Define a `state_t` array.
2. Optionally define a `substate_t` array.
3. Call `init_state_machine()`.
4. Use `transition_to()` or `transition_toNum()` to move between states.
5. Call `run_state_machine()` periodically.
6. Use `get_current_state()` when you need to inspect the active IDs.

## Public API

### `init_state_machine()`

Initialises the machine and sets the current state to state `0`.

It will reject:

- a null state machine pointer
- a null state array
- zero states
- state IDs that are not in ascending order
- a null substate array when substates are requested
- substate IDs that are not in ascending order
- init state hooks that include `exit` or `loop`
- init substate hooks that include `exit` or `loop`
- invalid parent mapping for substates

It also propagates failures from the init state and init substate `enter` hooks using the documented encoded return values.

After the `init_state_machine` call returns, the machine should be transition to its normal operations state.

> Technically it is possible to leave the state machine in the init state, but as it has no loop hooks it will be hard to drive it to a working state when using proper state machine logic.

### `transition_to()`

Transitions by pointer to a state and optional substate.

It supports:

- state-only transitions when `substate_count == 0`
- same-state substate changes
- full state + substate changes

It will reject:

- null state machine
- uninitialised machine
- null new state
- out-of-bounds state IDs
- out-of-bounds substate IDs
- mismatched state/substate pairs
- inconsistent state-only usage in a state + substate system

### `transition_toNum()`

Transitions by numeric state and substate number.

This is the wrapper that exists because the pointer-based version can be awkward as it would require the call to be made like:
```c
transition_to(&sm, &states[STATE_ACTIVE], &substates[SUBSTATE_RUNNING]);
```
when what I originally intended but didnt think of how C interacts with typedefs is this:
```c
transition_toNum(&sm, STATE_ACTIVE, SUBSTATE_RUNNING);
```

It follows the same return codes as `transition_to()`, but uses IDs directly and respects state-only mode.

> Technically the declaration of max of 2^8 states and substates is based on this decision as I am uint8_t for loops and state ID's so technically you can increase this limit by changing alot of the uint8_t to a higher uint. but there needs to be a limit and 255 is alot in my opinion

### `run_state_machine()`

Runs the current state's `loop` hook and, if present, the current substate's `loop` hook.

It validates:

- state machine pointer
- initialisation state
- current state pointer
- current state bounds
- current substate pointer when substates exist
- current substate bounds
- the absence of a current substate when no substates are configured

### `get_current_state()`

Returns the current state and substate IDs, if requested.

- Either output pointer may be `NULL`
- If substates are not configured, the substate output is reported as `0`

## Return Codes

The implementation is intentionally explicit about failure modes.

Return codes are defined in `stateMachine.h`. In general, 0 indicates success and any other value indicates an error.

## Restrictions

These are the main things to keep in mind when using the framework:

- IDs must be sequential and start at `0`.
- State `0` and substate `0` are special.
- Substates are optional, but if you use them the arrays and parent mapping must be valid.
- Do not define `exit` or `loop` on the init state or init substate.
- `transition_toNum()` should be used with valid IDs only, just like the table-based APIs.


## AI Use

AI was used here for documentation support, through the use of GitHub Copilot's inline suggestions and a local Gwen Coder 2.5 7B model when copilot's inline suggestions were not available.

AI was also used partly on the test suite so I did lose my will writing practically the same thing some 40 times. 5 tests were written by hand over the course of 2 evenings before coming to this conclusion. The light framework around the test was also written by hand.

Other than the test suite, as with all my other modules, this libraries code was exclusively written by hand.

## Short Example

This is the basic shape of a state-only setup:

```c
typedef enum
{
    STATE_INIT = 0,
    STATE_ACTIVE,
    STATE_COUNT
} state_id_t;

state_t states[STATE_COUNT] =
{
    {STATE_INIT, NULL, NULL, NULL},
    {STATE_ACTIVE, enter_active, loop_active, exit_active},
};

state_machine_t sm;
init_state_machine(&sm, states, NULL, STATE_COUNT, 0);
transition_toNum(&sm, STATE_ACTIVE, 0);
run_state_machine(&sm);
```

And this is the same idea when substates are enabled:

```c
typedef enum
{
    STATE_INIT = 0,
    STATE_ACTIVE,
    STATE_COUNT
} state_id_t;

typedef enum
{
    SUBSTATE_INIT = 0,
    SUBSTATE_RUNNING,
    SUBSTATE_COUNT
} substate_id_t;

state_t states[STATE_COUNT] =
{
    {STATE_INIT, NULL, NULL, NULL},
    {STATE_ACTIVE, enter_active, loop_active, exit_active},
};

substate_t substates[SUBSTATE_COUNT] =
{
    {SUBSTATE_INIT, STATE_INIT, NULL, NULL, NULL},
    {SUBSTATE_RUNNING, STATE_ACTIVE, enter_run, loop_run, exit_run},
};

state_machine_t sm;
init_state_machine(&sm, states, substates, STATE_COUNT, SUBSTATE_COUNT);
transition_toNum(&sm, STATE_ACTIVE, SUBSTATE_RUNNING);
run_state_machine(&sm);
```
