// cl: /Oy- /DNDEBUG /MD /GX-
// ?parseAutoResolveReinforcementScheduleDefinition@@YAXPAVINI@@@Z, retail 0x00413D58, 115 bytes.
// INI type dispatch for AutoResolveReinforcementSchedule: getNextToken(0),
// strcmpi against "Attacker" (index 1) / "Defender" (index 0), then
// rva00413D46 off TheLivingWorldAutoResolveReinforcementScheduleStore + 0xc + index*16; else INIException(1, msg)
// plus CxxThrow. Evidence: chain lane (calls just-landed 0x00413D46);
// strings Attacker Defender; prev/next Common Rva parse TUs.
#include <string.h>

#include "../../Include/Common/INI/INI.h"

class Rva00413D46
{
public:
	void rva00413D46(INI *ini);
};

void * TheLivingWorldAutoResolveReinforcementScheduleStore;	// retail RVA 0x00A03064 (.data, 8 bytes), defined here: nothing else owns it

#include "../../Include/Common/INI/FieldParse.h"


void parseAutoResolveReinforcementScheduleDefinition(INI *ini)
{
	const char *tok = ini->getNextToken(0);
	int idx;
	if (_strcmpi(tok, "Attacker") == 0)
		idx = 1;
	else if (_strcmpi(tok, "Defender") == 0)
		idx = 0;
	else
	{
		throw INIException(1, "Unknown AutoResolveReinforcementSchedule type '%s'. Should be 'Attacker' or 'Defender'", tok);
	}
	Rva00413D46 *elem = (Rva00413D46 *)((char *)TheLivingWorldAutoResolveReinforcementScheduleStore + 0xc + (idx << 4));
	elem->rva00413D46(ini);
}
