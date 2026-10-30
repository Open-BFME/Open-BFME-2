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
    // Inline-only target view; do not emit a competing shared accessor copy.
    __declspec(dllimport) __forceinline const class AsciiString &getSide() const { return *(const AsciiString *)side58; }
    int getPlayerIndex() const { return playerIndex54; }
    unsigned char prefix00[0x54];
    int playerIndex54;
    unsigned char side58[0x2ec-0x58];
    Team *defaultTeam2ec;
};
class PlayerList {
public:
    Player *getNthPlayer(int);
    unsigned char prefix00[0x14];
    int playerCount14;
};
extern PlayerList *ThePlayerList;


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
class AIGameTeam { public: void addPlayer(const ModuleData *); void rva004E94FB();void rva004E951C(void*); };


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
void Rva002A8F24::xfer(Xfer* xfer) {
 ManagerXferView*io=reinterpret_cast<ManagerXferView*>(xfer);
 if(io->slot10())return;
 ManagerVersion version(1,2);
 io->version(&version);
 AIEconomyBuilder::DoXferFarmLibrary(xfer);
 Rva004E99F1Xfer(xfer);
 for(const ModuleData**it=teams914.begin();it!=teams914.end();++it)
  reinterpret_cast<AIGameTeam*>(const_cast<ModuleData*>(*it))->rva004E951C(xfer);
 for(_STL::map<int,int>::iterator it=collectors908.begin(),end=collectors908.end();it!=end;++it)
  reinterpret_cast<Rva004DFA0E*>(it->second)->rva004DFA0E(xfer,&version);
}

#include <hash_map>
class AsciiString;
typedef _STL::hash_map<int,AsciiString> DozerMap;
class Rva004E94CA { public: bool rva004E94CA(Player *); };
class Rva004E9600 { public: void *rva004E95D4(void *); };
class Rva004E962A { public: Rva004E962A(); unsigned char nativeStorage[0x28]; };
class ArmorTemplate;
class ArmorStore { public: const ArmorTemplate *rva0041F474(const AsciiString &) const; };
class Rva0022BD25Subsystem;
extern Rva0022BD25Subsystem *TheArmyDefinitionManager;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva002A9140 { public: AsciiString &rva002A9140(const int &); };
class Rva004EC1CE { public: void rva004EC1CE(const AsciiString &); };
// WB E8E370 proves this method and its player/team/army/collector behavior.
// Native 2A9476..2A95B9: preparation of the side reference in each selection
// path preserves the compiler allocation; the common use emits one LEA.
void *Rva002A8F24::addNewAIForPlayer(Player *player) {
    const AsciiString *side;
    void *ai=0;
    for (const ModuleData **it=teams914.begin(), **end=teams914.end(); it!=end; ++it) {
        side=&player->getSide();
        if (((Rva004E94CA *)*it)->rva004E94CA(player)) {
            ((AIGameTeam *)*it)->addPlayer((const ModuleData *)player);
            ai=((Rva004E9600 *)*it)->rva004E95D4(player);
            break;
        }
    }
    if (!ai) {
        Rva004E962A *team=new Rva004E962A;
        ((AIGameTeam *)team)->addPlayer((const ModuleData *)player);
        ai=((Rva004E9600 *)team)->rva004E95D4(player);
        teams914.push_back((const ModuleData *&)team);
        side=&player->getSide();
    }
    if (((ArmorStore *)TheArmyDefinitionManager)->rva0041F474(*side)) {
        int key=TheNameKeyGenerator->nameToKey(*side);
        if (((DozerMap *)builders920)->find(key) != ((DozerMap *)builders920)->end())
            ((Rva004EC1CE *)ai)->rva004EC1CE(((Rva002A9140 *)builders920)->rva002A9140(key));
    } else {
        *(bool *)((char *)ai+0x168)=true;
    }
    AIStatCollector *collector=new AIStatCollector(player);
    collectors908[player->getPlayerIndex()]=(int)collector;
    return ai;
}
