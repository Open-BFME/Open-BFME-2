// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??1MineshaftPortalNetworkManager@@UAE@XZ @0x0037381C (85B).
// Dtor for MI class with SubsystemInterface primary (size 0xC) and empty
// secondary at +0xC, Tree00372FF4 map at +0x10. Calls rowed values-delete
// 0x003734C0 then member and base dtors with EH states 2/1. Caller of 3734C0.
// Vtables 0x00C17E14/0x00C17E04 via gate, base reset to g_00BBB554.
#include <map>

struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;

// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

// The secondary native table C17E04 has Snapshot's four slots; its name
// getter373411 returns MineshaftPortalNetworkManager and xfer3732BF is
// independently recovered. The base restore is canonical Snapshot BBB554.
// This teardown-only view retains the derived address name and does not
// construct a partial virtual interface.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class MineshaftPortalNetworkManager : public SubsystemInterface, public Snapshot
{
public:
	virtual ~MineshaftPortalNetworkManager();
	virtual void reset();
private:
	Tree00372FF4 m_map;
public:
	// retail vftable slot: the rowed override
	virtual void update();
};

// ??1MineshaftPortalNetworkManager@@UAE@XZ
MineshaftPortalNetworkManager::~MineshaftPortalNetworkManager()
{
	MineshaftPortalNetworkManager::reset();
}
