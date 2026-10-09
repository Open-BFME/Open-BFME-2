// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /MD /EHs /D_STLP_USE_STATIC_LIB
// stlport
// ChecklistUIImpl constructor916B (57B5AA), destructor158B (57AD6E),
// scalar deleting destructor28B (42D523), and private height helper271B
// (57AE1F). Identity: WB14BB620 names the constructor and file; native
// C6F118/C6F0FC/C6F0F4 tables and callback strings tie it independently to
// the existing named callbacks. Base declarations are storage/ABI views;
// the original interface names remain unknown. Native members establish
// level0C/path10/map18/flags24..26/scrollbar28/list30/current34/height3C.
// The original neutral destructor and its consumers now share this name.
// Height source carried from the previously verified unit; proper holder
// base initialization preserves its271 bytes. The real constructor supplies
// its ECX-path/stack-level private ABI; no artificial emission caller remains.
// RegistryAsciiPath supplies the concat-node semantic guide. Binding uses
// this actual three-base class, hence native eight-byte member pointers.
// /EHs preserves the destructor state5 store before list-base cleanup;
// /EHsc omits those four bytes. All four bodies and affected consumers verify.
#include <list>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
struct AsciiStringRef {const AsciiString *m_string;};
struct AsciiStringPlusString : AsciiStringRef {AsciiStringRef m_second;};
class Rva000B3F84Pair {public:Rva000B3F84Pair(){} Rva000B3F84Pair *init(const char*);const char *text;int length;};
struct AsciiStringPlusStringText : AsciiStringPlusString {operator AsciiString();Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b) {AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
// ?operatorPlusTwoStringsText present-unmatched: exact61B relocation twin at109CFD
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString&a,const char*b) {Rva000B3F84Pair p;p.init(b);AsciiStringPlusStringText r;static_cast<AsciiStringPlusString&>(r)=a;r.m_right=p;return r;}


struct Rva0057ACEBData {int m_0,m_4;};
class Rva0057ACEB {public:Rva0057ACEB(const Rva0057ACEBData*);void* impl;};
class Rva005D4E22 {public:Rva005D4E22(bool*,AsciiString*);int m_0,m_4;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class AptExternHandler;
template<class T>class AptRef;
template<>class AptRef<AptExternHandler>:public Rva0057ACEB {public:__forceinline AptRef(Rva005D4E22 data):Rva0057ACEB(reinterpret_cast<const Rva0057ACEBData*>(&data)){}AptRef(const AptRef& other):Rva0057ACEB(other){if(impl)++reinterpret_cast<int*>(impl)[1];}~AptRef(){if(impl)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C*>(impl));}};
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

class __multiple_inheritance FunctorTarget;
typedef void(FunctorTarget::*FunctorMethod)(void);
struct FunctorBinding {FunctorBinding(FunctorMethod m,FunctorTarget*o):object(o),method(m){} FunctorTarget*object;unsigned word;FunctorMethod method;};
class FunctorWrapperHead {public:void*vt;int refCount;};
class Rva0057BC63FunctorHolder {public:Rva0057BC63FunctorHolder(const FunctorBinding&);Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder&o):ptr(o.ptr){if(ptr)++ptr->refCount;}FunctorWrapperHead*ptr;};
__forceinline FunctorBinding MakeBinding(FunctorMethod m,FunctorTarget*o){return FunctorBinding(m,o);}
template<class T> class AptRef:public Rva0057BC63FunctorHolder {public:AptRef(const FunctorBinding&b):Rva0057BC63FunctorHolder(b){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};
class AptCommandMap;
class AptCommandMapAdder {public:AptCommandMapAdder();~AptCommandMapAdder();void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);__forceinline void AddCommandMapDelegate(const AsciiString&n,FunctorBinding b){AddCommandMap(n,b);}private:_STL::vector<AsciiString> names;};
class Base1 {public:virtual void b1();~Base1(){}};
class Base2 {public:virtual void b2();~Base2(){}};
class Base3 {public:virtual void b3();~Base3(){}};
class Rva000AD6F4 {public:void clear();Rva000AD6F4():ptr(0){}~Rva000AD6F4(){clear();}void*ptr;};
class GameTextInterface {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual UnicodeString fetch(const char*,bool=0);};
extern GameTextInterface *TheGameText;
class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
struct Rva0057A51CTeam;struct Rva0057A685Team;
namespace StrategicHUD {void SetTurnNumberString(int,Rva0057A51CTeam**,int);void SetPhaseTitleString(int,Rva0057A685Team**,int);}
struct YBase
{
	virtual void y0();
	virtual void y1();
	virtual void y2();
	virtual void y3();
	virtual void y4();
	virtual void y5(void *p);
};

struct XNode
{
	char m_pad[0x54];
	YBase *m_y;
};

namespace StrategicHUD {class ChecklistUIImpl;}
class StrategicHUD::ChecklistUIImpl:public Base1,public Base2,public Base3 {
public:ChecklistUIImpl(int,const AsciiString&);virtual~ChecklistUIImpl();
 void OnScrollBarLoaded(const char*);void OnScrollBarUnloaded(const char*);void OnOpen(const char*);void OnClosed(const char*);void OnExpandButtonClicked(const char*);
 int level;AsciiString path;int state;AptCommandMapAdder maps;bool open,flag25,flag26;Rva000AD6F4 scrollbar;int word2C;_STL::list<int>items;_STL::list<int>::iterator position;bool flag38;float viewHeight;int turn,phase,word48;bool flag4C;
};
#define BIND(TEXT,METHOD) {FunctorMethod method=reinterpret_cast<FunctorMethod>(&ChecklistUIImpl::METHOD);const AsciiString&name=prefix+path+TEXT;maps.AddCommandMapDelegate(name,MakeBinding(method,reinterpret_cast<FunctorTarget*>(this)));}
StrategicHUD::ChecklistUIImpl::ChecklistUIImpl(int l,const AsciiString&n):level(l),path(n),state(0),open(true),flag25(false),flag26(false),word2C(0),position(items.end()),flag38(false),viewHeight(ChecklistViewHeight(n,l)),turn(1),phase(-1),word48(0),flag4C(false){
 AsciiString prefix;prefix.format("_level%u.",level);
 BIND("_OnScrollBarLoaded",OnScrollBarLoaded);
 BIND("_OnScrollBarUnloaded",OnScrollBarUnloaded);
 BIND("_OnOpen",OnOpen);BIND("_OnClosed",OnClosed);BIND("_OnExpandButtonClicked",OnExpandButtonClicked);
 {AsciiString name("APT:StrategicHUDNoChecklistItems");g_bfmeAptWindowManager->bfmeSetText(name,TheGameText->fetch("STRATEGICHUD:CriticalTasksWillBeDisplayedHere"),false);}
 StrategicHUD::SetTurnNumberString(level,reinterpret_cast<Rva0057A51CTeam**>(&path),turn);
 StrategicHUD::SetPhaseTitleString(level,reinterpret_cast<Rva0057A685Team**>(&path),phase);
}

StrategicHUD::ChecklistUIImpl::~ChecklistUIImpl()
{
	void *head = *(void **)&items;
	void *cur = *(void **)head;
	if (cur != head) {
		void *nxt;
		XNode *x;
		YBase *y;
		do {
			nxt = *(void **)cur;
			x = *(XNode **)((char *)cur + 8);
			y = x->m_y;
			y->y5(x);
			cur = nxt;
		} while (nxt != head);
	}
}
