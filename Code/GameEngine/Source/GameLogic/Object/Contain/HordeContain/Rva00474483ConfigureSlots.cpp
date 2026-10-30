// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport46
// Native 474483..474517 RET4: definition20C pointer vector, owner270 pointer
// vector, allocate8 {resolved-template,slot}, 474431 position and key0, then
// 2D06CA name lookup on TheThingFactory. The following HordeContain formation
// builder calls this with its definition4 when vector20C is nonempty. Target
// offsets and ownership come from retail; no original member name is asserted.
// vector<>::_M_insert_overflow inlines max(size(), n). Retail never calls
// _STL::max<unsigned> (0x00013740 has no call site), but cl 13.10 still emits
// the template's COMDAT, and under /O1 /G7 it is not retail's blend body. A
// file-static unsigned overload takes the call instead: no external max copy
// (the SubsystemInterface.cpp recipe).
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <functional>
// Retail's out-of-line less<int>::operator() is the speed-form copy stlport_list_int.cpp emits;
// this /O1 unit inlines it but, imported, emits no copy of its own.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<int>::operator()(const int &x, const int &y) const { return x < y; }
}
#include <vector>

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
#include <list>
// Keep the inlined node comparison local; this unit's incidental
// tree-base operator!= copy conflicts with the selected provider.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <new>
// Keep integer construction inline; stlport_deque_int.cpp owns retail's
// out-of-line _Construct<int, int> body at 0x00620140.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void _Construct<int, int>(int *p, const int &value) { new (p) int(value); }
}
#include "../../../../../../Libraries/Include/Lib/Coord2D.h"
#include "ascii_string.h"
class ThingTemplate;
class ThingFactory;
extern ThingFactory *TheThingFactory;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); };
struct Rva00474431Pair { int m_00, m_04; };
struct Rva00474483Input { AsciiString name; Rva00474431Pair position; };
// Native474519..474842 RET4 views. Target offsets come from retail; no original
// member or type name is asserted.
struct Rva00474519Jitter {
 float x,y;
 // ?Rva00474519Jitter::Rva00474519Jitter present-unmatched
 __forceinline Rva00474519Jitter(const Rva00474519Jitter &other) :x(other.x),y(other.y) {}
};
struct Rva00474519Position { Coord2D position; int partner,localIndex; };
struct HordeRankInfo { int key; AsciiString name; _STL::vector<Rva00474519Position> positions; };
struct Rva00474519RecordValues { int key; Coord2D position,original; float value; unsigned partner; };
class Rva00064640Record {
public:
 // ?Rva00064640Record::Rva00064640Record present-unmatched
 __forceinline Rva00064640Record() : m_00(0),m_14(0),m_18(-1) {}
 Rva00064640Record(const Rva00064640Record &);
 int m_00,m_04,m_08,m_0C; float m_10,m_14; unsigned m_18;
};
namespace _STL { template<> void _Construct<Rva00064640Record,Rva00064640Record>(Rva00064640Record*,const Rva00064640Record&); }
struct Rva00474483Definition {
 char opaque00[0x18c]; _STL::vector<HordeRankInfo*> ranks;
 char opaque198[0x1d0-0x198]; Rva00474519Jitter jitter;
 char opaque1d8[0x1f4-0x1d8]; _STL::vector<int> extraSlots;
 Rva00474431Pair extraPosition;
 char opaque208[4]; _STL::vector<Rva00474483Input*> entries;
 _STL::vector<int> specialSlots;
};
struct Rva00474483Entry {
 // ?Rva00474483Entry::Rva00474483Entry present-unmatched
 __forceinline Rva00474483Entry() : target(0), slot(-1) {}
 void *target; int slot;
};
// 8-byte conditional descriptor returned by the rowed 46247D pair out-copy twin.
#include "../../../../../Include/GameLogic/ContainmentListView.h"
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_empty_initialize(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::clear(); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$a:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::_Rb_tree(const less<int> &, const allocator<pair<const int, int> > &); }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }
class Rva0046247DDescriptor { public: Rva0036AE51ListView rva0046247D(); };
// Native 4746E5/474713: the returned conditional descriptor is a guarded
// temporary - retail writes the constructed flag ([ebp-0x18] |= 1 before the
// call, test/clear after the full condition); the view's empty destructor
// (ContainmentListView.h) gives it.
// 12-byte rank->first-record map view. Native 474597/4745D6 construct and
// subscript it through the rowed tree members; the 47482C destruction is the
// rowed 0022C612 container destructor (clear 0022999F, header free 00030830).
class Rva00226883 {
public:
 ~Rva00226883();
 _STL::map<int,int> m_tree;
};
class Rva004693D9 { public: void rva004693D9(); };
class Rva00474519Notifier { public: virtual void unused0(); virtual void resize(int); };
int GetGameLogicRandomValue(int,int,char*,int);
class Rva00474431 {
public:
 int rva00474431(const Rva00474431Pair &, int);
 void rva00474483(Rva00474483Definition *);
 void rva00474519(int);
 void *vptr; Rva00474483Definition *definition;
 char opaque008[0x174-8]; int field174;
 char opaque178[4]; _STL::map<int,int> occupied;
 _STL::vector<Rva00064640Record> records;
 _STL::list<int> available;
 bool ready;
 char opaque199[0x268-0x199]; int extraIndex;
 char opaque26c[4]; _STL::vector<Rva00474483Entry*> entries;
 char opaque27c[0x2c8-0x27c]; Rva00474519Notifier *notifier;
};
void Rva00474431::rva00474483(Rva00474483Definition *definition)
{
 for (unsigned i=0; i<definition->entries.size(); ++i) {
  Rva00474483Entry *entry = new Rva00474483Entry;
  entry->slot = rva00474431(definition->entries[i]->position, 0);
  entry->target = (void *)TheThingFactory->findTemplate(definition->entries[i]->name);
  entries.push_back(entry);
 }
}
// BF1 f98983a7 Rva00245010RecordBuild is the semantic/structural guide.
// Native474519..474842 RET4 supplies target rank16 records, per-rank map,
// partner linkage, occupied slot exclusion, notifier and exact jitter strings.
void Rva00474431::rva00474519(int force)
{
 Rva00474483Definition *data=definition;
 const _STL::vector<HordeRankInfo*> &ranks=data->ranks;
 int total=0; unsigned i=0; unsigned count=ranks.size();
 for(;i<count;++i) total+=ranks[i]->positions.size();
 _STL::vector<Rva00064640Record> &recordList=records;
 recordList.reserve(total);
 Rva00474519Jitter jitter=data->jitter;
 Rva00226883 starts;
 for(i=0;i<ranks.size();++i) {
  int key=ranks[i]->key;
  const _STL::vector<Rva00474519Position> &positions=ranks[i]->positions;
  starts.m_tree[key]=(int)recordList.size();
  for(unsigned j=0;j<positions.size();++j) {
   const Rva00474519Position &pos=positions[j];
   {
   Rva00474519RecordValues record;
   record.position=pos.position;record.key=key;
   if(jitter.x>0) record.position.x += GetGameLogicRandomValue((int)-jitter.x,(int)jitter.x,
    "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",1532);
   if(jitter.y>0) record.position.y += GetGameLogicRandomValue((int)-jitter.y,(int)jitter.y,
    "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",1536);
   record.original=record.position;record.value=0;
   if(pos.partner!=-1) record.partner=starts.m_tree[pos.partner]+pos.localIndex;
   else record.partner=-1;
   recordList.push_back(*(const Rva00064640Record*)&record);
   }
   if(force || (((const _STL::list<void*> *)((Rva0046247DDescriptor *)this)->rva0046247D().b)->empty() && field174==0)) {
    _STL::map<int,int>::iterator it=occupied.begin();
    for(;it!=occupied.end();++it) if(it->second==recordList.size()-1) break;
    if(it==occupied.end()) available.push_back(recordList.size()-1);
   }
  }
 }
 notifier->resize(recordList.size());
 if(!data->extraSlots.empty()) extraIndex=rva00474431(data->extraPosition,0);
 if(!data->specialSlots.empty()) rva00474483(data);
 ((Rva004693D9*)this)->rva004693D9();ready=true;
}
