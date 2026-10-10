// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common
// WB 01430060 and native 0056833F..0056850D establish the Impl constructor.
// Native observer table has two callback slots and no destructor slot; the
// complete 40-byte layout agrees with the matched destructor and hotkey method.
// Constructor registers its own instance, initializes the per-stance records,
// unregisters the button hotkey, finds the selected StancesBehavior, attaches
// its observer, selects the stance image and registers its individual hotkeys.
// The 76-byte record-array constructor remains a proven native callee; its
// separate bank differs only in allocation-unwind bookkeeping.
// The helper is rehomed from the existing stance TU so its actual local
// optimizer-selected EDI parameter is preserved rather than approximated.
#include <list>
#include <vector>
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
class Image; class GameWindow; class StancesBehavior;
class Rva0086CE84Observer {public:
 virtual void onDestroyingStancesBehavior(StancesBehavior&) {}
 virtual void onStancesBehaviorStanceChanged(StancesBehavior&,int,int) {}
 __forceinline ~Rva0086CE84Observer(){}
};
class Rva00005C357FPtrChaseField {public:int get()const;};
class StanceMenuFactory {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void *getMenu();};
class CommandButton {public:int getStance(int);const AsciiString &rva0035B1E9()const;const Image *rva0035B19E()const;char pad[0x234];_STL::vector<int> stances;};
struct Rva005681CE { Rva005681CE(unsigned); ~Rva005681CE(); void *start,*finish,*limit; };
class Rva00200667 : public _STL::list<int> {public:~Rva00200667();};
Rva00200667 *Rva005680F9GetInstances();
void *GadgetButtonGetData(GameWindow *);
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *,const Image *);
class HotKeyManager {public:AsciiString rva00358CCD(const AsciiString &);};
class Rva00E01E28Owner;extern Rva00E01E28Owner *g_00E01E28;
struct Rva003597C3Element {char bytes[8];};
class Rva00359811 {public:unsigned rva00359811(const Rva003597C3Element &,bool);};
enum NameKeyType {NK_UNKNOWN=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const char *);};
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Object;
extern GameLogic *TheGameLogic;
struct Rva002BA8F1Listener;
struct Rva005A0B4CList {void append(Rva002BA8F1Listener *);};
class StancesBehavior {public:int rva0045ED4B()const;char pad[0x20];Rva005A0B4CList observers;};
class Rva0035B424 {public:void rva0035B424(int);};
struct Drawable {char pad[0xfc];Object *object;};
typedef _STL::list<Drawable *> DrawableList;
class InGameUI;extern InGameUI *TheInGameUI;
class StanceUISelectionView {public:
#define SLOT(N) virtual void s##N();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
 SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
 SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
 SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
 SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
 SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
 SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
 SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
 SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
 SLOT(72)
#undef SLOT
 virtual const DrawableList *selection();
};
__declspec(noinline) static int StanceToButtonSlot(CommandButton *button,int stance){
 int count=button->stances.size();for(int i=0;i<count;++i)if(button->getStance(i)==stance)return i;return -1;
}
class InGameToggleStanceCommandButton {public:class Impl:public Rva0086CE84Observer {public:
 Impl(Rva00005C357FPtrChaseField *,StanceMenuFactory *,GameWindow *);
 ~Impl();void rva00567DA6();
 virtual void onDestroyingStancesBehavior(StancesBehavior&);
 virtual void onStancesBehaviorStanceChanged(StancesBehavior&,int,int);
 private:_STL::list<int>::iterator listPosition;Rva00005C357FPtrChaseField *owner08;StanceMenuFactory *factory0C;GameWindow *window10;CommandButton *button14;StancesBehavior *behavior18;Rva005681CE hotKeys;
};};
class Object {friend class InGameToggleStanceCommandButton::Impl;protected:Module *findModule(NameKeyType)const;};
InGameToggleStanceCommandButton::Impl::Impl(Rva00005C357FPtrChaseField *owner,StanceMenuFactory *factory,GameWindow *window)
 :listPosition(Rva005680F9GetInstances()->insert(Rva005680F9GetInstances()->end(),reinterpret_cast<int>(this))),owner08(owner),factory0C(factory),window10(window),button14(static_cast<CommandButton *>(GadgetButtonGetData(window))),behavior18(0),hotKeys(button14->stances.size())
{
 if(g_00E01E28){
  AsciiString hotkey=reinterpret_cast<HotKeyManager *>(g_00E01E28)->rva00358CCD(button14->rva0035B1E9());
  if(!hotkey.isEmpty())reinterpret_cast<Rva00359811 *>(g_00E01E28)->rva00359811(reinterpret_cast<const Rva003597C3Element &>(hotkey),false);
 }
 int stance=0;
 static NameKeyType key=TheNameKeyGenerator->nameToKey("StancesBehavior");
 int id=owner08->get();
 if(id){
  Object *object=TheGameLogic->findObjectByID((ObjectID)id);
  if(object){
   behavior18=reinterpret_cast<StancesBehavior *>(object->findModule(key));
   if(behavior18){stance=behavior18->rva0045ED4B();behavior18->observers.append(reinterpret_cast<Rva002BA8F1Listener *>(this));}
  }
 }else{
  const DrawableList *selected=reinterpret_cast<StanceUISelectionView *>(TheInGameUI)->selection();
  DrawableList::const_iterator end=selected->end();
  for(DrawableList::const_iterator it=selected->begin();it!=end;++it){
   Object *object=(*it)->object;if(!object)continue;
   behavior18=reinterpret_cast<StancesBehavior *>(object->findModule(key));
   if(behavior18){stance=behavior18->rva0045ED4B();behavior18->observers.append(reinterpret_cast<Rva002BA8F1Listener *>(this));break;}
  }
 }
 int slot=StanceToButtonSlot(button14,stance);
 if(slot>=0)reinterpret_cast<Rva0035B424 *>(button14)->rva0035B424(slot);
 GadgetButtonSetEnabledImage_Rva002C0433(window10,button14->rva0035B19E());
 rva00567DA6();
}
