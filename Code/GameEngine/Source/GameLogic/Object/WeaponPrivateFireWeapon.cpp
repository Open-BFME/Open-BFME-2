// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/GameEngine/Source
// stlport
//
// Weapon.cpp fire path: Weapon::privateFireWeapon (retail 0x002CE30A, 955 bytes) with every
// function it passes &bonus to, and its linear-pattern helper getLinearPosition (0x002CB594).
// Retail's 0x24 frame lets the six-float WeaponBonus share its stack slot with the copied target
// coordinate; VC7.1 proves that only when every callee receiving &bonus (computeBonus 0x002C9A6F,
// both appendBonuses 0x002C96F7/0x002C9778, the delay getter 0x002C9322, the special-fire nugget
// walk 0x002CAA9D and the fire body 0x002CBBF5) is defined in this translation unit, and the last
// two take the bonus typed (const WeaponBonus &). Each of those bodies, moved here from its
// earlier single-function unit, still compiles to retail's bytes; retail keeps them all in
// Weapon.cpp (the random-value diagnostics name it).
//
// WeaponTemplate::fireWeaponTemplate (retail 0x002CBBF5..0x002CC20E, 1561 bytes, RET 0x2C): the weapon
// fire path; WorldBuilder 0xBB0E40 (WeaponTemplate::fireWeaponTemplate, callgraph lead) and the
// Zero Hour Weapon.cpp body are the structural guides (donor facts), the eleven-word ABI, field
// offsets, vslots and call targets are read from the retail bytes (target facts).
// Closing lever: the nugget local is declared at function scope with an initializer; the early
// definition gives its web the lower number, which flips the ESI/EDI reload order after the
// scatter copy (0x2CBBF5 nd2 -> exact). The redundant source->m_ai re-read is the IR-load-count
// lever that fixed the atan2f POP/FSTP pair.
//
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

#include "Lib/Coord3DCtorView.h"
#include <vector>
// The leech frame's max(extra, 1) is inlined; a file-static int overload
// takes the call so this /O1 SSE unit emits no cmov max<int> COMDAT against
// retail's 0x00013630 (as rva0048DC51Rva0048DC51Farm.cpp).
namespace _STL {
static inline const int &max(const int &a, const int &b)
{
    return a < b ? b : a;
}
}
#include <math.h>
#include "Lib/Coord2D.h"

struct WeaponScatterPoint : Coord3D
{
    ~WeaponScatterPoint() {}
    WeaponScatterPoint()
    {
    }
    WeaponScatterPoint(const Coord3D &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }
    WeaponScatterPoint(const WeaponScatterPoint &weaponScatterPoint)
    {
        x = weaponScatterPoint.x;
        y = weaponScatterPoint.y;
        z = weaponScatterPoint.z;
    }
};
typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "Common/GameLogicObjectLookupView.h"

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
class Object;
class FXList;
float GetGameLogicRandomValueReal(float, float, char *, int);

class WeaponBody
{
  public:
    virtual void s000();
    virtual void s004();
    virtual void s008();
    virtual void s00C();
    virtual void s010();
    virtual void s014();
    virtual void s018();
    virtual void s01C();
    virtual void s020();
    virtual void s024();
    virtual void s028();
    virtual void s02C();
    virtual void s030();
    virtual void s034();
    virtual void s038();
    virtual void s03C();
    virtual void s040();
    virtual void s044();
    virtual void s048();
    virtual void s04C();
    virtual void s050();
    virtual void s054();
    virtual void s058();
    virtual void s05C();
    virtual void s060();
    virtual void s064();
    virtual void s068();
    virtual void s06C();
    virtual void s070();
    virtual void s074();
    virtual void s078();
    virtual void s07C();
    virtual void s080();
    virtual void s084();
    virtual void s088();
    virtual float s8C();
};
class WeaponContain
{
  public:
    virtual void s000();
    virtual void s004();
    virtual void s008();
    virtual void s00C();
    virtual void s010();
    virtual void s014();
    virtual void s018();
    virtual void s01C();
    virtual void s020();
    virtual void s024();
    virtual void s028();
    virtual void s02C();
    virtual void s030();
    virtual void s034();
    virtual void s038();
    virtual void s03C();
    virtual void s040();
    virtual void s044();
    virtual void s048();
    virtual void s04C();
    virtual void s050();
    virtual void s054();
    virtual void s058();
    virtual void s05C();
    virtual void s060();
    virtual void s064();
    virtual void s068();
    virtual void s06C();
    virtual void s070();
    virtual void s074();
    virtual void s078();
    virtual int s7C();
    virtual void s080();
    virtual void s084();
    virtual void s088();
    virtual void s08C();
    virtual void s090();
    virtual void s094();
    virtual void s098();
    virtual void s09C();
    virtual void s0A0();
    virtual void s0A4();
    virtual void s0A8();
    virtual void s0AC();
    virtual void s0B0();
    virtual void s0B4();
    virtual void s0B8();
    virtual void s0BC();
    virtual void s0C0();
    virtual void s0C4();
    virtual void s0C8();
    virtual void s0CC();
    virtual void s0D0();
    virtual void s0D4();
    virtual void s0D8();
    virtual void s0DC();
    virtual void s0E0();
    virtual void s0E4();
    virtual void s0E8();
    virtual void s0EC();
    virtual void s0F0();
    virtual Object *sF4(const Coord3D *);
};

