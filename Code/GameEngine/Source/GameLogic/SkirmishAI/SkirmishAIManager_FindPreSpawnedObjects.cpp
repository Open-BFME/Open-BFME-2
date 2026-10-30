// cl: /Ireference/shims/bfmealloc /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// WB E8E070 names SkirmishAIManager::Register. Retail2A9365..2A93F5
// establishes the controller dispatches and unique hero-ID insertion.
// The manager's existing Rva002A8F24 identity and callee spellings are kept
// consistent with its already verified providers and consumers.
// Object +4B0/+74 and template +121 bit10 are native evidence; WB's
// corresponding offsets and flag implementation differ from this target.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <algorithm>
#include <map>

// Preserve STLport's inlined walk without emitting a competing size-profile
// wrapper. stlport_map_int_int.cpp owns the complete retail entry at 0x169ED0.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator++()
{
    _M_node = _Rb_global_inst::_M_increment(_M_node);
    return *this;
}
}
// Keep the inlined node comparison local; this unit's incidental
// tree-base operator!= copy conflicts with the selected provider.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <new>

class Xfer;
class Player;
class CreateAHeroData;
enum ObjectID { OBJECTID_INVALID = 0 };

struct SkirmishRegisterTemplate
{
    unsigned char prefix00[0x121];
    unsigned char kindOf121;
};
class Object
{
public:
    Player *getControllingPlayer() const;
    void *vtable00;
    SkirmishRegisterTemplate *template04;
    unsigned char gap08[0x6c];
    ObjectID id74;
    unsigned char gap78[0x438];
    unsigned char excluded4b0;
};
struct Rva002A8AB1Record
{
    void rva002C6A3D(Object *);
};
class AIStatCollector
{
public:
    void Register(Object *);
    AIStatCollector(Player *);
    unsigned char nativeStorage[0x38];
};
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
typedef bool Bool;
#include "subsystem_interface.h"
// Bind allocator<ObjectID>::deallocate to the kept retail copy.
// Split from SkirmishAIManager.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
namespace _STL { template <> void allocator<ObjectID>::deallocate(ObjectID *, size_t) const; }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_create_node(pair<int const, int> const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@IAEXPAW4Ob:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum ObjectID;
namespace _STL { template <> void vector<ObjectID, allocator<ObjectID> >::_M_insert_overflow(ObjectID *, const ObjectID &, const __false_type &, size_t, bool); }
// Suppress this TU's non-retail copy of ?push_back@?$vector@W4ObjectID@@...: the caller binds
// retail's ICF-shared push_back at 0x002E01C6. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<ObjectID, allocator<ObjectID> >::push_back(const ObjectID &); }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }
class Rva002A8F24 :public SubsystemInterface,public Snapshot
{
public:
    Rva002A8AB1Record *rva002A8AB1(void *);
    void *rva002A8F24(Player *);
    void rva002A9365(Object *);
    void findPreSpawnedObjects();
    void *addNewAIForPlayer(Player *);
    void rva002A95F9();
    virtual ~Rva002A8F24();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
private:
    unsigned char prefix00[0x860-0x10];
    bool forceAI860;
    unsigned char gap861[0x908-0x861];
    _STL::map<int,int> collectors908;
    _STL::vector<const class ModuleData *> teams914;
    unsigned char builders920[0x14];
    _STL::vector<ObjectID> heroIDs934;
    class ObjectCreationList *owned940;
};

void Rva002A8F24::rva002A9365(Object *object)
{
    if (object->excluded4b0)
        return;
    Rva002A8AB1Record *record = rva002A8AB1(object->getControllingPlayer());
    if (record)
        record->rva002C6A3D(object);
    AIStatCollector *collector = static_cast<AIStatCollector *>(rva002A8F24(object->getControllingPlayer()));
    if (collector)
        collector->Register(object);
    if (!(object->template04->kindOf121 & 0x10))
        return;
    ObjectID id = object->id74;
    ObjectID *end = heroIDs934.end();
    CreateAHeroData **found = _STL::find(reinterpret_cast<CreateAHeroData **>(heroIDs934.begin()),
        reinterpret_cast<CreateAHeroData **>(end), reinterpret_cast<CreateAHeroData *&>(id));
    if (reinterpret_cast<ObjectID *>(found) == end)
    {
        ObjectID appendID = object->id74;
        heroIDs934.push_back(appendID);
    }
}

// WB E8D510 and native 2A9411..2A9476: iterate every AI player's default
// team and register its members. The 24-byte iterator ABI is independently
// established by TeamIterateTeamMemberList.cpp; target default team is +2EC.
template<class OBJCLASS> class DLINK_ITERATOR {
    OBJCLASS *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};
#include "../../../Include/Common/TeamBFME2.h"
class Player {
public:
    bool rva002AA245() const;
    unsigned char prefix00[0x2ec];
    Team *defaultTeam2ec;
};
class PlayerList {
public:
    Player *getNthPlayer(int);
    unsigned char prefix00[0x14];
    int playerCount14;
};
extern PlayerList *ThePlayerList;
void Rva002A8F24::findPreSpawnedObjects() {
    for (int i=0; i<ThePlayerList->playerCount14; ++i) {
        Player *player=ThePlayerList->getNthPlayer(i);
        if (player->rva002AA245()) {
            for (DLINK_ITERATOR<Object> it=player->defaultTeam2ec->iterate_TeamMemberList();
                !it.done(); it.advance())
                rva002A9365(it.cur());
        }
    }
}

class GameInfo {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual bool slot48();
    virtual bool slot4c();
};
extern GameInfo *TheGameInfo;
class GameLogic;
extern GameLogic *TheGameLogic;
class Rva0023C6A4 { public: bool rva00200084(); };
void Rva004ECE14Clear();
class AIGameTeam { public: void rva004E94FB();void rva004E951C(void*); };
// WB E8D0A0 names newMap. Native2A95F9..2A9706 preserves the
// multiplayer/replay guards and AI/collector split before team startup.
// addNewAIForPlayer remains a separately banked unconverted dependency.
void Rva002A8F24::rva002A95F9() {
    if (!TheGameInfo || (!TheGameInfo->slot48() && !TheGameInfo->slot4c()) ||
        ((Rva0023C6A4 *)TheGameLogic)->rva00200084())
        return;
    Rva004ECE14Clear();
    for (int i=0; i<ThePlayerList->playerCount14; ++i) {
        Player *player=ThePlayerList->getNthPlayer(i);
        if (player->rva002AA245()) {
            if (*(int *)((char *)player+0x5c)==1 || forceAI860)
                addNewAIForPlayer(player);
            else {
                AIStatCollector *collector=new AIStatCollector(player);
                int id=*(int *)((char *)player+0x54);
                collectors908[id]=(int)collector;
            }
        }
    }
    for (const ModuleData **it=teams914.begin(); it!=teams914.end(); ++it)
        ((AIGameTeam *)*it)->rva004E94FB();
    findPreSpawnedObjects();
}

// Native manager snapshot pass; version min1/current2, CRC bail then farm/wall
// shared libraries, every owned team, and every collector with version pointer.
struct ManagerVersion { ManagerVersion(unsigned char a,unsigned char b):min(a),current(b){} unsigned char min,current; };
struct ManagerXferHead {virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();virtual bool slot10() const;};
template<int N>struct ManagerXferSlots:ManagerXferSlots<N-1>{virtual void gap(char(*)[N]);};
template<>struct ManagerXferSlots<0>:ManagerXferHead{};
struct ManagerXferView:ManagerXferSlots<5>{virtual void version(ManagerVersion*);};
class AIEconomyBuilder {public:static void DoXferFarmLibrary(Xfer*);};
void Rva004E99F1Xfer(Xfer*);
class Rva004DFA0E {public:void rva004DFA0E(void*,void*);};

