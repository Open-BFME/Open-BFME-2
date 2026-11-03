#ifndef BFME2_ARMY_SUMMARY_H
#define BFME2_ARMY_SUMMARY_H
// Existing native ArmySummary layout shared by the provider and query callers.
#include <vector>
#include "ascii_string.h"
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT 1
#endif
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include <stdlib.h>
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
enum ObjectID;
class ArmySummary : public Snapshot, public Rva0040D8D6List {
public:
 virtual ~ArmySummary();
 // Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
 // ?ArmySummary::loadPostProcess present-unmatched
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
 virtual void LoadPostProcess() {}
#else
 virtual void loadPostProcess() {}
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
 virtual const char *GetSnapshotName();
#else
 virtual const char *GetSnapshotName() const;
#endif
#else
 virtual void crc(Xfer *);
#endif
protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
 virtual void DoXfer(Xfer &);
#else
 virtual void DoXfer(Xfer *);
#endif
#else
 virtual void xfer(Xfer *);
#endif
public:
 Rva0040DD3ARef RemoveEntry(int);
 Rva0040DD3ARef rva0040E672(int);
 void rva0040DED9();
 void rva0040DF77();
 void rva0040DE16();
 bool HasDelayedCarryoverUnitOfTypes(ObjectTypes*);
 ObjectID SpawnOneDelayedCarryoverUnit(ObjectTypes*);
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

