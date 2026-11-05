// cl: /DNDEBUG /MD
//
// ?xfer@GateOpenAndCloseBehavior@@MAEXPAVXfer@@@Z, retail 0x00498BCB, 225 bytes.
//
// GateOpenAndCloseBehavior behavior xfer. Slot 3 (offset 0x0C) of vtable
// 0x00850144 (secondary of rowed ctor 0x0049889C in
// GateOpenAndCloseBehaviorCtorShard.cpp). BehaviorModule base xfer via rowed
// 0x004C9C7D then Version(1,3) via Xfer slot 0x28 reusing [ebp+8] then
// version-gated UpdateModule xfer via rowed 0x0044DF9F then ints at +0x24
// and +0x28 via Xfer slot 0x7C through locals then bool at +0x2C via 0x90
// then int at +0x38 via 0x7C then ObjectID at +0x20 via rowed XferObjectID
// 0x003060B2 then int at +0x3C via 0x7C then TheAudio (data 0x009FE6E8)
// xferAudioHandle at AudioManager slot 0x160 for +0x40 then bool at +0x44
// via 0x90 then version-gated raw 4B at +0x28 via 0x24 plus floats at
// +0x30 and +0x34 via 0x70. Member offsets are UpdateModule-relative
// (this is the +4 secondary); Gate-relative names in the ctor shard are +4
// higher (m_20 here is m_24 there through m_44 here is m_48 there). The two
// leading ints go through locals (retail push ecx pair and [ebp-4]/[ebp-8]
// temps with writeback) and the gated tail reuses the +0x28 address in ebx.
// Recipe is FireWeaponWhenDamagedBehaviorXfer raw-plus-float tail plus
// FoundationAIUpdateXfer audio-handle shape.

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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

typedef unsigned int AudioHandle;

#include "../../../../Include/Common/GameAudio.h"

// The existing link definition is the AudioManager singleton at this VA.
extern AudioManager *TheAudio;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	protected: virtual void xfer(Xfer *xfer);
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class GateOpenAndCloseBehavior : public UpdateModule
{
public:
	GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_20;
	int m_24;
	int m_28;
	bool m_2c;
	float m_30;
	float m_34;
	int m_38;
	int m_3c;
	AudioHandle m_40;
	bool m_44;
};

void GateOpenAndCloseBehavior::xfer(Xfer *xfer)
{
	BehaviorModule::xfer(xfer);
	Xfer::Version version(1, 3);
	*xfer == version;
	if (version.m_minimum >= 3) {
		UpdateModule::xfer(xfer);
	}
	int tmp24 = m_24;
	*xfer == tmp24;
	m_24 = tmp24;
	int tmp28 = m_28;
	*xfer == tmp28;
	m_28 = tmp28;
	*xfer == m_2c;
	*xfer == m_38;
	XferObjectID(xfer, &m_20);
	*xfer == m_3c;
	TheAudio->xferAudioHandle(xfer, &m_40);
	*xfer == m_44;
	if (version.m_minimum >= 2) {
		xfer->XferRawBytes(&m_28, 4);
		*xfer == m_30;
		*xfer == m_34;
	}
}
