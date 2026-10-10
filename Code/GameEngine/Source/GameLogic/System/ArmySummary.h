#ifndef BFME2_ARMY_SUMMARY_H
#define BFME2_ARMY_SUMMARY_H
// Existing native ArmySummary layout shared by the provider and query callers.
#include <vector>
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT 1
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
extern "C" void __cdecl free(void*);
struct TargetRef00217D4C { void* vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva004F69C3Target { unsigned char unknown0[4]; AsciiString templateName; unsigned char opaque[0xAC-8]; TargetRef00217D4C ref; };
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
#include "../../Common/BfmeIntVecG.h"
class Rva0040CB3AIndexedField { public: int find(int key) const; int get(int key) const; };
class ObjectTypes;
class ArmySummary : public Snapshot, public Rva0040D8D6List {
public:
 virtual ~ArmySummary();
 virtual const char *GetSnapshotName() const;
 Rva0040DD3ARef RemoveEntry(int);
 Rva0040DD3ARef rva0040E672(int);
 void rva0040DED9();
 void rva0040DE16();
 bool HasDelayedCarryoverUnitOfTypes(ObjectTypes*);
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
#endif

