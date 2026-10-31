// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/GameEngine/Include/GameLogic /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
//
// ?update@MineshaftPortalNetworkManager@@UAEXXZ @0x003734FD (670B).
// Native 3734FD..37379B and WB MineshaftPortalNetworkManager::update (wpA/wpB
// asserts at MineshaftPortalBehaviour.cpp:337..395; the registration calls and
// asserts are compiled out of retail). For every portal network (the map at
// +0x10: key at node+0x10, group at node+0x14) whose group is flagged changed:
// clear the flag, score every portal of the group by the mean squared 2D
// distance to the others (portal slot 0x8C of TheTerrainLogic, position at
// +0xC/+0x10) and keep the three highest scores in a float-keyed multimap
// (insert_equal 0x004EA301, erase 0x005530A8 of the folded POD tree, dtor
// 0x00372FBC). A portal that is not kept is re-linked through 0x00373158 when
// its 0x002E6ECA test passes, as is each evicted one. Then every kept portal is
// linked to every other kept one (hasLink 0x00372CEC, addLink 0x00272306) and
// handed to the pathfinder (0x002E8FE5) when the 0x002E6ECA test fails.
// The map ctor is the ICF-folded 12-byte empty-tree body 0x0033C432; the
// local's dtor is the rowed 0x00372FBC.
// Evicting the smallest score goes through a throw() helper: without it the
// by-value iterator argument of the erase call saves ESP, which retail does not.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <set>
#include <vector>
#include <new>
#include "../../../Common/GameLogicObjectLookupView.h"

namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree<int, pair<const int, void *>, _Select1st<pair<const int, void *> >, less<int>, allocator<pair<const int, void *> > >::~_Rb_tree()
{ clear(); }
}
struct TreeOpaqueMapped00372FF4 { unsigned int m_bits; };
typedef _STL::pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _STL::_Rb_tree<float, TreeValue00372FF4, _STL::_Select1st<TreeValue00372FF4>, _STL::less<float>, _STL::allocator<TreeValue00372FF4> > Tree00372FF4;
typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > SetIntTree;

class Rva00372F00 { public: ~Rva00372F00(); };

struct LocalTree {
    void *header;
    unsigned int count;
    int pad;
    __forceinline LocalTree() { ((_STL::map<int, void *> *)this)->_STL::map<int, void *>::map(); }
    __forceinline ~LocalTree() { ((Rva00372F00 *)this)->~Rva00372F00(); }
};

static __forceinline void eraseFirst(LocalTree *tree) throw()
{
    ((SetIntTree *)tree)->erase(SetIntTree::iterator((SetIntTree::_Link_type)((_STL::_Rb_tree_node_base *)tree->header)->_M_left));
}
class Rva00373373Portal
{
public:
    virtual void *destroy(unsigned int flags);
    unsigned int id;
    char pad08[4];
    float x, y, z;
};
class Rva002E6ECA { public: int get() const; };
class Rva00372CA8
{
public:
	void rva00372CA8(int value);
	bool rva00372CEC(int value);
};
class AsciiString;
struct Coord3D;
class Waypoint
{
public:
	Waypoint(unsigned int id, AsciiString name, const Coord3D *pLoc, AsciiString label1, AsciiString label2, AsciiString label3, bool biDirectional, int bfmeType, AsciiString bfmeName);
	__forceinline int getID() const { return id; }
	void addLink(Waypoint *other);
	char m_pad00[0x4];
	int id; // +0x04
	char m_pad08[0x40];
	unsigned char m_48; // +0x48
	char m_pad49[0x5F];
	unsigned char m_A8; // +0xA8
	unsigned char m_A9; // +0xA9
	char m_padAA[0x6];
	int m_B0; // +0xB0
	char m_padB4[0xC];
};
class Rva002E9042
{
public:
	void rva002E9042(void *portal);
	void AddPortal(void *portal);
};
class AI { public: char pad[0x10]; Rva002E9042 *pathfinder; };
extern AI *TheAI;
class TerrainLogic {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34();
    virtual Rva00373373Portal *portalAt(unsigned int id);
};
extern TerrainLogic *TheTerrainLogic;

