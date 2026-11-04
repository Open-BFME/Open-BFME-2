// cl: /O1 /arch:SSE /G7 /MD
// Retail 0x00332B0D/27: a three-argument cdecl forward to virtual slot 0x98
// of the debug manager through theDebug (VA 0x00DE0880), the same shape as
// the rowed static forward Debug::SetBuildInfo 0x00001705 (WinMain.cpp),
// which reaches slot 0x9C. It sits among the Lua script engine bodies.
// Slot 0x98 is Debug::GetInput in the canonical header; the wrapper's own
// name and dword argument types are not established, so the name stays
// address-derived and the arguments are cast to GetInput's parameters.
#include "../../Common/debug.h"

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

void Rva00332B0D(int a, int b, int c)
{
	theDebug->GetInput(reinterpret_cast<char *>(a), b, reinterpret_cast<bool *>(c));
}
