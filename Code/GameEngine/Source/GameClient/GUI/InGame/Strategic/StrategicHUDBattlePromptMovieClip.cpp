// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WB StrategicHUDBattlePromptMovieClip.cpp:795..837 identifies the paired tab
// callbacks. Native records have two 32-bit properties and a wide string at +8,
// stride 12; destructor 5F9217 tail-releases that string.
// This view preserves the already rowed BfmeStringRecord005F93E3 push-back type.
// Tabs and helper views below assert only witnessed receiver/stack arguments.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
struct BfmeStringRecord005F93E3 {unsigned int word0,word1;UnicodeString text;~BfmeStringRecord005F93E3();};
struct Rva005F91F3Src {unsigned int header,word0,word1;UnicodeString text;};
struct Rva005F91F3 {unsigned int word0,word1;UnicodeString text;Rva005F91F3(const Rva005F91F3Src &);};
void Rva00030830FreeAllocation(void *);
class Rva005FA0C9;
struct Rva005FA197Element {Rva005FA0C9 *ptr;Rva005FA197Element(Rva005FA0C9 *);Rva005FA197Element(const Rva005FA197Element &);~Rva005FA197Element();};
class Rva005FA0F7;
struct Rva005FA1CEElement {Rva005FA0F7 *ptr;Rva005FA1CEElement(Rva005FA0F7 *);Rva005FA1CEElement(const Rva005FA1CEElement &);~Rva005FA1CEElement();};
namespace _STL {
template<> inline void allocator<BfmeStringRecord005F93E3>::deallocate(BfmeStringRecord005F93E3 *p,size_t) const {if(p)::Rva00030830FreeAllocation(p);}
template<> void vector<BfmeStringRecord005F93E3>::push_back(const BfmeStringRecord005F93E3 &);
}
namespace AptUtils { const char *__cdecl SkipLevelN(const char *); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *); }
class Object;
class Rva00575674 {public: void rva00575674(Object *);};
class Rva005CB260 {public: void rva005CB260();};
class Rva005CC208 {public: virtual void rva005CC208();};
class Rva005CB260Properties {public: void rva005CB260(int,unsigned int,unsigned int,const UnicodeString &);};
class Rva005CC208Select {public: void rva005CC208(int);};
// Tab page views (pages are Rva005FA0C9/Rva005FA0F7; +0x28 is the page state, 3 = settled).
class Rva005F94C2 {public: void rva005F94C2(); void rva005F9567(); char m_pad[0x28]; int m_state;};
class Rva005F8F31 {public: void rva005F8F31();};
// Tab window forwarder 0x005CB265 (ICF-folded vslot thunk); the qualified call binds the pin directly.
class Rva005CB265 {public: virtual int rva005CB265();};
namespace StrategicHUD {class BattlePromptPlayerTabsMovieClip {public: void SetTabCount(int);};}
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
// ?Rva005FA197Element::~Rva005FA197Element present-unmatched
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
// ?Rva005FA1CEElement::~Rva005FA1CEElement present-unmatched
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
