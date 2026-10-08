// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?xfer@RebuildHoleBehavior@@MAEXPAVXfer@@@Z, retail 0x004833EC, 338 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00849A74 (class of ??0RebuildHoleBehavior
// rowed at 0x00483271 in RebuildHoleBehaviorCtor.cpp). Version {1,3} via Xfer
// slot 0x28, base UpdateModule xfer via rowed 0x0044DF9F, three ObjectIDs at
// +0x28/+0x2C/+0x30 via rowed XferObjectID 0x003060B2, uint at +0x34 via Xfer
// slot 0x78, two ThingTemplate* at +0x38/+0x3C via AsciiString round-trip
// (copy ctor rowed 0x000365F0, xferAsciiString slot 0x6C, IsLoading slot 0x04,
// compare rowed 0x000069D6, lookup rowed 0x002D06CA via g_009FF000,
// releaseBuffer rowed 0x00036410, empty via AsciiString::TheEmptyString),
// bool at +0x44 via Xfer slot 0x90, float at +0x40 via Xfer slot 0x70 gated
// on current>=3. Layout is the rowed RebuildHoleBehaviorDtor shape (UpdateModule
// base 0x20 plus Die plus RebuildHole interfaces plus six words +0x28..+0x3C
// plus float +0x40 plus bool +0x44). Identity is slot 3 plus the UpdateModule
// base call. Shape follows the rowed SpawnBehaviorXfer at 0x00460586 (same
// Version(1,3) plus template-name round-trip plus bool plus version-gated tail).
#include "ascii_string.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	unsigned short m_pad;
};

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

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08();
	virtual void slot09();

	virtual Xfer &xferVersion(XferVersion *version);

	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;

	virtual Xfer &xferAsciiString(AsciiString &value);

	virtual Xfer &xferReal(float &value);
	virtual void slot29() = 0;

	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
	virtual Xfer &xferInt(int &value);

	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;

	virtual Xfer &xferBool(bool &value);
};

class Thing;
class ModuleData;
class Object;
class ThingTemplate
{
public:
	unsigned char m_pad[0x64];
	AsciiString m_name;
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

// ?g_009FF000@@3PAVRva002D06CA@@A: the global at this VA is ?TheThingFactory@@3PAVRva002D06CA@@A; this name is an alias for it.
extern class ThingFactory *TheThingFactory;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class DieModuleInterface
{
public:
	virtual void onDie();
};

class RebuildHoleBehaviorInterface
{
public:
	virtual void startRebuildProcess(const ThingTemplate *rebuild, ObjectID spawnerID);
	virtual ObjectID getSpawnerID();
	virtual ObjectID getReconstructedBuildingID();
	virtual const ThingTemplate *getRebuildTemplate() const;
};

class RebuildHoleBehavior : public UpdateModule,
	public DieModuleInterface,
	public RebuildHoleBehaviorInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_workerID;
	ObjectID m_reconstructingID;
	ObjectID m_spawnerObjectID;
	UnsignedInt m_workerWaitCounter;
	const ThingTemplate *m_workerTemplate;
	const ThingTemplate *m_rebuildTemplate;
	float m_40;
	bool m_44;
};

void RebuildHoleBehavior::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 3;
	xfer->xferVersion(&version);
	UpdateModule::xfer(xfer);
	XferObjectID(xfer, &m_workerID);
	XferObjectID(xfer, &m_reconstructingID);
	XferObjectID(xfer, &m_spawnerObjectID);
	xfer->xferUnsignedInt(m_workerWaitCounter);
	AsciiString tmp1(m_workerTemplate ? m_workerTemplate->m_name : AsciiString::TheEmptyString);
	xfer->xferAsciiString(tmp1);
	if (xfer->IsLoading()) {
		if (tmp1.compare(AsciiString::TheEmptyString) != 0)
			m_workerTemplate = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&tmp1);
		else
			m_workerTemplate = 0;
	}
	AsciiString tmp2(m_rebuildTemplate ? m_rebuildTemplate->m_name : AsciiString::TheEmptyString);
	xfer->xferAsciiString(tmp2);
	if (xfer->IsLoading()) {
		m_rebuildTemplate = 0;
		if (tmp2.compare(AsciiString::TheEmptyString) != 0)
			m_rebuildTemplate = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&tmp2);
	}
	xfer->xferBool(m_44);
	if (version.m_currentVersion >= 3)
		xfer->xferReal(m_40);
}
