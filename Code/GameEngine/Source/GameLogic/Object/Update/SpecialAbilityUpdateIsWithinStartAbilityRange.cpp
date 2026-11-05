// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /D_STLP_USE_STATIC_LIB
// stlport
//
// ?isWithinStartAbilityRange@SpecialAbilityUpdate@@IAE_NXZ
// retail 0x0044F28E..0x0044F4F7 (617 bytes) thiscall RET 0.
//
// Shape notes: the no-target/no-position branch is an if-form compare on
// the final override's power type (cmp 0x88 / setne al); the contact
// intersection and the line-of-sight filter share one if/else-if chain so
// both results reach the single "test al,al / je false / mov al,1" tail;
// the stack-built LOS filter carries vtable 0x00C07150.
// Identity: BFME 2 form of SpecialAbilityUpdate::isWithinStartAbilityRange
// (Zero Hour SpecialAbilityUpdate.cpp; Open-BFME-1
// SpecialAbilityUpdate_isWithinStartAbilityRange.cpp is the closest donor).
// Only caller is 0x00452230.
// Callees are all rowed or pinned: isEmpty 0x00001E2F,
// getWorldspaceBestContactPoint 0x002904DC, 0x002C97E8, 0x0044E6B8,
// 0x002615E3, 0x00263763, friend_getFinalOverride 0x00288609, testStatus
// 0x0004E536, 0x001E435D, CollidesWith 0x006BEB80, filter allow
// 0x002619C1 and 0x0026163A.
#include "ascii_string.h"
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"

typedef float Real;
typedef int Int;
typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_5B = 0x5B
};

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/Common/Geometry.h"

#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

// 0x002615E3 is rowed as Rva000CBA20::distSq (Rva000CBA20DistSq.cpp).
#include "../../../Common/RTS/XYDistanceCallView.h"

class Object
{
public:
	Bool getWorldspaceBestContactPoint(Coord3D *out, const Coord3D *from, const char *boneName, Int a, Int b, Bool c) const;
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	Real rva0044E6B8(const Object *other) const;
	Real rva00263763(const void *other) const;
	Bool testStatus(ObjectStatusTypes status) const;

	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_angle; }
	const GeometryInfo &getGeometryInfo() const { return m_geometry; }
	AIUpdateInterface *getAI() const { return m_ai; }

	void *m_vtable;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos;						// +0x38
	Real m_angle;						// +0x44
	unsigned char m_pad048[0xA8 - 0x48];
	GeometryInfo m_geometry;			// +0xA8
	unsigned char m_pad0BC[0x258 - 0x104];
	AIUpdateInterface *m_ai;			// +0x258
};

class BfmeVec3EJ;
class Gen_000E5A50
{
public:
	Real Get3DCenterDistanceSquared(const BfmeVec3EJ *pos) const;
};

extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/Overridable.h"

struct SpecialPowerTemplateView
{
	unsigned char m_pad00[0x1C];
	Int m_type;							// +0x1C
};

class SpecialPowerTemplate : public Overridable
{
public:
	Int getSpecialPowerType() const { return ((const SpecialPowerTemplateView *)friend_getFinalOverride())->m_type; }
};

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad000[0x38];
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x38
	unsigned char m_pad03C[0x4C - 0x3C];
	Real m_startAbilityRange;							// +0x4C
	Real m_abilityAbortRange;							// +0x50
	unsigned char m_pad054[0xB1 - 0x54];
	Bool m_approachRequiresLOS;							// +0xB1
	unsigned char m_pad0B2[0xB8 - 0xB2];
	Bool m_contactOnZeroDistance;						// +0xB8
	unsigned char m_pad0B9[0xBC - 0xB9];
	AsciiString m_contactBone;							// +0xBC
	unsigned char m_pad0C0[0xC5 - 0xC0];
	Bool m_addRadiusC5;									// +0xC5
};

// The line-of-sight partition filter (vtable 0x00C07150).
// Native C07150 slot0 uses395A19 and resets the BC26E0 base vptr at49C38A.
// The base has a next-filter pointer at+4 and three virtual slots; the owner
// remains at+8. This is the same base used by the exact2FD66B-family provider.
#include "../../../../Include/GameLogic/PartitionFilter.h"

class Rva002619C1Filter : public Rva000421C8
{
public:
	Rva002619C1Filter(Object *owner) : m_owner(owner) {}
	virtual ~Rva002619C1Filter() {}
	virtual Bool allow(Object *other);

	Object *m_owner;
};

class Rva0026163A
{
public:
	Bool rva0026163A(const Coord3D *target);
};

#include "../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

