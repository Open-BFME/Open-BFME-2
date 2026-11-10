// cl: /O1 /G7 /MD /EHs /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB StrategicHUDBattlePromptMovieClip.cpp:795..837 identifies the paired tab
// callbacks. Native records have two 32-bit properties and a wide string at +8,
// stride 12; destructor 5F9217 tail-releases that string.
// This view preserves the already rowed BfmeStringRecord005F93E3 push-back type.
// Tabs and helper views below assert only witnessed receiver/stack arguments.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Common/BfmeStringRecord005F93E3.h"
struct Rva005F91F3Src {unsigned int header,word0,word1;UnicodeString text;};
struct Rva005F91F3 {unsigned int word0,word1;UnicodeString text;Rva005F91F3(const Rva005F91F3Src &);};
class Rva005FA0C9;
struct Rva005FA197Element {Rva005FA0C9 *ptr;Rva005FA197Element(Rva005FA0C9 *);Rva005FA197Element(const Rva005FA197Element &);~Rva005FA197Element();};
class Rva005FA0F7;
struct Rva005FA1CEElement {Rva005FA0F7 *ptr;Rva005FA1CEElement(Rva005FA0F7 *);Rva005FA1CEElement(const Rva005FA1CEElement &);~Rva005FA1CEElement();};
namespace _STL {
}
// Range cleanup: retail's 24B _Destroy forwarder 0x005F97BC into the 27B
// __destroy_aux 0x004F72ED, which calls the 34B reference-slot cleanup
// 0x005F8FCC with flags 0 for every 4B slot (as Rva002B7000Dtor.cpp).
struct Rva005F8FCC {void *rva005F8FCC(unsigned);};
namespace _STL {
template<> __declspec(noinline) inline void __destroy_aux<Rva005FA197Element *>(Rva005FA197Element *first,Rva005FA197Element *last,const __false_type &)
{
 for(;first!=last;++first) reinterpret_cast<Rva005F8FCC *>(first)->rva005F8FCC(0);
}
template<> __declspec(noinline) inline void __destroy_aux<Rva005FA1CEElement *>(Rva005FA1CEElement *first,Rva005FA1CEElement *last,const __false_type &)
{
 for(;first!=last;++first) reinterpret_cast<Rva005F8FCC *>(first)->rva005F8FCC(0);
}
template<> __declspec(noinline) inline void _Destroy<Rva005FA197Element *>(Rva005FA197Element *first,Rva005FA197Element *last)
{
 __false_type trivial;
 __destroy_aux(first,last,trivial);
}
template<> __declspec(noinline) inline void _Destroy<Rva005FA1CEElement *>(Rva005FA1CEElement *first,Rva005FA1CEElement *last)
{
 __false_type trivial;
 __destroy_aux(first,last,trivial);
}
template<> inline void allocator<BfmeStringRecord005F93E3>::deallocate(BfmeStringRecord005F93E3 *p,size_t) const {if(p)::free(p);}
template<> void vector<BfmeStringRecord005F93E3>::push_back(const BfmeStringRecord005F93E3 &);
}
// Retail's 4-byte vectors share one clear worker (0x00577EF1, rowed as
// vector<Rva002B9062Element>::_M_clear in StlportVectorClearRva00577EF1.cpp);
// the page vectors' _M_insert_overflow copies call it through this view.
struct Rva002B9062Element;
namespace _STL { template <> void vector<Rva002B9062Element, allocator<Rva002B9062Element> >::_M_clear(); }
struct Rva002B9062ClearAccess : _STL::vector<Rva002B9062Element>
{
	__forceinline void clearWorker() { _M_clear(); }
};
namespace _STL {
template <> __declspec(dllimport) __forceinline void vector<Rva005FA197Element, allocator<Rva005FA197Element> >::_M_clear() { ((Rva002B9062ClearAccess *)this)->clearWorker(); }
template <> __declspec(dllimport) __forceinline void vector<Rva005FA1CEElement, allocator<Rva005FA1CEElement> >::_M_clear() { ((Rva002B9062ClearAccess *)this)->clearWorker(); }
}
namespace AptUtils { const char *__cdecl SkipLevelN(const char *); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *); }
class Object;
#include "../../../../../Include/Common/Rva00575674.h"
class Rva005CB260Properties {public: void rva005CB260(int,unsigned int,unsigned int,const UnicodeString &);};
class Rva005CC208Select {public: void rva005CC208(int);};
// Tab page views (pages are Rva005FA0C9/Rva005FA0F7; +0x28 is the page state, 3 = settled).
class Rva005F94C2 {public: void rva005F94C2(); void rva005F9567(); char m_pad[0x28]; int m_state;};
class Rva005F8F31 {public: void rva005F8F31();};
// Tab window forwarder 0x005CB265 (ICF-folded vslot thunk); the qualified call binds the pin directly.
class Rva005CB265 {public: virtual int rva005CB265();};
namespace StrategicHUD {class BattlePromptPlayerTabsMovieClip {public: void SetTabCount(unsigned int);};}
namespace StrategicHUD {class BattlePromptMovieClip {public: class Impl;};}
class Rva005F8E37 {public: Rva005F8E37(StrategicHUD::BattlePromptMovieClip::Impl *,int,const AsciiString &);private:char opaque[0x40];};
class Rva005F8E5A {public: Rva005F8E5A(StrategicHUD::BattlePromptMovieClip::Impl *,int,const AsciiString &);private:char opaque[0x3c];};
struct BattlePromptEnemyTabsSlot {Rva005F8E5A *ptr;void set(Rva005F8E5A *p){((Rva00575674 *)this)->rva00575674((Object *)p);}};
struct BattlePromptTabsSlot {Rva005F8E37 *ptr;void set(Rva005F8E37 *p){((Rva00575674 *)this)->rva00575674((Object *)p);}};
class StrategicHUD::BattlePromptMovieClip::Impl {
public: void OnAllyTabsLoaded(const char *);void OnEnemyTabsLoaded(const char *);void AddAlly(const Rva005F91F3Src &);void AddEnemy(const Rva005F91F3Src &);void rva005F963A(int);void rva005F9687(int);void rva005F96D4();
private: char prefix[0x20];_STL::vector<BfmeStringRecord005F93E3> allies;BattlePromptTabsSlot allyTabs;_STL::vector<BfmeStringRecord005F93E3> enemies;BattlePromptEnemyTabsSlot enemyTabs;_STL::vector<Rva005FA197Element> allyPages;int selectedAlly;_STL::vector<Rva005FA1CEElement> enemyPages;int selectedEnemy;
};

