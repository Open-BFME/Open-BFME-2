// cl: /DNDEBUG /MD
//
// ?loadPostProcess@PartTheHeavensUpdate@@MAEXXZ, retail 0x004ACBE8, 16 bytes.
// Slot 1 of vftable 0x00C54DA4 (??_7PartTheHeavensUpdate, slot 0 is the rowed ??_G,
// slot 3 the xfer). The body chains to the rowed UpdateModule::loadPostProcess
// and then tail-calls a no-argument member at 0x004ACADA (identity not
// recovered; address-named and pinned), the usual ZH loadPostProcess override
// shape: base first, then rebuild transient state.

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

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	virtual void loadPostProcess();

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class PartTheHeavensUpdatePointee
{
public:
	virtual void pointeeSlot0();
	virtual void pointeeSlot1();
	virtual void releasePointee();
};

class PartTheHeavensUpdate : public UpdateModule
{
public:
	PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~PartTheHeavensUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	void rva004AC9FA(int elapsed);
	void rva004ACADA();

	unsigned int m_startFrame;	// +0x20
	PartTheHeavensUpdatePointee *m_pointee;	// +0x24
};

// ?loadPostProcess@PartTheHeavensUpdate@@MAEXXZ @0x004ACBE8
void PartTheHeavensUpdate::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	rva004ACADA();
}