struct TBridgeAttackInfo
{
    Coord3D point1, point2;
};
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
#include "../../../Include/GameLogic/AIPathfind.h"
class AI
{
  public:
    char pad[0x10];
    Pathfinder *pathfinder;
};
extern AI *TheAI;
class BfmeRangedWeaponTemplate;
class Rva002C9B80Owner
{
public:
	float rva002C9B80(void *, float);
	void rva002C9A6F(void *a, int b, void *arr);
private:
	void *m_00; // +0x00
	BfmeRangedWeaponTemplate *m_m04; // +0x04
};
class WeaponBonus
{
  public:
    enum Field { DAMAGE = 0, RADIUS, RANGE, RATE_OF_FIRE, PRE_ATTACK };
    WeaponBonus()
    {
        for (int i = 0; i < 6; ++i)
            m_field[i] = 1.0f;
    }
    Real getField(Field field) const
    {
        return m_field[field];
    }
    void appendBonuses(WeaponBonus &bonus) const;
    Real m_field[6];
};
class INI;
class WeaponBonusSet
{
public:
	void appendBonuses(unsigned int flags, WeaponBonus &bonus) const;
	void parseWeaponBonusSet(INI *ini);
	WeaponBonus m_bonus[22]; // +0x00
};
#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
#include "../../../Include/GameLogic/ObjectFilter.h"
enum WeaponStatus
{
    READY_TO_FIRE,
    OUT_OF_AMMO,
    BETWEEN_FIRING_SHOTS,
    RELOADING_CLIP,
    PRE_ATTACK
};
// One linear firing-pattern entry: an offset in the source's frame and the frames to wait
// before the next entry fires (privateFireWeapon reads the third word as its delay).
#include "../../../Include/GameLogic/WeaponLinearTarget.h"
class WeaponTemplate;
extern GameLogic *TheGameLogic;
class Weapon
{
  public:
    bool isWithinAttackRange(Object *, const Coord3D *, Object *, const Coord3D *, float, bool); // 0x002CB35C
    bool privateFireWeapon(const Object *sourceObj, const Coord3D *sourcePos, const Object *victimObj,
                           int victimID, const Coord3D *victimPos, bool ignoreRanges, bool special,
                           UnsignedInt extraBonusFlags, int *projectileID);
    WeaponStatus getStatus() const;
    UnsignedInt getRemainingAmmo(bool) const;
    void reloadAmmo(const Object *sourceObj);
    void prepareProjectileStreamForFiring();
    void setLeechUntil(Int delay)
    {
        rangeUntil = TheGameLogic->getFrame() + delay;
    }

  protected:
    void computeBonus(const Object *source, UnsignedInt extra, WeaponBonus &bonus) const;
    void processRequestAssistance(const Object *requestingObject, Object *victimObject);

  public:
    char pad00[4];
    WeaponTemplate *m_template; // +0x04
    int m_owner;
    int m_wslot; // +0x0C
    WeaponStatus m_status;
    int m_ammoInClip;
    UnsignedInt m_whenWeCanFireAgain; // +0x18
    UnsignedInt m_frame1C;
    UnsignedInt m_frame20;
    int m_pad24;
    UnsignedInt m_whenLastReloadStarted; // +0x28
    UnsignedInt m_lastFireFrame;
    unsigned fxUntil; // +0x30
    int m_maxShotCount;
    int m_curBarrel;
    int m_numShotsForCurBarrel;
    std::vector<int> m_scatterTargetsUnused; // +0x40
    int m_pad4C;
    unsigned rangeUntil; // +0x50, the leech-range frame
    int m_linearIndex;   // +0x54
};
class Matrix3D;
class FXList
{
public:
	static void doFXObj(const FXList *, const Object *, const Object *);
	static void doFXPos(const FXList *, const Coord3D *, const Matrix3D *, float, const Coord3D *);
};
class WeaponNugget
{
  public:
    virtual void s000();
    virtual bool s04(Weapon *, Object *);
    virtual bool s08(Weapon *, const Coord3D *);
    virtual void s00C();
    virtual void s010();
    virtual void s14(Weapon *, Object *);
    virtual void s18(Weapon *, const Coord3D *);
    virtual void s01C();
    virtual void s020();
    virtual void s024();
    virtual void s028();
    virtual void s02C();
    virtual bool s30();
};
struct WeaponNuggetNode
{
    WeaponNuggetNode *next, *prev;
    WeaponNugget *nugget;
};

