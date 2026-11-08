// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include
//
// ?computeApproachTarget@Weapon@@QBE_NPBVObject@@0PBUCoord3D@@MAAU3@@Z
// ?clipToTerrainExtent@@YAXAAUCoord3D@@@Z
// Retail 0x002CAEA3 (1070 bytes, ret 0x14) and the static helper it calls at
// 0x002C950B (115 bytes). Both sat in Weapon.cpp; they live together here because
// retail calls clipToTerrainExtent with the argument in esi and no push, the private
// register convention MSVC 7.1 gives a static function only when its one caller
// is in the same TU.
//
// Donor (structure, carried facts): Open-BFME-1
// game/GameEngine/Source/GameLogic/Object/Weapon_computeApproachTarget.cpp
// (reference/open-bfme-1 @ c20abf17, BFME 1 retail 0x001E43D0, 1042 bytes), the
// Zero Hour body as BFME changed it: helper-object direction, the too-close branch
// refining the range up to ten times, the far branch shrinking the 0.9-scaled range
// until it holds (done-flag loop), no contact-weapon early-out.
// Target evidence (BFME 2 retail): the direction helpers 0x00265514 (on the target)
// and 0x002C986B (on the source); the range helpers 0x002C9BC3 (source, target
// position) and 0x002C9B80 (source, height); WeaponTemplate::getMinimumAttackRange
// 0x002C92FA with no UNDERSIZE clamp; position +0x38, orientation +0x44, bounding
// sphere radius +0xBC and AI +0x258 on Object; atan2f 0x000422CD and fabs through the
// import thunk 0x00629210 (no /Oi at /O1); TheAI->m_pathfinder at +0x10.
// The source position copies field-wise into a local, as BFME's Coord3D copy does,
// which loads all three components before the differences are stored.

#include "Lib/Region3D.h"
// Retail calls math.h's float atan2 overload 0x000422CD out of line; this unit's
// math.h copies of it and of atan2f (0x000422A0) are retail's bodies.
#include <math.h>

typedef float Real;
typedef int Int;
typedef bool Bool;

// Zero Hour's inline Coord3D members (GeneralsMD BaseType.h). At /O1 they stay out of
// line (retail 0x00003571 and 0x000035B6), but their visible bodies let the compiler
// keep dir's components in their homes across the calls, as retail does.
inline Real Coord3D::length() const
{
	return (Real)sqrt(x*x + y*y + z*z);
}

inline void Coord3D::normalize()
{
	Real len = length();
	if (len != 0.0f)
	{
		len = 1.0f / len;
		x *= len;
		y *= len;
		z *= len;
	}
}

Real Cos(Real);									///< retail 0x0002FBC0
Real Sin(Real);									///< retail 0x0002FBB0

#define PI 3.14159265359f
#define PATHFIND_CELL_SIZE_F 10.0f

class Object;

#include "../../../Include/GameLogic/WeaponTemplate.h"

#include "../../../Include/GameLogic/AIPathfind.h"

class AI;
extern AI *TheAI;
struct AIView
{
	char m_unreconstructed_00[0x10];
	Pathfinder *m_pathfinder;					///< TheAI+0x10
};

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	Coord3D rva00265514(const Object *other) const;			///< retail 0x00265514
	Coord3D Get2DBorderVectorTo(const Coord3D *pos) const;	///< retail 0x002C986B
	Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	char m_unreconstructed_60[0xbc - 0x60];
	Real m_boundingSphereRadius;				///< +0xBC
	char m_unreconstructed_c0[0x258 - 0xc0];
	AIUpdateInterface *m_ai;					///< +0x258
};

// Height-adjusted Weapon::getAttackRange helpers, under their ledger names.
class Rva002C9BC3Owner
{
public:
	float rva002C9BC3(void *source, void *targetPos); // retail 0x002C9BC3
};

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

#include "../../../Include/GameLogic/Weapon.h"

// Height-adjusted range helpers retail inlines into computeApproachTarget.
static inline Real getAttackRangeToPos(const Weapon *weapon, const Object *source, const Coord3D *targetPos)
{
	return ((Rva002C9BC3Owner *)weapon)->rva002C9BC3((void *)source, (void *)targetPos);
}
static inline Real getAttackRangeAtHeight(const Weapon *weapon, const Object *source, Real heightDifference)
{
	return ((Rva002C9B80Owner *)weapon)->rva002C9B80((void *)source, heightDifference);
}

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

//-------------------------------------------------------------------------------------------------
static __declspec(noinline) void clipToTerrainExtent(Coord3D& approachTargetPos)
{
	Region3D bounds;
	TheTerrainLogic->getExtent(&bounds);
	if (approachTargetPos.x < bounds.lo.x+PATHFIND_CELL_SIZE_F) {
		approachTargetPos.x = bounds.lo.x+PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.y < bounds.lo.y+PATHFIND_CELL_SIZE_F) {
		approachTargetPos.y = bounds.lo.y+PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.x > bounds.hi.x-PATHFIND_CELL_SIZE_F) {
		approachTargetPos.x = bounds.hi.x-PATHFIND_CELL_SIZE_F;
	}
	if (approachTargetPos.y > bounds.hi.y-PATHFIND_CELL_SIZE_F) {
		approachTargetPos.y = bounds.hi.y-PATHFIND_CELL_SIZE_F;
	}
}

