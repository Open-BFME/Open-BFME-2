// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?xfer@PassiveAreaEffectBehavior@@MAEXPAVXfer@@@Z, retail 0x00484C58, 51 bytes.
// Slot 3 of ??_7PassiveAreaEffectBehavior 0x00C4A448 (slot-2 name getter
// returns "PassiveAreaEffectBehavior"; installed by the rowed ctor
// 0x00484A67). Version1, the rowed UpdateModule::xfer 0x0044DF9F, the
// unsigned int at +0x20 (Xfer slot 0x78), then the list<int> at +0x24
// through the rowed Rva0036ABAFXfer. Member names not recovered.

#include <list>

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../../../Include/Common/ObjectModule.h"

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

Xfer *Rva0036ABAFXfer(Xfer *xfer, _STL::list<int> *values);

class PassiveAreaEffectBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_20;
	_STL::list<int> m_trackedIds;
};

// ?xfer@PassiveAreaEffectBehavior@@MAEXPAVXfer@@@Z @0x00484C58
void PassiveAreaEffectBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_20;
	Rva0036ABAFXfer(xfer, &m_trackedIds);
}