class Weapon;
struct Coord3D;

#include "../../../Include/Common/ThingTemplate.h"
// Kind-mask readers on the canonical +0x108 storage. Words: 0x80 STRUCTURE,
// 0x40 SHRUBBERY, 0x2000000 PROJECTILE, 0x400 (BFME 2) in word 0; 0x100000
// SMALL_MISSILE, 0x10000000 (BFME 2) in word 1; 0x800 BALLISTIC_MISSILE in word 2.
static inline UnsignedInt thingTemplateTestKindOf(const ThingTemplate *tmpl, Int word, UnsignedInt mask)
{
    return tmpl->m_kindof[word] & mask;
}
static inline unsigned char thingTemplateKindByte(const ThingTemplate *tmpl, int i)
{
    return ((const unsigned char *)tmpl->m_kindof)[i];
}

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
#include "../../Common/Thing/thing.h"
#include "../../../Include/GameClient/Drawable.h"

class Object
{
  public:
    const ThingTemplate *getTemplate() const
    {
        return m_template;
    }
    ObjectID getID() const
    {
        return m_id;
    }
    Object *getContainedBy() const
    {
        return m_containedBy;
    }
    AIUpdateInterface *getAI() const
    {
        return m_ai;
    }
    Bool testStatus(ObjectStatusTypes bit) const;
    Relationship getRelationship(const Object *that) const;
    Player *getControllingPlayer() const;
    const Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0) const;
    Int rva0028B511() const;
    float rva002C97E8(const Coord3D *, const Coord3D *) const;
    float rva00263763(const void *) const;
    bool rva0028F44C(const Object *) const;
    bool isLocallyControlled() const;
    bool rva002943B2(const Player *);
    bool rva0028C15E(int, float *, int, int);

  public:
    void *m_vtbl;
    const ThingTemplate *volatile m_template;
    Matrix3D m_transform; // +0x08
    Coord3D pos;
    char m_pad044[0x74 - 0x44];
    ObjectID m_id; // +0x74
    char m_pad078[0x250 - 0x78];
    WeaponContain *contain250;
    WeaponBody *body254;
    AIUpdateInterface *m_ai; // +0x258
    char m_pad25C[0x274 - 0x25C];
    Object *m_containedBy; // +0x274
    char m_pad278[0x380 - 0x278];
    UnsignedInt m_weaponBonusCondition; // +0x380
};

struct ListNode
{
    ListNode *m_next;
    ListNode *m_prev;
    void *m_data;
};
class VirtNode2
{
public:
	virtual void v00();
	virtual bool v04(int a, const void *b);
	virtual void v08();
	virtual void v0c(int a, const void *b);
	virtual void v10();
	virtual void v14(int a, const void *b);
	virtual void v18();
	virtual bool v1c();
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual void v2c() = 0;
	virtual void v30();
	virtual bool v34();
	virtual void v38();
	virtual void v3c();
};
class Rva001E11F8;
class Rva002CA9CA
{
private:
	friend class Weapon;
public:
	bool rva002CA9CA(int damageType, const void *weapon);
	void rva002CAA9D(int a1, const void *a2, const void *a3, const WeaponBonus &bonus);
	bool rva002CAA59(int source, const void *weapon);
	void postProcessLoad();
	void rva002CA970(int firingWeapon, int source, const void *weapon, int position);
	float getProjectileNuggetRadiusIfAlliesAffected(const void *arg);
	bool rva002CAD8B();
	void rva002CAC6E(int a, int context);
	bool getAutoReloadsClip() const { return m_128 == 0; }
	float getReal168() const { return m_168; }
	char m_pad00[0x58];
private:
	int m_58; // +0x58
	char m_pad5C[0x48];
	Rva001E11F8 *m_a4; // +0xA4
	Rva001E11F8 *m_a8; // +0xA8
	Rva001E11F8 *m_ac; // +0xAC
	Rva001E11F8 *m_b0; // +0xB0
	char m_padB4[0x4];
	Rva001E11F8 *m_b8; // +0xB8
	Rva001E11F8 *m_bc; // +0xBC
	Rva001E11F8 *m_c0; // +0xC0
	Rva001E11F8 *m_c4; // +0xC4
	char m_padC8[0x48];
	unsigned char m_110; // +0x110
	char m_pad111[0x17];
	int m_128; // +0x128
	char m_pad12C[0x4];
	float m_130; // +0x130
	char m_pad134[0x34];
	unsigned char m_168; // +0x168
	char m_pad169[0x13];
	ListNode *m_17c; // +0x17C
};

