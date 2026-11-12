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
// Suppress this TU's non-retail copy of ??F?$_List_iterator@HU?$_Nonconst_traits@H@_STL@@@_STL@@QAEAAU01@XZ:
// the kept copy serves the link. The rows here inline it: dllimport + __forceinline body emits no copy.
namespace _STL { template <> __declspec(dllimport) __forceinline _List_iterator<int, _Nonconst_traits<int> > &_List_iterator<int, _Nonconst_traits<int> >::operator--() { this->_M_node = this->_M_node->_M_prev; return *this; } }

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_List_node@H@_STL@@@_STL@@QBEXPAU?$_List_node@H@2@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<_List_node<int> >::deallocate(_List_node<int> *, size_t) const; }
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}
#include "../../../../../Include/Common/AsciiStringRef.h"
#include "../../../../../Include/Common/AsciiStringPlusString.h"
#include "../../../../../Include/Common/Rva000B3F84Pair.h"
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
#include "../../../../../Include/Common/Rva00222A8BTarget.h"
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
#include "../../../../../Include/Common/FunctorWrapperHead.h"
class Rva0057BC63FunctorHolder {public:Rva0057BC63FunctorHolder(const FunctorBinding&);Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder&o):ptr(o.ptr){if(ptr)++ptr->m_refCount;}FunctorWrapperHead*ptr;};
__forceinline FunctorBinding MakeBinding(FunctorMethod m,FunctorTarget*functorTarget){return FunctorBinding(m,functorTarget);}
template<class T> class AptRef:public Rva0057BC63FunctorHolder {public:AptRef(const FunctorBinding&b):Rva0057BC63FunctorHolder(b){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};
class AptCommandMap;
class AptCommandMapAdder {public:AptCommandMapAdder();~AptCommandMapAdder();void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);__forceinline void AddCommandMapDelegate(const AsciiString&n,FunctorBinding b){AddCommandMap(n,b);}private:_STL::vector<AsciiString> names;};
class ChecklistItemRef;
// Base1 and Base2 are interfaces: retail's base table 0x00C6EE28 is all __purecall.
class Base1 {public:virtual ChecklistItemRef DoCreateNewItem()=0;~Base1(){}};
class Base2
{
public:
	virtual void b2() = 0;
	// Retail table 0x00C6EE28: six __purecall entries follow.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	~Base2() {}
};
// Base3's table is native C6EE20, the scroll listener whose two empty callbacks are rowed in
// Rva005F2CBAProgress.cpp; novtable so only Base3 (its pinned dtor at 0x0057A235) stores a vptr.
class __declspec(novtable) Rva0086EE20 {public:virtual void slot0(int);virtual void rva005F267E(int,float);};
class Base3:public Rva0086EE20 {public:~Base3(){}};
#include "../../../../../Include/Common/Rva000AD6F4.h"
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
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

