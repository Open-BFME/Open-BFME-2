// cl: /DNDEBUG /MD
//
// ??1BfmeDirtyBase@@UAE@XZ, retail 0x00658650 (7 bytes). Dedicated TU: the
// shared DirtySock base destructor only reinstalls its vtable (0x00CE0FB8).
// It lives apart from Y2ScalarDeleters.cpp on purpose -- nine matched
// scalar-deleting rows there call it out of line, and a same-TU definition
// would inline the 7 bytes into every one of them. The 0x007EB6C0 address
// that TU's header comment names disassembles to data, not code.

#include "../../../GameEngine/Include/Common/BfmeDirtyBase.h"

__declspec(noinline) BfmeDirtyBase::~BfmeDirtyBase()
{
}