struct TargetCoord
{
public:
	TargetCoord() {}
	TargetCoord(float a,float b,float c):x(a),y(b),z(c){}
	TargetCoord(const Coord3D &p):x(p.x),y(p.y),z(p.z){}
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
};
#include "../../../Include/GameLogic/WeaponTemplate.h"
static __forceinline Bool weaponTemplateIsDamageType(const WeaponTemplate *wt, Int damageType, const Weapon *weapon)
{
    return ((Rva002CA9CA *)wt)->rva002CA9CA(damageType, weapon);
}
static __forceinline Int weaponTemplateCollideMask(const WeaponTemplate *wt)
{
    return wt->m_collideMask;
}
static __forceinline const std::vector<WeaponLinearTarget> &weaponTemplateLinearTargets(const WeaponTemplate *wt)
{
    return *(const std::vector<WeaponLinearTarget> *)wt->m_field4C;
}
static __forceinline Int weaponTemplateTimingExtra144(const WeaponTemplate *wt, const WeaponBonus &)
{
    return wt->m_field144;
}


Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
// Upstream basetype.h x87 conversion. Cast/floor, roundf, and SSE intrinsic
// trials differed; the target uses this fld/fistp sequence after floor.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

// ?rva002C9322@WeaponTemplate@@QBEHABVWeaponBonus@@M@Z @0x002C9322 90B
// Delay-between-shots getter: min/max at F0/F4 (twins prove offsets), rate
// bonus at +0x0C with extra Real factor (ret8), random diagnostic line 988
// in Weapon.cpp, no modulo-3 tail. Provisional address-derived name.
Int WeaponTemplate::rva002C9322(const WeaponBonus &bonus, Real factor) const
{
	Int delayToUse;
	if (m_minDelayBetweenShots == m_maxDelayBetweenShots)
		delayToUse = m_minDelayBetweenShots;
	else
		delayToUse = GetGameLogicRandomValue(m_minDelayBetweenShots, m_maxDelayBetweenShots,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp", 988);
	return fast_float2long_round((Real)floor((double)((Real)delayToUse / (bonus.getField(WeaponBonus::RATE_OF_FIRE) * factor))));
}

// Target code combines six floats per bonus and selects 22 entries at stride 0x18.
void WeaponBonus::appendBonuses(WeaponBonus &bonus) const
{
	for (int f = 0; f < 6; ++f)
		bonus.m_field[f] += this->m_field[f] - 1.0f;
}
void WeaponBonusSet::appendBonuses(UnsignedInt flags, WeaponBonus &bonus) const
{
	if (flags == 0)
		return;
	for (int i = 0; i < 22; ++i)
	{
		if ((flags & (1 << i)) == 0)
			continue;
		this->m_bonus[i].appendBonuses(bonus);
	}
}

// Donor: BFME 1 Weapon_computeBonus. Target accesses establish the object mask +0x380,
// global bonus set +0xAD0 and template bonus set +0xE0.
void Weapon::computeBonus(const Object *source, UnsignedInt extra, WeaponBonus &bonus) const
{
	for (int i = 0; i < 6; ++i)
		bonus.m_field[i] = 1.0f;
	UnsignedInt flags = source->m_weaponBonusCondition | extra;
	WeaponBonusSet *global = TheWritableGlobalData->m_weaponBonusSet;
	if (global)
		global->appendBonuses(flags, bonus);
	WeaponBonusSet *own = m_template->m_extraBonus;
	if (own)
		own->appendBonuses(flags, bonus);
}

// ?rva002CAA9D@Rva002CA9CA@@QAEXHPBX0ABVWeaponBonus@@@Z, retail 0x002CAA9D, 93 bytes: the
// special-fire nugget walk privateFireWeapon calls for a special shot (weapon, source, victim,
// bonus): null source/victim guards, intrusive nugget list at +0x17C, slot 0x1C gate, slot 0x04
// test and slot 0x14 fire. The bonus is passed but unused.
void Rva002CA9CA::rva002CAA9D(int a1, const void *a2, const void *a3, const WeaponBonus &)
{
	if (a2 == 0)
		return;
	if (a3 == 0)
		return;
	ListNode *cur = m_17c->m_next;
	while (cur != m_17c)
	{
		VirtNode2 *obj = (VirtNode2 *)cur->m_data;
		if (obj->v1c())
		{
			if (obj->v04(a1, a3))
			{
				obj->v14(a1, a3);
			}
		}
		cur = cur->m_next;
	}
}

// Native 0x002CB594 (199 bytes) and WB 0xBB9080 establish return by value: one linear-pattern
// offset rotated by the source's heading, added to its position and dropped onto the ground.
static Coord3D getLinearPosition(const std::vector<WeaponLinearTarget> &positions, int index, const Object *object)
{
    const WeaponLinearTarget &point = positions[index];
    Coord2D point2 = {point.x, point.y};
    float px = point2.x, py = point2.y;
    float angle = object->m_transform.Get_Z_Rotation();
    // sinf/cosf emit only retail's _sinf/_cosf copies; math.h's sin(float) and
    // cos(float) would add call-_sin/_cos copies unlike retail's (0x2FBB0/0x2FBC0).
    float sine = (float)(double)sinf(angle);
    float cosine = (float)(double)cosf(angle);
    Coord3D rotated;
    rotated.x = cosine * px - sine * py;
    rotated.y = sine * px + cosine * py;
    Coord3D position;
    position.x = object->pos.x;
    position.y = object->pos.y;
    position.x += rotated.x;
    position.y += rotated.y;
    float x = position.x;
    float y = position.y;
    position.z = TheTerrainLogic->getGroundHeight(x, y, 0);
    return position;
}

//-------------------------------------------------------------------------------------------------
Bool WeaponTemplate::shouldProjectileCollideWith(
    const Object *projectileLauncher, const Object *projectile, const Object *thingWeCollidedWith,
    ObjectID intendedVictimID // could be INVALID_OBJECT_ID for a position-shot
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
        if (weaponTemplateIsDamageType(this, 6, projectileLauncher->getCurrentWeapon()))
        {
            if (thingWeCollidedWith->testStatus(OBJECT_STATUS_BURNED))
                return false;
        }
    }

    // if something has a Sneaky Target offset, it is momentarily immune to being hit...
    const AIUpdateInterface *ai = thingWeCollidedWith->getAI();
    if (ai != 0 && ai->vslot128(0))
        return false;

    Int requiredMask = 0;

    Relationship r = projectile->getRelationship(thingWeCollidedWith);
    if (r == ALLIES)
        requiredMask = WEAPON_COLLIDE_ALLIES;
    else if (r == ENEMIES)
        requiredMask = WEAPON_COLLIDE_ENEMIES;
    else if (r == NEUTRAL)
        requiredMask = WEAPON_COLLIDE_NEUTRALS;

    if (thingTemplateTestKindOf(thingWeCollidedWith->getTemplate(), 0, 0x80))
    {
        if (thingWeCollidedWith->getControllingPlayer() == projectile->getControllingPlayer())
            requiredMask |= WEAPON_COLLIDE_CONTROLLED_STRUCTURES;
        else
            requiredMask |= WEAPON_COLLIDE_STRUCTURES;
    }

    const ThingTemplate *thingTemplate = thingWeCollidedWith->getTemplate();
    if (thingTemplateTestKindOf(thingTemplate, 0, 0x40))
        requiredMask |= WEAPON_COLLIDE_SHRUBBERY;
    if (thingTemplateTestKindOf(thingTemplate, 0, 0x2000000))
        requiredMask |= WEAPON_COLLIDE_PROJECTILE;
    if (thingTemplate->m_fenceWidth > 0)
        requiredMask |= WEAPON_COLLIDE_WALLS;
    if (thingTemplateTestKindOf(thingTemplate, 1, 0x100000))
        requiredMask |= WEAPON_COLLIDE_SMALL_MISSILES;
    if (thingTemplateTestKindOf(thingTemplate, 2, 0x800))
        requiredMask |= WEAPON_COLLIDE_BALLISTIC_MISSILES;
    if (thingTemplateTestKindOf(thingTemplate, 0, 0x400))
        requiredMask |= WEAPON_COLLIDE_BFME2_400;

    // if any in requiredMask are present in collidemask, do the collision. (srj)
    if ((weaponTemplateCollideMask(this) & requiredMask) == 0)
        return false;

    if (thingTemplateTestKindOf(thingTemplate, 1, 0x10000000) && intendedVictimID != INVALID_OBJECT_ID)
    {
        Object *victim = TheGameLogic->findObjectByID(intendedVictimID);
        if (victim && victim->rva0028B511() > 1)
            return false;
    }

    return true;
}

