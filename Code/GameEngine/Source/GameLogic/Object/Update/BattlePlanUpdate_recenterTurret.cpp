// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?recenterTurret@BattlePlanUpdate@@IAEXXZ, retail 0x00497769 (36B).
// Ported from the Zero Hour reference
// (GameLogic/Object/Update/BattlePlanUpdate.cpp): fetch the object's AI,
// ask it which turret the current weapon uses, and recenter that turret.
// A missing AI or an invalid turret recenters nothing.
// Host type is Rva00497769Host, not Object: this body reads its AI cell at
// +0x258 while the rowed Object::getAI (0x00313EB6) reads m_ai at +0x19C.

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
	void recenterTurret(WhichTurretType tur);
};

class Rva00497769Host
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
	void recenterTurret();

private:
	Rva00497769Host *getObject() { return m_object; }

	void *m_vtable;	// +0x00
	int m_pad04;	// +0x04 (unmapped Module base member)
	Rva00497769Host *m_object;	// +0x08
};

// ?recenterTurret@BattlePlanUpdate@@IAEXXZ
void BattlePlanUpdate::recenterTurret()
{
	AIUpdateInterface *ai = getObject()->getAI();
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			ai->recenterTurret(tur);
		}
	}
}
