// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
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
// 0x0004E536, 0x001E435D, bfmeIntersects 0x006BEB80, filter allow
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

class GeometryInfo
{
public:
	Bool bfmeIntersects(const Coord3D &pos, Real a, const GeometryInfo &other, const Coord3D &otherPos, Real otherAngle) const;
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x115];
	unsigned char m_kindOf115;			// +0x115
	unsigned char m_pad116[0x118 - 0x116];
	unsigned char m_kindOf118;			// +0x118
};

class AIUpdateInterface
{
public:
#define AI_SLOT(n) virtual void slot##n();
	AI_SLOT(00) AI_SLOT(01) AI_SLOT(02) AI_SLOT(03) AI_SLOT(04) AI_SLOT(05) AI_SLOT(06) AI_SLOT(07)
	AI_SLOT(08) AI_SLOT(09) AI_SLOT(10) AI_SLOT(11) AI_SLOT(12) AI_SLOT(13) AI_SLOT(14) AI_SLOT(15)
	AI_SLOT(16) AI_SLOT(17) AI_SLOT(18) AI_SLOT(19) AI_SLOT(20) AI_SLOT(21) AI_SLOT(22) AI_SLOT(23)
	AI_SLOT(24) AI_SLOT(25) AI_SLOT(26) AI_SLOT(27) AI_SLOT(28) AI_SLOT(29) AI_SLOT(30) AI_SLOT(31)
	AI_SLOT(32) AI_SLOT(33) AI_SLOT(34) AI_SLOT(35) AI_SLOT(36) AI_SLOT(37) AI_SLOT(38) AI_SLOT(39)
	AI_SLOT(40) AI_SLOT(41) AI_SLOT(42) AI_SLOT(43) AI_SLOT(44) AI_SLOT(45) AI_SLOT(46) AI_SLOT(47)
	AI_SLOT(48) AI_SLOT(49) AI_SLOT(50) AI_SLOT(51) AI_SLOT(52) AI_SLOT(53) AI_SLOT(54) AI_SLOT(55)
	AI_SLOT(56) AI_SLOT(57) AI_SLOT(58) AI_SLOT(59) AI_SLOT(60) AI_SLOT(61) AI_SLOT(62) AI_SLOT(63)
	AI_SLOT(64) AI_SLOT(65) AI_SLOT(66) AI_SLOT(67) AI_SLOT(68) AI_SLOT(69) AI_SLOT(70) AI_SLOT(71)
	AI_SLOT(72) AI_SLOT(73) AI_SLOT(74) AI_SLOT(75) AI_SLOT(76) AI_SLOT(77) AI_SLOT(78) AI_SLOT(79)
	AI_SLOT(80) AI_SLOT(81) AI_SLOT(82) AI_SLOT(83) AI_SLOT(84) AI_SLOT(85) AI_SLOT(86) AI_SLOT(87)
	AI_SLOT(88) AI_SLOT(89)
#undef AI_SLOT
	virtual Bool slot90();					// +0x168
};

class Object
{
public:
	Bool getWorldspaceBestContactPoint(Coord3D *out, const Coord3D *from, const char *boneName, Int a, Int b, Bool c) const;
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	Real rva0044E6B8(const Object *other) const;
	Real rva002615E3(const Coord3D *pos) const;
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
	unsigned char m_pad0A9[0xB8 - 0xA9];
	Real m_radiusB8;					// +0xB8
	unsigned char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai;			// +0x258
};

class BfmeVec3EJ;
class Gen_000E5A50
{
public:
	Real bfmeDistanceSquared(const BfmeVec3EJ *pos) const;
};

extern GameLogic *TheGameLogic;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

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
	unsigned char m_pad050[0xB1 - 0x50];
	Bool m_approachRequiresLOS;							// +0xB1
	unsigned char m_pad0B2[0xB8 - 0xB2];
	Bool m_contactOnZeroDistance;						// +0xB8
	unsigned char m_pad0B9[0xBC - 0xB9];
	AsciiString m_contactBone;							// +0xBC
	unsigned char m_pad0C0[0xC5 - 0xC0];
	Bool m_addRadiusC5;									// +0xC5
};

// The line-of-sight partition filter (vtable 0x00C07150).
class Rva002619C1FilterBase
{
public:
	Rva002619C1FilterBase() : m_zero(0) {}
	Int m_zero;
};

class Rva002619C1Filter : public Rva002619C1FilterBase
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

class SpecialAbilityUpdate
{
protected:
	Bool isWithinStartAbilityRange();

private:
	void *m_vtable;
	const SpecialAbilityUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;									// +0x08
	unsigned char m_pad00C[0x40 - 0x0C];
	ObjectID m_targetID;								// +0x40
	Coord3D m_targetPos;								// +0x44
	unsigned char m_pad050[0x80 - 0x50];
	Bool m_withinStartAbilityRange;						// +0x80
};

Bool SpecialAbilityUpdate::isWithinStartAbilityRange()
{
	const SpecialAbilityUpdateModuleData *data = m_moduleData;
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
				if (target->getTemplate()->m_kindOf118 & 0x10)
					fDistSquared = target->rva0044E6B8(self);
				else if ((self->getTemplate()->m_kindOf115 & 0x20) && data->m_addRadiusC5)
				{
					Real radius = self->m_radiusB8;
					fDistSquared = target->rva002615E3(self->getPosition()) + radius;
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
		if (self->testStatus(OBJECT_STATUS_BFME_5B) || (self->getAI()->slot90() && type == 0x38))
			fDistSquared = ((const Gen_000E5A50 *)self)->bfmeDistanceSquared((const BfmeVec3EJ *)&m_targetPos);
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
			if (self->getGeometryInfo().bfmeIntersects(*self->getPosition(), 0.0f, target->getGeometryInfo(), *target->getPosition(), target->getOrientation()))
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