void WeaponTemplate::fireWeaponTemplate(Object *source, int wordC, int barrel, int word14, Object *victim, int word1C, const Coord3D *position, const WeaponBonus &, bool ignore, Weapon *weapon, int word30)
{
    if (!source || (!victim && !position)) return;
    const Coord3D *sourcePos=&source->pos;
    {unsigned irB=(unsigned)(source->m_ai); unsigned irS=0; irS+=(irB!=(unsigned)(source->m_ai)); }
 float distance;
    Coord3D shifted;
    TBridgeAttackInfo bridge;
    if (victim)
    {
        position = &victim->pos;
        Coord3D offset;
        const AIUpdateInterface *ai = victim->getAI();
        if (ai && ai->vslot128(&offset))
        {
            shifted = *position;
            shifted.x += offset.x;
            shifted.y += offset.y;
            shifted.z += offset.z;
            position = &shifted;
            victim = 0;
            distance = source->rva002C97E8(sourcePos, position);
        }
        else if (thingTemplateKindByte(victim->getTemplate(), 2) & 0x40)
        {
            TheTerrainLogic->getBridgeAttackPoints(victim, &bridge);
            distance = source->rva002C97E8(sourcePos, &bridge.point1);
            float other = source->rva002C97E8(sourcePos, &bridge.point2);
            if (other < distance)
            {
                distance = other;
                position = &bridge.point2;
            }
        }
        else
            distance = source->rva00263763(victim);
    }
    else
        distance = source->rva002C97E8(sourcePos, position);
    if (!ignore && weapon->rangeUntil <= TheGameLogic->getFrame())
    {
        float range =
            ((Rva002C9B80Owner *)weapon)->rva002C9B80(source, position->z - source->pos.z);
        if (distance > range * range &&
            !weapon->isWithinAttackRange(source, sourcePos, victim, position, 0.f, true))
            return;
        float minimum = getMinimumAttackRange();
        if (distance < minimum * minimum)
            return;
    }
    if (((const Thing *)source)->getDrawable())
    {
        Coord3D firePosition;
        if (victim)
        {
            Coord3D adjusted;
            firePosition = (const Coord3D &)adjustTargetPositionOnVictim((Object *)source, (Object *)victim, true);
        }
        else
        {
            firePosition.x = position->x;
            firePosition.y = position->y;
            firePosition.z = position->z;
        }
        float pitch = m_weaponRecoil;
        float heading;
        if(pitch != 0.f)
        {
            heading=(victim ? (atan2(position->y - source->pos.y, position->x - source->pos.x)) : (atan2(position->y - source->pos.y, position->x - source->pos.x)));
        }
        else
            heading=0.f;
        const FXList *fx = 0;
        if (victim && victim->rva0028F44C(source))
            fx = m_fieldB4;
        if (!fx)
            fx = m_fireFXs[0];
        if (TheGameLogic->getFrame() < weapon->fxUntil)
            fx = 0;
        if (source->isLocallyControlled() || !source->rva002943B2(0) || m_playFXWhenStealthed)
        {
            float sound=m_weaponSpeed;
            if (!((const Thing *)source)
                     ->getDrawable()
                     ->handleWeaponFireFX(barrel, word14, (int)fx, sound, pitch, heading,
                                          (int)&firePosition) &&
                fx)
                FXList::doFXObj(fx, source, victim);
        }
    }
    float oldZ = position->z;
    if (m_damageDealtAtSelfPosition)
    {
        position = sourcePos;
        victim = 0;
    }
    const Coord3D *aim = position ? position : &victim->pos;
    typedef Coord3D (WeaponTemplate::*ScatterFn)(const Object *, const Object *,
                                                 WeaponScatterPoint);
    ScatterFn scatterFn = reinterpret_cast<ScatterFn>(&WeaponTemplate::bfmeCalcScatterTargetPos);
    Coord3D target;
    target.x = aim->x;
    target.y = aim->y;
    target.z = aim->z;
    if (m_damageDealtAtSelfPosition && source->m_ai->vslot097())
        target.z = oldZ;
    volatile bool scatter = false;
    Pathfinder *pathfinder;
    if (m_infantryInaccuracyDist > 0.f && victim && (thingTemplateKindByte(victim->getTemplate(), 1) & 1) &&
        (!m_field3D || !(pathfinder=TheAI->pathfinder, pathfinder->IsPointOnWall((int)&victim->pos, false))))
        scatter = true;
    char *filename =
        "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon."
        "cpp";
    if (m_field158 < 1.f)
    {
        float chance = m_field158;
        if (GetGameLogicRandomValueReal(0, 1, filename, 0x5D1) >= chance)
            scatter = true;
    }
    if (m_field75 && victim && victim->body254->s8C() > 0.f)
    {
        WeaponBody *body = victim->body254;
        float random = GetGameLogicRandomValueReal(0, 1, filename, 0x5D7);
        if (body->s8C() >= random)
            scatter = true;
    }
    bool useContained = false;
    if (!scatter && victim)
    {
        WeaponContain *contain=victim->contain250;
        if(contain && !contain->s7C() && m_field15C > 0.f)
    {
        float chance = m_field15C;
        if (chance >= GetGameLogicRandomValueReal(0, 1, filename, 0x5E1))
        {
            useContained = true;
            scatter = false;
        }
    }
    }
    WeaponNugget *nugget = 0;
    WeaponNuggetNode *it = 0;
    if (m_field3C)
    {
        for (it = ((WeaponNuggetNode *)m_field17C)->next; it != ((WeaponNuggetNode *)m_field17C); it = it->next)
        {
            nugget = it->nugget;
            if (scatter)
            {
                target = (this->*scatterFn)(source, victim, WeaponScatterPoint(target));
                victim = 0;
            }
            if (nugget->s08(weapon, &target))
                nugget->s18(weapon, &target);
        }
    }
    else
    {
        if (scatter)
        {
            target = (this->*scatterFn)(source, victim, WeaponScatterPoint(target));
            victim = 0;
        }
        else if(useContained == true)
        {
            WeaponContain *contain=victim->contain250;
            if(contain) {
                Object *inside=contain->sF4(&victim->pos);
                if(inside) victim=inside;
            }
        }
        for (it = ((WeaponNuggetNode *)m_field17C)->next; it != ((WeaponNuggetNode *)m_field17C); it = it->next)
        {
            nugget = it->nugget;
            if (victim && !nugget->s30())
            {
                if (nugget->s04(weapon, victim))
                    nugget->s14(weapon, victim);
            }
            else if (nugget->s08(weapon, &target))
                nugget->s18(weapon, &target);
        }
    }
}

