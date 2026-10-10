// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ??0AutoResolve@Data@StrategicVeterancy@@QAE@PAX00@Z @ 0x005ECE81 (327 B)
// Auto-resolve veterancy score rows: builds the sorted entry list (army record plus its
// ThingTemplate, looked up by name) for the local player's selected side from the
// units-by-side vectors, then hands it to the 0x005ECD8C row builder (class Rva005ECD8C in
// ScoreRowSort.cpp). The base is the address-named Rva005ECA91 (rowed ctor); the entry vector
// uses the BfmeE8 push_back instantiation retail folded it onto (0x00539A2E), and the row
// builder keeps its S4SortElem8B vector spelling, so the list is passed through a cast.
#include <vector>
class AsciiString;
class ThingTemplate;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
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
 TreeHintRef00217D4C(const TreeHintRef00217D4C &o):ptr(o.ptr) { if(ptr) ++ptr->refs; }
 ~TreeHintRef00217D4C() { if(ptr) ReleaseTreeHintRef00217D4C(ptr); }
};
struct S4SortElem8B { void *first; const ThingTemplate *second; };
struct BfmeE8 { int a, b; };
class Rva005ECD8C { public: void rva005ECD8C(_STL::vector<S4SortElem8B> *,int); };
class Rva002B2B66 {public: int rva002B2B66();};
struct Record52 { char unknown[0x2c]; int selected2C; int player30; };
struct Records52 { Record52 *first,*last; };
class Rva004F92E3 { public: void rva004F92E3(void *); };
class Rva005ECA91 { public: Rva005ECA91(); protected: virtual ~Rva005ECA91(); private: char observed04[24]; };
class StrategicVeterancy {
public:
 class Data : public Rva005ECA91 {
 public: class AutoResolve;
 };
};
class StrategicVeterancy::Data::AutoResolve : public StrategicVeterancy::Data {
public: AutoResolve(void *,void *,void *);
protected: virtual ~AutoResolve();
};
StrategicVeterancy::Data::AutoResolve::AutoResolve(void *a,void *b,void *c) {
 _STL::vector<BfmeE8> entries;
 int selected=0;
 int player=((Rva002B2B66 *)a)->rva002B2B66();
 int index=0;
 Records52 *records=(Records52 *)c;
 for(Record52 *p=records->first;p!=records->last;++p) {
  if(p->player30==player) { selected=p->selected2C;break; }
  ++index;
 }
 _STL::vector<TreeHintRef00217D4C> units[2];
 ((Rva004F92E3 *)c)->rva004F92E3(units);
 _STL::vector<TreeHintRef00217D4C> &selectedUnits=units[selected];
 for(TreeHintRef00217D4C *p=selectedUnits.begin();p!=selectedUnits.end();++p) {
  TreeHintRef00217D4C ref=*p;
  if(ref.ptr->index30!=index) continue;
  void *army=ref.ptr->payload;
  const ThingTemplate *thing=TheThingFactory->findTemplate(*(AsciiString *)((char *)army+4));
  if(!thing) continue;
  BfmeE8 entry; entry.a=(int)army; entry.b=(int)thing;
  entries.push_back(entry);
 }
 ((Rva005ECD8C *)this)->rva005ECD8C((_STL::vector<S4SortElem8B> *)&entries,((Rva002B2B66 *)a)->rva002B2B66());
}
