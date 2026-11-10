// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ??0AutoResolve@Data@StrategicVeterancy@@QAE@PAX00@Z @ 0x005ECE81 (327 B)
// Auto-resolve veterancy score rows: builds the sorted entry list (army record plus its
// ThingTemplate, looked up by name) for the local player's selected side from the
// units-by-side vectors, then hands it to the 0x005ECD8C row builder (class Rva005ECD8C in
// ScoreRowSort.cpp). The base is the address-named Rva005ECA91 (rowed ctor); the entry vector
// uses the BfmeE8 push_back instantiation retail folded it onto (0x00539A2E), and the row
// builder keeps its S4SortElem8B vector spelling, so the list is passed through a cast.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ??$__destroy@PAURva004F77E0Element@@U1@@_STL@@YAXPAURva004F77E0Element@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004F77E0Element;
namespace _STL { template <> void __destroy<Rva004F77E0Element *,Rva004F77E0Element>(Rva004F77E0Element *,Rva004F77E0Element *,Rva004F77E0Element *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva004F77E0Element@@@_STL@@YAXPAURva004F77E0Element@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004F77E0Element;
namespace _STL { template <> void __destroy_aux<Rva004F77E0Element *>(Rva004F77E0Element *,Rva004F77E0Element *,__false_type const &); }
class AsciiString;
class ThingTemplate;
#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;
struct TargetRef00217D4C {
 virtual void *destroy(unsigned int flags);
 int refs;
 void *payload;
 char unknown0C[0x24];
 int index30;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TargetRef00217D4C *ptr;
 TreeHintRef00217D4C() : ptr(0) {}
 TreeHintRef00217D4C(const TreeHintRef00217D4C &other):ptr(other.ptr) { if(ptr) ++ptr->refs; }
 ~TreeHintRef00217D4C() { if(ptr) ReleaseTreeHintRef00217D4C(ptr); }
};
// The units-by-side vectors: retail destroys them through the vector dtor 0x005EC919
// (its row's element spelling, Rva004F77E0Element), not the twin 0x000806B4 that
// vector<TreeHintRef00217D4C> names. Same one-pointer element and release.
struct Rva004F77E0Element {
 TargetRef00217D4C *ptr;
 ~Rva004F77E0Element() { if(ptr) ReleaseTreeHintRef00217D4C(ptr); }
};
namespace _STL { template <> vector<Rva004F77E0Element>::~vector(); }
struct S4SortElem8B { void *first; const ThingTemplate *second; };
struct BfmeE8 { int a, b; };
class Rva005ECD8C { public: void rva005ECD8C(_STL::vector<S4SortElem8B> *,int); };
#include "../../../Include/Common/Rva002B2B66.h"
struct Record52 { char unknown[0x2c]; int m_sideIndex; int m_playerID; };
struct Records52 { Record52 *first,*last; };
class Rva004F92E3 { public: void rva004F92E3(void *); };
class Rva005ECA91 { public: Rva005ECA91(); protected: virtual ~Rva005ECA91(); private: char observed04[24]; };
#include "../../../Include/GameClient/StrategicVeterancy.h"
class StrategicVeterancy::Data : public Rva005ECA91 {
public: class AutoResolve;
};
class StrategicVeterancy::Data::AutoResolve : public StrategicVeterancy::Data {
public: AutoResolve(void *,void *,void *);
protected: virtual ~AutoResolve();
};
StrategicVeterancy::Data::AutoResolve::AutoResolve(void *a,void *b,void *autoResolveBattle) {
 _STL::vector<BfmeE8> entries;
 int selected=0;
 int player=((Rva002B2B66 *)a)->rva002B2B66();
 int index=0;
 Records52 *records=(Records52 *)autoResolveBattle;
 for(Record52 *record=records->first;record!=records->last;++record) {
  if(record->m_playerID==player) { selected=record->m_sideIndex;break; }
  ++index;
 }
 _STL::vector<Rva004F77E0Element> units[2];
 ((Rva004F92E3 *)autoResolveBattle)->rva004F92E3(units);
 _STL::vector<Rva004F77E0Element> &selectedUnits=units[selected];
 for(Rva004F77E0Element *unitIter=selectedUnits.begin();unitIter!=selectedUnits.end();++unitIter) {
  TreeHintRef00217D4C ref=*(TreeHintRef00217D4C *)unitIter;
  if(ref.ptr->index30!=index) continue;
  void *army=ref.ptr->payload;
  const ThingTemplate *thing=TheThingFactory->findTemplate(*(AsciiString *)((char *)army+4));
  if(!thing) continue;
  BfmeE8 entry; entry.a=(int)army; entry.b=(int)thing;
  entries.push_back(entry);
 }
 ((Rva005ECD8C *)this)->rva005ECD8C((_STL::vector<S4SortElem8B> *)&entries,((Rva002B2B66 *)a)->rva002B2B66());
}