// Checklist item views for DoCreateNewItem; layouts as in the rowed Item
// constructor 0x0057A748 (StrategicHUDChecklistUIImpl.cpp): reference-counted
// base +0 (inc 0x005D1A79, Release_Ref 0x005D1A7D), movie clip base +8, 0x60 bytes.
namespace StrategicHUD {class ChecklistUIImpl;}
struct ChecklistSelectNode;
struct ChecklistIteratorView
{
	ChecklistSelectNode *node;
	ChecklistIteratorView(const ChecklistIteratorView &other) : node(other.node) {}
};
class Rva005D1A6C {public:virtual ~Rva005D1A6C();int m_04;};
class Rva005D40A6 {public:virtual ~Rva005D40A6();char m_pad04[0x40 - 0x04];};
namespace StrategicHUD {
class ChecklistUIItemView : public Rva005D1A6C, public Rva005D40A6 {};
}
#include "../../../../../Include/Common/Rva005D1A79DwordCounter.h"
class RefCountClass {public:void Release_Ref();};
#include "../../../../../Include/GameClient/Rva005D3FE4.h"
#include "../../../../../Include/GameClient/Rva004987FEFloatField.h"
struct RetObj {char m_pad[4];float m_4;};
struct GlobalObj {virtual ~GlobalObj() {} virtual void *d1(); virtual void *d2(); virtual void *d3(); virtual void *d4(); virtual void *d5(); virtual void *d6(); virtual void *d7(); virtual void *d8(); virtual void *d9(); virtual void *d10(); virtual void *d11(); virtual void *d12(); virtual void *d13(); virtual void *d14(); virtual RetObj *slot15();};
// Native57A24A..57A260 RET0: shared item spacing, the window manager's slot15
// scale times +0x20 of g_Va00E06360. It stays a real noinline call; its body
// being visible here is what keeps the callers' x87 values live across it
// (rva0057ABD0's spill schedule, DoCreateNewItem's st(1) sum).
class Rva0057A24A {public:__declspec(noinline) float rva0057A24A() const;private:char m_pad[0x20];float m_20;};
float Rva0057A24A::rva0057A24A() const { return (*(GlobalObj **)&g_bfmeAptWindowManager)->slot15()->m_4 * m_20; }
extern unsigned int g_Va00E06360[9];
namespace AptUtils {const char *SkipLevelN(const char *);int LevelIndexFromTarget(const char *);}
int __cdecl Rva0052519DFire(void *,void *,const char *,const char *,int *);
namespace StrategicHUD {
struct ChecklistHeightItem {char prefix[0x38];float top;};
struct ChecklistHeightNode {ChecklistHeightNode *next,*prev;ChecklistHeightItem *item;};
}
// The owning item pointer DoCreateNewItem returns (WorldBuilder: newItem.GetPtr()).
// Native57A3F4..57A40C (24B, returns this): the out-of-line pointer constructor
// takes a reference; copy and release are inline at their call sites.
class ChecklistItemRef
{
public:
	__forceinline ChecklistItemRef() : m_ptr(0) {}
	ChecklistItemRef(StrategicHUD::ChecklistUIItemView *p);
	__forceinline ChecklistItemRef(const ChecklistItemRef &checklistItemRef) : m_ptr(checklistItemRef.m_ptr) {if(m_ptr)reinterpret_cast<Rva005D1A79DwordCounter *>(m_ptr)->inc();}
	__forceinline ~ChecklistItemRef() {if(m_ptr)reinterpret_cast<RefCountClass *>(m_ptr)->Release_Ref();}
	StrategicHUD::ChecklistUIItemView *operator->() const {return m_ptr;}
	StrategicHUD::ChecklistUIItemView *m_ptr;
};
ChecklistItemRef::ChecklistItemRef(StrategicHUD::ChecklistUIItemView *p) : m_ptr(p)
{
	if (p)
		reinterpret_cast<Rva005D1A79DwordCounter *>(p)->inc();
}
class StrategicHUD::ChecklistUIImpl:public Base1,public Base2,public Base3 {
public:ChecklistUIImpl(int,const AsciiString&);virtual~ChecklistUIImpl();
 class Item;
 virtual ChecklistItemRef DoCreateNewItem();
 float rva0057ABD0() const;
 void OnScrollBarLoaded(const char*);void OnScrollBarUnloaded(const char*);void OnOpen(const char*);void OnClosed(const char*);void OnExpandButtonClicked(const char*);
 int level;AsciiString path;int state;AptCommandMapAdder maps;bool open,flag25,flag26;Rva000AD6F4 scrollbar;int word2C;_STL::list<int>items;_STL::list<int>::iterator position;bool flag38;float viewHeight;int turn,phase,word48;bool flag4C;
};
#define BIND(TEXT,METHOD) {FunctorMethod method=reinterpret_cast<FunctorMethod>(&ChecklistUIImpl::METHOD);const AsciiString&name=prefix+path+TEXT;maps.AddCommandMapDelegate(name,MakeBinding(method,reinterpret_cast<FunctorTarget*>(this)));}
StrategicHUD::ChecklistUIImpl::ChecklistUIImpl(int l,const AsciiString&asciiString):level(l),path(asciiString),state(0),open(true),flag25(false),flag26(false),word2C(0),position(items.end()),flag38(false),viewHeight(ChecklistViewHeight(asciiString,l)),turn(1),phase(-1),word48(0),flag4C(false){
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
		XNode *xNode;
		YBase *yBase;
		do {
			nxt = *(void **)cur;
			xNode = *(XNode **)((char *)cur + 8);
			yBase = xNode->m_y;
			yBase->y5(xNode);
			cur = nxt;
		} while (nxt != head);
	}
}

