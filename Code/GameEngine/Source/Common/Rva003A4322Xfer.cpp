// cl: /MD
//
// ?xfer@Rva003A4322@@MAEXPAVXfer@@@Z, retail 0x003A4408, 84 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x0081AF60 (class of rowed dtor
// ??1Rva003A4322@@UAE@XZ in Rva0024A797Derived.cpp): Version(1,2) via Xfer
// slot 0x28 then base UpdateModule xfer via rowed 0x0044DF9F then IsLightCRC
// early-out via Xfer slot 0x10 then ObjectID at +0x20 via rowed XferObjectID
// 0x003060B2 then version-gated float at +0x24 via Xfer slot 0x70. Layout
// is UpdateModule base 0x20 plus E1 vptr at +0x20 giving +0x20 start (cf.
// rowed dtor). Identity is slot 3 plus the UpdateModule base call; class
// name stays honest Rva address name.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

#include "../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class Rva003A4322 : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_20;
	float m_24;
};

void Rva003A4322::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	XferObjectID(xfer, &m_20);
	if (version.m_minimum >= 2) {
		*xfer == m_24;
	}
}

// The secondary update interface is at owner+0x10: constructor 0x003A439D
// installs 0x00C1AF54 there, whose first slot is this 103-byte body.
// The constructor, factory and pool-name string establish the enclosing
// FadeAndDieOrnamentUpdate identity. Keep the existing secondary-vtable
// owner spelling Rva003A4322_B2; this is a view of that interface only.
// BFME1 cee35b7d8 BfmeConv1921::bfmeStartBX is the semantic lead; target
// 0x003A4473..0x003A44D9 and WB 0x00FA6550 independently prove the calls,
// negative owner offsets, +0x438 flag and drawable +0xB0 store. The donor's
// virtual drawable getter and resource identity do not carry over to BFME2.
struct Coord3D;
class Drawable;
#include "Thing/thing.h"
enum DamageType { DAMAGE_UNRESISTABLE = 8 };
enum DeathType { DEATH_NORMAL = 0 };
class Object : public Thing
{
public:
	void kill(DamageType, DeathType);
};
class HijackerUpdate
{
public:
	Object *getTargetObject() const;
};
class Rva001048C0
{
public:
	bool update(const float *in, float *out);
private:
	unsigned char m_envelope[0x28];
};
struct Rva003A4473DataView
{
	unsigned char m_head[0x34];
	unsigned char m_relocate;
};
struct Rva003A4473ObjectView
{
	unsigned char m_head[0x438];
	unsigned char m_flags;
};
struct Rva003A4473DrawableView
{
	unsigned char m_head[0xB0];
	int m_value;
};
class Rva003A4322_B2
{
public:
	virtual void f2();
	int update();
private:
	unsigned char m_head[0x10];
	float m_value;
	Rva001048C0 m_envelope;
};

int Rva003A4322_B2::update()
{
	Object *owner = *(Object **)((char *)this - 8);
	if ((*(Rva003A4473DataView **)((char *)this - 0xC))->m_relocate)
	{
		// Reuse the existing row's getter spelling. Its original owner name
		// is not established here; the retail receiver is owner+0x00.
		Object *target = ((const HijackerUpdate *)((char *)this - 0x10))->getTargetObject();
		if (target && !(((Rva003A4473ObjectView *)target)->m_flags & 1))
			owner->setPosition((const Coord3D *)((char *)target + 0x38));
		else
			owner->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}
	Drawable *drawable = owner->getDrawable();
	if (drawable)
	{
		m_envelope.update(&m_value, &m_value);
		((Rva003A4473DrawableView *)drawable)->m_value = *(int *)&m_value;
	}
	return 1;
}
