// ?rva0040DF77@ArmySummary@@QAEXXZ
// partial score=0.95 date=2026-10-08
// WorldBuilder 0x010893B0 names ArmySummary::RemoveEntry at ArmySummary.cpp:573.
// Native Ghidra boundary 0x0040DD3A / 156 B and calls prove the listener list
// at +4, 8-byte key/reference entries in the vector at +0x40, and returned
// 4-byte reference handle. Its target's count is +0xB0 and release base +0xAC.
// Target identity and the original handle template spelling remain unproven;
// use the same address-derived target view as the established entry destructor.
// Native listener member pointers are the compiler's virtual-slot 4 / 3 thunks.
// The output retains the target before the local handle releases it; erase
// uses the independently verified Rva004F69C3 vector provider at 0x0040DC1F.
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"
extern "C" void __cdecl free(void*);
struct TargetRef00217D4C { void* vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva004F69C3Target { unsigned char opaque[0xAC]; TargetRef00217D4C ref; };
struct Rva004F69C3 { int key; Rva004F69C3Target* value; ~Rva004F69C3(); };
namespace _STL { template<> vector<Rva004F69C3>::iterator vector<Rva004F69C3>::erase(iterator); }
// The existing 40E0EB provider destroys this same eight-byte entry range.
class Rva0040E0EB : public _STL::vector<Rva004F69C3> { public: ~Rva0040E0EB(); };
class Rva0040D8B8Listener { public: virtual void slot0(); virtual void notify(void*); };
class Rva0040D8B8List { public: void forEach(void(Rva0040D8B8Listener::*)(void*),void*); };
class Rva0040D8D6Listener {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void removed(void*,int); virtual void removing(void*,int);
};
class Rva0040D8D6List {
public: void forEach(void(Rva0040D8D6Listener::*)(void*,int),void*,int);
public: ~Rva0040D8D6List() { if(begin) free(begin); }
private: void *begin,*end,*limit; unsigned int index;
};
struct Rva0040DD3ARef {
 Rva004F69C3Target* value;
 Rva0040DD3ARef():value(0){}
 Rva0040DD3ARef(Rva004F69C3Target* p):value(p){if(value)++value->ref.references;}
 Rva0040DD3ARef(const Rva0040DD3ARef& x):value(x.value){if(value)++value->ref.references;}
 ~Rva0040DD3ARef(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}
};
// Existing 532803 provider view: twelve-byte vector of opaque four-byte
// words, with the same observed range-erasure ABI. Element purpose unknown.
class BfmeIntVecG {
public:
 void bfmeErase(int*,int*);
 __forceinline void clear() { bfmeErase(begin,end); }
 __forceinline bool empty() const { return begin==end; }
 ~BfmeIntVecG() { if(begin) free(begin); }
 int *begin,*end,*limit;
};
class ArmySummary : public Snapshot, public Rva0040D8D6List {
public:
 virtual ~ArmySummary();
 Rva0040DD3ARef RemoveEntry(int);
 void rva0040DED9();
 void rva0040DF77();
private:
 bool flag14;
 unsigned char pad15[3];
 AsciiString name18;
 int at1C;
 AsciiString name20;
 unsigned char gap[0x3C-0x24];
 int at3C;
 Rva0040E0EB entries;
 BfmeIntVecG words4C;
 unsigned char gap58[0x64-0x58];
 AsciiString name64;
};
Rva0040DD3ARef ArmySummary::RemoveEntry(int index) {
 Rva004F69C3* entry=entries.begin()+index;
 Rva0040D8D6List::forEach(&Rva0040D8D6Listener::removing,this,entry->key);
 Rva0040DD3ARef value(entry->value);
 entries.erase(entry);
 Rva0040D8D6List::forEach(&Rva0040D8D6Listener::removed,this,(int)value.value);
 return value;
}

// Native40DED9..40DF77/158B pops entries in reverse order. The matched
// RemoveEntry156B provides the listener callbacks and target ref-count ABI;
// target bytes independently establish reset word3C and vector4C/flag14.
// The original method name and the four-byte-vector element meaning are unknown.
void ArmySummary::rva0040DED9()
{
 while (!entries.empty()) {
  Rva004F69C3 &entry=entries.back();
  Rva0040D8D6List::forEach(&Rva0040D8D6Listener::removing,this,entry.key);
  Rva0040DD3ARef value(entry.value);
  entries.pop_back();
  Rva0040D8D6List::forEach(&Rva0040D8D6Listener::removed,this,(int)value.value);
 }
 at3C=1;
 words4C.clear();
 flag14=false;
}

// Native40E499..40E534/155B is the C394F0 slot-0 target, whose
// name-getter40E493 returns ArmySummary. The destructor proves Snapshot
// at +0, the listener list as a second base at +4 (nullable derived-to-base
// EH cleanup conversion), and strings +18/+20/+64 from its teardown calls.
ArmySummary::~ArmySummary()
{
 rva0040DED9();
 ((Rva0040D8B8List*)static_cast<Rva0040D8D6List*>(this))->forEach(&Rva0040D8B8Listener::notify,this);
}

// Native40DF77..40E02B/180B keeps entries whose keys appear in words4C.
// Its empty-list path calls the verified full cleanup; the other path uses
// the same removal notifications and reference lifetime as RemoveEntry.
// Target bytes prove the operation, but its original name remains unknown.
void ArmySummary::rva0040DF77()
{
 if(words4C.empty()) {
  rva0040DED9();
 } else {
  int* stop=words4C.end;
  _STL::vector<Rva004F69C3>::iterator entry=entries.begin();
  while(entry!=entries.end()) {
   int* word=words4C.begin;
   for(;;) {
    if(word==stop) {
     Rva0040D8D6List::forEach(&Rva0040D8D6Listener::removing,this,entry->key);
     Rva0040DD3ARef value(entry->value);
     entry=entries.erase(entry);
     Rva0040D8D6List::forEach(&Rva0040D8D6Listener::removed,this,(int)value.value);
     break;
    }
    if(entry->key==*word) {
     ++entry;
     break;
    }
    ++word;
   }
  }
  flag14=false;
 }
}
