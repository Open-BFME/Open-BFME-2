// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BattlePlanUpdate.cpp: BattlePlanUpdate bodies retail links from this TU
// (tu_map approved). The turret helpers were folded in from split units with
// these exact flags; one BattlePlanUpdate view carries the offsets each body
// was verified against: +0x08 object, +0x2C affecting army, +0x30 status.
// getCommandOption stays split: it reads its plan through the interface
// subobject (+0x08 of that base), which this view cannot express.
// onObjectCreated (0x0049797F) stays split for now: it calls
// Object::setWeaponLock, whose kept definition is not retail's, and folding it
// would stop this unit linking.

enum BattlePlanStatus
{
	PLANSTATUS_NONE = 0
};

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
	void recenterTurret(WhichTurretType tur);
	void setTurretEnabled(WhichTurretType tur, bool enabled);
};

class Object
{
public:
	// Declaration only: the retail copy lives in Object.cpp (0x00313EB6) and
	// reads m_ai at +0x19C. Defining it here would emit a second COMDAT copy.
	AIUpdateInterface *getAI();

public:
	unsigned char m_pad[0x258];	// vtable + members ahead of m_aiDirect
	AIUpdateInterface *m_aiDirect;	// +0x258 (retail-measured direct AI slot, not the +0x19C getAI member)
};

// recenterTurret's host: this body reads its AI cell at +0x258 through an
// inline accessor, while the rowed Object::getAI (0x00313EB6) reads +0x19C.
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
public:
	BattlePlanStatus getActiveBattlePlan() const;

protected:
	void enableTurret(bool enable);
	void recenterTurret();
	bool isTurretInNaturalPosition();

private:
	Object *getObject() { return m_object; }

	void *m_vtable; // +0x00
	int m_pad04; // +0x04 (unmapped Module base member)
	Object *m_object; // +0x08
	char m_pad0C[0x2C - 0x0C];
	int m_planAffectingArmy;	// +0x2C
	int m_status;		// +0x30
};

// ?enableTurret@BattlePlanUpdate@@IAEX_N@Z, retail 0x0049773F (42B).
// Ported from the Zero Hour reference
// (GameLogic/Object/Update/BattlePlanUpdate.cpp): fetch the object's AI,
// ask it which turret the current weapon uses, and enable or disable that
// turret. A missing AI or an invalid turret changes nothing.
void BattlePlanUpdate::enableTurret(bool enable)
{
	AIUpdateInterface *ai = getObject()->m_aiDirect;
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			ai->setTurretEnabled(tur, enable);
		}
	}
}

// ?recenterTurret@BattlePlanUpdate@@IAEXXZ, retail 0x00497769 (36B).
// Ported from the Zero Hour reference: fetch the object's AI, ask it which
// turret the current weapon uses, and recenter that turret. A missing AI or an
// invalid turret recenters nothing.
void BattlePlanUpdate::recenterTurret()
{
	AIUpdateInterface *ai = ((Rva00497769Host *)getObject())->getAI();
	if (ai)
	{
		WhichTurretType tur = ai->getWhichTurretForCurWeapon();
		if (tur != TURRET_INVALID)
		{
			ai->recenterTurret(tur);
		}
	}
}

// ?isTurretInNaturalPosition@BattlePlanUpdate@@IAE_NXZ, retail 0x0049778D (40B).
// Ported from the Zero Hour reference: fetch the object's AI, ask it which
// turret the current weapon uses, and report whether that turret sits in its
// natural position. A missing AI or an invalid turret reads as not in position.
bool BattlePlanUpdate::isTurretInNaturalPosition()
{
	AIUpdateInterface *ai = getObject()->m_aiDirect;
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

// ?getActiveBattlePlan@BattlePlanUpdate@@QBE?AW4BattlePlanStatus@@XZ
// BFME2 BattlePlanUpdate active-plan getter, transferred from the exact
// BFME1 reconstruction
// (Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp).
// Retail BFME2 keeps the same fields: the affecting army at +0x2C and the
// transition status at +0x30; only the active status reads the army.
BattlePlanStatus BattlePlanUpdate::getActiveBattlePlan() const
{
	if (m_status == 2)
	{
		return (BattlePlanStatus)m_planAffectingArmy;
	}
	return PLANSTATUS_NONE;
}
