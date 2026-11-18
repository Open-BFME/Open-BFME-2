// cl: /MD
// ThingTemplate::getBuildable @0x0033A632, 44B.
// Canonical identity: ZH implementation and three Player::canBuild calls;
// target fallback establishes signed buildable byte at +0x5F2.
// Framed __thiscall returning int: if TheGameLogic present and rowed
// GameLogic::rva00245EDF(this,&out) true return out else sign-extended
// byte at +0x5F2. Evidence: TheGameLogic extern plus rowed 0x00245EDF
// plus movsx fallback plus 7 callers.
#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

#include "../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/BuildableStatus.h"

#include "../../Include/Common/ThingTemplate.h"

BuildableStatus ThingTemplate::getBuildable() const
{
	int out;
	if (TheGameLogic && TheGameLogic->rva00245EDF(const_cast<ThingTemplate *>(this), &out))
		return (BuildableStatus)out;
	return (BuildableStatus)m_buildable;
}
