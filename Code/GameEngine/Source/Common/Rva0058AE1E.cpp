// cl: /MD
// ?Rva0058AE1EHasVictim@@YG_NPAVObject@@@Z 0x0058AE1E 24B evidence: AIUpdateInterface+0x258 victim !=0 via rowed getCurrentVictim; ret 4 stdcall.
// Its caller 0x005D874A tests only AL, so the result is a bool (the
// neg/sbb/neg form is the same for an int).
class Object;
#include "../../Include/GameLogic/Module/AIUpdate.h"

bool __stdcall Rva0058AE1EHasVictim(Object *obj)
{
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)obj + 0x258);
	return ai->getCurrentVictim() != 0;
}