Bool SpecialAbilityUpdate::isWithinStartAbilityRange()
{
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	const SpecialPowerTemplate *power = data->m_specialPowerTemplate;
	Object *self = m_object;

	if (m_withinStartAbilityRange)
		return true;

	Real fDistSquared = 0.0f;
	Object *target = 0;
	if (m_targetID != INVALID_OBJECT_ID)
	{
		target = TheGameLogic->findObjectByID(m_targetID);
		if (target)
		{
			Bool contact = false;
			if (!((const StringBase<char> *)&data->m_contactBone)->isEmpty())
			{
				Coord3D point;
				point.x = 0.0f;
				point.y = 0.0f;
				point.z = 0.0f;
				if (target->getWorldspaceBestContactPoint(&point, self->getPosition(), data->m_contactBone.str(), 0, 42, true))
				{
					fDistSquared = self->rva002C97E8(self->getPosition(), &point);
					contact = true;
				}
			}
			if (!contact)
			{
				if (target->getTemplate()->m_kindof[4] & (1U << 4))
					fDistSquared = target->rva0044E6B8(self);
				else if ((self->getTemplate()->m_kindof[3] & (1U << 13)) && data->m_addRadiusC5)
				{
					Real radius = self->m_geometry.m_boundingCircleRadius;
					fDistSquared = ((Rva000CBA20 *)target)->distSq((const Rva000CBA20Point *)self->getPosition()) + radius;
				}
				else
					fDistSquared = target->rva00263763(self);
			}
		}
		else
		{
			m_targetID = INVALID_OBJECT_ID;
			return false;
		}
	}
	else if (m_targetPos.x || m_targetPos.y || m_targetPos.z)
	{
		Int type = power->getSpecialPowerType();
		if (self->testStatus(OBJECT_STATUS_BFME_5B) || (self->getAI()->vslot090() && type == 0x38))
			fDistSquared = ((const Gen_000E5A50 *)self)->Get3DCenterDistanceSquared((const BfmeVec3EJ *)&m_targetPos);
		else
			fDistSquared = self->rva002C97E8(self->getPosition(), &m_targetPos);
		if (type == 0x27)
			fDistSquared -= 400.0f;
	}
	else
	{
		if (power->getSpecialPowerType() == 0x88)
			return false;
		return true;
	}

	Real fStartRangeSquared = data->m_startAbilityRange * data->m_startAbilityRange;
	if (fDistSquared <= fStartRangeSquared)
	{
		if (fDistSquared == 0.0f && m_targetID != INVALID_OBJECT_ID && data->m_contactOnZeroDistance)
		{
			if (!target)
				return false;
			if (self->getGeometryInfo().CollidesWith(*self->getPosition(), 0.0f, target->getGeometryInfo(), *target->getPosition(), target->getOrientation()))
				return true;
		}
		else if (data->m_approachRequiresLOS)
		{
			Rva002619C1Filter filterLOS(self);
			if (target)
			{
				if (filterLOS.allow(target))
					return true;
			}
			else
			{
				if (((Rva0026163A *)&filterLOS)->rva0026163A(&m_targetPos))
					return true;
			}
		}
		else
			return true;
		return false;
	}
	return false;
}

// Zero Hour's __max macro, written out: the comparison reads the zero first, as retail does.
#define ABILITY_MAX(a, b) (((a) > (b)) ? (a) : (b))

// ZH SpecialAbilityUpdate::isWithinAbilityAbortRange with BFME 2's distance helpers (the same ones
// isWithinStartAbilityRange reads) and the abort range at module data +0x50.
Bool SpecialAbilityUpdate::isWithinAbilityAbortRange() const
{
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	const SpecialPowerTemplate *power = data->m_specialPowerTemplate;
	const Object *self = m_object;

	Real range = data->m_startAbilityRange;
	const Real UNDERSIZE = 2.5f;
	range = ABILITY_MAX(0.0f, range - UNDERSIZE);

	Real fDistSquared = 0.0f;
	Object *target = 0;
	if (m_targetID != INVALID_OBJECT_ID)
	{
		target = TheGameLogic->findObjectByID(m_targetID);
		if (target)
			fDistSquared = self->rva00263763(target);
	}
	else if (m_targetPos.x || m_targetPos.y || m_targetPos.z)
	{
		fDistSquared = self->rva002C97E8(self->getPosition(), &m_targetPos);
		if (power->getSpecialPowerType() == 0x27)
			fDistSquared -= 400.0f;
	}
	else
		return true;

	Real fAbortRangeSquared = data->m_abilityAbortRange * data->m_abilityAbortRange;
	if (fDistSquared <= fAbortRangeSquared)
	{
		if (range == 0.0f && m_targetID != INVALID_OBJECT_ID)
		{
			if (!target)
				return false;
			if (!self->getGeometryInfo().CollidesWith(*self->getPosition(), 0.0f, target->getGeometryInfo(), *target->getPosition(), target->getOrientation()))
				return false;
		}
		return true;
	}
	return false;
}
