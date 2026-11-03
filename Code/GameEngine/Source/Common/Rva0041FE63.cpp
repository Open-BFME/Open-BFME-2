// cl: /MD
// platformsdk
// ?rva0041FE63@VictoryConditions@@UAEXXZ @0x0041FE63 35B
// Vslot 31 of vtable 0x0083BA28 (class VictoryConditions). Evidence: byte at +0x10
// gates DWORD delta at +0x14 via winmm timeGetTime against 0x1b58 timeout
// then tail-jmps vtable slot 24 (offset 0x60).

#include <windows.h>

#include "../../Include/GameLogic/VictoryConditionsClass.h"

void VictoryConditions::rva0041FE63()
{
	if (m_10 == 0)
		return;
	DWORD t = timeGetTime();
	if (t - m_14 <= 0x1b58)
		return;
	slot24();
}
