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
struct BattlePromptTabsSlot {Rva005F8E37 *ptr;void set(Rva005F8E37 *p){((Rva00575674 *)this)->rva00575674((Object *)p);}};
class StrategicHUD::BattlePromptMovieClip::Impl {
public: void OnAllyTabsLoaded(const char *);void OnEnemyTabsLoaded(const char *);void AddAlly(const Rva005F91F3Src &);void AddEnemy(const Rva005F91F3Src &);
private: char prefix[0x20];_STL::vector<BfmeStringRecord005F93E3> allies;BattlePromptTabsSlot allyTabs;_STL::vector<BfmeStringRecord005F93E3> enemies;BattlePromptTabsSlot enemyTabs;char allyPages[12];int selectedAlly;char enemyPages[12];int selectedEnemy;
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
