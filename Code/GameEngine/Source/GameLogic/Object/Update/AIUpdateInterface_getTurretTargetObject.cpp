// cl: /DNDEBUG /MD
//
// ?getTurretTargetObject@AIUpdateInterface@@QAEPAVObject@@W4WhichTurretType@@@Z,
// retail 0x00262605, 49 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:677) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). BFME2 dropped the clearDeadTargets
// parameter on both sides: the TurretAI helper takes (Object*&, Coord3D&)
// and returns the TurretTargetType, compared against TARGET_OBJECT (1).
// The Object* home reuses the dead turret parameter slot (ebp+8), which
// is why retail passes &tur as the Object*& out-parameter.

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

enum TurretTargetType
{
	TARGET_NONE,
	TARGET_OBJECT,
	TARGET_POSITION
};

class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct TurretAI
{
	TurretTargetType friend_getTurretTarget(Object *&obj, Coord3D &pos) const;
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[1];

public:
	Object *getTurretTargetObject(WhichTurretType tur);
};

// ?getTurretTargetObject@AIUpdateInterface@@QAEPAVObject@@W4WhichTurretType@@@Z
Object *AIUpdateInterface::getTurretTargetObject(WhichTurretType tur)
{
	if (m_turretAI[tur])
	{
		Object *obj;
		Coord3D pos;
		if (m_turretAI[tur]->friend_getTurretTarget(obj, pos) == TARGET_OBJECT)
		{
			return obj;
		}
	}
	return 0;
}
