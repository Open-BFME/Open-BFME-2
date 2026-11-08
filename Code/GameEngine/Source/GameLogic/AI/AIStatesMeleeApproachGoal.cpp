// cl: /O1 /G7 /EHsc /MD /arch:SSE /DNDEBUG /ICode/Libraries/Include/Lib
// Native 0x003449C5..0x00344D60, cdecl RET0, 923 bytes. Calls from the
// matched AI approach states at 0x00345AB7 and 0x00348E9F establish the
// goal/source/victim ABI. WB 0x00E10AB0 and BFME1's melee-engage helper
// support the approach/fallback purpose; the original helper name is unknown.
// Object position38, radiusB8, AI258, template108 kind bits, and AI data D4
// are target accesses, not claims of complete class layouts. The existing
// Pathfinder integer gate spelling is retained with explicit pointer bits
// and an AL-sized result, as the owned provider and native call require.
//
// All four real Coord3D length/normalization bodies must be visible together
// for MSVC7.1 to reproduce the native loop's XMM allocation. Every proper
// subset leaves the register mirror. These are the existing coord3d.cpp
// implementations, kept out of line as in retail; no new helper pins.

#include <math.h>
#include "Coord3D.h"
// Scalar copy/subtraction/scale preserve the target's component operations.
struct ApproachCoordCopy : Coord3D
{
    __forceinline ApproachCoordCopy(const Coord3D &other)
    { x = other.x; y = other.y; z = other.z; }
    __forceinline void sub(const Coord3D *other)
    { x -= other->x; y -= other->y; z -= other->z; }
    __forceinline void scale(float factor)
    { x *= factor; y *= factor; z *= factor; }
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class Weapon;
class Rva002C9B80Owner;
class LocomotorSet;

class Rva004C5772CmpBoolField
{
public:
	bool get() const;
};

#include "../../../Include/Common/ThingTemplate.h"

#include "../../../Include/GameLogic/Module/AIUpdate.h"

class Object
{
public:
	int rva0028B511() const;
 float getBfmeRadiusB8() const { return m_radius; }
 const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() { return m_ai; }
protected:
	Module *findModule(NameKeyType key) const;
	friend bool rva003449C5(Coord3D *, Object *, Object *);
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;

	char m_pad00[4];
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	char m_pad44[0xB8 - 0x44];
	float m_radius; // +0xB8
	char m_padBC[0x258 - 0xBC];
	AIUpdateInterface *m_ai; // +0x258
};

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/TAiData.h"
#include "../../../Include/GameLogic/AI.h"

#include "../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

bool rva003449C5(Coord3D *goal, Object *source, Object *victim)
{
	AIUpdateInterface *ai = source->getAI();
	if (ai == 0)
		return false;

	ApproachCoordCopy delta = *goal;
	delta.sub(source->getPosition());
	delta.z = 0.0f;
	float goalDist = delta.GetLength();

	ApproachCoordCopy target = *goal;
	if (victim)
	{
		static_cast<Coord3D&>(target) = *victim->getPosition();
		if (((victim->getTemplate()->m_kindof[2] & (1U << 29)) != 0))
		{
			static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
			Module *module = victim->findModule(key);
			if (module && ((Rva004C5772CmpBoolField *)module)->get())
				return true;
		}
	}

	bool canApproach = TheAI->pathfinder()->CanApproachToTarget(source, &target, (Rva002C9B80Owner *)source->getCurrentWeapon(0), false);
	if (canApproach && TheAI->pathfinder()->QuickDoesPathExist(source, source->getPosition(), goal, 0))
		return true;

	ApproachCoordCopy pos = *goal;
	static_cast<Coord3D&>(delta) = *goal;
	delta.sub(source->getPosition());
	delta.z = 0.0f;
	int steps = -(int)(-delta.length() / 20.0f) - 1;
	delta.Normalize();
	delta.scale(20.0f);
	bool found = false;
	bool blocked = false;
	for (int i = 0; i < steps; ++i)
	{
		pos.sub(&delta);
		if (TheAI->pathfinder()->QuickDoesPathExist(source, source->getPosition(), &pos, 0))
		{
			found = true;
			break;
		}
		if (TheTerrainLogic->getLayerForDestination(source, &pos) > LAYER_GROUND)
			blocked = true;
		else if ((unsigned char)TheAI->pathfinder()->isBlockedGateObstacleCell((int)&pos, LAYER_GROUND))
			blocked = true;
	}
	if (!found)
		return false;

	bool adjusted = false;
	if (blocked && !canApproach)
	{
		float offset = source->m_radius + TheAI->getAiData()->m_castleSiegeStandBackDistance;
		delta.normalize();
		delta.scale(offset);
		pos.sub(&delta);
		adjusted = true;
	}

	static_cast<Coord3D&>(delta) = *goal;
	delta.sub(&pos);
	delta.z = 0.0f;
	float newDist = delta.GetLength();
	if (!adjusted && newDist + 20.0f > goalDist)
		return false;

	TheAI->pathfinder()->adjustToPossibleDestination(source, ai->getLocomotorSet(), &pos);
	*goal = pos;
	return true;
}

__declspec(noinline) inline float Coord3D::GetLength() const
{
    float x_value = x;
    float y_value = y;
    float z_value = z;
    return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}

__declspec(noinline) inline float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

__declspec(noinline) inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}

