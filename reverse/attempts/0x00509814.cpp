// ?doEffectObject@ProjectileNugget@@UAEXPBUProjectileNuggetFireInfo@@PAVObject@@@Z
// partial score=0.9 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00509A3C@ProjectileNugget@@UAEXPBUProjectileNuggetFireInfo@@PBUCoord3D@@@Z,
// retail 0x00509A3C (647 bytes). Slot 6 of the ProjectileNugget vtable
// 0x00C646B0 (slot 1 the rowed canAffectObject 0x00509720, slot 8 the rowed
// friend_postProcessLoad 0x005097CD, which fills the detonation weapon +0x128
// and projectile template +0x12C). Zero Hour's projectile launch from
// Weapon::fireWeaponTemplate in nugget form. WorldBuilder twin 0x010A4D90
// (callgraph evidence). Target evidence:
//  - the firer is the rowed GameLogic::findObjectByID 0x00049DC5 of the fire
//    info's +0x08 ID; none returns;
//  - the launch point is the firer's transform applied to the nugget offset
//    +0x140 when +0x14C is set (Matrix3D::Transform_Vector inline), else the
//    given position;
//  - with a valid filter at the info's template +0x120 (rowed
//    ObjectFilter::isValid 0x00360CED) and a firer +0x250 module, the pinned
//    Weapon::calcProjectileLaunchPosition 0x002C9E48 fills the launch matrix
//    and that module's slot 79 hands out the projectile; else with the
//    template's +0x124 byte the firer itself is launched from its own
//    transform; else (with a projectile template) the rowed
//    ThingFactory::newObject 0x002D0A23 makes one for the controlling player's
//    team (+0x2EC) with no launch matrix;
//  - the first behavior module (+0x244 list) with a projectile update
//    interface (slot 18 of its +0x0C interface) launches it after the rowed
//    setProducer 0x0028AFD2 (weapon slot overridden by +0x13C when 0..5);
//    without one the rowed GameLogic::destroyObject 0x00242C09 removes it.
// The method name is a placeholder for the vtable slot.
//
// ?doEffectObject@ProjectileNugget@@UAEXPBUProjectileNuggetFireInfo@@PAVObject@@@Z,
// retail 0x00509814 (552 bytes), slot 5: the object-target twin (WorldBuilder
// 0x010A4740 ProjectileNugget::doEffectObject, ProjectileNugget.cpp). The
// same projectile choice, except the launch-self case also takes its matrix
// from calcProjectileLaunchPosition; the launch names the victim and no
// position. Afterwards, Zero Hour's projectile-stream hookup: the fire
// info's +0x5C object's ProjectileStreamUpdate module (rowed findModule
// 0x0028B6D6, static NAMEKEY guard) is moved to the re-looked-up firer's
// position (rowed 0x0033EF86) and records firer, projectile and victim IDs
// with the victim's position (rowed addProjectile 0x0033EEE2).

#include <string.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// Local views of the WWMath types; only Matrix3D's name is load-bearing (the
// launch-position callee takes one). The helpers below expand retail's inline
// Matrix3D copy (member-wise) and Matrix3D::Transform_Vector.
struct ProjectileNuggetVector3
{
	float X;
	float Y;
	float Z;
	ProjectileNuggetVector3() {}
	ProjectileNuggetVector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};

struct ProjectileNuggetRow
{
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	ProjectileNuggetRow Row[3];
};

struct ProjectileNuggetMath
{
	static __forceinline void copyRow(ProjectileNuggetRow &dst, const ProjectileNuggetRow &src)
	{
		dst.X = src.X;
		dst.Y = src.Y;
		dst.Z = src.Z;
		dst.W = src.W;
	}
	static __forceinline void copyMatrix(Matrix3D &dst, const Matrix3D &src)
	{
		copyRow(dst.Row[0], src.Row[0]);
		copyRow(dst.Row[1], src.Row[1]);
		copyRow(dst.Row[2], src.Row[2]);
	}
	static __forceinline void transformVector(const Matrix3D &A, const ProjectileNuggetVector3 &in, ProjectileNuggetVector3 *out)
	{
		ProjectileNuggetVector3 tmp;
		const ProjectileNuggetVector3 *v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = &in;
		}
		out->X = (A.Row[0].X * v->X + A.Row[0].Y * v->Y + A.Row[0].Z * v->Z + A.Row[0].W);
		out->Y = (A.Row[1].X * v->X + A.Row[1].Y * v->Y + A.Row[1].Z * v->Z + A.Row[1].W);
		out->Z = (A.Row[2].X * v->X + A.Row[2].Y * v->Y + A.Row[2].Z * v->Z + A.Row[2].W);
	}
};

