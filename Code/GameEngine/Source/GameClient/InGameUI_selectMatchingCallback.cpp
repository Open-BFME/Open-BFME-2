// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva002A1EF5@@YAHPAVDrawable@@PAX@Z, retail 0x002A1EF5..0x002A2184 (655
// bytes), the select-matching drawable callback InGameUI::selectMatchingAcrossRegion
// 0x002A3AFA calls twice (cdecl Drawable*, user data): skip an object whose
// +0x78 partner has KindOf bit 13 and status 3, accept template-equivalent
// objects (or, for a bit-13 container, one holding such an object), honour
// the max-selection warning and select the drawable.
// Template reads go through Object's inline getTemplate(): that is what puts
// the guard's template in EDX like retail (a direct m_template read uses ECX).
#include "unicode_string.h"
#include "ascii_string.h"
#include <list>

// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0.
// The base constructor (0x00239BB0) and node creator (0x00239BD8) are spelled
// as stlport_list_drawable_base_ctor.cpp and InGameUISelectDrawable.cpp spell
// them, and the destructor (0x00239AF4) is defined once elsewhere, so this
// unit emits no stock allocator copy of them for the link to reject.
class Drawable;
#include "../../Include/Common/FreelistPool.h"
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline)
_List_base<Drawable *, allocator<Drawable *> >::_List_base(const allocator<Drawable *> &__a)
	: _M_node(__a, (_List_node<Drawable *> *)0)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	node->_M_next = node;
	node->_M_prev = node;
	_M_node._M_data = node;
}
template <> _List_base<Drawable *, allocator<Drawable *> >::~_List_base();
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}
#include "../Common/GameLogicObjectLookupView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class Object;
namespace _STL {
template<> inline __declspec(noinline) _List_base<const Object*,allocator<const Object*> >::_List_base(const allocator<const Object*>& __a) : _M_node(_STLP_CONVERT_ALLOCATOR(__a, _Node), (_Node*)0) {
    _Node* __n = _M_node.allocate(1);
    __n->_M_next = __n;
    __n->_M_prev = __n;
    _M_node._M_data = __n;
}
template<> inline __declspec(noinline) _List_base<const Object*,allocator<const Object*> >::~_List_base() {
    clear();
    _M_node.deallocate(_M_node._M_data, 1);
}
}
class Object;
class Drawable;
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
 const ThingTemplate *getTemplate() const { return m_template; }
 void *vptr;
 ThingTemplate *m_template;
 char unknown008[0x78-8]; ObjectID guardID;
 char unknown07c[0x250-0x7c]; SelectionContain *contain;
 char unknown254[0x274-0x254]; Object *containedBy;
};
#include "../../Include/GameClient/Drawable.h"
extern GameLogic *TheGameLogic;
#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

struct SelectionData { const ThingTemplate *type; _STL::list<Drawable*> selected; bool includeContained; };
int Rva002A1EF5(Drawable *test,void *userData) {
 SelectionData *data=static_cast<SelectionData*>(userData);
 const ThingTemplate *selectedType=data->type;
 if(test) {
  const Object *object=test->m_object;
  if(!object)return 2;
  if(object->guardID) {
   Object *guard=TheGameLogic->findObjectByID(object->guardID);
   if(guard && (guard->getTemplate()->m_kindof[3]&0x2000) && guard->testStatus((ObjectStatusTypes)3))return 2;
  }
  bool equivalent=object->getTemplate()->isEquivalentTo(selectedType);
  if(!equivalent) {
   if(data->includeContained || !(object->getTemplate()->m_kindof[3]&0x2000) || (selectedType->m_kindof[3]&0x2000))return 2;
   SelectionContain *contain=object->contain;
   if(!contain)return 2;
   SelectionContain *contained=contain->slot31();
   if(!contained)return 2;
   _STL::list<const Object*> words;
   contained->slot67(&words);
   for(_STL::list<const Object*>::iterator it=words.begin();it!=words.end();++it) {
    const Object *child=*it;
    if(child && child->m_template && child->m_template->isEquivalentTo(selectedType)){ equivalent=true;break; }
   }
  }
  if(object && equivalent && object->isLocallyControlled() && !object->containedBy && !object->getDrawable()->m_selected && object->isMassSelectable()) {
   if(TheInGameUI->getMaxSelectCount()>0 && TheInGameUI->getSelectCount()>=TheInGameUI->getMaxSelectCount()) {
    if(!TheInGameUI->getDisplayedMaxWarning()) {
     TheInGameUI->setDisplayedMaxWarning(true);
     UnicodeString msg;
     msg.format(TheGameText->fetch("GUI:MaxSelectionSize").str(),TheInGameUI->getMaxSelectCount());
     TheInGameUI->rva0029E846(msg);
    }
   }else{
    TheInGameUI->selectDrawable(test);
    TheInGameUI->setDisplayedMaxWarning(false);
    data->selected.push_back(test);
    return 0;
   }
  }
 }
 return 2;
}
