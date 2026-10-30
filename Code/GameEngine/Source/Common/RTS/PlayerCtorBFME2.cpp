// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Player constructor semantic donor: BF1 f98983a7d Player.cpp399-459 and
// ZH Player.cpp303-362. Target init2AF729 establishes field meanings;
// native2B0F3C establishes initialization order and three base views.
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include "ascii_string.h"
#include "unicode_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <hash_map>
#include <list>
#include <vector>
// vector<unsigned int>'s allocator constructor inlines at every use here;
// imported force-inline so this unit emits no COMDAT copy of it (its copy
// differs from retail's kept /Od body at 0x00025100). The vector base
// constructor stays a declared nothrow call to its kept copy (0x00211E58).
namespace _STL {
template <> _Vector_base<unsigned int,allocator<unsigned int> >::_Vector_base(const allocator<unsigned int> &) throw();
template <> __declspec(dllimport) __forceinline
vector<unsigned int, allocator<unsigned int> >::vector(const allocator<unsigned int> &__a)
	: _Vector_base<unsigned int, allocator<unsigned int> >(__a) {}
}
#include <cstddef>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}
#define BFME_SNAPSHOT_NAME_SLOT
#include "reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
class Player;
class PlayerTemplate;
class Rva002B0F3CIface {
public:
 Rva002B0F3CIface() {} ~Rva002B0F3CIface() {}
 virtual void v0()=0; virtual void v1()=0; virtual void v2()=0;
};
class ExperienceScalarTable;
class Rva00380200 {
public:
 Rva00380200(); virtual ~Rva00380200() {}
 virtual bool rva0038037C(int); virtual void slot2();
 virtual void resetRank(); virtual void onRank(void*); virtual bool isReady();
private:
 AsciiString *m_ptr; ExperienceScalarTable *m_scalars;
 float m_0C,m_10; int m_14,m_18,m_1C,m_20,m_24,m_28;
};
class Rva003B0E83 {public:Rva003B0E83*rva003B0E83();};
struct HandicapView {float values[4];HandicapView(){((Rva003B0E83*)this)->rva003B0E83();}};
class Rva002AE5EB {
public: Rva002AE5EB() throw(); virtual ~Rva002AE5EB();
private: int words[10]; bool flag;
};
class S3Money : public Snapshot {
public:
 S3Money():money(0),owner(0){} virtual ~S3Money() {}
 virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 int money,owner;
};
class Rva001EAE6FHelper {public:Rva001EAE6FHelper*clear80() throw();};
struct Rva002B0F3CUpgradeMask {unsigned words[32];Rva002B0F3CUpgradeMask() throw(){((Rva001EAE6FHelper*)this)->clear80();}};
// Scope the target 16-byte energy member: the older EnergyConstructorThunk
// emits a different 20-byte ABI at808880 and cannot provide this member.
class Rva002B0F3CEnergy : public Snapshot {
public:
 Rva002B0F3CEnergy():production(0),consumption(0),owner(0){} virtual ~Rva002B0F3CEnergy() {}
 virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 int production,consumption;Player*owner;
};
class Rva004F599E : public Snapshot {public:Rva004F599E();virtual ~Rva004F599E();virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);int words[42];};
struct Rva001FEAB2Element {char bytes[1];};
struct Rva002AF438Element {char bytes[8];Rva002AF438Element();Rva002AF438Element(const Rva002AF438Element&);~Rva002AF438Element(){} };
#include "Code/Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL {
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@HU?$pair@$$CBHPAX@_STL@@U?$_Select1st@U?$pair@$$CBHPAX@_STL@@@2@U?$less@H@2@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree<int,pair<int const ,void *>,_Select1st<pair<int const ,void *> >,less<int>,allocator<pair<int const ,void *> > >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ?_M_next_size@?$hashtable@U?$pair@$$CBHURva001FEAB2Element@@@_STL@@HU?$hash@H@2@U?$_Select:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001FEAB2Element;
namespace _STL { template <> unsigned int hashtable<pair<int const ,Rva001FEAB2Element>,int,hash<int>,_Select1st<pair<int const ,Rva001FEAB2Element> >,equal_to<int>,allocator<pair<int const ,Rva001FEAB2Element> > >::_M_next_size(unsigned int) const; }
// Native ctor2AC340/dtor2AC366: Snapshot vptr, int+4, BfmeE16 vector+8.
class Rva002AC340 : public Snapshot {
 friend class Player;
public: Rva002AC340() throw();
protected: virtual ~Rva002AC340();
 virtual void loadPostProcess(); virtual const char *GetSnapshotName() const; virtual void xfer(Xfer *);
private: int m_int; _STL::vector<BfmeE16> m_vec;
};
// Native pool-list lifetime wrapper2AC007 destroys the sentinel from init2AC026.
class Rva002AAC74PoolList { public: void destroy() throw(); };
class Rva002AC026Member {
public:
 void*head;void*init(void*);
 Rva002AC026Member(const _STL::allocator<int>&a){init((void*)&a);}
 ~Rva002AC026Member(){((Rva002AAC74PoolList*)this)->destroy();}
};
class Rva0029FB3BMember {
public:
 void*head;void*init(void*);
 Rva0029FB3BMember(const _STL::allocator<int>&a){init((void*)&a);}
 ~Rva0029FB3BMember();
};
// Destructor2B11A7 and vector cleanup2B0EDF establish the +3B0 record vector.
struct BfmeVectorRecord002AF478 { ~BfmeVectorRecord002AF478(); char bytes[36]; };
namespace _STL { template <> vector<BfmeVectorRecord002AF478>::~vector(); }
class ScoreKeeper {public:ScoreKeeper();virtual ~ScoreKeeper();private:unsigned words[0x330/4];};
struct ReadyTimer {int power,ready;};
struct ProductionCostModifier;
class UnitRevivalTracker {public:UnitRevivalTracker(Player*);virtual ~UnitRevivalTracker();private:unsigned words[4];};
class Squad;
class Player : public Snapshot, public Rva002B0F3CIface, public Rva00380200 {
public:
 Player(int);virtual ~Player();
 virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 virtual void v0();virtual void v1();virtual void v2();
 virtual bool rva0038037C(int);virtual void slot2();virtual void resetRank();virtual void onRank(void*);virtual bool isReady();
 void init(const PlayerTemplate*);
 const PlayerTemplate*tmplate;UnicodeString displayName;HandicapView handicap;
 AsciiString name;int nameKey,index;AsciiString side;int type;
 Rva002AE5EB r60;S3Money money;void*upgradeList;
 int radar,disableRadar;bool radarDisabled;char gapA9[3];int bombard,hold,search;void*battle;
 Rva002B0F3CUpgradeMask inProgress,completed;Rva002B0F3CEnergy energy;Rva004F599E stats;
 void*buildList;int unknown27C;unsigned color,nightColor;
 _STL::map<int,void*>cost;
 _STL::hash_map<int,Rva001FEAB2Element>time,scratchTime;
 _STL::hash_map<int,Rva002AF438Element>timeCounts;
 _STL::map<int,void*>veterancy;
 void*ai,*defaultTeam,*resources,*tunnel;int unknown2EC;
 _STL::vector<unsigned>sciences,disabled,hidden;float bounty;
 Rva002AC340 r318;
 Rva002AC026Member prototypes;void*playerRelations,*teamRelations;
 bool canBuildBase,canBuildUnits,observer,flag33B,listInScoreScreen,unitsHunt,flag33E,flag33F;
 bool attackedBy[20];int attackedFrame;unsigned attackFrames[20];int unknown3A8,unknown3AC;
 _STL::vector<BfmeVectorRecord002AF478>v3B0;
 ScoreKeeper score;int unknown6F0;
 _STL::list<ProductionCostModifier*>modifiers;float unknown6F8;int unknown6FC;
 _STL::list<int>unknown700;
 _STL::list<ReadyTimer>timers;
 Squad*squads[10];Squad*selection;bool dead,flag735;char gap736[2];
 UnitRevivalTracker revival;AsciiString text74C;void*unknown750;
 Rva0029FB3BMember r754;
};
typedef char PlayerCtorSizeCheck[sizeof(Player)==0x758?1:-1];
Player::Player(int playerIndex):
 index(playerIndex),upgradeList(0),battle(0),buildList(0),ai(0),resources(0),tunnel(0),
 prototypes(_STL::allocator<int>()),playerRelations(0),teamRelations(0),flag33F(false),unknown3AC(-1),
 selection(0),revival(this),unknown750(0),r754(_STL::allocator<int>())
{
 for(int i=0;i<10;++i)squads[i]=0;
 init(0);
}
