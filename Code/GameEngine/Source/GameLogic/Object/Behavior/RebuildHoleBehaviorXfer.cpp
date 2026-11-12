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

class AsciiString;
#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	unsigned short m_pad;
};

class Thing;
class ModuleData;
class Object;
#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../../Include/Common/ThingFactory.h"

// ?g_009FF000@@3PAVRva002D06CA@@A: the global at this VA is ?TheThingFactory@@3PAVRva002D06CA@@A; this name is an alias for it.
extern class ThingFactory *TheThingFactory;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

#include "../../../../Include/Common/BehaviorModuleBase.h"

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


#include "../../../../Include/GameLogic/Module/RebuildHoleBehaviorClass.h"



void RebuildHoleBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 3;
	*xfer == version;
	UpdateModule::xfer(xfer);
	XferObjectID(xfer, &m_workerID);
	XferObjectID(xfer, &m_reconstructingID);
	XferObjectID(xfer, &m_spawnerObjectID);
	*xfer == m_workerWaitCounter;
	AsciiString tmp1(m_workerTemplate ? m_workerTemplate->m_nameString : AsciiString::TheEmptyString);
	*xfer == tmp1;
	if (xfer->IsLoading()) {
		if (tmp1.compare(AsciiString::TheEmptyString) != 0)
			m_workerTemplate = TheThingFactory->findTemplate(tmp1);
		else
			m_workerTemplate = 0;
	}
	AsciiString tmp2(m_rebuildTemplate ? m_rebuildTemplate->m_nameString : AsciiString::TheEmptyString);
	*xfer == tmp2;
	if (xfer->IsLoading()) {
		m_rebuildTemplate = 0;
		if (tmp2.compare(AsciiString::TheEmptyString) != 0)
			m_rebuildTemplate = TheThingFactory->findTemplate(tmp2);
	}
	*xfer == m_44;
	if (version.m_currentVersion >= 3)
		*xfer == m_40;
}
