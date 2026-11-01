// cl: /DNDEBUG /MD /EHs-c-
//
// Free wrapper at retail 0x000385E0 (14 bytes): asks the Debug singleton
// (theDebug, 0x00DE0880) whether the game runs windowed, through the
// virtual at Debug vtable slot 0xAC (0x000397D0), as a tail call. The
// RaiseException hook at 0x0003E1C0 calls it before reporting a C++ throw.
// The name is descriptive; no symbol survives for it.

#include "../../../../GameEngine/Source/Common/debug.h"

extern Debug *theDebug;

// ?DebugIsWindowed@@YA_NXZ
bool DebugIsWindowed()
{
	return theDebug->IsWindowed();
}
