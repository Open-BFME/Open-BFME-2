// cl: /DNDEBUG /MD

// 0x000387C0, 12 bytes: returns the byte at +0x9F57 of the Debug singleton
// that the pointer at 0x00DE0880 names.  It sits among the Debug library's
// bodies and BFME_DX8_Thread_Lock at 0x0011F520 calls it to decide whether
// to report its twenty-second timeout.  Its own unit, because a definition in
// the lock's unit is inlined into the lock, where retail keeps the call.  The
// Debug model is reduced to its vtable pointer and the flag; the name is
// address-derived since the member's identity is not recovered.

#include "../../../GameEngine/Source/Common/debug.h"

extern Debug *theDebug;

bool bfmeRva000387C0()
{
	return theDebug->logErrorsToFile;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?_bfme_debugReportingEnabled@@YA_NXZ=?bfmeRva000387C0@@YA_NXZ")