class StrategicHUD::ChecklistUIImpl::Item : public ChecklistUIItemView
{
public:
	Item(ChecklistUIImpl *owner, ChecklistIteratorView position, int value, void *level, const AsciiString &path);
	ChecklistUIImpl *m_owner;
	ChecklistIteratorView m_listPos;
	int m_value;
	void *m_observer;
	int m_58;
	bool m_5c;
};
typedef char ChecklistItemSize[sizeof(StrategicHUD::ChecklistUIImpl::Item) == 0x60 ? 1 : -1];

// Native57AF2E..57B16D RET4: primary-table slot0 (C6F118) and WB14BCB70
// StrategicHUD::ChecklistUIImpl::DoCreateNewItem (asserts lines 783..804).
// Asks the movie for a new item clip through the _NewItem extern handler and
// the CreateItem call; without one returns an empty reference. Otherwise the
// item is placed below the last one (top38 plus its clip height, plus the
// shared spacing 57A24A), its list slot reserved with a null entry, then
// constructed (0x0057A748) with the next item number and the clip's level and
// level-relative path; it gets its y and the list is marked changed (flag38).
ChecklistItemRef StrategicHUD::ChecklistUIImpl::DoCreateNewItem()
{
	AsciiString itemPath;
	bool success = false;
	{
		AsciiString name;
		name.format("_level%u.%s_NewItem", level, path.str());
		AptSingleExternHandlerAdder handler(name, 0, AptRef<AptExternHandler>(Rva005D4E22(&success, &itemPath)));
		Rva0052519DFire(TheRva00222A8BTarget, reinterpret_cast<void *>(level), path.str(), "CreateItem", &word2C);
	}
	if (!success)
		return ChecklistItemRef();
	float y = 0.0f;
	if (!items.empty())
	{
		ChecklistHeightItem *last = reinterpret_cast<ChecklistHeightItem *>(items.back());
		float top = last->top;
		y = top + reinterpret_cast<Rva004987FEFloatField *>(reinterpret_cast<char *>(last) + 8)->get();
	}
	y += reinterpret_cast<Rva0057A24A *>(&g_Va00E06360)->rva0057A24A();
	_STL::list<int>::iterator pos = items.insert(items.end(), 0);
	ChecklistItemRef newItem = new Item(this, reinterpret_cast<const ChecklistIteratorView &>(pos), word2C++,
		reinterpret_cast<void *>(AptUtils::LevelIndexFromTarget(itemPath.str())),
		AsciiString(AptUtils::SkipLevelN(itemPath.str())));
	reinterpret_cast<Rva005D3FE4 *>(reinterpret_cast<char *>(newItem.operator->()) + 8)->rva005D3FE4(y);
	flag38 = true;
	return newItem;
}

// Native57ABD0..57AC0C RET0: unnamed height query. Last item top38 and
// +8 clip height plus shared spacing; empty list returns shared spacing.
float StrategicHUD::ChecklistUIImpl::rva0057ABD0() const
{
 ChecklistHeightNode *head=reinterpret_cast<ChecklistHeightNode *const &>(items);
 if(head->next!=head) {
  ChecklistHeightItem *last=head->prev->item;
  float top=last->top;
  return reinterpret_cast<Rva004987FEFloatField*>(reinterpret_cast<char*>(last)+8)->get()
    + reinterpret_cast<Rva0057A24A*>(&g_Va00E06360)->rva0057A24A() + top;
 }
 return reinterpret_cast<Rva0057A24A*>(&g_Va00E06360)->rva0057A24A();
}
