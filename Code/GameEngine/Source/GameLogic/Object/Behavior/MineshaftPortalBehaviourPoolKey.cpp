// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva000373109@MineshaftPortalBehaviour@@SA?AW4NameKeyType@@XZ @0x373109
// (69B): cached pool-name key for MineshaftPortalBehaviour. The class
// identity comes from the pool-name string the body pushes
// ("MineshaftPortalBehaviour"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

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

class MineshaftPortalBehaviour
{
public:
	static NameKeyType rva000373109();
};

// ?rva000373109@MineshaftPortalBehaviour@@SA?AW4NameKeyType@@XZ
NameKeyType MineshaftPortalBehaviour::rva000373109()
{
	static NameKeyType TheMineshaftPortalBehaviourPoolKey =
		TheNameKeyGenerator->nameToKey("MineshaftPortalBehaviour");
	return TheMineshaftPortalBehaviourPoolKey;
}

struct TreeOpaqueMapped00372FF4;
namespace _STL {
template <class T1, class T2> struct pair;
template <class T> struct _Select1st;
template <class T> struct less;
template <class T> class allocator;
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree {
public:
	~_Rb_tree();
};
typedef pair<const float, TreeOpaqueMapped00372FF4> TreeValue00372FF4;
typedef _Rb_tree<float, TreeValue00372FF4, _Select1st<TreeValue00372FF4>, less<float>, allocator<TreeValue00372FF4> > Tree00372FF4;
}

class Rva0037314E
{
public:
	void rva0037314E();
};

void Rva0037314E::rva0037314E()
{
	((_STL::Tree00372FF4 *)this)->~_Rb_tree();
}

class Rva00372F00
{
public:
	~Rva00372F00();
};

class Rva00373153
{
public:
	void rva00373153();
};

void Rva00373153::rva00373153()
{
	((Rva00372F00 *)this)->~Rva00372F00();
}

#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
class Rva00373373Portal {
public:
    virtual void *destroy(unsigned int flags);
    unsigned int id;
};
class Rva002E6ECA { public: int get() const; };
class Rva00372CA8 { public: void rva00372CA8(int value); };
class Rva002E9042 { public: void rva002E9042(void *portal); };
class Rva004618D4Caller { public: void rva002E7023(); };
class AI { public: char pad[0x10]; Rva002E9042 *pathfinder; };
extern AI *TheAI;
class TerrainLogic {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual Rva00373373Portal *portalAt(unsigned int id);
};
extern TerrainLogic *TheTerrainLogic;
struct Rva00373158Group : public _STL::vector<ObjectID> { bool changed; };
struct Rva00373158Node { char pad[0x14]; Rva00373158Group *group; };
class Rva00388F63Map {
public:
    void *find(int *key);
    void *header;
    unsigned int count;
};
class Player { public: char pad[0x54]; int key; };
class Rva0037381C {
public:
    void rva00373158(Rva00373373Portal *portal, int key);
    void rva003731CB(Rva00373373Portal *portal, Player *player);
private:
    char pad[0x10]; Rva00388F63Map map;
};
// Manager map10/count14 and group vector0/changedC are target facts.
// Terrain slot8C and reciprocal372CA8 removal establish portal-network maintenance.
void Rva0037381C::rva003731CB(Rva00373373Portal *portal, Player *player)
{
    if (map.count) {
        int key=player->key;
        Rva00373158Node *node=(Rva00373158Node *)map.find(&key);
        if (node != map.header) {
            Rva00373158Group *group=node->group;
            for (ObjectID *it=group->begin(); it!=group->end();) {
                unsigned id=(unsigned)*it;
                if (id==portal->id) {
                    it=group->erase(it);
                    node->group->changed=true;
                } else {
                    if ((unsigned char)((Rva002E6ECA *)portal)->get()) {
                        Rva00373373Portal *other=TheTerrainLogic->portalAt(id);
                        ((Rva00372CA8 *)other)->rva00372CA8((int)portal);
                    }
                    ++it;
                }
                group=node->group;
            }
        }
    }
    if ((unsigned char)((Rva002E6ECA *)portal)->get()) {
        TheAI->pathfinder->rva002E9042(portal);
        ((Rva004618D4Caller *)TheAI->pathfinder)->rva002E7023();
    }
}

// MineshaftPortalNetworkManager's snapshot transfer, native 003732BF..00373357
// RET4: the vtable slot (00817E10) after the "MineshaftPortalNetworkManager"
// name getter 00373411, reached through the Snapshot sub-object at +0C.
// Version 1/1; on load every player's network is marked changed and each of
// its portals whose 002E6ECA test passes is re-linked through 00373158 with
// the network's player key. The map nodes are the 0x10 key / 0x14 group
// records 003731CB already reads.
namespace _STL {
struct _Rb_tree_node_base { int _M_color; _Rb_tree_node_base *_M_parent, *_M_left, *_M_right; };
template <class _Dummy> class _Rb_global
{
public:
    static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}
class Xfer
{
public:
    struct Version { unsigned char a, b; Version(unsigned char x, unsigned char y) : a(x), b(y) {} };
    virtual void slot00();
    virtual bool IsLoading() const;
    virtual void slot02(); virtual void slot03(); virtual void slot04();
    virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09();
    virtual Xfer &xferVersion(Version &);
};
class Rva003732BFSubsystem { public: virtual ~Rva003732BFSubsystem(); char pad04[8]; };
class Rva003732BFSnapshot
{
protected:
    virtual void crc(Xfer *xfer);
    virtual void xfer(Xfer *xfer) = 0;
    virtual void loadPostProcess();
};
struct Rva003732BFNode : _STL::_Rb_tree_node_base { int key; Rva00373158Group *group; };
class MineshaftPortalNetworkManager : public Rva003732BFSubsystem, public Rva003732BFSnapshot
{
public:
    virtual void xfer(Xfer *xfer);
    Rva00388F63Map map;
};
void MineshaftPortalNetworkManager::xfer(Xfer *xfer)
{
    Xfer::Version version(1, 1);
    xfer->xferVersion(version);
    if (xfer->IsLoading()) {
        _STL::_Rb_tree_node_base *header = (_STL::_Rb_tree_node_base *)map.header;
        for (Rva003732BFNode *node = (Rva003732BFNode *)header->_M_left; node != header;
             node = (Rva003732BFNode *)_STL::_Rb_global<bool>::_M_increment(node)) {
            node->group->changed = true;
            ObjectID *end = node->group->end();
            for (ObjectID *it = node->group->begin(); it != end; ++it) {
                Rva00373373Portal *portal = TheTerrainLogic->portalAt(*it);
                if ((unsigned char)((Rva002E6ECA *)portal)->get())
                    ((Rva0037381C *)this)->rva00373158(portal, node->key);
            }
        }
    }
}
