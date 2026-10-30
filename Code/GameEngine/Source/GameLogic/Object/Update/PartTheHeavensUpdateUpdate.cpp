// cl: /DNDEBUG /MD
//
// PartTheHeavensUpdate::update, retail 0x004ACBB3 (53 bytes): slot 0 of the
// class's +0x10 update-module interface table 0x00C54D98, so `this` is that
// subobject (module data at -0x0C). Sleeps forever without module data;
// otherwise, with the frames since the start frame at +0x20 (TheGameLogic
// +0x40 is the frame), runs the pinned rva004ACADA first on the start frame
// itself and then the class's 0x004AC9FA (pinned by address) with that
// count, staying awake.

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

UpdateSleepTime PartTheHeavensUpdate::update()
{
	if (m_moduleData == 0)
		return UPDATE_SLEEP_FOREVER;
	int elapsed = TheGameLogic->getFrame() - m_startFrame;
	if (elapsed == 0)
		rva004ACADA();
	rva004AC9FA(elapsed);
	return UPDATE_SLEEP_NONE;
}