//-------------------------------------------------------------------------------------------------
Bool Weapon::computeApproachTarget(const Object *source, const Object *target, const Coord3D *pos, Real angleOffset, Coord3D& approachTargetPos) const
{
	// compute unit direction vector from us to our victim
	const Coord3D *targetPos;
	Coord3D dir;
	if (target)
	{
		targetPos = target->getPosition();
		dir = target->rva00265514(source);
	}
	else if (pos)
	{
		targetPos = pos;
		dir = source->Get2DBorderVectorTo(pos);
		// Flip the vector to get from source to pos.
		dir.x = -dir.x;
		dir.y = -dir.y;
		dir.z = -dir.z;
	}
	else
	{
		approachTargetPos.x = 0.0f;
		approachTargetPos.y = 0.0f;
		approachTargetPos.z = 0.0f;
		return false;
	}

	Real dist = dir.length();
	Real minAttackRange = m_template->getMinimumAttackRange();
	if (minAttackRange > 10.0f && dist < minAttackRange)
	{
		// We are too close, so move away from the target.
		// Recompute dir, cause if the bounding spheres touch, it will be 0.
		const Coord3D *p = source->getPosition();
		Coord3D srcPos;
		srcPos.x = p->x;
		srcPos.y = p->y;
		srcPos.z = p->z;
		dir.x = srcPos.x - targetPos->x;
		dir.y = srcPos.y - targetPos->y;
		dir.z = srcPos.z - targetPos->z;
		dir.normalize();

		// if we're airborne and too close, just head for the opposite side.
		if (source->isAboveTerrain())
		{
			// Don't do a 180 degree turn.
			Real angle = atan2(-dir.y, -dir.x);
			Real relAngle = source->getOrientation() - angle;
			if (relAngle > 2*PI) relAngle -= 2*PI;
			if (relAngle < -2*PI) relAngle += 2*PI;
			if (fabs(relAngle) < PI/2) {
				dir.x = -dir.x;
				dir.y = -dir.y;
				dir.z = -dir.z;
			}
		}

		if (angleOffset != 0.0f)
		{
			Real angle = atan2(dir.y, dir.x);
			dir.x = Cos(angle + angleOffset);
			dir.y = Sin(angle + angleOffset);
		}

		// select a spot along the line between us, halfway between the min & max range.
		Real attackRange = (getAttackRangeToPos(this, source, targetPos) + minAttackRange)/2.0f;
		for (Int i = 0; i < 10; ++i)
		{
			if (target)
				attackRange += target->getBoundingSphereRadius();
			attackRange += source->getBoundingSphereRadius();
			Real range = getAttackRangeAtHeight(this, source, -attackRange * dir.z);
			if (!(attackRange > range))
				break;
			attackRange = range;
		}
		approachTargetPos.x = attackRange * dir.x + targetPos->x;
		approachTargetPos.y = attackRange * dir.y + targetPos->y;
		approachTargetPos.z = attackRange * dir.z + targetPos->z;
		///@todo - make sure we can get to the approach position.
		clipToTerrainExtent(approachTargetPos);
		return false;
	}

	const Real FUDGE = 0.001f;
	if (dist < FUDGE)
	{
		// we're close enough!
		approachTargetPos = *source->getPosition();
		return true;
	}

	dir.x /= dist;
	dir.y /= dist;
	dir.z /= dist;

	if (angleOffset != 0.0f)
	{
		Real angle = atan2(dir.y, dir.x);
		dir.x = Cos(angle + angleOffset);
		dir.y = Sin(angle + angleOffset);
	}

	// select a spot along the line between us, in range of our weapon
	const Real ATTACK_RANGE_APPROACH_FUDGE = 0.9f;
	Real attackRange = getAttackRangeToPos(this, source, targetPos) * ATTACK_RANGE_APPROACH_FUDGE;
	if (dir.z != 0.0f)
	{
		Bool done = false;
		for (Int i = 0; !done && i < 10; ++i)
		{
			Real range = getAttackRangeAtHeight(this, source, -(attackRange * dir.z));
			if (range < attackRange)
			{
				attackRange = range * ATTACK_RANGE_APPROACH_FUDGE;
				done = false;
			}
			else
			{
				done = true;
			}
		}
	}
	approachTargetPos.x = attackRange * dir.x + targetPos->x;
	approachTargetPos.y = attackRange * dir.y + targetPos->y;
	approachTargetPos.z = attackRange * dir.z + targetPos->z;

	if (source->getAI() && source->getAI()->isAircraftThatAdjustsDestination()) {
		// Adjust the target so that we are not stacked atop another aircraft.
		((AIView *)TheAI)->m_pathfinder->AdjustTargetDestination((Object *)source, (Int)target, (Int)pos, (Int)this, &approachTargetPos);
	}

	return false;
}
