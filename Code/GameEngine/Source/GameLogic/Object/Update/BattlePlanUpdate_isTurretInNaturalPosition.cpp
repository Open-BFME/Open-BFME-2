// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// ?isTurretInNaturalPosition@BattlePlanUpdate@@IAE_NXZ, retail 0x0049778D (40B).
// Ported from the Zero Hour reference
// (GameLogic/Object/Update/BattlePlanUpdate.cpp): fetch the object's AI,
// ask it which turret the current weapon uses, and report whether that
// turret sits in its natural position. A missing AI or an invalid turret
// reads as not in position.

enum WhichTurretType
{
	TURRET_INVALID = -1,

	TURRET_MAIN = 0,
	TURRET_ALT,

	MAX_TURRETS
};

class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForCurWeapon() const;
	bool isTurretInNaturalPosition(WhichTurretType tur) const;
};

class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }

private:
	unsigned char m_pad[0x258];	// vtable + members ahead of m_ai
	AIUpdateInterface *m_ai;	// +0x258
};

class BattlePlanUpdate
{
protected:
	bool isTurretInNaturalPosition();

private:
	Object *getObject() { return m_object; }

	void *m_vtable;	// +0x00
	int m_pad04;	// +0x04 (unmapped Module base member)
	Object *m_object;	// +0x08
};

// ?isTurretInNaturalPosition@BattlePlanUpdate@@IAE_NXZ
bool BattlePlanUpdate::isTurretInNaturalPosition()
{
	AIUpdateInterface *ai = getObject()->getAI();
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			return ai->isTurretInNaturalPosition(tur);
		}
	}
	return false;
}