struct NetGroup : public _STL::vector<ObjectID> { bool changed; };
struct NetNode : _STL::_Rb_tree_node_base { int key; NetGroup *group; };
struct TreeNode : _STL::_Rb_tree_node_base { float key; ObjectID id; };

class Rva0037381CMap { public: void *header; unsigned int count; };
class Player;
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "Common/Snapshot.h"
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
    _STL::map<int, void *> m_map;
};

void MineshaftPortalNetworkManager::update()
{
    _STL::_Rb_tree_node_base *mapHeader = (_STL::_Rb_tree_node_base *)((Rva0037381CMap *)&m_map)->header;
    for (NetNode *node = (NetNode *)mapHeader->_M_left; node != (NetNode *)mapHeader;
         node = (NetNode *)_STL::_Rb_global<bool>::_M_increment(node)) {
        if (!node->group->changed)
            continue;
        node->group->changed = false;
        LocalTree tree;
        ObjectID *end = node->group->end();
        for (ObjectID *it = node->group->begin(); it != end; ++it) {
            Rva00373373Portal *portal = TheTerrainLogic->portalAt(*it);
            float sum = 0.0f;
            for (ObjectID *jt = node->group->begin(); jt != end; ++jt) {
                if (*it != *jt) {
                    Rva00373373Portal *other = TheTerrainLogic->portalAt(*jt);
                    float dx = portal->x - other->x;
                    float dy = portal->y - other->y;
                    sum += dy * dy + dx * dx;
                }
            }
            if (node->group->size() > 1)
                sum /= (float)(node->group->size() - 1);
            if (tree.count == 0 || tree.count < 3) {
                TreeOpaqueMapped00372FF4 m = { (unsigned)*it };
                TreeValue00372FF4 v(sum, m);
                ((Tree00372FF4 *)&tree)->insert_equal(v);
            } else {
                if (sum > ((TreeNode *)((_STL::_Rb_tree_node_base *)tree.header)->_M_left)->key) {
                    Rva00373373Portal *old = TheTerrainLogic->portalAt(((TreeNode *)((_STL::_Rb_tree_node_base *)tree.header)->_M_left)->id);
                    if ((unsigned char)((Rva002E6ECA *)old)->get())
                        rva00373158(old, node->key);
                    eraseFirst(&tree);
                    TreeOpaqueMapped00372FF4 m = { (unsigned)*it };
                    TreeValue00372FF4 v(sum, m);
                    ((Tree00372FF4 *)&tree)->insert_equal(v);
                } else {
                    if ((unsigned char)((Rva002E6ECA *)portal)->get())
                        rva00373158(portal, node->key);
                }
            }
        }
        _STL::_Rb_tree_node_base *treeHeader = (_STL::_Rb_tree_node_base *)tree.header;
        for (TreeNode *treeNode = (TreeNode *)treeHeader->_M_left; treeNode != (TreeNode *)treeHeader;
             treeNode = (TreeNode *)_STL::_Rb_global<bool>::_M_increment(treeNode)) {
            Rva00373373Portal *wa = TheTerrainLogic->portalAt(treeNode->id);
            for (TreeNode *b = (TreeNode *)((_STL::_Rb_tree_node_base *)tree.header)->_M_left; b != (TreeNode *)treeHeader;
                 b = (TreeNode *)_STL::_Rb_global<bool>::_M_increment(b)) {
                Rva00373373Portal *wb = TheTerrainLogic->portalAt(b->id);
                if (wa != wb) {
                    if (!((Rva00372CA8 *)wa)->rva00372CEC((int)wb)) {
                        ((Waypoint *)wa)->addLink((Waypoint *)wb);
                        ((Waypoint *)wb)->addLink((Waypoint *)wa);
                    }
                    if (!(unsigned char)((Rva002E6ECA *)wa)->get())
                        TheAI->pathfinder->AddPortal(wa);
                    if (!(unsigned char)((Rva002E6ECA *)wb)->get())
                        TheAI->pathfinder->AddPortal(wb);
                }
            }
        }
    }
}
