#include "testSupport.h"


int32_t x = 0;
int32_t y = 0;
int32_t z = 0;

/**=========================================
 *   State Machine Test Functions
 * =========================================
 */
#pragma region StateMachineTestFunctions
uint8_t func_multiplyXByTwo(void)
{
    x *= 2;
    return 0;
}
uint8_t func_addFiveToX(void)
{
    x += 5;
    return 0;
}
uint8_t func_addOneToY(void)
{
    y += 1;
    return 0;
}
uint8_t func_addFourToZ(void)
{
    z += 4;
    return 0;
}
uint8_t func_subFiveFromZ(void)
{
    z -= 5;
    return 0;
}

uint8_t func_setYToX(void)
{
    y = x;
    return 0;
}
uint8_t func_setZToY(void)
{
    z = y;
    return 0;
}
uint8_t func_setAllToOne(void)
{
    x = 1;
    y = 1;
    z = 1;
    return 0;
}
uint8_t func_setAllToZero(void)
{
    x = 0;
    y = 0;
    z = 0;
    return 0;
}

uint8_t func_failOne(void)
{
    return 1;
}
uint8_t func_failSeven(void)
{
    return 2;
}
uint8_t func_failFifteen(void)
{
    return 15;
}
#pragma endregion




uint32_t get_x(void)
{
    return x;
}
uint32_t get_y(void)
{
    return y;
}
uint32_t get_z(void)
{
    return z;
}