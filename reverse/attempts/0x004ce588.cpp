// ?isDieApplicable@DieMuxData@@QBE_NPBVObject@@PBVDamageInfo@@@Z
// partial score=0.99 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
// ?isDieApplicable@DieMuxData@@QBE_NPBVObject@@PBVDamageInfo@@@Z,
// retail 0x004CE588, 277 bytes (thiscall, ret 8).
// Zero Hour DieMuxData::isDieApplicable keeps the death-type bit and the
// required/exempt status masks; BFME2 drops the veterancy test and adds a
// minimum-damage gate and a facing arc. Target evidence: death type at
// DamageInfo+0x1C tested as bit (type - 1) of the mask at +0x00; the object
// status at +0x94 checked against the required (+0x14) and exempt (+0x04)
// masks by rowed 0x0026157E; minimum damage at +0x24 against the amount at
// DamageInfo+0x20 when non-negative; when the arc at +0x28..+0x2C is
// non-empty, the damage source (DamageInfo+0x08) is looked up through
// TheGameLogic (0x00049DC5), its planar direction taken by 0x002654FC, and
// the object's orientation (+0x44) minus atan2f (0x000422CD) normalized by
// 0x00238954 must lie within half the arc of its centre (fabs import).
#include "Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern "C" double __cdecl fabs(double);
extern "C" float __cdecl atan2f(float, float);
float normalizeAngle(float angle);

extern GameLogic *TheGameLogic;

class Rva0026157E
{
public:
	bool testMasks(const void *required, const void *exempt) const;
};

class Object
{
public:
	Coord3D *getPlanarDirectionTo(Coord3D *out, const Object *other) const;

	char m_pad00[0x44];
	float m_orientation; // +0x44
	char m_pad48[0x94 - 0x48];
	Rva0026157E m_status; // +0x94
};

class DamageInfo
{
public:
	char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
	char m_pad0C[0x1C - 0x0C];
	int m_deathType; // +0x1C
	float m_amount; // +0x20
};

class DieMuxData
{
public:
	bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;

	unsigned int m_deathTypes; // +0x00
	unsigned int m_exemptStatus[4]; // +0x04
	unsigned int m_requiredStatus[4]; // +0x14
	float m_minDamage; // +0x24
	float m_arcStart; // +0x28
	float m_arcEnd; // +0x2C
};

bool DieMuxData::isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const
{
	if ((m_deathTypes & (1 << (damageInfo->m_deathType - 1))) == 0)
		return false;

	if (!obj->m_status.testMasks(m_requiredStatus, m_exemptStatus))
		return false;

	if (m_minDamage >= 0.0f && m_minDamage > damageInfo->m_amount)
		return false;

	if (m_arcStart < m_arcEnd)
	{
		Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
		if (source == 0)
			return false;

		Coord3D dir;
		obj->getPlanarDirectionTo(&dir, source);
		const float orientation = obj->m_orientation;
		const float dirAngle = atan2f(dir.y, dir.x);
		float angle = normalizeAngle(orientation - dirAngle);
		float centre = (m_arcEnd + m_arcStart) / 2.0f;
		float halfArc = m_arcEnd - centre;
		double off = fabs(normalizeAngle(angle - centre));
		if (off > halfArc)
			return false;
	}
	return true;
}
