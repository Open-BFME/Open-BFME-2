// cl: /MD
//
// ?xfer@FoundationAIUpdate@@MAEXPAVXfer@@@Z @0x004550F8, 100 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00840608 (primary of
// ??1Rva00455050@@UAE@XZ). Class is FoundationAIUpdate: slot 2 at
// 0x00455070 returns "FoundationAIUpdate", slot 4 at 0x00455167 is the
// FoundationAIUpdate pool key, and the ctor at 0x004551B3 installs this
// vtable. Base UpdateModule xfer via rowed 0x0044DF9F, Version(1,1) via Xfer
// slot 0x28, IsLightCRC guard via Xfer slot 0x10 skipping only the audio
// handle, TheAudio (data 0x009FE6E8) xferAudioHandle at AudioManager slot
// 0x160 for +0x24, ObjectID at +0x28 via rowed XferObjectID 0x003060B2, bool
// at +0x2C via Xfer slot 0x90. Layout is the rowed 0x30-byte class from
// FoundationAIUpdateCtor.cpp (UpdateModule base 0x20 plus trailing vptr at
// +0x20 giving +0x24 start). Recipe is the BloodthirstyUpdateXfer slot-3
// pattern plus the FiringTracker audio-handle shape.

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

extern AudioManager *TheAudio;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class FoundationTrailing { public: virtual void trailingSlot(); };

class FoundationAIUpdate : public UpdateModule, public FoundationTrailing
{
public:
	FoundationAIUpdate(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	AudioHandle m_24;
	ObjectID m_28;
	bool m_2C;
};

void FoundationAIUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	UpdateModule::xfer(xfer);
	if (!xfer->IsLightCRC()) {
		TheAudio->xferAudioHandle(xfer, &m_24);
	}
	XferObjectID(xfer, &m_28);
	*xfer == m_2C;
}
