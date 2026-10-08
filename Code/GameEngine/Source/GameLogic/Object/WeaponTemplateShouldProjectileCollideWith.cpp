// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?shouldProjectileCollideWith@WeaponTemplate@@QBE_NPBVObject@@00W4ObjectID@@@Z
// retail 0x002CBA7C, 377 bytes (Ghidra FUN_006cba7c, ret 0x10).
//
// Donor: Zero Hour / BFME 1 Weapon.cpp WeaponTemplate::shouldProjectileCollideWith
// (launcher, projectile, thingWeCollidedWith, intendedVictimID).
//
// Target evidence: four stack args; null projectile/thing guards; the
// intended victim id compare against Object +0x74; the launcher == thing and
// launcher->getContainedBy() (+0x274) == thing rejections; the sneaky
// targeting probe through the thing's AI (+0x258, vtable +0x200, NULL); the
// rowed Object::getRelationship (0x0028D156) mapping ALLIES/ENEMIES/NEUTRAL to
// collide bits 1/2/4; the STRUCTURE split on getControllingPlayer
// (0x0028AFA9) into 0x200/8; the ThingTemplate KindOf words at +0x108 and
// fence width at +0x4A0 feeding the SHRUBBERY/PROJECTILE/WALLS/SMALL_MISSILE/
// BALLISTIC_MISSILE bits; and the final test against the collide mask at
// this+0x118.
//
// BFME 2 differences (target evidence): the burned-thing rejection asks the
// rowed WeaponTemplate damage-type query 0x002CA9CA for type 6 with the
// launcher's current weapon (0x0028AEBD), inside the launcher block, and
// tests status 0xB; the airfield parking case is gone; a new KindOf bit 10
// adds collide bit 0x400; and a thing with KindOf bit 60 ignores a collision
// when the intended victim (TheGameLogic->findObjectByID) reports more than
// one from the rowed Object getter 0x0028B511.

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "../../Common/GameLogicObjectLookupView.h"

enum WeaponSlotType
{
	PRIMARY_WEAPON
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BURNED = 0x0B
};

enum WeaponCollideMaskType
{
	WEAPON_COLLIDE_ALLIES = 0x0001,
	WEAPON_COLLIDE_ENEMIES = 0x0002,
	WEAPON_COLLIDE_NEUTRALS = 0x0004,
	WEAPON_COLLIDE_STRUCTURES = 0x0008,
	WEAPON_COLLIDE_SHRUBBERY = 0x0010,
	WEAPON_COLLIDE_PROJECTILE = 0x0020,
	WEAPON_COLLIDE_WALLS = 0x0040,
	WEAPON_COLLIDE_SMALL_MISSILES = 0x0080,
	WEAPON_COLLIDE_BALLISTIC_MISSILES = 0x0100,
	WEAPON_COLLIDE_CONTROLLED_STRUCTURES = 0x0200,
	WEAPON_COLLIDE_BFME2_400 = 0x0400
};

class Player;
class Weapon;
struct Coord3D;

class ThingTemplate
{
public:
	// KindOf words: 0x80 STRUCTURE, 0x40 SHRUBBERY, 0x2000000 PROJECTILE, 0x400 (BFME 2) in
	// word 0; 0x100000 SMALL_MISSILE, 0x10000000 (BFME 2) in word 1; 0x800 BALLISTIC_MISSILE in word 2.
	UnsignedInt testKindOf(Int word, UnsignedInt mask) const { return m_kindOf[word] & mask; }
	Real getFenceWidth() const { return m_fenceWidth; }
private:
	char m_pad000[0x108];
	UnsignedInt m_kindOf[4]; // +0x108
	char m_pad118[0x4A0 - 0x118];
	Real m_fenceWidth; // +0x4A0
};

class AIUpdateInterface
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003();
	virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007();
	virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011();
	virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015();
	virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023();
	virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027();
	virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031();
	virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035();
	virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043();
	virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047();
	virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051();
	virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055();
	virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063();
	virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067();
	virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071();
	virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075();
	virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079();
	virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083();
	virtual void s084(); virtual void s085(); virtual void s086(); virtual void s087();
	virtual void s088(); virtual void s089(); virtual void s090(); virtual void s091();
	virtual void s092(); virtual void s093(); virtual void s094(); virtual void s095();
	virtual void s096(); virtual void s097(); virtual void s098(); virtual void s099();
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103();
	virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107();
	virtual void s108(); virtual void s109(); virtual void s110(); virtual void s111();
	virtual void s112(); virtual void s113(); virtual void s114(); virtual void s115();
	virtual void s116(); virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121(); virtual void s122(); virtual void s123();
	virtual void s124(); virtual void s125(); virtual void s126(); virtual void s127();
	virtual Bool getSneakyTargetingOffset(Coord3D *offset) const; // +0x200
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getContainedBy() const { return m_containedBy; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Bool testStatus(ObjectStatusTypes bit) const;
	Relationship getRelationship(const Object *that) const;
	Player *getControllingPlayer() const;
	const Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0) const;
	Int rva0028B511() const;
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +4
	char m_pad008[0x74 - 0x08];
	ObjectID m_id; // +0x74
	char m_pad078[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
};

