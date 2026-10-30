// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// ??1LifeEventModuleInfo@FXParticleSystem@@UAE@XZ @0x003A9F8A 48B
// Dtor releasing StringBase<char> at +4 via rowed releaseBuffer 0x00036410
// plus Snapshot base BBB554. Evidence: EH_prolog with handler 0x00781D33
// plus single releaseBuffer call plus BBB554 store, layout from
// LifeEventModuleInfoCopyCtorThunk, ghidra ~LifeEventModuleInfo.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"



#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"

namespace FXParticleSystem
{
class __declspec(novtable) LifeEventModuleInfo : public Snapshot
{
public:
	virtual ~LifeEventModuleInfo();
private:
	StringBase<char> m_name;
	int m_values[3];
	int m_eventType;
};
}

FXParticleSystem::LifeEventModuleInfo::~LifeEventModuleInfo()
{
}

// Retail exports fold TerrainCollision into the same48B primary cleanup.
// Its independently verified ctor56459E places the owned narrow string at4;
// the random-variable and trailing scalar fields are trivially destructible.
// Like LifeEvent above, retail omits the transient derived-vptr store.
namespace FXParticleSystem {
class __declspec(novtable) TerrainCollisionModuleInfo : public Snapshot
{
public:
    virtual ~TerrainCollisionModuleInfo();
    virtual void LoadPostProcess();
    virtual const char *GetSnapshotName();
    virtual void DoXfer(::Xfer &);
private:
    StringBase<char> m_name;
    int m_randomVariable[3];
    bool m_flag14;
    int m_18;
};
TerrainCollisionModuleInfo::~TerrainCollisionModuleInfo() {}
void TerrainCollisionModuleInfo::LoadPostProcess() {}
}
