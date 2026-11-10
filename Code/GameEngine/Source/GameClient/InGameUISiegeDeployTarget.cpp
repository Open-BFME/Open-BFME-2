// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
// InGameUI 0x0029CC19 (441 bytes): whether the selection can siege-deploy
// onto the target. For a target of template kind bit 0x10000000 (+0x10C) with
// a selection, each selected uncontained object whose template carries bit
// 0x20000000 (+0x110) and is ready for its siege deploy command (the ladder
// variant for template bit 0x800 at +0x118), lacking status 59, answers yes
// when it has no AI, or when the target's SiegeDockingBehavior gives it no
// dock position or its AI has a quick path to that position. Strings,
// callees and offsets are retail's; the name stays address-derived.
// Retail saves EBX/ESI/EDI only after the opening test: that test is an
// inlined helper and the walk its else scope. Object::findModule is rowed
// protected (0x0028B6D6), so this view keeps it protected for InGameUI.
#include "unicode_string.h"
#include "ascii_string.h"
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include "Coord3D.h"
class Object;
class CommandButton;
class Module;
class AIUpdateInterface;
enum NameKeyType { INVALID_KEY=0 };
namespace _STL {
template<> _List_base<const Object*,allocator<const Object*> >::_List_base(const allocator<const Object*>&);
template<> _List_base<const Object*,allocator<const Object*> >::~_List_base();
}
class Object;
class Drawable;
enum ObjectID { INVALID_ID=0 };
enum ObjectStatusTypes { STATUS_ZERO=0 };
#include "../../Include/Common/ThingTemplate.h"
class SelectionContain
{
public:
	bool rva0029CC19(const Object*);
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
	virtual void slot14();
	virtual void slot15();
	virtual void __cdecl message(UnicodeString,...);
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual SelectionContain *slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void selectDrawable(Drawable *);
	virtual void slot67(_STL::list<const Object*> *);
};
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 bool isLocallyControlled() const;
 bool isMassSelectable() const;
 Drawable *getDrawable() const;
 bool rva002922D9(const CommandButton*);
 void *vptr;
 ThingTemplate *m_template;
 char unknown008[0x74-8]; ObjectID id; ObjectID guardID;
 char unknown07c[0x250-0x7c]; SelectionContain *contain;
 char unknown254[4]; AIUpdateInterface *ai; char unknown25c[0x274-0x25c]; Object *containedBy;
protected:
 friend class InGameUI;
 Module *findModule(NameKeyType) const;	// rowed 0x0028B6D6 (protected)
};
#include "../../Include/GameLogic/Module/AIUpdate.h"
#include "../../Include/GameClient/Drawable.h"
#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;


#include "../../Include/GameClient/CommandButton.h"
#include "../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;
#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class SiegeDockInterface { public: virtual void slot0(); virtual bool slot1(ObjectID,Coord3D*); };
#include "../../Include/Common/Module.h"

// Partial storage view: the native dock receiver is module+0x20.
class Rva0029CC19ModuleView : public Module
{
public:
    char prefix08[0x20 - 0x08];
    SiegeDockInterface dock;
};
static __forceinline bool rva0029CC19Applies(const Object *target) {
 return target && (target->m_template->m_kindof[1]&0x10000000) && TheInGameUI->getSelectCount();
}
bool InGameUI::rva0029CC19(const Object *target) {
 if(!rva0029CC19Applies(target)) return false;
 else {
 const _STL::list<Drawable*> *selected=TheInGameUI->getAllSelectedDrawables();
 for(_STL::list<Drawable*>::const_iterator it=selected->begin();it!=selected->end();++it) {
  Object *object=(*it)->m_object;
  if(!object || object->containedBy)continue;
  const CommandButton *command;
  if(object->m_template->m_kindof[4]&0x800)command=TheControlBar->findCommandButton(AsciiString("Command_SpecialAbilitySiegeLadderDeploy"));
  else command=TheControlBar->findCommandButton(AsciiString("Command_SpecialAbilitySiegeDeploy"));
  if(!command || !(object->m_template->m_kindof[2]&0x20000000) || object->testStatus((ObjectStatusTypes)59) || !object->rva002922D9(command) || !command->isReady(object))continue;
  if(!object->ai)return true;
  static NameKeyType key=TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
  Module *module=target->findModule(key);
  if(module) {
   Coord3D location;
   Coord3D *pos=&location;
   ObjectID id=object->id;
   if(!((Rva0029CC19ModuleView *)module)->dock.slot1(id,pos) || object->ai->isQuickPathAvailable(pos))return true;
  }
 }
 return false;
 }
}