// Keep the verified eight-byte destructor selectable with its exact implicit twins.
inline BfmeStringRecord005F93E3::~BfmeStringRecord005F93E3() {}

void StrategicHUD::BattlePromptMovieClip::Impl::OnAllyTabsLoaded(const char *path){
 if(allyTabs.ptr)return;
 allyTabs.set(new Rva005F8E37(this,AptUtils::LevelIndexFromTarget(path),AsciiString(AptUtils::SkipLevelN(path))));
 int count=allies.size();
 ((StrategicHUD::BattlePromptPlayerTabsMovieClip *)allyTabs.ptr)->SetTabCount(count);
 for(int i=0;i<count;++i){
  BfmeStringRecord005F93E3 &item=allies[i];
  ((Rva005CB260Properties *)allyTabs.ptr)->rva005CB260(i,item.word0,item.word1,item.text);
 }
 _STL::vector<BfmeStringRecord005F93E3>().swap(allies);
 if(selectedAlly>=0)((Rva005CC208Select *)allyTabs.ptr)->rva005CC208(selectedAlly);
}

void StrategicHUD::BattlePromptMovieClip::Impl::OnEnemyTabsLoaded(const char *path){
 if(enemyTabs.ptr)return;
 enemyTabs.set(new Rva005F8E5A(this,AptUtils::LevelIndexFromTarget(path),AsciiString(AptUtils::SkipLevelN(path))));
 int count=enemies.size();
 ((StrategicHUD::BattlePromptPlayerTabsMovieClip *)enemyTabs.ptr)->SetTabCount(count);
 for(int i=0;i<count;++i){
  BfmeStringRecord005F93E3 &item=enemies[i];
  ((Rva005CB260Properties *)enemyTabs.ptr)->rva005CB260(i,item.word0,item.word1,item.text);
 }
 _STL::vector<BfmeStringRecord005F93E3>().swap(enemies);
 if(selectedEnemy>=0)((Rva005CC208Select *)enemyTabs.ptr)->rva005CC208(selectedEnemy);
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva005FA0C9 {public:Rva005FA0C9(StrategicHUD::BattlePromptMovieClip::Impl *,int,const Rva005F91F3Src &);unsigned int vtable;int refs;char rest[0x28];};
// ?Rva005FA197Element::Rva005FA197Element present-unmatched
inline Rva005FA197Element::Rva005FA197Element(Rva005FA0C9 *p):ptr(p){if(p)++p->refs;}
// ?Rva005FA197Element::Rva005FA197Element present-unmatched
inline Rva005FA197Element::Rva005FA197Element(const Rva005FA197Element &other):ptr(other.ptr){if(ptr)++ptr->refs;}
inline Rva005FA197Element::~Rva005FA197Element(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);}
void StrategicHUD::BattlePromptMovieClip::Impl::AddAlly(const Rva005F91F3Src &item) {
 allies.push_back((const BfmeStringRecord005F93E3 &)Rva005F91F3(item));
 try {
  Rva005FA197Element page(new Rva005FA0C9(this,allyPages.size(),item));
  allyPages.push_back(page);
 } catch(...) {allies.pop_back();throw;}
}