class Team;
class ThingTemplate;
class WeaponTemplate;
struct CreateMask
{
	unsigned int m_bits[4];
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class ObjectFilter
{
public:
	Bool isValid() const;
};

class ProjectileUpdateInterface
{
public:
	virtual void projectileLaunch(const Object *victim, const Coord3D *victimPos,
		const Object *launcher, WeaponSlotType wslot, Int specificBarrelToUse,
		const void *fireInfo, const WeaponTemplate *detonationWeapon,
		const Matrix3D *launchTransform) = 0;
};

template <int N> class ProjectileNuggetSlots : public ProjectileNuggetSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class ProjectileNuggetSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

// The behavior-module interface each module carries at +0x0C.
class BehaviorModuleInterface : public ProjectileNuggetSlots<18>
{
public:
	virtual ProjectileUpdateInterface *getProjectileUpdateInterface() = 0; // slot 18
};

class BehaviorModule
{
public:
	// Calls slot 18 through the module's +0x0C interface.
	ProjectileUpdateInterface *projectileUpdateInterfaceView()
	{
		return ((BehaviorModuleInterface *)((char *)this + 0x0C))->getProjectileUpdateInterface();
	}
};

// The firer's +0x250 module: slot 79 hands out the projectile.
class ProjectileSourceModule : public ProjectileNuggetSlots<79>
{
public:
	virtual Object *getProjectileToLaunch(const ObjectFilter *filter) = 0; // slot 79
};

class Module;
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(x) TheNameKeyGenerator->nameToKey(x)

class Rva0033EEC9
{
public:
	void rva0033EF86(const Coord3D *pos);	// the stream's position
};
class ProjectileStreamUpdate
{
public:
	void addProjectile(ObjectID sourceID, ObjectID projectileID, ObjectID victimID, const Coord3D *victimPos);
};

class Object
{
	friend class ProjectileNugget;
public:
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	ProjectileSourceModule *getProjectileSource() const { return m_250; }
	Player *getControllingPlayer() const;
	void setProducer(Object *producer);
protected:
	Module *findModule(NameKeyType key) const;
private:
	unsigned char m_pad000[0x08];
	Matrix3D m_transform; // +0x08
	Coord3D m_pos; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x244 - 0x78];
	BehaviorModule **m_behaviors; // +0x244
	unsigned char m_pad248[0x250 - 0x248];
	ProjectileSourceModule *m_250; // +0x250
};

class Weapon
{
public:
	static void calcProjectileLaunchPosition(const Object *launcher, WeaponSlotType wslot,
		Int specificBarrelToUse, Matrix3D &worldTransform, Coord3D &worldPos);
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, Bool b);
};

extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;

// The fire info's template: its filter and launch-self byte.
struct ProjectileNuggetWeapon
{
	unsigned char m_pad000[0x120];
	ObjectFilter m_filter; // +0x120
	unsigned char m_pad121[3];
	Bool m_launchSelf; // +0x124
};

struct ProjectileNuggetFireInfo
{
	unsigned char m_pad00[0x04];
	const ProjectileNuggetWeapon *m_weapon; // +0x04
	ObjectID m_sourceID; // +0x08
	WeaponSlotType m_wslot; // +0x0C
	unsigned char m_pad10[0x38 - 0x10];
	Int m_specificBarrel; // +0x38
	unsigned char m_pad3C[0x5C - 0x3C];
	ObjectID m_streamOwnerID; // +0x5C
};

class ProjectileNugget
{
public:
	virtual void doEffectObject(const ProjectileNuggetFireInfo *info, Object *victim);
	virtual void rva00509A3C(const ProjectileNuggetFireInfo *info, const Coord3D *pos);
private:
	unsigned char m_pad004[0x128 - 0x04];
	const WeaponTemplate *m_detonationWeapon; // +0x128
	const ThingTemplate *m_projectileTemplate; // +0x12C
	unsigned char m_pad130[0x13C - 0x130];
	Int m_weaponSlotOverride; // +0x13C
	Coord3D m_launchOffset; // +0x140
	Bool m_useLaunchOffset; // +0x14C
};

