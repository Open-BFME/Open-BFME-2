// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Include
// stlport
//
// ?rva00498FAA@GateOpenAndCloseBehavior@@AAEXXZ, retail 0x00498FAA: the
// gate's push-out scan, run by slots 7 and 8 (GateOpenAndCloseBehaviorSlots.cpp)
// before the gate changes state. A cylinder (height 30, both radii the
// template's +0xB0) is moved ahead of the gate along its 2D direction by
// 0.66 of its major radius (+0x10); every object that is alive, has an AI,
// is of none of kinds 0x59 0x68 0x3C 2 (against KINDOFMASK_NONE), lacks
// status 0x26 and lies inside that footprint at the gate's angle
// (0x0027C2C9) within 1.1 times its minor radius (+0x14) is handed to
// 0x00498DF3 with that offset.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (0x00625790), then each filter's members; address-derived names
// after the out-of-line ctor, else after allow (slot 1).
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/PartitionRangeQueryCallView.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../Common/Thing/thing.h"

enum NameKeyType { NK_UNKNOWN = 0 };

enum ObjectID;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum UpdateSleepTime;

class GateOpenAndCloseBehaviorModuleData;
struct Rva00498DF3Arg;

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void loadPostProcess();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_bfmeReserved; // +0x1C
};

// 4-byte polymorphic primary at +0. Inline ctor installs the first vtable
// ahead of the UpdateModule call; the implicit trivial dtor arms nothing
// (the single EH state completes with the UpdateModule construction, whose
// mirror carries the declared-only dtor).
class GatePrimary
{
public:
	GatePrimary() {}
	virtual void gap0() = 0;
	virtual bool rva00498BAF(Object *object) = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual bool slot6() const = 0;
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void rva00498806() = 0;
	virtual unsigned char slot10() const = 0;
};

class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
public:
	GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GateOpenAndCloseBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onObjectCreated();
	virtual UpdateSleepTime update();
	virtual bool rva00498BAF(Object *object);
	virtual void open();
	virtual void close();
	virtual void rva00498806();
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Player *p) const;
	void changeWantOpenCount(int delta);
	bool rva00498980();
	void rva00498DF3(Rva00498DF3Arg *unit, float flt);
	void rva00498F46(Rva00498DF3Arg *unit, int u1, int u2);

protected:
	virtual void xfer(Xfer *xfer);

private:
	void rva004989F5();
	void setOpenCloseState(int state);
	void rva00498FAA();
	void rva0049924B(bool flag);
	void rva004992D5(bool a, bool b);

	const GateOpenAndCloseBehaviorModuleData *getGateModuleData() const
	{
		return (const GateOpenAndCloseBehaviorModuleData *)m_moduleData;
	}
	Object *getObject() const { return m_object; }

	ObjectID m_linkedObjectId; // +0x24
	int m_state; // +0x28
	int m_2C; // +0x2C
	bool m_30; // +0x30
	float m_34; // +0x34
	float m_38; // +0x38
	unsigned int m_stateFrame; // +0x3C
	int m_request; // +0x40
	unsigned int m_soundHandle; // +0x44
	bool m_soundPlayed; // +0x48
};

enum ArmorSetType { ARMORSET_NONE = 0 };

enum ObjectID;

// How the rowed setFlag 0x006BF3C0 names its argument, one of the module
// data's geometry-name AsciiStrings.
class BfmeStrF9
{
public:
	unsigned char m_pad[4];
};

class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};

// The object's template as this unit reads it: +0xB0 the gate's cylinder
// radius, +0x108 the flag byte the rowed test 0x00498B8B masks with 4.
class ThingTemplate
{
public:
	char m_pad00[0xB0];
	float m_B0; // +0xB0
	char m_padB4[0x108 - 0xB4];
	unsigned char m_flag108; // +0x108
};

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Player *getControllingPlayer() const;
	int rva0028B511() const;
	void clearArmorSetFlag(ArmorSetType v);
	void setArmorSetFlag(ArmorSetType v);
	void rva0028AB75(bool v);

protected:
	friend class GateOpenAndCloseBehavior;
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad060[0x74 - 0x60];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x88 - 0x78];
	AsciiString m_name; // +0x88
	Object *m_next; // +0x8C
	unsigned char m_pad090[0xA8 - 0x90];
