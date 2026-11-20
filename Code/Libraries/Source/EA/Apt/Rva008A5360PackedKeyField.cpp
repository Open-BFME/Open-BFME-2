// cl: /DNDEBUG /MD /EHsc
// RVA 0x008A5360: extract bits 2-9 of the last packed key, offset by two.

#include "../../../../GameEngine/Include/Common/AptInteger.h"

#include "../../Apt/AptActionInterpreter.h"
extern AptActionInterpreter g_aptDateInterpreter;

AptInteger *aptPackedKeyFieldAt008A5360()
{
    return (AptInteger *)AptInteger::Create(((g_aptDateInterpreter.mLastKey >> 2) & 0xff) - 2);
}
