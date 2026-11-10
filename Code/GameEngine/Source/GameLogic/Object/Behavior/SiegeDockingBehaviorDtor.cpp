// cl: /GX /DNDEBUG /MD
//
// ??1SiegeDockingBehavior@@UAE@XZ, retail 0x00459DAA, 91 bytes.
// Target evidence: vtable 0x00C414DC slot 0 = deleting dtor 0x0045A17D which
// calls here; donor BFME1 SiegeDockingBehaviorDestructors.cpp:82 proves the
// stopDocking plus UpdateModule base; ctor 0x0045996C installs vtables
// 0x00C414DC/+0x0C 0x00C41420/+0x10 0x00C41414/+0x20 0x00C41404 with entries
// at +0x24 and bool at +0x30. Teardown restores 4 vptrs then nothrow
// stopDocking via rowed 0x00459C27 then inline null-checked free of +0x24
// via rowed _free 0x00030830 then base ??1Rva0024A797 at 0x0024A797.
// Layout follows AutoAbilityBehaviorDtor MI base with 3 vptrs to 0x20 plus
// secondary base vptr at +0x20. Manual 3-pointer view earns retail free.

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
	virtual void unused();
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


// Same view as SiegeDockingBehaviorConstructorThunk.cpp, so both units emit one
// +0x20 table (retail 0x00C41404).
class SiegeDockingBehaviorSecondaryBase
{
public:
	virtual void slot() = 0;
};

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

struct SiegeDockingVec
{
	~SiegeDockingVec()
	{
		if (m_start != 0)
			free(m_start);
	}

	void *m_start;
	void *m_finish;
	void *m_end;
};

class SiegeDockingBehavior : public UpdateModule, public SiegeDockingBehaviorSecondaryBase
{
public:
	virtual ~SiegeDockingBehavior();
	// Retail primary table 0x00C414DC slots 1, 3 and 4 (rowed 0x0045A16D, 0x0045A02F,
	// 0x004599E5), as SiegeDockingBehaviorView.h declares them.
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	void stopDocking() throw();
	SiegeDockingVec m_vector; // +0x24
	bool m_enabled; // +0x30
};

SiegeDockingBehavior::~SiegeDockingBehavior()
{
	stopDocking();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
