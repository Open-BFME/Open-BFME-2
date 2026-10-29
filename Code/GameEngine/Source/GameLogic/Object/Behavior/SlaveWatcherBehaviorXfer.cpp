// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// SlaveWatcherBehavior::xfer, retail 0x00484673 (84 bytes): slot 3 of the
// class's primary vtable 0x00C4A264. Version 1 (the rowed Xfer::Version1)
// over the rowed UpdateModule::xfer, then the watched Object's ID (+0x20)
// and the 1024-bit set at +0x24: while the Xfer's slot 4 answers false the
// set goes through the free helper 0x003064CB (pinned by address; its own
// Version1 block), otherwise through the rowed Rva00291440 packer with the
// Xfer as its byte sink (the second caller of that row besides 0x002977F8). The class view
// is the one SlaveWatcherBehaviorDtor.cpp declares.
class Thing;
class ModuleData;
#include "ascii_string.h"

typedef bool Bool;
class Snapshot;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

class SlaveWatcherBehaviorModuleData
{
public:
	unsigned char m_pad[0x8];
	AsciiString m_upgradeToRemove; // +0x08
	AsciiString m_upgradeOnRelease; // +0x0C
	bool m_updateSlave; // +0x10
	bool m_letSlaveLive; // +0x11
};

#include "../../../Common/GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);

enum DamageType
{
	DAMAGE_NORMAL = 0
};

enum DeathType
{
	DEATH_SLAVE_WATCHER_RELEASE = 13
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

namespace _STL
{
template <int N> struct _Base_bitset
{
public:
	unsigned int m_bits;
	void _M_do_or(const _Base_bitset<N> &other);
};
}

// The shared 0x80-byte clear (0x001EAE6F) the ctor runs on the +0x24 set.
class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();

private:
	char m_pad[0x80];
};

// The Xfer's byte-sink packer (0x00291440) the light-CRC xfer path runs.
class Sink00291440;
class Rva00291440
{
public:
	void rva00291440(Sink00291440 *sink);

private:
	unsigned int m_bits[32];
};

void xferUpgradeMask(Xfer *xfer, Rva00291440 *bits);

class SlaveWatcherBits : public _STL::_Base_bitset<32>
{
public:
	SlaveWatcherBits() { ((Rva001EAE6FHelper *)this)->clear80(); }

private:
	unsigned char m_pad[0x7C];
};

class UpgradeTemplate;

class Object
{
public:
	void kill(DamageType type, DeathType death);
	void updateUpgradeModules();
	void removeUpgrade(const UpgradeTemplate *upgrade);
	void rva00293077(const void *upgrade);
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	unsigned char m_pad00[0x284];
	SlaveWatcherBits m_upgradeBits;
	unsigned char m_pad304[0x438 - 0x304];
	unsigned char m_privateStatus; // +0x438
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

bool Rva0045F4C2NotEqual(const void *a, const void *b);


extern GameLogic *TheGameLogic;

// Slot 0 of each module's primary vftable is its deleting destructor
// (0x004848CA in 0x00C4A264), so the base's first virtual is the destructor.
class BehaviorModuleBase
{
public:
	virtual ~BehaviorModuleBase();
	const SlaveWatcherBehaviorModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleOther
{
public:
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_UNREADY = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

// Primary vftable 0x00C4A264: the deleting dtor, loadPostProcess, the snapshot
// name getter, xfer (0x00484673) and getModuleNameKey (0x0048462E) in slots
// 0-4, as UpdateModule's own table lays them out.
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	virtual void loadPostProcess();				// slot 1
	virtual const char *GetSnapshotName() const;		// slot 2
public:
	virtual void xfer(Xfer *xfer);				// slot 3
	virtual NameKeyType getModuleNameKey() const = 0;	// slot 4

protected:
	void setWakeFrame(Object *object, UpdateSleepTime sleepTime);
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_reserved1C; // +0x1C
};

class SlaveWatcherBehavior : public UpdateModule
{
public:
	SlaveWatcherBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~SlaveWatcherBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void rva00484869(int id);

protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_slaveID; // +0x20
	SlaveWatcherBits m_upgradeBits; // +0x24
};

void SlaveWatcherBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	Bool viaHelper = !xfer->IsLightCRC();
	XferObjectID(xfer, &m_slaveID);
	if (viaHelper)
		xferUpgradeMask(xfer, (Rva00291440 *)&m_upgradeBits);
	else
		((Rva00291440 *)&m_upgradeBits)->rva00291440((Sink00291440 *)xfer);
}
