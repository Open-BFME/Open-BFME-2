#pragma once

#include <vector>
// BFME2's Snapshot puts GetSnapshotName where Zero Hour spells crc.
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../Include/Common/ObjectModule.h"

enum NameKeyType { NK_UNKNOWN = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// The canonical module chain, as SiegeDockingBehaviorDtor.cpp reads it, so both units emit
// the same SiegeDockingBehavior tables (LINK-168 mechanism 4). UpdateModuleCtor.cpp owns
// retail 0x00253390; derived constructors call it.
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

// Retail installs table 0x00C4EF80 at +0x20 before the derived table 0x00C41404.
// Every base slot is __purecall (0x0003B810).
class SiegeDockingBehaviorSecondaryBase
{
public:
	virtual void slot() = 0;
};

struct Rva004598F2Point;

class SiegeDockingBehavior : public UpdateModule, public SiegeDockingBehaviorSecondaryBase
{
public:
	SiegeDockingBehavior(Thing *thing, const ModuleData *data);
	virtual ~SiegeDockingBehavior();
	Rva004598F2Point rva004598F2(int index);
	Rva004598F2Point rva0045992F(int index);
	// Retail primary table 0x00C414DC slots 1, 3 and 4: the rowed overrides 0x0045A16D,
	// 0x0045A02F and 0x004599E5.
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);


private:
	void stopDocking() throw();
	_STL::vector<int> m_vector; // +0x24
	bool m_enabled; // +0x30
public:
	// BehaviorModuleInterface table 0x00C41420 (+0x0C) slot 34: retail 0x004543A9, the +0x0C
	// receiver converted to the +0x20 interface (the null-preserving cast retail folds).
	virtual void *slot34();
protected:
	virtual const char *GetSnapshotName() const;	// primary slot 2: retail 0x004599DF
};