class Rva005FA0F7 {public:Rva005FA0F7(StrategicHUD::BattlePromptMovieClip::Impl *,int,const Rva005F91F3Src &);unsigned int vtable;int refs;char rest[0x28];};
// ?Rva005FA1CEElement::Rva005FA1CEElement present-unmatched
inline Rva005FA1CEElement::Rva005FA1CEElement(Rva005FA0F7 *p):ptr(p){if(p)++p->refs;}
// ?Rva005FA1CEElement::Rva005FA1CEElement present-unmatched
inline Rva005FA1CEElement::Rva005FA1CEElement(const Rva005FA1CEElement &other):ptr(other.ptr){if(ptr)++ptr->refs;}
inline Rva005FA1CEElement::~Rva005FA1CEElement(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);}
void StrategicHUD::BattlePromptMovieClip::Impl::AddEnemy(const Rva005F91F3Src &item) {
 enemies.push_back((const BfmeStringRecord005F93E3 &)Rva005F91F3(item));
 try {
  Rva005FA1CEElement page(new Rva005FA0F7(this,enemyPages.size(),item));
  enemyPages.push_back(page);
 } catch(...) {enemies.pop_back();throw;}
}

// ?rva005F963A: select the ally page. A settled (state 3) or absent current
// page lets the selection change: the old page fades out, the tab window gets
// the new index, the new page fades in. 0x005F9687 is the enemy twin.
void StrategicHUD::BattlePromptMovieClip::Impl::rva005F963A(int index){
 int cur=selectedAlly;
 if(cur>=0&&((Rva005F94C2 *)allyPages[cur].ptr)->m_state!=3)return;
 if(index==cur)return;
 if(cur>=0)((Rva005F94C2 *)allyPages[cur].ptr)->rva005F9567();
 selectedAlly=index;
 ((Rva005CC208Select *)allyTabs.ptr)->rva005CC208(index);
 ((Rva005F94C2 *)allyPages[selectedAlly].ptr)->rva005F94C2();
}

