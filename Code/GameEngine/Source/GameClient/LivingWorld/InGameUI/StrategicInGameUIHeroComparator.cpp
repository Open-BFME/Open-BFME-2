// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Native005E6B3E..005E6B8F obtains archetype at template+5C4 for the
// selected entry+18 and sends its Unicode tooltip to the owned Mouse API.
// Native005E4300..005E4389 low-byte comparator of selected hero keys;
// groupB8 signed order with zero priority then the native118B fallback.
// Its three private bodies are reconstructed from target; original template
// and record class names remain unknown. Public char describes the observed
// AL zero/one ABI without claiming the original C++ return spelling.
#include "ascii_string.h"
#include "unicode_string.h"
class ThingTemplate;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
extern ThingFactory *TheThingFactory;
struct Rva005E4300Entry {
 int key;
 AsciiString name;
 float metric;
 char pad[0xb8-0xc];
 int group;
};
struct Rva005E3967Template {
 char pad[0x110]; unsigned int mask; char toArchetype[0x5C4-0x114];int archetype;
};
class Rva0040CB3AIndexedField { public: int get(int) const; };
struct Rva005E4300Context {
 char pad0[0x18]; AsciiString selectedName;
 char pad1[0x78-0x1c]; Rva0040CB3AIndexedField *index;
};
namespace StrategicInGameUI {
static __declspec(noinline) Rva005E3967Template *Rva005E3967(const Rva005E4300Entry *entry)
{
 return (Rva005E3967Template *)TheThingFactory->findTemplate(entry->name);
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
 char operator()(int,int) const;
private: Rva005E4300Context *m_context;
};
char Rva005E4300Cmp::operator()(int keyA,int keyB) const
{
 const Rva005E4300Entry *a=(const Rva005E4300Entry *)m_context->index->get(keyA);
 if(a->name.compare(m_context->selectedName)==0)return true;
 int rawB=m_context->index->get(keyB);
 const AsciiString *selected=&m_context->selectedName;
 const Rva005E4300Entry *b=(const Rva005E4300Entry *)rawB;
 if(b->name.compare(*selected)==0)goto no;
 {int ga=a->group,gb=b->group;
 if(ga!=gb) {if(ga==0)return true; if(gb==0)goto no; return ga<gb;}
 return StrategicInGameUI::Rva005E3FE6(a,b,keyA,keyB);}
 no:return false;
}

class Rva005E549E {public:void rva005E549E();};
class Rva005F6022ByteChaseField {public:unsigned char get()const;};
namespace StrategicInGameUI {UnicodeString GetTooltipText(int);}
struct RGBColor;class Mouse {public:void rva001EEA6D(UnicodeString,int,const RGBColor*,float);};extern Mouse*TheMouse;
class Rva005E6B3E {public:void rva005E6B3E();char unknown0[4];void*clip;char unknown8[0x10];Rva005E4300Entry*entry;};
void Rva005E6B3E::rva005E6B3E(){
 ((Rva005E549E*)((char*)clip+0xC))->rva005E549E();
 if(((Rva005F6022ByteChaseField*)clip)->get()){
  Rva005E3967Template*t=StrategicInGameUI::Rva005E3967(entry);
  int kind=t->archetype;
  TheMouse->rva001EEA6D(StrategicInGameUI::GetTooltipText(kind),-1,0,1.0f);
 }
}

struct TargetRef00217D4C {void*vtable;int count;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct TreeHintRef00217D4C {
 ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TreeHintRef00217D4C&operator=(const TreeHintRef00217D4C&);
 TargetRef00217D4C*m_ptr;
};
namespace StrategicInGameUI {TreeHintRef00217D4C Rva005E6A23(const Rva005E4300Entry*);}
class Rva003FE20FBase {public:virtual void slot1(void*);};
class Rva005E4157 {public:void rva005E4157(int);};
class Rva005E6AD8 {public:void rva005E6AD8();char pad0[4];void*clip;Rva003FE20FBase*owner;char padC[8];int value;Rva005E4300Entry*entry;TreeHintRef00217D4C held;};
void Rva005E6AD8::rva005E6AD8(){
 held=StrategicInGameUI::Rva005E6A23(entry);
 if(held.m_ptr)owner->Rva003FE20FBase::slot1(&held);
 ((Rva005E4157*)((char*)clip+0xC))->rva005E4157(value);
}
