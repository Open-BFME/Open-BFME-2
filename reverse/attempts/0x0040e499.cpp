// ??1ArmySummary@@UAE@XZ
// partial score=0.95 date=2026-10-08
// Banked 40E499..40E534 155B destructor body. Native C394F0 has
// deleting40E81E / empty B3FD0 / name40E493("ArmySummary") / transfer40EE89.
// The canonical Snapshot header exposes legacy void crc(Xfer*) in slot2;
// this trial inherits that incomplete interface and its emitted vtable has
// pure slots. Do not land it until the complete concrete table and class
// interface are reconciled. Native body instructions match apart from the
// cleanup call binding now owned by ArmySummary::rva0040DED9.
// WorldBuilder 0x010893B0 names ArmySummary::RemoveEntry at ArmySummary.cpp:573.
// Native Ghidra boundary 0x0040DD3A / 156 B and calls prove the listener list
// at +4, 8-byte key/reference entries in the vector at +0x40, and returned
// 4-byte reference handle. Its target's count is +0xB0 and release base +0xAC.
// Target identity and the original handle template spelling remain unproven;
// use the same address-derived target view as the established entry destructor.
// Native listener member pointers are the compiler's virtual-slot 4 / 3 thunks.
// The output retains the target before the local handle releases it; erase
// uses the independently verified Rva004F69C3 vector provider at 0x0040DC1F.
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
#include <vector>
struct TargetRef00217D4C { void* vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva004F69C3Target { unsigned char opaque[0xAC]; TargetRef00217D4C ref; };
struct Rva004F69C3 { int key; Rva004F69C3Target* value; ~Rva004F69C3(); };
namespace _STL { template<> vector<Rva004F69C3>::iterator vector<Rva004F69C3>::erase(iterator); }
class Rva0040D8D6Listener {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void removed(void*,int); virtual void removing(void*,int);
};
class Rva0040D8D6List {
public: void forEach(void(Rva0040D8D6Listener::*)(void*,int),void*,int);
private: unsigned char opaque[0x10];
};
struct Rva0040DD3ARef {
 Rva004F69C3Target* value;
 Rva0040DD3ARef():value(0){}
 Rva0040DD3ARef(Rva004F69C3Target* p):value(p){if(value)++value->ref.references;}
 Rva0040DD3ARef(const Rva0040DD3ARef& x):value(x.value){if(value)++value->ref.references;}
 ~Rva0040DD3ARef(){if(value)ReleaseTreeHintRef00217D4C(&value->ref);}
};


#include "ascii_string.h"
#include "Common/Snapshot.h"
extern const void*const g_00C394F0[];
struct Rva0040E0EB{ std::vector<Rva004F69C3>entries;~Rva0040E0EB();};
struct Rva0040E499Listeners{std::vector<Rva0040D8D6Listener*>entries;unsigned index;};
enum ScienceType{SCIENCE_0=0};
namespace _STL { template<> ScienceType*vector<ScienceType,allocator<ScienceType> >::erase(ScienceType*,ScienceType*); }
class Rva0040D8B8Listener{public:virtual void slot0();virtual void destroyed(void*);};
class Rva0040D8B8List{public:void forEach(void(Rva0040D8B8Listener::*)(void*),void*);};
class ArmySummary:public Snapshot {
public:virtual ~ArmySummary();void rva0040DED9();
private:Rva0040E499Listeners listeners;bool flag14;char pad15[3];AsciiString name18;int field1C;AsciiString name20;
 int fields24[6];int state3C;Rva0040E0EB m40;std::vector<ScienceType>pending;float floats58[2];int field60;AsciiString name64;
};
void ArmySummary::rva0040DED9(){
 while(!m40.entries.empty()){
  Rva004F69C3*entry=&m40.entries.back();
  ((Rva0040D8D6List*)&listeners)->forEach(&Rva0040D8D6Listener::removing,this,entry->key);
  Rva0040DD3ARef value(entry->value);
  m40.entries.pop_back();
  ((Rva0040D8D6List*)&listeners)->forEach(&Rva0040D8D6Listener::removed,this,(int)value.value);
 }
 std::vector<ScienceType>*toClear=(std::vector<ScienceType>*)((char*)this+0x4C);
 state3C=1;toClear->erase(toClear->begin(),toClear->end());flag14=false;
}
ArmySummary::~ArmySummary(){
 rva0040DED9();
 ((Rva0040D8B8List*)&listeners)->forEach(&Rva0040D8B8Listener::destroyed,this);
}
