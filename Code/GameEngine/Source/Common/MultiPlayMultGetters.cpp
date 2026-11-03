// cl: /DNDEBUG /MD /EHsc
// Getter siblings of the BFME1-derived MultiPlayMults facade.
// Array roles come from PC FieldParse callbacks and their matched setters.
// PC callers add GlobalData+0xEC4 before the XP/speed accessors; no Xbox ABI reused.
// Invalid signed slot-1 returns the independently checked float literal 1.0.
typedef int Int;
typedef float Real;
#include "../../Include/Common/MultiPlayMults.h"


Real MultiPlayMults::getMoneyMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_money[index];
    return 1.0f;
}

Real MultiPlayMults::getUnitXPMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_unitXP[index];
    return 1.0f;
}

Real MultiPlayMults::getBuildingXPMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_buildingXP[index];
    return 1.0f;
}

Real MultiPlayMults::getUnitSpeedMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_unitSpeed[index];
    return 1.0f;
}

Real MultiPlayMults::getBuildingSpeedMult(Int slot) const
{
    Int index = slot - 1;
    if (index >= 0 && index < 20)
        return m_buildingSpeed[index];
    return 1.0f;
}
