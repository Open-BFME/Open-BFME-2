// cl: /DNDEBUG /MD
// ?getMaxTurnRate@Locomotor@@QBEMPAVObject@@@Z @0x001E3E9F 105B. Locomotor turn-rate
// query taking the owning Object: reads Body damage state via slot 0x20, picks the
// normal vs damaged angular period (uints at template +0x2C/+0x30), returns
// 2*PI / period clamped to instance max at +0x38. Ported from Open-BFME-1
// (Code/GameEngine/Source/GameLogic/Object/LocomotorGetMaxTurnRateObject.cpp,
// retail 0x001B5860, Object+0x200 slot 0x20 template +0x28/+0x2C max +0x34
// TwoPi at 0x7C746C GlobalData penalty at +0xBD8); BFME2 deltas are Object body
// at +0x254, template periods at +0x2C/+0x30, max at +0x38, penalty at +0xB3C.
// Callers at 0x001E4089 0x001E68B9 0x001E6ADF prove Object* + float shape.

extern class GlobalData *TheWritableGlobalData;

typedef float Real;
typedef unsigned int UnsignedInt;

enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_DAMAGED = 1,
	BODY_REALLYDAMAGED = 2,
	BODY_RUBBLE = 3
};

#include "../../../Include/GameLogic/Module/BodyModule.h"

#include "object.h"

#include "../../../Include/GameLogic/LocomotorTemplate.h"

#include "../../../Include/Common/GlobalData.h"

#define TheGlobalData TheWritableGlobalData

#include "../../../Include/GameLogic/LocomotorClass.h"

Real Locomotor::getMaxTurnRate(Object *object) const
{
	BodyDamageType condition = object->m_body->getDamageState();
	Real turnRate;
	if (condition < TheGlobalData->m_movementPenaltyDamageState)
		turnRate = 6.283185307179586f / (Real)(UnsignedInt)m_template->m_turnTime;
	else
		turnRate = 6.283185307179586f / (Real)(UnsignedInt)m_template->m_turnTimeDamaged;
	if (turnRate > m_maxTurnRate)
		turnRate = m_maxTurnRate;
	return turnRate;
}