__declspec(noinline) inline float Coord3D::Normalize()
{
    float len = GetLength();
    float scale = 1.0f / len;
    x *= scale;
    y *= scale;
    z *= scale;
    return len;
}

// Native344249..3444CE, complete645B RET8. The rowed
// AIMoveToStateSA::computePath347959 calls this as a member; receiver unused.
// BFME1 Rva0016EE00 is the semantic guide. Like static sibling344749, it
// steps the goal toward its owner, applies clearance, and adjusts the result.
// Its original member name is unresolved. The neutral three-float temporary
// retains scalar copies while the canonical Coord3D supplies math workers.
struct MoveGoalCoord {
 float x,y,z;
 MoveGoalCoord() {}
 MoveGoalCoord(const Coord3D &p){x=p.x;y=p.y;z=p.z;}
 void sub(const Coord3D*p){x-=p->x;y-=p->y;z-=p->z;}
 void scale(float s){x*=s;y*=s;z*=s;}
 __forceinline float GetLength()const{return reinterpret_cast<const Coord3D*>(this)->GetLength();}
 __forceinline float length()const{return reinterpret_cast<const Coord3D*>(this)->length();}
 __forceinline float Normalize(){return reinterpret_cast<Coord3D*>(this)->Normalize();}
 __forceinline void normalize(){reinterpret_cast<Coord3D*>(this)->normalize();}
};
class AIMoveToStateSA
{
public:
	bool rva00344249(Coord3D *destination, Object *obj);
};

bool AIMoveToStateSA::rva00344249(Coord3D *destination, Object *obj)
{
	if (obj->rva0028B511() > 1)
		return true;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return false;
	MoveGoalCoord direction(*destination);
	direction.sub(obj->getPosition());
	direction.z = 0.0f;
	float distance = direction.GetLength();
	direction = *reinterpret_cast<MoveGoalCoord*>(destination);
	MoveGoalCoord candidate(*destination);
	direction.sub(obj->getPosition());
	direction.z = 0.0f;
	int count = -(int)(direction.length() * -0.05f) - 1;
	direction.Normalize();
	direction.scale(20.0f);
	bool found = false;
	for (int i = 0; i < count; ++i)
	{
		candidate.sub(reinterpret_cast<Coord3D*>(&direction));
		if (TheAI->pathfinder()->QuickDoesPathExist(obj, obj->getPosition(), reinterpret_cast<Coord3D*>(&candidate), 0))
		{
			found = true;
			break;
		}
	}
	if (!found)
		return false;
	float clearance = TheAI->getAiData()->m_castleSiegeStandBackDistance + obj->getBfmeRadiusB8();
	direction.normalize();
	direction.scale(clearance);
	candidate.sub(reinterpret_cast<Coord3D*>(&direction));
	direction = *reinterpret_cast<MoveGoalCoord*>(destination);
	direction.sub(reinterpret_cast<Coord3D*>(&candidate));
	direction.z = 0.0f;
	if (direction.GetLength() + 20.0f > distance)
		return false;
	TheAI->pathfinder()->adjustToPossibleDestination(obj, ai->getLocomotorSet(), reinterpret_cast<Coord3D*>(&candidate));
	TheAI->pathfinder()->AdjustDestination(obj, ai->getLocomotorSet(), reinterpret_cast<Coord3D*>(&candidate), 0);
	*destination = *reinterpret_cast<Coord3D*>(&candidate);
	return true;
}
