// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX- /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// Native 0021CB1F..0021CEF1, RET0. WB B7CCE0 unnamed debug sibling
// and existing CreateAHero getters establish text-cache traversal semantics.
// All member offsets below are target facts; original helper name is unknown.
// ZH GameText-interface fetch and canonical BFME2 strings are semantic guides.
// Record-label role names are structural inferences; offsets and call protocols
// come from retail/WB evidence. Inline GetKey materializes the target key load
// before argument pushes, preserving the native receiver register allocation.
// Native slot14 accepts an AsciiString reference and a null existence output.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class GameTextInterface;
extern GameTextInterface *TheGameText;
class ControlBar;
extern ControlBar *TheControlBar;
class Rva0040AAD5;
extern Rva0040AAD5 *TheAwardSystemManager;
class Rva0021CB1FTextView {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();

 virtual UnicodeString fetch(const AsciiString &, bool *);
};
struct Rva0021CB1FClassRecord { char opaque00[32]; };
struct Rva0021CB1FBinder {int key;__forceinline int GetKey() const{return key;} AsciiString name,description;char opaque0C[8];};
struct Rva0021CB1FButton {char opaque00[0x18];Rva0021CB1FButton *next;};
struct Rva0021CB1FControlBarView {char opaque00[0x2C];Rva0021CB1FButton *head;};
class Rva0035B29E {public:const AsciiString *rva0035B29E(int);};
class Rva0035B232 {public:const AsciiString *rva0035B232(int);};
class Rva0040A82DDivAvgField {public:int get() const;};
class Rva0040A85FDivAvgField {public:int get() const;};
struct Rva0040A83AElement {char opaque00[0x10];AsciiString description,name;char opaque18[0x10];};
struct Rva0040A86CElement {char opaque00[0x54];AsciiString description,name;char opaque5C[0xC];};
class Rva0040A83A {public:Rva0040A83AElement *rva0040A83A(unsigned);};
class Rva0040A86C {public:Rva0040A86CElement *rva0040A86C(unsigned);};
#include "../../../Include/GameLogic/CreateAHeroManager.h"
// The canonical header keeps these vector records opaque at +0x14C and +0x168.
void CreateAHeroManager::rva0021CB1F() {
 for(unsigned classIndex=0;classIndex<reinterpret_cast<const _STL::vector<Rva0021CB1FClassRecord> *>(field14C)->size();++classIndex) {
  reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(GetClassDescTag(classIndex),0);
  reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(GetClassNameTag(classIndex),0);
  reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(GetClassPowersTag(classIndex),0);
  for(unsigned subClassIndex=0;subClassIndex<(unsigned)rva00219D52(classIndex);++subClassIndex) {
   reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(GetSubClassNameTag(classIndex,subClassIndex),0);
   reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(GetSubClassDescTag(classIndex,subClassIndex),0);
   for(unsigned binderIndex=0;binderIndex<reinterpret_cast<const _STL::vector<Rva0021CB1FBinder> *>(field168)->size();++binderIndex) {
    Rva0021CB1FBinder *binding=static_cast<Rva0021CB1FBinder*>(GetBlingBinder(binderIndex));
    reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(binding->description,0);
    reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(binding->name,0);
    for(unsigned k=0;k<(unsigned)rva0021BEE0(binding->GetKey(),classIndex,subClassIndex);++k) {
     reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(GetBlingDescTag(binding->GetKey(),classIndex,subClassIndex,k),0);
     reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(GetBlingNameTag(binding->GetKey(),classIndex,subClassIndex,k),0);
    }
   }
  }
 }
 for(Rva0021CB1FButton *button=reinterpret_cast<Rva0021CB1FControlBarView*>(TheControlBar)->head;button;button=button->next) {
  for(int i=0;!reinterpret_cast<const StringBase<char>*>(reinterpret_cast<Rva0035B29E*>(button)->rva0035B29E(i))->isEmpty();++i)
   reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(*reinterpret_cast<Rva0035B29E*>(button)->rva0035B29E(i),0);
  for(int i=0;!reinterpret_cast<const StringBase<char>*>(reinterpret_cast<Rva0035B232*>(button)->rva0035B232(i))->isEmpty();++i)
   reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(*reinterpret_cast<Rva0035B232*>(button)->rva0035B232(i),0);
 }
 for(unsigned i=0;i<(unsigned)reinterpret_cast<Rva0040A82DDivAvgField*>(TheAwardSystemManager)->get();++i) {
  Rva0040A83AElement *item=reinterpret_cast<Rva0040A83A*>(TheAwardSystemManager)->rva0040A83A(i);
  reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(item->description,0);
  reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(item->name,0);
 }
 for(unsigned i=0;i<(unsigned)reinterpret_cast<Rva0040A85FDivAvgField*>(TheAwardSystemManager)->get();++i) {
  Rva0040A86CElement *item=reinterpret_cast<Rva0040A86C*>(TheAwardSystemManager)->rva0040A86C(i);
  reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(item->description,0);
  reinterpret_cast<Rva0021CB1FTextView*>(TheGameText)->fetch(item->name,0);
 }
}
