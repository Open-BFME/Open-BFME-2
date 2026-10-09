// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <list>
#include "unicode_string.h"
// Native2BB5DD..2BB686 RET4: version1/3 and shared world state2BB2B7,
// non-CRC24B record-pointer vectorBC, polymorphic vectorsCC/D8, then
// version>=2 counted-list transfer. Names remain address-derived; offsets,
// stream slots and all call ABIs are target evidence. The two opaque helper
// bindings are full in-image boundaries2BB49C321 RET8 and2B8BFE264 RET4.
struct Version {unsigned char minimum,current;Version(unsigned char a,unsigned char b):minimum(a),current(b){}};
class Xfer {public:
virtual void s0();
virtual bool IsLoading() const;
virtual void s2();
virtual bool IsCRC() const;
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void xferRaw(void*,int);
virtual void xferVersion(Version*);
virtual void s11();
virtual void xferSnapshot(void*);
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void xferWide(UnicodeString*);
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void xferInt(int*);
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void xferBool(bool*);
virtual void s37();
};
class LivingWorldLogic{public:void rva002BB2B7(Xfer*);void rva002B83E5();};extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002B22AFArg;
class Rva002B22AF{public:Rva002B22AF():zeroC(0),zero10(0){}void rva002B22AF(Rva002B22AFArg*);char pad[8];int id;int zeroC,zero10,tail14;};
struct RecVec{Rva002B22AF**begin,**end,**cap;};
class Rva002BB49C{public:void rva002BB49C(Xfer*,RecVec*);};
struct BfmeStringRecord002B4DC1{UnicodeString text;unsigned word0,word1;BfmeStringRecord002B4DC1():word0(0),word1(3){} BfmeStringRecord002B4DC1(const BfmeStringRecord002B4DC1&);};
struct RecordNode{RecordNode*next,*prev;BfmeStringRecord002B4DC1 value;};
struct RecordList{RecordNode*head;__forceinline int size()const{int count=0;for(RecordNode*p=head->next;p!=head;p=p->next)++count;return count;}};

typedef _STL::_List_base<UnicodeString,_STL::allocator<UnicodeString> > WideListBase;
class Rva002B8106{public:void rva002B8106(const BfmeStringRecord002B4DC1&);};

class Rva002B8BFE{public:void rva002B8BFE(Xfer*);char pad[0xF0];_STL::list<BfmeStringRecord002B4DC1> records;};
class Rva002BB5DD {public:void rva002BB5DD(Xfer*);char pad[0xBC];RecVec records;char gap[4];RecVec first,second;};
void Rva002BB5DD::rva002BB5DD(Xfer*xfer){
 Version v(1,3);xfer->xferVersion(&v);
 ((LivingWorldLogic*)this)->rva002BB2B7(xfer);
 if(!xfer->IsCRC()){
  int count=records.end-records.begin;xfer->xferInt(&count);
  for(int i=0;i<count;++i)records.begin[i]->rva002B22AF((Rva002B22AFArg*)xfer);
 }
 ((Rva002BB49C*)this)->rva002BB49C(xfer,&first);
 ((Rva002BB49C*)this)->rva002BB49C(xfer,&second);
 if(!xfer->IsCRC() && v.current>=2)((Rva002B8BFE*)this)->rva002B8BFE(xfer);
}

void*operator new(unsigned int);
class ModuleData;
namespace _STL{template<class T>class allocator;template<class T,class A>class vector{public:void push_back(const T&);};}
typedef _STL::vector<const ModuleData*,_STL::allocator<const ModuleData*> > ModuleVec;
class LivingWorldManager;
class Coord2D;

// Owned CreateBeaconObject identifies id8 and coordinate prefix0.
// Keeping the separate stored pointer before transfer gives native EBX
// lifetime and the EBP-C temporary; direct pointer-reference casts reload it.
class LivingWorldManager{public:void CreateBeaconObject(int,const Coord2D*,int);};
extern LivingWorldManager*TheLivingWorldManager;
// Native2BBA45..2BBB18 RET4 returns the version widened in EAX.
class Rva002BBA45{public:virtual void slot0();virtual void reset();unsigned int rva002BBA45(Xfer*);char pad[0xBC-4];RecVec records;char gap[4];RecVec first,second;};
unsigned int Rva002BBA45::rva002BBA45(Xfer*xfer){
 Version v(1,3);xfer->xferVersion(&v);reset();TheLivingWorldLogic->rva002B83E5();
 ((LivingWorldLogic*)this)->rva002BB2B7(xfer);
 int count;xfer->xferInt(&count);
 for(int i=0;i<count;++i){
  Rva002B22AF*record=new Rva002B22AF;
  const ModuleData* stored=(const ModuleData*)record;
  record->rva002B22AF((Rva002B22AFArg*)xfer);
  ((ModuleVec*)&records)->push_back(stored);
  TheLivingWorldManager->CreateBeaconObject(record->id,(const Coord2D*)record,2);
 }
 ((Rva002BB49C*)this)->rva002BB49C(xfer,&first);
 ((Rva002BB49C*)this)->rva002BB49C(xfer,&second);
 if(v.current>=2)((Rva002B8BFE*)this)->rva002B8BFE(xfer);
 return v.current;
}

// Native264: one UnicodeString and two words per list value; existing
// copy/append providers establish the12B record. Actual STLport size()
// gives native headEAX/iteratorECX; hand-written node loops swap them.
// Clear borrows the owned UnicodeString-list base: node links and first
// string destructor are identical and the trailing words are trivial.
void Rva002B8BFE::rva002B8BFE(Xfer*xfer){
 int count=records.size();xfer->xferInt(&count);
 if(xfer->IsLoading()){
  ((WideListBase*)&records)->clear();
  for(int i=0;i<count;++i){BfmeStringRecord002B4DC1 value;
   xfer->xferWide(&value.text);xfer->xferInt((int*)&value.word0);xfer->xferRaw(&value.word1,4);
   ((Rva002B8106*)&records)->rva002B8106(value);
  }
 }else{
  for(RecordNode*p=((RecordList*)&records)->head->next;p!=((RecordList*)&records)->head;p=p->next){BfmeStringRecord002B4DC1 value=p->value;
   xfer->xferWide(&value.text);xfer->xferInt((int*)&value.word0);xfer->xferRaw(&value.word1,4);
  }
 }
}
