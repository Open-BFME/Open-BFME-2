// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?rva00212183@LivingWorldManager@@QAEXPAX0@Z, retail 0x00212183, 27 bytes.
// The BFME 1 donor (BfmeConv694.cpp) spelled this as a stdcall free function,
// but the body is a thiscall member: it hands its unchanged ECX to the rowed
// member 0x002120C2 (Rva002120A4::rva002120C2, which walks this+0x24C), and
// its only caller 0x005652F7 loads ECX from TheLivingWorldManager. The entry
// that lookup returns runs the rowed 0x003FD690 with the second argument.
// Both arguments are passed through as the caller's addresses of its record's
// first two words.

class AsciiString;
struct Coord;
struct Rva002120C2Entry;

#include "../../Include/Common/Rva002120A4.h"

#include "../../Include/Common/Rva003FD690.h"

#include "../../Include/GameLogic/LivingWorldManager.h"

void LivingWorldManager::rva00212183(void *key, void *value)
{
	Rva003FD690 *entry = (Rva003FD690 *)((Rva002120A4 *)this)->rva002120C2(*(const AsciiString *)key);
	if (entry != 0)
		entry->rva003FD690((const Coord *)value);
}
