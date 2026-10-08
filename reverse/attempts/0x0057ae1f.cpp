// ?ChecklistViewHeight@@YAMABVAsciiString@@H@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
#include "ascii_string.h"
extern "C" __declspec(dllimport) double __cdecl atof(const char*);
inline void *operator new(unsigned int,void *p){return p;}
struct Rva0057ACEBData {int m_0,m_4;};
class Rva0057ACEB {public:Rva0057ACEB(const Rva0057ACEBData*);void* impl;};
class Rva005D4E22 {public:Rva005D4E22(bool*,AsciiString*);int m_0,m_4;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class AptExternHandler;
template<class T> class AptRef {public:T* ptr;__forceinline AptRef(Rva005D4E22 data){reinterpret_cast<Rva0057ACEB*>(this)->Rva0057ACEB::Rva0057ACEB(reinterpret_cast<const Rva0057ACEBData*>(&data));}AptRef(const AptRef& other):ptr(other.ptr){if(ptr)++reinterpret_cast<int*>(ptr)[1];}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C*>(ptr));}};
class AptSingleExternHandlerAdder {public:AptSingleExternHandlerAdder(const AsciiString&,int,AptRef<AptExternHandler>);~AptSingleExternHandlerAdder();AsciiString name;};
struct Rva00222A8BScale {float x,y;};
class Rva00222A8BTarget {public:
virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();
virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();
virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
virtual void slot30();virtual void slot34();virtual void slot38();virtual Rva00222A8BScale *slot3C();};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget*,void*,const char*,const char*);
static __declspec(noinline) float ChecklistViewHeight(const AsciiString& path,int level)
{
 AsciiString value;
 {
  AsciiString name;
  name.format("_level%u.%s_ItemListViewHeight",level,path.str());
  bool ready;
  AptSingleExternHandlerAdder handler(name,0,AptRef<AptExternHandler>(Rva005D4E22(&ready,&value)));
  Rva00524EF4AptCall(TheRva00222A8BTarget,reinterpret_cast<void*>(level),path.str(),"GetItemListViewHeight");
 }
 float height=static_cast<float>(atof(value.str()));
 return TheRva00222A8BTarget->slot3C()->y*height;
}
float UseChecklistViewHeight(const AsciiString& path,int level){return ChecklistViewHeight(path,level);}
