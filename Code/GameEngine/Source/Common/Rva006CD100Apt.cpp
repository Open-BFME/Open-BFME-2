// cl: /DNDEBUG /MD /EHs-c-
// ?Rva006CD100Get@@YA_NXZ @0x006CD100 17B.
// Apt presence check: returns g_bfmeAptPtrAtE176D0->m_6c != 0. Evidence:
// global g_bfmeAptPtrAtE176D0 at VA 0x00A176D0 (packet extern name in use,
// mangled ?g_bfmeAptPtrAtE176D0@@3PAVRva006E34D0@@A); callers 0x00224F6C and
// 0x002251E5 (latter stores AL to byte [esi+0x329], proving bool return);
// neighbour TU Rva006CC950Mouse.cpp shares same global and class.
#include "../../../Libraries/Source/Apt/Rva006E34D0.h"
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
bool __cdecl Rva006CD100Get()
{
	return g_bfmeAptPtrAtE176D0->m_field6C != 0;
}
