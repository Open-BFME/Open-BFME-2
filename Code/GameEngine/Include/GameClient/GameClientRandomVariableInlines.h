// Retail's constructor at RVA 0x000B4979 clears the distribution and both
// bounds. Include its body in units whose matched callers inline those stores.
#pragma once

#include "GameClientRandomVariable.h"

inline GameClientRandomVariable::GameClientRandomVariable()
{
    m_type = CONSTANT;
    m_low = 0.0f;
    m_high = 0.0f;
}
