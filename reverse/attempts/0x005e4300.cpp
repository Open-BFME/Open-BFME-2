// ??RRva005E4300Cmp@@QBE_NHH@Z
// partial score=0.9 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHs-c-
#include "ascii_string.h"
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
struct Rva005E4300Entry {
 int key;
 AsciiString name;
 float metric;
 char pad[0xb8-0xc];
 int group;
};
struct Rva005E3967Template {
 char pad[0x110]; unsigned int mask;
};
class Rva0040CB3AIndexedField { public: int get(int) const; };
struct Rva005E4300Context {
 char pad0[0x18]; AsciiString selectedName;
 char pad1[0x78-0x1c]; Rva0040CB3AIndexedField *index;
};
namespace StrategicInGameUI {
static __declspec(noinline) Rva005E3967Template *Rva005E3967(const Rva005E4300Entry *entry)
{
 return (Rva005E3967Template *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&entry->name);
}
static __declspec(noinline) bool Rva005E3FE6(const Rva005E4300Entry *a,const Rva005E4300Entry *b,int keyA,int keyB)
{
 bool flagA=((Rva005E3967(a)->mask>>26)&1)!=0;
 bool flagB=((Rva005E3967(b)->mask>>26)&1)!=0;
 if(flagA!=flagB)return flagA;
 if(!flagA) {
  int cmp=a->name.compare(b->name);
  if(cmp)return cmp<0;
 }
 if(a->metric!=b->metric)return a->metric>b->metric;
 return keyA<keyB;
}
}
class Rva005E4300Cmp {
public:
 bool operator()(int,int) const;
private: Rva005E4300Context *m_context;
};
bool Rva005E4300Cmp::operator()(int keyA,int keyB) const
{
 const Rva005E4300Entry *a=(const Rva005E4300Entry *)m_context->index->get(keyA);
 if(a->name.compare(m_context->selectedName)==0)return true;
 int rawB=m_context->index->get(keyB);
 const AsciiString *selected=&m_context->selectedName;
 const Rva005E4300Entry *b=(const Rva005E4300Entry *)rawB;
 int groupA, groupB;
 if(b->name.compare(*selected)==0)goto no;
  groupA=a->group; groupB=b->group;
  if(groupA==groupB)goto equal;
  if(groupA==0)return true;
  if(groupB!=0)goto rank;
 no:
  return false;
 rank:
  return groupA<groupB;
 equal:
 return StrategicInGameUI::Rva005E3FE6(a,b,keyA,keyB);
}
