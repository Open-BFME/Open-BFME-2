// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/GameEngine/Include/GameLogic /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// MineshaftPortalNetworkManager::hasUsableNetwork (WorldBuilder name, MineshaftPortalBehaviour.cpp line 511: find in the +0x10 network map).
// stlport
//
// was ?rva00373278@Rva00373278@@QAE_NPAX@Z, retail 0x00373278 71B.
// Map lookup plus vector size check: null param plus int key at +0x54 via
// rowed Rb_tree _M_find 0x00388F63 plus empty plus size>1 via sbb/neg.
// Evidence: this+0x10 map plus caller 0x002F7265 plus rowed callee.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// Keep STLport4.5.3's integer comparison inline without a competing copy.
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int& a,const int& b) const
{ return a < b; }
}
#include <vector>

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "Common/Snapshot.h"
class Rva00373373Portal;
class Player;
class Waypoint;
class MineshaftPortalNetworkManager : public SubsystemInterface, public Snapshot
{
public:
    MineshaftPortalNetworkManager();
    virtual ~MineshaftPortalNetworkManager();
    virtual void xfer(Xfer *xfer);
    virtual void reset();
    virtual void update();
    void rva00373158(Rva00373373Portal *portal, int key);
    void rva003731CB(Rva00373373Portal *portal, Player *player);
    bool hasUsableNetwork(void *p);
    void addWaypoint(Waypoint *waypoint, Player *player);
    _STL::map<int, void *> m_map; // +0x10, after the 0xC subsystem base and the Snapshot pointer
};

// The +0x10 map's values are vector<int> pointers (4B, same as int) here.
typedef _STL::map<int, _STL::vector<int, _STL::allocator<int> > *, _STL::less<int>, _STL::allocator<_STL::pair<const int, _STL::vector<int, _STL::allocator<int> > *> > > UsableNetworkMap;

bool MineshaftPortalNetworkManager::hasUsableNetwork(void *p)
{
	if (p == 0)
		return false;
	int key = *(int *)((char *)p + 0x54);
	UsableNetworkMap::iterator it = ((UsableNetworkMap *)&m_map)->find(key);
	if (it == ((UsableNetworkMap *)&m_map)->end())
		return false;
	if (!(*it).second->empty())
		return (*it).second->size() > 1;
	return false;
}
