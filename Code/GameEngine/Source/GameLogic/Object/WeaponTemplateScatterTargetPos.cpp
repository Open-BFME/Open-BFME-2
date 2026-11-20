// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?bfmeCalcScatterTargetPos@WeaponTemplate@@QAE?AUCoord3D@@PBVObject@@0U2@@Z
// retail 0x002CB679, 582 bytes (ret 0x18: hidden result, source, victim and a
// Coord3D by value). The name is invented; the body is BFME 2 only.
//
// Target evidence: the scatter radius at this+0x34 is widened by the infantry
// inaccuracy distance at this+0x14C for a KindOf bit 8 (INFANTRY) victim, as
// Zero Hour's fireWeaponTemplate does, and randomized between it and the
// victim's bounding circle radius (Object +0xB8) plus 5.0 through
// GetGameLogicRandomValueReal (Weapon.cpp line 0x659). A STRUCTURE victim is
// aimed at through the rowed getAimPosition (0x002CAB3A, slot 1). With a
// victim the angle is the normalized source-minus-victim direction (a z-less
// Vector3 through WWMath Inv_Sqrt, whose 12-byte frame slot it shares with the
// aim position and the Coord3D offset; atan2f) +- pi/2 (line 0x667), without
// one 0..2pi (line 0x66B); the result is pos + radius * (Cos, Sin). The z then comes from the victim's
// position for KindOf bit 55, else from TheTerrainLogic->getLayerHeight
// (vtable +0x1C) on the layer from the rowed Object getter 0x0028B511 (or
// TheTerrainLogic->getLayerForDestination without a victim) when the victim's
// AI reports isDoingGroundMovement (slot 137, +0x224).

#include "../../../Include/Common/ScalarTypes.h"




#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/PathfindLayerEnum.h"





// Coord3D: retail user ctors, opt-in view (Lib/Coord3DCtorView.h); no private copy.
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/WWMathClass.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// Zero Hour's inline Vector3::Normalize body; retail inlines it here.
static __forceinline void bfmeNormalizeV3(Vector3 &vec)
{
	Real len2 = vec.X * vec.X + vec.Y * vec.Y + vec.Z * vec.Z;
	if (len2 != 0.0f)
	{
		Real oolen = WWMath::Inv_Sqrt(len2);
		vec.X *= oolen;
		vec.Y *= oolen;
		vec.Z *= oolen;
	}
}

#include <math.h>
Real Cos(Real x);
Real Sin(Real x);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);

#define WEAPON_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon.cpp"



#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../Include/Common/ThingTemplate.h"

#include "../../Common/Thing/thing.h"

#include "../../../Include/Common/Geometry.h"

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate() const { return *(const ThingTemplate *volatile *)&m_template; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getBoundingCircleRadius() const { return m_geometry.m_boundingCircleRadius; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Int rva0028B511() const;
private:
	char m_pad060[0xA8 - 0x60];
	GeometryInfo m_geometry;
	char m_pad104[0x258 - 0x104];
	AIUpdateInterface *m_ai; // +0x258
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

//-------------------------------------------------------------------------------------------------
Coord3D WeaponTemplate::bfmeCalcScatterTargetPos(const Object *source, const Object *victim, Coord3D pos)
{
	Real minRadius = victim ? victim->getBoundingCircleRadius() + 5.0f : 0.0f;
	Real scatterRadius = m_scatterRadius;
	PathfindLayerEnum layer;

	if (victim)
	{
		if ((victim->getTemplate()->m_kindof[0] & 0x80))
		{
			Coord3D aim;
			pos = (const Coord3D &)adjustTargetPositionOnVictim((Object *)source, (Object *)victim, true);
		}
		if (m_infantryInaccuracyDist > 0.0f && (victim->getTemplate()->m_kindof[0] & 0x100))
			scatterRadius += m_infantryInaccuracyDist;
		layer = (PathfindLayerEnum)victim->rva0028B511();
	}
	else
	{
		layer = TheTerrainLogic->getLayerForDestination(0, &pos);
	}

	Real radius;
	if (scatterRadius > minRadius)
		radius = GetGameLogicRandomValueReal(minRadius, scatterRadius, WEAPON_CPP, 0x659);
	else
		radius = scatterRadius;

	Real angle;
	if (victim)
	{
		Vector3 dir(source->getPosition()->x - victim->getPosition()->x,
			source->getPosition()->y - victim->getPosition()->y, 0.0f);
		bfmeNormalizeV3(dir);
		Real dirAngle = atan2(dir.Y, dir.X);
		angle = GetGameLogicRandomValueReal(dirAngle - 1.5707964f, dirAngle + 1.5707964f, WEAPON_CPP, 0x667);
	}
	else
	{
		angle = GetGameLogicRandomValueReal(0.0f, 6.2831855f, WEAPON_CPP, 0x66B);
	}

	Coord3D offset;
	offset.x = radius * Cos(angle);
	offset.y = radius * Sin(angle);
	pos.x += offset.x;
	pos.y += offset.y;

	if (victim)
	{
		if ((victim->getTemplate()->m_kindof[1] & 0x800000))
		{
			pos.z = victim->getPosition()->z;
		}
		else
		{
			AIUpdateInterface *ai = victim->getAI();
			if (ai && ai->isDoingGroundMovement())
				pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layer, 0, true);
		}
	}

	return pos;
}