void StrategicHUD::BattlePromptMovieClip::Impl::rva005F9687(int index){
 int cur=selectedEnemy;
 if(cur>=0&&((Rva005F94C2 *)enemyPages[cur].ptr)->m_state!=3)return;
 if(index==cur)return;
 if(cur>=0)((Rva005F94C2 *)enemyPages[cur].ptr)->rva005F9567();
 selectedEnemy=index;
 ((Rva005CC208Select *)enemyTabs.ptr)->rva005CC208(index);
 ((Rva005F94C2 *)enemyPages[selectedEnemy].ptr)->rva005F94C2();
}

// ?rva005F96D4: with nothing selected, show the first live page of each side,
// then close both tab windows and release every page.
void StrategicHUD::BattlePromptMovieClip::Impl::rva005F96D4(){
 if(selectedAlly<0&&allyPages.begin()!=allyPages.end()&&((Rva005F94C2 *)allyPages[0].ptr)->m_state!=0){
  ((Rva005F94C2 *)allyPages[0].ptr)->rva005F94C2();
  selectedAlly=0;
  if(allyTabs.ptr)((Rva005CC208Select *)allyTabs.ptr)->rva005CC208(0);
 }
 if(selectedEnemy<0&&enemyPages.begin()!=enemyPages.end()&&((Rva005F94C2 *)enemyPages[0].ptr)->m_state!=0){
  ((Rva005F94C2 *)enemyPages[0].ptr)->rva005F94C2();
  selectedEnemy=0;
  if(enemyTabs.ptr)((Rva005CC208Select *)enemyTabs.ptr)->rva005CC208(0);
 }
 if(allyTabs.ptr)((Rva005CB265 *)allyTabs.ptr)->Rva005CB265::rva005CB265();
 if(enemyTabs.ptr)((Rva005CB265 *)enemyTabs.ptr)->Rva005CB265::rva005CB265();
 _STL::vector<Rva005FA197Element>::iterator i=allyPages.begin();
 _STL::vector<Rva005FA197Element>::iterator iEnd=allyPages.end();
 for(;i!=iEnd;++i)((Rva005F8F31 *)i->ptr)->rva005F8F31();
 _STL::vector<Rva005FA1CEElement>::iterator jEnd=enemyPages.end();
 for(_STL::vector<Rva005FA1CEElement>::iterator j=enemyPages.begin();j!=jEnd;++j)((Rva005F8F31 *)j->ptr)->rva005F8F31();
}

