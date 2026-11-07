// cl: /MD
// ??_GReplaceSelfUpgrade@@MAEPAXI@Z @0x004B70CF 28B
// Deleting dtor slot 0 of vtable 0x00858B10; calls rowed ??1ReplaceSelfUpgrade@@MAE@XZ at 0x004B70EB then rowed operator delete at 0x0002FD60.
//
// The class is declared as its constructor's unit, ReplaceSelfUpgrade.cpp, declares it
// (UpgradeModule plus the +0x1C interface, the same overrides; only the constructor
// differs: this unit has the tag constructor below), so this
// unit's copies of the ??_7ReplaceSelfUpgrade tables are the constructor
// unit's tables, not one-slot ones.
struct EmitVtableTag;

class Thing;
class ModuleData;
class Xfer;

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../Include/GameLogic/Module/UpgradeModule.h"

enum NameKeyType;

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
	ReplaceSelfUpgrade(EmitVtableTag *);

	virtual NameKeyType getModuleNameKey() const;
	virtual bool wouldUpgrade(const BitFlags<128> &keyMask) const;
	virtual void upgradeImplementation();

	virtual void i1C_0() { }
	virtual void rva004B70F0();
	virtual void i1C_2() { }
	virtual bool i1C_3() { return true; }

protected:
	virtual ~ReplaceSelfUpgrade();
	virtual void xfer(Xfer *xfer);
	virtual void upgradeRemovalImplementation() { }
};
// ?<ReplaceSelfUpgrade::ReplaceSelfUpgrade> absent-from-retail
ReplaceSelfUpgrade::ReplaceSelfUpgrade(EmitVtableTag *) : UpgradeModule(0, 0) {}