extern GameLogic *TheGameLogic;

class Rva002CA9CA
{
public:
	Bool rva002CA9CA(Int damageType, const void *weapon);
};

class WeaponTemplate
{
public:
	Bool isDamageType(Int damageType, const Weapon *weapon) const
	{
		return ((Rva002CA9CA *)this)->rva002CA9CA(damageType, weapon);
	}
	Int getProjectileCollideMask() const { return m_projectileCollideMask; }

	Bool shouldProjectileCollideWith(const Object *projectileLauncher, const Object *projectile, const Object *thingWeCollidedWith, ObjectID intendedVictimID) const;
private:
	char m_pad000[0x118];
	Int m_projectileCollideMask; // +0x118
};

//-------------------------------------------------------------------------------------------------
Bool WeaponTemplate::shouldProjectileCollideWith(
	const Object* projectileLauncher,
	const Object* projectile,
	const Object* thingWeCollidedWith,
	ObjectID intendedVictimID	// could be INVALID_OBJECT_ID for a position-shot
) const
{
	if (!projectile || !thingWeCollidedWith)
		return false;

	// if it's our intended victim, we want to collide with it, regardless of any of the subsequent checks.
	if (intendedVictimID == thingWeCollidedWith->getID())
		return true;

	if (projectileLauncher != 0)
	{
		// Don't hit your own launcher, ever.
		if (projectileLauncher == thingWeCollidedWith)
			return false;

		// If our launcher is inside something, and that something is 'thingWeCollidedWith' we won't collide
		const Object *launcherContainedBy = projectileLauncher->getContainedBy();
		if (launcherContainedBy == thingWeCollidedWith)
			return false;

		// never bother burning already-burned things. (srj)
		if (isDamageType(6, projectileLauncher->getCurrentWeapon()))
		{
			if (thingWeCollidedWith->testStatus(OBJECT_STATUS_BURNED))
				return false;
		}
	}

	// if something has a Sneaky Target offset, it is momentarily immune to being hit...
	const AIUpdateInterface* ai = thingWeCollidedWith->getAI();
	if (ai != 0 && ai->getSneakyTargetingOffset(0))
		return false;

	Int requiredMask = 0;

	Relationship r = projectile->getRelationship(thingWeCollidedWith);
	if (r == ALLIES) requiredMask = WEAPON_COLLIDE_ALLIES;
	else if (r == ENEMIES) requiredMask = WEAPON_COLLIDE_ENEMIES;
	else if (r == NEUTRAL) requiredMask = WEAPON_COLLIDE_NEUTRALS;

	if (thingWeCollidedWith->getTemplate()->testKindOf(0, 0x80))
	{
		if (thingWeCollidedWith->getControllingPlayer() == projectile->getControllingPlayer())
			requiredMask |= WEAPON_COLLIDE_CONTROLLED_STRUCTURES;
		else
			requiredMask |= WEAPON_COLLIDE_STRUCTURES;
	}

	const ThingTemplate *tmpl = thingWeCollidedWith->getTemplate();
	if (tmpl->testKindOf(0, 0x40))					requiredMask |= WEAPON_COLLIDE_SHRUBBERY;
	if (tmpl->testKindOf(0, 0x2000000))					requiredMask |= WEAPON_COLLIDE_PROJECTILE;
	if (tmpl->getFenceWidth() > 0)							requiredMask |= WEAPON_COLLIDE_WALLS;
	if (tmpl->testKindOf(1, 0x100000))				requiredMask |= WEAPON_COLLIDE_SMALL_MISSILES;
	if (tmpl->testKindOf(2, 0x800))			requiredMask |= WEAPON_COLLIDE_BALLISTIC_MISSILES;
	if (tmpl->testKindOf(0, 0x400))			requiredMask |= WEAPON_COLLIDE_BFME2_400;

	// if any in requiredMask are present in collidemask, do the collision. (srj)
	if ((getProjectileCollideMask() & requiredMask) == 0)
		return false;

	if (tmpl->testKindOf(1, 0x10000000) && intendedVictimID != INVALID_OBJECT_ID)
	{
		Object *victim = TheGameLogic->findObjectByID(intendedVictimID);
		if (victim && victim->rva0028B511() > 1)
			return false;
	}

	return true;
}
