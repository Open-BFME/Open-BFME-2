// cl: /DNDEBUG /MD
//
// ??1Rva00666BA0@@UAE@XZ, retail 0x00666BA0 (7 bytes). Dedicated TU: the
// shared base destructor only reinstalls its vtable (0x00CE2BD8). It lives
// apart from the derived TU on purpose -- derived destructors at 0x00661350
// (11B) and 0x006617C0 (39B) call it out of line, and a same-TU definition
// would capture those calls locally instead of at the ledger address
// (BfmeDirtyBaseDtor.cpp precedent).

#include "Rva00666BA0.h"

// Retail's scalar deleting destructor (0x00661330) calls this body out of
// line; noinline keeps this unit's emitted ??_G the same call shape.
__declspec(noinline) Rva00666BA0::~Rva00666BA0()
{
}