public:
	BfmeObjF9 m_objA8; // +0xA8
private:
	unsigned char m_pad0A9[0x438 - 0xA9];
	unsigned char m_438; // +0x438
};

extern "C" void *memset(void *dst, int value, unsigned int size) throw();

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

// GeometryInfo as this scan reads it (ctor 0x00050B74, dtor 0x00050B2A).
class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, bool isSmall, float height, float majorRadius,
		float minorRadius);
	virtual ~GeometryInfo();
	char m_pad04[0x10 - 0x04];
	float m_majorRadius;	// +0x10
	float m_minorRadius;	// +0x14
	// The +0x14 read is the getMinorRadius copy other units emit.
	float getMinorRadius() const { return m_minorRadius; }
	char m_pad18[0x5C - 0x18];
};

// vftable 0x00BFB1B8; the out-of-line ctor 0x0027C2C9: +0x08 a position,
// +0x14 a geometry, +0x18 an angle, +0x1C a flag.
class Rva00261603Filter : public Rva000421C8
{
public:
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, float angle, bool flag);
	virtual bool allow(Object *obj);
	Coord3D m_pos;
	const GeometryInfo *m_geom;
	float m_angle;
	bool m_flag;
};

// A 128-bit ObjectStatusMaskType; 0x0023DA79 clears it and sets one bit.
class BfmeObject872Header
{
	unsigned int m_words[4];
};

class Rva0023DA79 : public BfmeObject872Header
{
public:
	Rva0023DA79 *rva0023DA79(int base, int bit) throw();	// 0x0023DA79
};

struct ObjectStatusMaskNone : BfmeObject872Header
{
	ObjectStatusMaskNone() throw() { memset(this, 0, sizeof(*this)); }
};

// vftable 0x00C17968: must have every status of the first mask and none of
// the second.
class Rva003685CF : public Rva000421C8
{
public:
	Rva003685CF(const BfmeObject872Header &must, const BfmeObject872Header &mustNot) throw();	// 0x003685CF
	virtual bool allow(Object *obj);
	BfmeObject872Header m_must;
	BfmeObject872Header m_mustNot;
};

// The 224-bit KindOf mask.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// Its (unused, four bits) constructor 0x0006EEBC.
struct Rva0006EE7A
{
	unsigned int words[7];
	Rva0006EE7A(int unused, int b1, int b2, int b3, int b4) throw();
};

template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00C17F08, allow 0x0026118B: the object has an AI (+0x258).
class Rva0026118BFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

extern PartitionManager *ThePartitionManager;

void GateOpenAndCloseBehavior::rva00498FAA()
{
	Object *us = m_object;
	if (!us)
		return;
	Coord3D pos;
	pos.x = us->getPosition()->x;
	pos.y = us->getPosition()->y;
	pos.z = us->getPosition()->z;
	float radius = us->getTemplate()->m_B0;
	GeometryInfo geom(GEOMETRY_CYLINDER, false, 30.0f, radius, radius);
	float offset = geom.m_majorRadius * 0.66;
	Coord3D dir;
	us->getUnitDirectionVector2D(dir);
	dir.x *= offset;
	dir.y *= offset;
	dir.z *= offset;
	// Retail reloads pos.x / pos.y as the add's first operand (movss, addss
	// the direction); a plain read folds the load into the add instead.
	volatile Coord3D *vp = &pos;
	pos.x = vp->x + dir.x;
	pos.y = vp->y + dir.y;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, geom.getMinorRadius() * 1.1f, 3,
		Rva0026119DFilter().link(&Rva0026118BFilter())
			->link(&Rva0004584D(*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE,
				*(const BfmeFixedStorage0004543D *)&Rva0006EE7A(0, 0x59, 0x68, 0x3C, 2)))
			->link(&Rva003685CF(ObjectStatusMaskNone(), *Rva0023DA79().rva0023DA79(0, 0x26)))
			->link(&Rva00261603Filter(pos, geom, us->getOrientation(), true)), 0);
	for (Object *obj = hits.next(); obj; obj = hits.next())
		rva00498DF3((Rva00498DF3Arg *)obj, offset);
}