void ProjectileNugget::rva00509A3C(const ProjectileNuggetFireInfo *info, const Coord3D *pos)
{
	Object *source = TheGameLogic->findObjectByID(info->m_sourceID);
	if (source == 0)
		return;

	Matrix3D launchTransform;
	const Matrix3D *launchTransformPtr = &launchTransform;
	Coord3D launchPos;
	Coord3D worldPos;
	CreateMask mask;
	if (m_useLaunchOffset)
	{
		ProjectileNuggetVector3 result;
		ProjectileNuggetMath::transformVector(*source->getTransformMatrix(),
			ProjectileNuggetVector3(m_launchOffset.x, m_launchOffset.y, m_launchOffset.z), &result);
		launchPos.x = result.X;
		launchPos.y = result.Y;
		launchPos.z = result.Z;
	}
	else
	{
		launchPos = *pos;
	}

	Object *projectile;
	const ProjectileNuggetWeapon *weapon = info->m_weapon;
	if (weapon->m_filter.isValid() && source->getProjectileSource())
	{
		Weapon::calcProjectileLaunchPosition(source, info->m_wslot, info->m_specificBarrel, launchTransform, worldPos);
		const ObjectFilter *filter = &info->m_weapon->m_filter;
		projectile = source->getProjectileSource()->getProjectileToLaunch(filter);
	}
	else if (info->m_weapon->m_launchSelf)
	{
		ProjectileNuggetMath::copyMatrix(launchTransform, *source->getTransformMatrix());
		projectile = source;
	}
	else
	{
		if (m_projectileTemplate == 0)
			return;
		launchTransformPtr = 0;
		memset(&mask, 0, sizeof(mask));
		projectile = TheThingFactory->newObject(m_projectileTemplate,
			source->getControllingPlayer()->getDefaultTeam(), &mask, false);
	}

	ProjectileUpdateInterface *pui = 0;
	for (BehaviorModule **u = projectile->getBehaviorModules(); *u; ++u)
	{
		if ((pui = (*u)->projectileUpdateInterfaceView()) != 0)
			break;
	}
	if (pui)
	{
		WeaponSlotType wslot = info->m_wslot;
		if (m_weaponSlotOverride >= 0 && m_weaponSlotOverride < 6)
			wslot = (WeaponSlotType)m_weaponSlotOverride;
		projectile->setProducer(source);
		pui->projectileLaunch(0, &launchPos, source, wslot, info->m_specificBarrel, info,
			m_detonationWeapon, launchTransformPtr);
	}
	else
	{
		TheGameLogic->destroyObject(projectile);
	}
}

void ProjectileNugget::doEffectObject(const ProjectileNuggetFireInfo *info, Object *victim)
{
	Object *source = TheGameLogic->findObjectByID(info->m_sourceID);
	if (source == 0)
		return;

	Matrix3D launchTransform;
	const Matrix3D *launchTransformPtr = &launchTransform;
	Coord3D worldPos;
	CreateMask mask;
	Object *projectile;
	const ProjectileNuggetWeapon *weapon = info->m_weapon;
	if (weapon->m_filter.isValid() && source->getProjectileSource())
	{
		Weapon::calcProjectileLaunchPosition(source, info->m_wslot, info->m_specificBarrel, launchTransform, worldPos);
		const ObjectFilter *filter = &info->m_weapon->m_filter;
		projectile = source->getProjectileSource()->getProjectileToLaunch(filter);
	}
	else if (info->m_weapon->m_launchSelf)
	{
		Weapon::calcProjectileLaunchPosition(source, info->m_wslot, info->m_specificBarrel, launchTransform, worldPos);
		projectile = source;
	}
	else
	{
		if (m_projectileTemplate == 0)
			return;
		launchTransformPtr = 0;
		memset(&mask, 0, sizeof(mask));
		projectile = TheThingFactory->newObject(m_projectileTemplate,
			source->getControllingPlayer()->getDefaultTeam(), &mask, false);
	}

	ProjectileUpdateInterface *pui = 0;
	for (BehaviorModule **u = projectile->getBehaviorModules(); *u; ++u)
	{
		if ((pui = (*u)->projectileUpdateInterfaceView()) != 0)
			break;
	}
	if (pui)
	{
		WeaponSlotType wslot = info->m_wslot;
		if (m_weaponSlotOverride >= 0 && m_weaponSlotOverride < 6)
			wslot = (WeaponSlotType)m_weaponSlotOverride;
		projectile->setProducer(source);
		pui->projectileLaunch(victim, 0, source, wslot, info->m_specificBarrel, info,
			m_detonationWeapon, launchTransformPtr);
	}
	else
	{
		TheGameLogic->destroyObject(projectile);
	}

	GameLogic *logic = TheGameLogic;
	Object *streamOwner = logic->findObjectByID(info->m_streamOwnerID);
	if (streamOwner == 0)
		return;
	Object *launcher = logic->findObjectByID(info->m_sourceID);
	if (launcher == 0)
		return;
	static NameKeyType key_ProjectileStreamUpdate = NAMEKEY("ProjectileStreamUpdate");
	ProjectileStreamUpdate *update = (ProjectileStreamUpdate *)streamOwner->findModule(key_ProjectileStreamUpdate);
	if (update == 0)
		return;
	((Rva0033EEC9 *)update)->rva0033EF86(launcher->getPosition());
	update->addProjectile(launcher->getID(), projectile->getID(),
		victim ? victim->getID() : INVALID_OBJECT_ID, victim->getPosition());
}
