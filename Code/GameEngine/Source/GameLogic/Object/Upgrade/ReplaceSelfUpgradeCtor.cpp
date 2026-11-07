// cl: /DNDEBUG /MD
//
// ??0ReplaceSelfUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004B7045, 63 bytes.
// ReplaceSelfUpgrade behavior ctor over the canonical UpgradeModule base
// (0x460AEC, thing plus data). The rowed name getter at 0x4B708A proves the
// class; the rowed instance factory 0x250696 is the sole raw caller. Row
// supersedes the ctor pin.
//
// Target facts (vftables are VAs): the ctor first stores the +0x1C
// interface's own table 0x00C4EF80 (four __purecall slots; retail folds it
// with other all-pure interface tables), then the class's tables 0x00C58B10
// at +0, UpgradeModule's 0x00C58110 at +0x0C, 0x00C58AC8 (UpgradeMux) at
// +0x10, UpgradeModule's 0x00C58790 at +0x18 and 0x00C58AB8 at +0x1C. The
// class is declared over the canonical UpgradeModule.h with a +0x1C
// interface, so the compiler stores the vptrs in that order.
//  - 0x00C58B10 (12 slots): deleting dtor 0x004B70CF, loadPostProcess
//    0x00497805 (`jmp 0x0058B03E`, UpgradeModule's own body; inherited here),
//    the name getter 0x004B7084 (rowed as the free-function scaffold
//    ?Rva004B7084Get@@YAHXZ, so slot 2 stays UpgradeModule's), xfer 0x004B6FF7,
//    getModuleNameKey 0x004B708A, then UpgradeModule's slots.
//  - 0x00C58AC8 (UpgradeMux, 18 slots): UpgradeModule's except slot 2,
//    wouldUpgrade 0x004B7110, slot 8, upgradeRemovalImplementation, the shared
//    empty body 0x000B3FD0, and slot 10, upgradeImplementation 0x004B74CB.
//  - 0x00C58AB8 (+0x1C, 4 slots): the empty body 0x000B3FD0, rva004B70F0
//    0x004B70F0, 0x000B3FD0 again and 0x0050B5C6 (`mov al,1; ret`). The
//    interface's name is not established; its slots keep neutral names.

class Thing;
class ModuleData;
class Xfer;

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

enum NameKeyType;

// The +0x1C interface: the ctor's temporary table 0x00C4EF80, then 0x00C58AB8.
class Rva004B70F0Iface1C
{
public:
	virtual void i1C_0() = 0;
	virtual void rva004B70F0() = 0;
	virtual void i1C_2() = 0;
	virtual bool i1C_3() = 0;
};

class ReplaceSelfUpgrade : public UpgradeModule, public Rva004B70F0Iface1C
{
public:
	ReplaceSelfUpgrade(Thing *thing, const ModuleData *moduleData);

	virtual NameKeyType getModuleNameKey() const;
	virtual bool wouldUpgrade(const BitFlags<128> &keyMask) const;
	virtual void upgradeImplementation();

	virtual void i1C_0() { }												// +0x1C slot 0
	virtual void rva004B70F0();												// +0x1C slot 1
	virtual void i1C_2() { }												// +0x1C slot 2
	virtual bool i1C_3() { return true; }									// +0x1C slot 3

protected:
	virtual ~ReplaceSelfUpgrade();
	virtual void xfer(Xfer *xfer);											// primary slot 3
	virtual void upgradeRemovalImplementation() { }						// UpgradeMux slot 8
};

// ??0ReplaceSelfUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z @0x4B7045
ReplaceSelfUpgrade::ReplaceSelfUpgrade(Thing *thing, const ModuleData *moduleData)
	: UpgradeModule(thing, moduleData)
{
}
