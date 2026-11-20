// cl: /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00373158@MineshaftPortalNetworkManager@@QAEXPAVRva00373373Portal@@H@Z @0x00373158 115B.
// Portal-network link step of the mineshaft portal manager (the 0x3731CB removal
// sibling and 0x373294 caller live in MineshaftPortalBehaviourPoolKey.cpp): links
// the portal with every other portal of its network group, then lets the
// pathfinder re-evaluate it. Retail keeps an EBP frame here (/Oy-), unlike the
// rest of that unit, so the body has its own TU. The pathfinder receiver of the
// 0x2E9042 call is an equal-arm conditional (late-folded ?:), which reproduces
// retail's argument register order (W7-R1's lever, found by W7-S2's sweep).
#include <vector>
#include <map>
#define BFME_SUBSYSTEM_SLOTS
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Common/GameLogicObjectLookupView.h"
class Rva00373373Portal
{
public:
	virtual void *destroy(unsigned int flags);
	unsigned int id; // +0x04
	char m_pad08[0x4];
	float x; // +0x0C
	float y; // +0x10
	float z; // +0x14
};
#include "../../../../Include/GameLogic/Module/Rva00372CA8.h"
#include "../../../../Include/GameLogic/Module/Rva002E9042.h"
#include "../../../../Include/Common/Rva004618D4Caller.h"
class AI { public: char pad[0x10]; Rva002E9042 *pathfinder; };
extern AI *TheAI;
#include "../../../../Include/GameLogic/TerrainLogic.h"
struct Rva00373158Group : public _STL::vector<ObjectID> { bool changed; };
struct Rva00373158Node { char pad[0x14]; Rva00373158Group *group; };

// The player-keyed map's lookup is the rowed STLport map<int,int> _M_find<int> 0x00388F63.
typedef _STL::pair<const int, int> IntIntPair;
typedef _STL::_Rb_tree<int, IntIntPair, _STL::_Select1st<IntIntPair>, _STL::less<int>, _STL::allocator<IntIntPair> > MapIntIntTree;
// Keep the existing out-of-line signed-key lookup; find exposes its iterator.
template <> template <class Key> _STL::_Rb_tree_node<IntIntPair> *
MapIntIntTree::_M_find(const Key &) const;
class Rva0037381CMap {
public:
    void *header;
    unsigned int count;
};
#include "../../../../Include/Common/Player.h"
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
// Manager map10/count14 and group vector0/changedC are target facts.
// Terrain slot8C and reciprocal372CA8 removal establish portal-network maintenance.
void MineshaftPortalNetworkManager::rva00373158(Rva00373373Portal *portal, int key)
{
    Rva00373158Group *group = ((Rva00373158Node *)((MapIntIntTree *)&m_map)->find(key)._M_node)->group;
    Rva00373373Portal &current=*portal;
    ObjectID *end = group->end();
    for (ObjectID *it=group->begin(); it!=end; ++it) {
        if ((unsigned)*it != current.id) {
            key=(int)TheTerrainLogic->getWaypointByID((unsigned)*it);
            ((Rva00372CA8 *)key)->remove((int)&current);
            ((Rva00372CA8 *)&current)->remove(key);
        }
    }
    (TheTerrainLogic ? TheAI->pathfinder : TheAI->pathfinder)->rva002E9042(portal);
    ((Rva004618D4Caller *)TheAI->pathfinder)->rva002E7023();
}
