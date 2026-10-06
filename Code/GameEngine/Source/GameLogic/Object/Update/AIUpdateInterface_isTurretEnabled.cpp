// cl: /DNDEBUG /MD
//
// ?isTurretEnabled@AIUpdateInterface@@QBE_NW4WhichTurretType@@@Z,
// retail 0x00262683, 25 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:719) with TurretAI::isTurretEnabled() inlined: the retail body
// reads the flag directly at TurretAI+0x3C with no call, so the inner query
// is a non-virtual inline here too. m_turretAI lives at +0x20C.

typedef bool Bool;

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

struct TurretAI
{
	char m_pad[0x3C];
	Bool m_enabled;

	Bool isTurretEnabled() const { return m_enabled; }
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[1];

public:
	Bool isTurretEnabled(WhichTurretType tur) const;
};

// ?isTurretEnabled@AIUpdateInterface@@QBE_NW4WhichTurretType@@@Z
Bool AIUpdateInterface::isTurretEnabled(WhichTurretType tur) const
{
	if (m_turretAI[tur])
	{
		return m_turretAI[tur]->isTurretEnabled();
	}
	return false;
}
