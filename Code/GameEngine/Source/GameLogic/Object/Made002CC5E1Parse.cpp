// cl: /DNDEBUG /MD
//
// ?q4Notify002CC5E1@@YAXPAXPAVDamageNugget@@HH@Z @0x005088F0 (53B).
// DamageNugget field parser: MultiIni tmp, buildFieldParse via rowed
// 0x005088CE, then INI initFromINIMulti via pin. Caller
// parseDamageNugget at 0x002CC626. Same tail as sibling q4Notify002CC64B
// 0x0050893A but with adds factored into buildFieldParse.
class DamageNugget;
#include "../../../Include/Common/INI/FieldParse.h"
#include "../../../Include/GameLogic/Module/Rva005088CE.h"
#include "../../../Include/Common/INI/INI.h"
void __cdecl q4Notify002CC5E1(void *ini, DamageNugget *damageNugget, int store, int userData)
{
	MultiIniFieldParse tmp;
	Rva005088CE::buildFieldParse(tmp);
	((INI *)ini)->initFromINIMulti(damageNugget, tmp);
}