// PlayerPageFrame: WorldBuilder VA01609450 assertions111/123 name
// StrategicHUD::`anonymous-namespace'::PlayerPageFrame::PlayerPageFrame in
// StrategicHUDBattlePromptMovieClip.cpp. A named reconstruction namespace
// allows its existing recovered callers to share the class identity.
// Target: native RVA005F9DCB..005FA0C9 RET20; ECX receiver and five stack args;
// vtable879D20 = deleting dtor5F942E then two pure virtual slots.
// Ally/Enemy constructors5FA0C9/5FA0F7 supply level/name/side/index/factory.
// Native stores prove all offsets below; FuncInfo95ED10 has11 states:
// base/name/factory/commands/page, prefix/number and four string temporaries.
// Existing destructor5F8FEE and callbacks5F8E0D/5F8E22 moved here unchanged
// in behavior; original names/layout are from WB and native evidence, no donor.
// Defining the first concat operator (established RegistryAsciiPath idiom)
// is significant even when emitted out of line: MSVC preserves its three
// temporary homes A4/94/40. A declaration alone wrongly shares that storage.
#include "ascii_string.h"
// Keep ??1?$_Vector_base@UBfmeStringRecord005F93E3@@V?$allocator@UBfmeStringRecord005F93E3@@@_STL
// inline: retail's ~vector at 0x005F97D4 (rowed through this unit's fold proof) frees the
// storage itself. The out-of-line copy an unwind action still needs is the same body the
// other units emit.
struct BfmeStringRecord005F93E3;
namespace _STL { template <> inline _Vector_base<BfmeStringRecord005F93E3,allocator<BfmeStringRecord005F93E3> >::~_Vector_base() { if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); } }
// Suppress this TU's non-retail copy of ??$__destroy@PAURva005FA1CEElement@@U1@@_STL@@YAXPAURva005FA1CEElement@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005FA1CEElement;
namespace _STL { template <> void __destroy<Rva005FA1CEElement *,Rva005FA1CEElement>(Rva005FA1CEElement *,Rva005FA1CEElement *,Rva005FA1CEElement *); }
// Suppress this TU's non-retail copy of ??$__destroy@PAURva005FA197Element@@U1@@_STL@@YAXPAURva005FA197Element@@00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005FA197Element;
namespace _STL { template <> void __destroy<Rva005FA197Element *,Rva005FA197Element>(Rva005FA197Element *,Rva005FA197Element *,Rva005FA197Element *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva005FA1CEElement@@@_STL@@YAXPAURva005FA1CEElement@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005FA1CEElement;
namespace _STL { template <> void __destroy_aux<Rva005FA1CEElement *>(Rva005FA1CEElement *,Rva005FA1CEElement *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva005FA197Element@@@_STL@@YAXPAURva005FA197Element@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005FA197Element;
namespace _STL { template <> void __destroy_aux<Rva005FA197Element *>(Rva005FA197Element *,Rva005FA197Element *,__false_type const &); }

#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Reference holder: copy AddRefs; dtor 0x005F8F96 releases.
class Rva005F8F96
{
public:
	Rva005F8F96() : m_ptr(0) {}
	Rva005F8F96(const Rva005F8F96 &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->references++;
	}
	~Rva005F8F96() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }

	TargetRef00217D4C *m_ptr;
};

// The ally / enemy record (Rva005F91F3Copy.cpp): page factory reference first.


#include "../../../../../../Libraries/Source/Apt/AptCommandTarget.h"

#include "../../../../../Include/Common/DelegateDesc.h"

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

class Rva00579E47 {public:Rva00579E47(const DelegateDesc &); void *ptr;};
template <class T> class AptRef {
public:
 AptRef(const DelegateDesc *desc):holder(*desc){}
 ~AptRef(){if(holder.ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)holder.ptr);}
private:Rva00579E47 holder;
};
#include "../../../../../../Libraries/Source/Apt/AptCommandMapAdder.h"

static __forceinline void AddCommandMapDelegate(AptCommandMapAdder &adder, const AsciiString &name, DelegateDesc desc)
{
	adder.AddCommandMap(name, &desc);
}

// Expression-template concat nodes (System/RegistryAsciiPath.cpp family).
#include "../../../../../Include/Common/Rva000B3F84Pair.h"

#include "../../../../../Include/Common/AsciiStringRef.h"

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	Rva000B3F84Pair m_right;
};

struct Rva005D32EC : AsciiStringPlusStringText
{
	Rva000B3F84Pair m_right2;
};

struct Rva005D3311 : Rva005D32EC
{
	Rva000B3F84Pair m_right3;
};

struct Rva005F8FA2Src
{
	int m_data[8];
};

struct Rva005F8FA2Dst
{
	int m_data[9];
};

// The "... + AsciiString" node (36 bytes); converts through 0x005F9D69.
class Rva005F9852
{
public:
	operator AsciiString();
};

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}

Rva005D32EC __cdecl operator+(const AsciiStringPlusStringText &left, const char *right);
Rva005D3311 __cdecl operator+(const Rva005D32EC &left, const char *right);
Rva005F8FA2Dst *__cdecl Rva005F8FA2Copy(Rva005F8FA2Dst *dest, Rva005F8FA2Src *src, int value);

struct AsciiStringRefWithChar
{
	const AsciiString *m_string;
	char m_char;
};

struct AsciiStringCharPlusText : AsciiStringRefWithChar
{
	Rva000B3F84Pair m_right;
};

