// cl: /Oy- /DNDEBUG /MD
//
// ?getTurretTurnRate@AIUpdateInterface@@QBEMW4WhichTurretType@@@Z,
// retail 0x00262730, 46 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:761) with the BFME2 layout: m_turretAI lives at +0x20C.
// TurretAI::getTurnRate is an inline m_data->m_turnRate read (m_data at
// TurretAI+8, rate at +0), matching retail's two-chase movss.

typedef float Real;

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

struct TurretAIData
{
	Real m_turnRate;
};

struct TurretAI
{
	char m_pad[8];
	const TurretAIData *m_data;

	Real getTurnRate() const { return m_data->m_turnRate; }
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[1];

public:
	Real getTurretTurnRate(WhichTurretType tur) const;
};

// ?getTurretTurnRate@AIUpdateInterface@@QBEMW4WhichTurretType@@@Z
Real AIUpdateInterface::getTurretTurnRate(WhichTurretType tur) const
{
	return (tur != TURRET_INVALID && m_turretAI[tur] != 0) ?
					m_turretAI[tur]->getTurnRate() :
					0.0f;
}
