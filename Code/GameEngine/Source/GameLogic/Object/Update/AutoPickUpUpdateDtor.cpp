// cl: /MD
// ??1AutoPickUpUpdate@@UAE@XZ retail 0x00495C48 32 bytes.
// AutoPickUpUpdate destructor: restores the four vtable pointers of the
// complete object -- the derived slot at +0x00 plus the BehaviorModuleOther
// slot at +0x0C, the UpdateModuleInterface slot at +0x10 and the trailing
// AutoPickUpUpdateInterface slot at +0x20 -- then tail-jumps to the
// UpdateModule base destructor at rowed 0x0024A797. The trailing interface
// base has a trivial destructor, so it contributes a store but no call.
// Evidence: slot restores match the rowed ctor 0x00495D31 installs;
// sole caller at 0x00495DAD in ??_GAutoPickUpUpdate; BFME1 donor
// AutoPickUpUpdateDestructor.cpp trivial dtor.
class Thing;
class ModuleData;
class Object;
class Xfer;
enum NameKeyType;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class AutoPickUpUpdateInterface
{
public:
	virtual void anchor() = 0;
	virtual void slot1() = 0;
	virtual void rva00495C6E() = 0;
};

class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface
{
public:
	virtual ~AutoPickUpUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva00495C6E();
	virtual UpdateSleepTime update();
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned int m_count24;
	bool m_flag28;
	bool m_flag29;
};

// ??1AutoPickUpUpdate@@UAE@XZ @0x00495C48
AutoPickUpUpdate::~AutoPickUpUpdate()
{
}