struct Rva005D2F96S16
{
	int m0, m1, m2, m3;
};

struct Rva005D2F96Base24
{
	int m0, m1, m2, m3, m4, m5;
};

struct Rva005D2F96S24 : Rva005D2F96Base24
{
};

Rva000B3F84Pair __cdecl Rva00108B93Make(const char *text);
AsciiStringCharPlusText __cdecl operator+(const AsciiStringRefWithChar &left, const char *right);
Rva005D2F96S24 __cdecl Rva005D2F96Build(const Rva005D2F96S16 &left, const char *right);
class Rva002D4688;
AsciiString __cdecl Rva002D56C3Construct(Rva002D4688 &node);
int __cdecl Rva0052519DFire(void *target, void *owner, const char *prefix, const char *event, int *result);
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// Reference-counted base Rva0007DF07: vtable 0x007C6F20 and its destructor 0x004E84A4.
#include "../../../../../Include/Common/Rva0007DF07.h"

namespace StrategicHUD {
class PlayerPageFrame : public Rva0007DF07
{
public:
	PlayerPageFrame(int level, const AsciiString &name, const char *side, int index, const Rva005F91F3Src &data);
	virtual ~PlayerPageFrame();
 virtual void vslot01() = 0;
 virtual void vslot02() = 0;
	void OnPageLoaded(const char *path);     // 0x005F9053
	void InternalOnOpen(const char *path);   // 0x005F8E0D
	void InternalOnClosed(const char *path); // 0x005F8E22

private:
	int m_level;                   // +0x08
	AsciiString m_name;            // +0x0C
	const char *m_side;            // +0x10
	int m_index;                   // +0x14
	Rva005F8F96 m_pageFactory;     // +0x18
	AptCommandMapAdder m_commands; // +0x1C
	int m_state;                   // +0x28
	Rva005F8F96 m_page;            // +0x2C
};

PlayerPageFrame::PlayerPageFrame(int level, const AsciiString &name, const char *side, int index, const Rva005F91F3Src &data)
	: m_level(level), m_name(name), m_side(side), m_index(index), m_pageFactory(*(const Rva005F8F96 *)&data.header), m_state(0)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	AsciiString number;
	number.format("%d", m_index);
	Rva005F8FA2Dst node;
	AddCommandMapDelegate(m_commands, *(Rva005F9852 *)Rva005F8FA2Copy(&node, (Rva005F8FA2Src *)&(prefix + m_name + "_On" + m_side + "PageLoaded"), (int)&number), DelegateDesc(this, &PlayerPageFrame::OnPageLoaded));
	AddCommandMapDelegate(m_commands, *(Rva005F9852 *)Rva005F8FA2Copy(&node, (Rva005F8FA2Src *)&(prefix + m_name + "_On" + m_side + "PageFrameOpen"), (int)&number), DelegateDesc(this, &PlayerPageFrame::InternalOnOpen));
	AddCommandMapDelegate(m_commands, *(Rva005F9852 *)Rva005F8FA2Copy(&node, (Rva005F8FA2Src *)&(prefix + m_name + "_On" + m_side + "PageFrameClosed"), (int)&number), DelegateDesc(this, &PlayerPageFrame::InternalOnClosed));
	Rva0052519DFire((void *)g_bfmeAptWindowManager, (void *)m_level, m_name.str(),
		Rva002D56C3Construct((Rva002D4688 &)(Rva005D2F96Base24 &)Rva005D2F96Build(
			(const Rva005D2F96S16 &)operator+(
				(const AsciiStringRefWithChar &)Rva00108B93Make("Add"),
				m_side),
			"Page")).str(), &m_index);
}

PlayerPageFrame::~PlayerPageFrame() {}
void PlayerPageFrame::InternalOnOpen(const char *) { if (m_state==2) { m_state=3; vslot01(); } }
void PlayerPageFrame::InternalOnClosed(const char *) { if (m_state==4) { m_state=1; vslot02(); } }
}