//-------------------------------------------------------------------------------------------------
// return true if we auto-reloaded our clip after firing.
// Native 0x002CE30A (955 bytes, ret 0x24). BFME 1 / Zero Hour Weapon.cpp privateFireWeapon is the
// semantic donor; the source position argument, the special-fire branch, the linear and scatter
// target patterns and the post-fire timing word +0x144 are read from the retail bytes.
//DECLARE_PERF_TIMER(fireWeapon)
bool Weapon::privateFireWeapon(const Object *sourceObj, const Coord3D *sourcePos,
    const Object *victimObj, int victimID, const Coord3D *victimPos,
    bool ignoreRanges, bool special, UnsignedInt extraBonusFlags, int *projectileID)
{
    //CRCDEBUG_LOG(("Weapon::privateFireWeapon() for %s\n", DescribeObject(sourceObj).str()));
    //USE_PERF_TIMER(fireWeapon)
    WeaponBonus bonus;
    computeBonus(sourceObj, extraBonusFlags, bonus);
    if (projectileID)
        *projectileID = 0;
    if (!m_template)
        return false;
    // If we are a networked weapon, tell everyone nearby they might want to get in on this shot
    if (m_template->m_requestAssistRange && victimObj)
        processRequestAssistance(sourceObj, const_cast<Object *>(victimObj));
    //For weapon templates that have the leech range weapon flag set, it essentially grants
    //the weapon unlimited range for the remainder of the attack. While it's triggered here
    //it's the AIAttackState machine that actually uses and resets this value.
    //This makes the ASSUMPTION that it is IMPOSSIBLE TO FIRE A WEAPON WITHOUT BEING IN AN AIATTACKSTATE
    //
    // @todo srj -- this isn't a universally true assertion! eg, FireWeaponDie lets you do this easily.
    //
    if (m_template->m_leechRangeWeapon)
    {
        setLeechUntil(std::max(weaponTemplateTimingExtra144(m_template, bonus), 1));
    }
    if (getStatus() != READY_TO_FIRE)
        return false;
    prepareProjectileStreamForFiring();
    UnsignedInt now = TheGameLogic->getFrame();
    bool reloaded = false;
    float factor = 1.0f;
    if (sourceObj)
        ((Object *)sourceObj)->rva0028C15E(21, &factor, 0, 1);
    int delay = m_template->rva002C9322(bonus, factor);
    if (getRemainingAmmo(false) > 0)
    {
        int barrelCount = ((const Thing *)sourceObj)->getDrawable()->rva0027434D(m_wslot);
        if (m_curBarrel >= barrelCount)
        {
            m_curBarrel = 0;
            m_numShotsForCurBarrel = m_template->m_shotsPerBarrel;
        }
        if (special)
        {
            ((Rva002CA9CA *)m_template)->rva002CAA9D((int)this, sourceObj, victimObj, bonus);
        }
        else if (weaponTemplateLinearTargets(m_template).size() && sourceObj)
        {
            delay = 0;
            int whileCount = 0;
            while (!delay)
            {
                if (whileCount++ == weaponTemplateLinearTargets(m_template).size())
                    break;
                Coord3D targetPos = getLinearPosition(weaponTemplateLinearTargets(m_template), m_linearIndex, sourceObj);
                if (!m_template->m_field154 || m_linearIndex != 0)
                    m_template->fireWeaponTemplate((Object *)sourceObj, (int)sourcePos, m_wslot, m_curBarrel,
                        (Object *)victimObj, victimID, &targetPos, bonus, ignoreRanges, this, (int)projectileID);
                delay = weaponTemplateLinearTargets(m_template)[m_linearIndex].delay;
                m_linearIndex = (m_linearIndex + 1) % weaponTemplateLinearTargets(m_template).size();
            }
        }
        else if (m_scatterTargetsUnused.size())
        {
            // If I have a set scatter pattern, I need to offset the target by a random pick from that pattern
            if (victimObj)
            {
                victimPos = &victimObj->pos;
                victimObj = 0;
            }
            Coord3D targetPos = *victimPos; // need to copy, as this pointer is actually inside somebody potentially
            int randomPick = GetGameLogicRandomValue(0, m_scatterTargetsUnused.size() - 1,
                "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp", 3261);
            int targetIndex = m_scatterTargetsUnused[randomPick];
            float scatterTargetScalar = m_template->m_scatterTargetScalar; // essentially a radius, but operates only on this scatterTarget table
            const Coord2D &point = (*(const std::vector<Coord2D> *)m_template->m_field40)[targetIndex];
            Coord2D scatterOffset = {point.x, point.y};
            scatterOffset.x *= scatterTargetScalar;
            scatterOffset.y *= scatterTargetScalar;
            targetPos.x += scatterOffset.x;
            targetPos.y += scatterOffset.y;
            targetPos.z = TheTerrainLogic->getGroundHeight(targetPos.x, targetPos.y, 0);
            // To erase from a vector, put the last on the one you used and pop the back.
            m_scatterTargetsUnused[randomPick] = m_scatterTargetsUnused.back();
            m_scatterTargetsUnused.pop_back();
            m_template->fireWeaponTemplate((Object *)sourceObj, (int)sourcePos, m_wslot, m_curBarrel,
                (Object *)victimObj, victimID, &targetPos, bonus, ignoreRanges, this, (int)projectileID);
        }
        else
        {
            m_template->fireWeaponTemplate((Object *)sourceObj, (int)sourcePos, m_wslot, m_curBarrel,
                (Object *)victimObj, victimID, victimPos, bonus, ignoreRanges, this, (int)projectileID);
        }
        m_lastFireFrame = now;
        --m_ammoInClip;
        --m_maxShotCount;
        --m_numShotsForCurBarrel;
        if (m_numShotsForCurBarrel <= 0)
        {
            ++m_curBarrel;
            m_numShotsForCurBarrel = m_template->m_shotsPerBarrel;
        }
        if (getRemainingAmmo(false) <= 0)
        {
            if (!m_template->m_field128)
            {
                reloadAmmo(sourceObj);
                reloaded = true;
            }
            else
            {
                if (m_status != OUT_OF_AMMO)
                    m_status = OUT_OF_AMMO;
                if (!((const ObjectFilter *)&m_template->m_field120)->isValid())
                    m_whenWeCanFireAgain = 0x7fffffff;
                //CRCDEBUG_LOG(("Just set m_whenWeCanFireAgain to %d in Weapon::privateFireWeapon 1\n", m_whenWeCanFireAgain));
            }
        }
        else
        {
            if (m_status != BETWEEN_FIRING_SHOTS)
                m_status = BETWEEN_FIRING_SHOTS;
            //CRCDEBUG_LOG(("Weapon::privateFireWeapon() just set m_status to BETWEEN_FIRING_SHOTS\n"));
            m_whenLastReloadStarted = now;
            m_whenWeCanFireAgain = now + delay;
            //CRCDEBUG_LOG(("Just set m_whenWeCanFireAgain to %d (delay is %d) in Weapon::privateFireWeapon\n", m_whenWeCanFireAgain, delay));
            int extra = weaponTemplateTimingExtra144(m_template, bonus);
            if (extra > 0)
                m_frame20 = TheGameLogic->getFrame() + extra;
        }
    }
    return reloaded;
}
