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
const char *Rva00412845AfterLevel(const char *);
int Rva004128BBGetLevel(const char *);
class Object;
class Rva00575674 {public: void rva00575674(Object *);};
class Rva005CB260 {public: void rva005CB260();};
class Rva005CC208 {public: virtual void rva005CC208();};
class Rva005CB260Properties {public: void rva005CB260(int,unsigned int,unsigned int,const UnicodeString &);};
class Rva005CC208Select {public: void rva005CC208(int);};
namespace StrategicHUD {class BattlePromptPlayerTabsMovieClip {public: void SetTabCount(int);};}
namespace StrategicHUD {class BattlePromptMovieClip {public: class Impl;};}
class Rva005F8E37 {public: Rva005F8E37(StrategicHUD::BattlePromptMovieClip::Impl *,int,const AsciiString &);private:char opaque[0x40];};
class Rva005F8E5A {public: Rva005F8E5A(StrategicHUD::BattlePromptMovieClip::Impl *,int,const AsciiString &);private:char opaque[0x3c];};
struct BattlePromptEnemyTabsSlot {Rva005F8E5A *ptr;void set(Rva005F8E5A *p){((Rva00575674 *)this)->rva00575674((Object *)p);}};
struct BattlePromptTabsSlot {Rva005F8E37 *ptr;void set(Rva005F8E37 *p){((Rva00575674 *)this)->rva00575674((Object *)p);}};
class StrategicHUD::BattlePromptMovieClip::Impl {
public: void OnAllyTabsLoaded(const char *);void OnEnemyTabsLoaded(const char *);void AddAlly(const Rva005F91F3Src &);void AddEnemy(const Rva005F91F3Src &);
private: char prefix[0x20];_STL::vector<BfmeStringRecord005F93E3> allies;BattlePromptTabsSlot allyTabs;_STL::vector<BfmeStringRecord005F93E3> enemies;BattlePromptEnemyTabsSlot enemyTabs;_STL::vector<Rva005FA197Element> allyPages;int selectedAlly;_STL::vector<Rva005FA1CEElement> enemyPages;int selectedEnemy;
};

BfmeStringRecord005F93E3::~BfmeStringRecord005F93E3() {}

void StrategicHUD::BattlePromptMovieClip::Impl::OnAllyTabsLoaded(const char *path){
 if(allyTabs.ptr)return;
 allyTabs.set(new Rva005F8E37(this,Rva004128BBGetLevel(path),AsciiString(Rva00412845AfterLevel(path))));
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
 enemyTabs.set(new Rva005F8E5A(this,Rva004128BBGetLevel(path),AsciiString(Rva00412845AfterLevel(path))));
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
