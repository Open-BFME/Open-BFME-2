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
#include "ArmySummary.h"
// Target lookup2D06CA and the following byte test prove only this flag offset.
class ThingTemplate { public: unsigned char opaque[0x113]; unsigned char flags113; };
class ThingFactory { public: const ThingTemplate* findTemplate(const AsciiString&); };
extern ThingFactory* TheThingFactory;

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

// Native C394F0 slot2 returns the complete ArmySummary literal.
const char *ArmySummary::GetSnapshotName() const { return "ArmySummary"; }

// Native40DE16..40DED9/195B traverses entries in reverse. A successful
// lookup by the target name at +4 whose template byte113 lacks bit4 causes
// removal through the established listener/reference sequence. The native
// class is ArmySummary; the method name and bit meaning remain unproven.
void ArmySummary::rva0040DE16()
{
 for(int index=(int)entries.size()-1;index>=0;--index) {
  const ThingTemplate* definition=TheThingFactory->findTemplate(entries[index].value->templateName);
  if(!definition || (definition->flags113&4)) continue;
  Rva004F69C3* entry=entries.begin()+index;
  Rva0040D8D6List::forEach(&Rva0040D8D6Listener::removing,this,entry->key);
  Rva0040DD3ARef value(entry->value);
  entries.erase(entry);
  Rva0040D8D6List::forEach(&Rva0040D8D6Listener::removed,this,(int)value.value);
 }
}

// Native40E672..40E6A4 and WB10892F0: find the key, return an empty
// owning handle on a miss, otherwise remove and return the indexed entry.
// The original method name is not present in WorldBuilder. Returning the
// nontrivial handle directly preserves retail's hidden output and return flag.
Rva0040DD3ARef ArmySummary::rva0040E672(int key) {
 int index=reinterpret_cast<const Rva0040CB3AIndexedField *>(this)->find(key);
 if(index<0) return Rva0040DD3ARef();
 return RemoveEntry(index);
}

// Native40CC3C..40CC8F and WB1088820 identify this ArmySummary query.
// Native reads its delayed entry ids at4C/50 and ObjectTypes string vector
// at8/C; the independently rowed ObjectTypes ctor establishes that prefix.
// Lookup40CBB8 yields the entry whose name4 is passed to contains376A62.
struct ArmySummaryObjectTypesRange {
 unsigned char opaque[8];
 _STL::vector<AsciiString> types;
 bool empty()const{return types.size()==0;}
};
class Rva00376A62 { public: bool rva00376A62(const StringBase<char>&); };
bool ArmySummary::HasDelayedCarryoverUnitOfTypes(ObjectTypes *types)
{
 if(reinterpret_cast<const ArmySummaryObjectTypesRange*>(types)->empty())return false;
 const int *end=words4C.end;
 for(const int *cur=words4C.begin;cur!=end;++cur) {
  int entry=reinterpret_cast<const Rva0040CB3AIndexedField*>(this)->get(*cur);
  if(entry && reinterpret_cast<Rva00376A62*>(types)->rva00376A62(*reinterpret_cast<const StringBase<char>*>(entry+4)))return true;
 }
 return false;
}
