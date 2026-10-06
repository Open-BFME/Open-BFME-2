// cl: /DNDEBUG /MD
//
// ?isAbleToAttack@Object@@QBE_NXZ, retail 0x00290B73, 440 bytes.
// Dedicated TU so Object.cpp cannot see this body.
//
// BFME2 rewrite of the BFME1/ZH Object::isAbleToAttack
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp:3619).
// Check order is preserved (NO_ATTACK -> container -> UNDER_CONSTRUCTION ->
// SOLD -> template/portable gate -> turret loop -> CAN_ATTACK kind -> CAN_ATTACK
// status -> container/fire gate -> AI/weapon -> spawn -> false) but BFME2 reads
// members directly where the ancestor called virtuals: the status checks go
// through testStatus with BFME2 bit numbers (retail immediates 5, 0x25, 2,
// 0x13, 1), the template KindOf checks read template bytes directly, and the
// container/fire gate calls slots of the interface at +0x250.
//
// Offsets (all retail-measured): template +0x04, statusByte +0x1C8 (bit 2),
// iface +0x250, AI +0x258, containedBy +0x274, weaponSet +0x330 (lea only),
// weaponSetPresent +0x358 (same dword ObjectGetCurrentWeapon.cpp reads).
// testStatus (+0x94 words), isKindOf (+0x10C words) and getContain (+0x190)
// are already matched and prove the low Object layout this TU extends.

typedef bool Bool;
typedef float Real;

#ifndef NULL
#define NULL 0
#endif

enum ObjectStatusTypes
{
	OBJECT_STATUS_CAN_ATTACK = 1,
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_NO_ATTACK = 5,
	OBJECT_STATUS_SOLD = 0x13,
	OBJECT_STATUS_0x25 = 0x25
};

enum KindOfType
{
	KINDOF_0x81 = 0x81
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

class Object;
class Weapon;

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	unsigned char m_kindByte108;
	unsigned char m_pad109[0x10F - 0x109];
	unsigned char m_kindByte10F;
	unsigned char m_pad110[0x112 - 0x110];
	unsigned char m_kindByte112;
	unsigned char m_pad113[0x115 - 0x113];
	unsigned char m_kindByte115;
};

struct WeaponSet
{
	char m_pad[8];
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
};

class AIUpdateInterface
{
public:
	WhichTurretType getWhichTurretForWeaponSlot(WeaponSlotType wslot, Real *turretAngle, Real *turretPitch) const;
	Bool isTurretEnabled(WhichTurretType tur) const;
	Object *getCurrentVictim() const;
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual Bool canAnySlavesAttack() = 0;
};

// Interface at Object+0x250. Slots 45 (0-arg gate) and 69 (1-arg count) play
// exactly the BFME1 contain tail (isPassengerAllowedToFire + getContainCount);
// slots 44/48 are unmapped so they keep opaque names.
class Bfme250Interface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual const unsigned *slot44(void *buf16, const Object *obj) = 0;
	virtual Bool slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual Bool slot48(const Object *a, const Object *b) = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual unsigned slot69(int zero) = 0;
};

class Object
{
	char m_pad0[4];
	ThingTemplate *m_template;
	char m_pad8[0x1C8 - 0x8];
	unsigned char m_statusByte1C8;
	char m_pad1C9[0x250 - 0x1C9];
	Bfme250Interface *m_iface250;
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_aiUpdate;
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;
	char m_pad278[0x330 - 0x278];
	WeaponSet m_weaponSet;
	char m_padW[0x358 - 0x330 - 8];
	int m_weaponSetPresent;

public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isKindOf(KindOfType kind) const;
	Bool isAbleToAttack() const;
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
};

// ?isAbleToAttack@Object@@QBE_NXZ
Bool Object::isAbleToAttack() const
{
	unsigned tmpBuf[4];
	Real dummy;
	Bool anyEnabled;
	Bool anyWeapon;
	Bfme250Interface *iface;
	const unsigned *flags;
	AIUpdateInterface *aiTmp;
	Object *victim;
	ThingTemplate *tmpl;
	AIUpdateInterface *ai;
	Bfme250Interface *myIface;
	SpawnBehaviorInterface *spawnInterface;

	if (testStatus(OBJECT_STATUS_NO_ATTACK))
		return false;
	if (isKindOf(KINDOF_0x81))
		return false;

	const Object *container = m_containedBy;
	if (container != NULL && (container->m_template->m_kindByte115 & 0x20) != 0)
		container = container->m_containedBy;
	if (container == NULL)
		goto soldCheck;
	iface = container->m_iface250;
	if (iface == NULL)
		goto soldCheck;
	if (testStatus(OBJECT_STATUS_0x25))
		goto soldCheck;
	flags = iface->slot44(tmpBuf, this);
	if ((((unsigned char)(*flags >> 1)) & 1) == 0)
		return false;
	aiTmp = m_aiUpdate;
	if (aiTmp == NULL)
		goto soldCheck;
	victim = aiTmp->getCurrentVictim();
	if (victim == NULL)
		goto soldCheck;
	if (iface->slot48(this, victim))
		return false;

soldCheck:
	if (testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		return false;
	if (testStatus(OBJECT_STATUS_SOLD))
		return false;

	tmpl = m_template;
	if (((tmpl->m_kindByte10F & 2) != 0) || ((tmpl->m_kindByte112 & 0x10) != 0))
	{
		if ((m_statusByte1C8 & 4) != 0)
			return false;
	}

	ai = m_aiUpdate;
	anyEnabled = false;
	anyWeapon = false;
	if (ai != NULL && (tmpl->m_kindByte108 & 8) == 0)
	{
		for (int i = 0; i < WEAPONSLOT_COUNT; i++)
		{
			Weapon *weapon = m_weaponSet.getWeaponInWeaponSlot((WeaponSlotType)i);
			if (weapon == NULL)
				continue;
			anyWeapon = true;
			WhichTurretType tur = ai->getWhichTurretForWeaponSlot((WeaponSlotType)i, &dummy, NULL);
			if (tur == TURRET_INVALID)
				goto checkKind;
			if (ai->isTurretEnabled(tur))
			{
				anyEnabled = true;
				break;
			}
		}
		if (anyWeapon && !anyEnabled)
			return false;
	}

checkKind:
	if ((m_template->m_kindByte108 & 8) != 0)
		return true;
	if (testStatus(OBJECT_STATUS_CAN_ATTACK))
		return true;

	myIface = m_iface250;
	if (myIface != NULL)
	{
		if (myIface->slot45())
		{
			if (myIface->slot69(0) > 0)
				return true;
		}
	}

	if (m_aiUpdate != NULL && m_weaponSetPresent != 0)
		return true;

	spawnInterface = getSpawnBehaviorInterface();
	if (spawnInterface != NULL)
	{
		if (spawnInterface->canAnySlavesAttack())
			return true;
	}

	return false;
}
