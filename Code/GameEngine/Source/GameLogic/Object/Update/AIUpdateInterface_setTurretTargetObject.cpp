// cl: /DNDEBUG /MD
//
// ?setTurretTargetObject@AIUpdateInterface@@QAEXW4WhichTurretType@@PAVObject@@_N@Z,
// retail 0x002625E6, 31 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:668) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). TurretAI::setTurretTargetObject is
// a direct (non-virtual) call, resolved by pin.

typedef bool Bool;

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

class Object;

struct TurretAI
{
	void setTurretTargetObject(Object *o, Bool forceAttacking);
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[1];

public:
	void setTurretTargetObject(WhichTurretType tur, Object *o, Bool forceAttacking);
};

// ?setTurretTargetObject@AIUpdateInterface@@QAEXW4WhichTurretType@@PAVObject@@_N@Z
void AIUpdateInterface::setTurretTargetObject(WhichTurretType tur, Object *o, Bool forceAttacking)
{
	if (m_turretAI[tur])
	{
		m_turretAI[tur]->setTurretTargetObject(o, forceAttacking);
	}
}
