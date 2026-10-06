// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// ?enableTurret@BattlePlanUpdate@@IAEX_N@Z, retail 0x0049773F (42B).
// Ported from the Zero Hour reference
// (GameLogic/Object/Update/BattlePlanUpdate.cpp): fetch the object's AI,
// ask it which turret the current weapon uses, and enable or disable that
// turret. A missing AI or an invalid turret changes nothing.

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
	void setTurretEnabled(WhichTurretType tur, bool enabled);
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
	void enableTurret(bool enable);

private:
	Object *getObject() { return m_object; }

	void *m_vtable;	// +0x00
	int m_pad04;	// +0x04 (unmapped Module base member)
	Object *m_object;	// +0x08
};

// ?enableTurret@BattlePlanUpdate@@IAEX_N@Z
void BattlePlanUpdate::enableTurret(bool enable)
{
	AIUpdateInterface *ai = getObject()->getAI();
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			ai->setTurretEnabled(tur, enable);
		}
	}
}
