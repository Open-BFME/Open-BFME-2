// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCA5DSet@ScriptActions@@QAEXE@Z @0x003BCA5D 11B evidence: mov ecx [0x00DFDC30] tail-jmp to rowed Rva001DD240::rva001DD276 at 0x001DD276; caller at 0x003CD716; siblings Rva003BCA43Do Rva003BCA7BSet fix stdcall void shape
#include "../../../Include/Common/Rva001DD240.h"
extern class Eva *TheEva;
void ScriptActions::Rva003BCA5DSet(unsigned char flag)
{
	(*(Rva001DD240 **)&TheEva)->setFlag(flag);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
