// cl: /DNDEBUG /MD
//
// ?q4Notify002CC9D4@@YAXPAXPAVMade002CC9D4@@HH@Z @0x0050ADB9 (53B).
// DamageContainedNugget field parser: builds a 0x84-byte MultiIniFieldParse on the stack
// through the rowed ??0MultiIniFieldParse@@QAE@XZ, runs the rowed
// ?Rva0050AD97BuildFieldParse@@YAXAAVMultiIniFieldParse@@@Z, then forwards
// the Made (as void*) plus the table through the pin-only
// ?initFromINIMulti@INI@@QAEXPAXABVMultiIniFieldParse@@@Z. Caller is
// ?parseDamageContainedNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at 0x002CCA19
// (Code/GameEngine/Source/GameLogic/Object/WeaponNuggetParse.cpp), which
// declares this q4Notify (c/d unused, matching retail ignoring [ebp+16]/+20).

class Made002CC9D4;

#include "../../../Include/Common/INI/FieldParse.h"

void Rva0050AD97BuildFieldParse(MultiIniFieldParse &m);

#include "../../../Include/Common/INI/INI.h"

void q4Notify002CC9D4(void *ini, Made002CC9D4 *nugget, int c, int d)
{
	MultiIniFieldParse tmp;
	Rva0050AD97BuildFieldParse(tmp);
	((INI *)ini)->initFromINIMulti(nugget, tmp);
}
