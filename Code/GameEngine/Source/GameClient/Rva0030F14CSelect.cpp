// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/GameEngine/Source /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?Rva0030F14CSelect@@YAHPAVDrawable@@PAX@Z retail 0x0030F14C..0x0030F2AB (351 bytes).
// Drawable iteration callback (its address is pushed at 0x00430193 and
// 0x004301D2) that collects selectable drawables into the caller's list and
// keeps only the highest selection priority. 2 means skip: no list in the
// user data, the template's kind-of bits failing the must-have set (+0x08) or
// hitting the must-not set (+0x24) (rowed BitFlags<69>::test 0x002615C0), a
// kind-of 0x49 object of kind 14 when the user data's flag +0x05 is set, a
// drawable that fails the rowed 0x00271745 test, an object the local player
// sees through shroud worse than 2 (rowed getShroudStatusForPlayer
// 0x0028D2A2), a drawable or related object's drawable (rowed 0x002931F5,
// pinned getDrawable 0x005508E2) in state 5 at +0x164, a kind-of 0x6D
// container (rowed findObjectByID 0x00049DC5 on the object's +0x78 id) with
// status 3 (rowed testStatus 0x0004E536), or a template priority (+0x63C, -1
// without a template) below -1. A higher priority than the user data's best
// (+0x40) clears the list (rowed 0x00239380) and returns 1 after the push
// (rowed list push_back 0x00239E0B). WorldBuilder twin 0x00EB6700 (unnamed)
// has the same tests behind a debug-only shortcut.
// The list is STLport's real list<Drawable *>: with push_back's body visible
// VC7.1 keeps the address-taken drawable parameter in EBX until the push and
// writes its home only where the container branch replaces it, as retail does.
#include <list>
// list<Drawable *> takes its nodes from the 12-byte pool at VA 0x00DBA5E0:
// the node creator 0x00239BD8 is spelled as InGameUISelectDrawable.cpp spells
// it, so push_back's call reaches retail's body rather than a stock
// allocator copy.
class Drawable;
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool00DBA5E0;
namespace _STL {
template <> __declspec(noinline) _List_node<Drawable *> *
list<Drawable *>::_M_create_node(Drawable *const &value)
{
	_List_node<Drawable *> *node = (_List_node<Drawable *> *)g_freelistPool00DBA5E0.pop();
	_Construct(&node->_M_data, value);
	return node;
}
}
#include "Common/GameLogicObjectLookupView.h"
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// bfme link decl-only end
typedef int Int;
enum KindOfType
{
 KINDOF_73 = 0x49
};
enum CellShroudStatus
{
 CELLSHROUD_CLEAR = 0
};
enum ObjectStatusTypes
{
 OBJECT_STATUS_3 = 3
};
template <int N> class BitFlags
{
 public:
 bool test(const void *other) const;
 private:
 unsigned int m_bits[7];
};
struct ThingTemplateView
{
 __forceinline bool hasKindBit(int bit) const 
 {
  return (m_kindOf[bit >> 3] & (1 << (bit & 7))) != 0;
 }
 unsigned char m_pad000[0x108];
 unsigned char m_kindOf[0x63C - 0x108];
// +0x108
 Int m_selectionPriority;
// +0x63C
};
#include "../../Include/Common/Player.h"
class PlayerList
{
 public:
 // Keep retail's inlined +0x10 access without a competing external copy.
 __declspec(dllimport) __forceinline Player *getLocalPlayer()
 {
  return m_local;
 }
 private:
 unsigned char m_pad00[0x10];
 Player *m_local;
// +0x10
};
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
class Drawable
{
 public:
 const ThingTemplateView *getTemplate() const 
 {
  return m_template;
 }
 Object *getObject() const 
 {
  return m_object;
 }
 Int rva00271745() const;
 void *m_vtable;
 const ThingTemplateView *m_template;
// +0x04
 unsigned char m_pad08[0xFC - 0x08];
 Object *m_object;
// +0xFC
 unsigned char m_pad100[0x164 - 0x100];
 Int m_state;
// +0x164
};
class Object
{
 public:
 const ThingTemplateView *getTemplate() const 
 {
  return m_template;
 }
 bool isKindOf(KindOfType kind) const;
 CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
 Object *rva002931F5(bool flag);
 Drawable *getDrawable() const;
 bool testStatus(ObjectStatusTypes status) const;
 Int getSelectionPriority() const
 {
  const ThingTemplateView *thingTemplateView = getTemplate();
  if (thingTemplateView == 0)
  return -1;
  return thingTemplateView->m_selectionPriority;
 }
 void *m_vtable;
 const ThingTemplateView *m_template;
// +0x04
 unsigned char m_pad08[0x78 - 0x08];
 ObjectID m_containerID;
// +0x78
};
class Rva00239380Holder
{
 public:
 void rva00239380();
};
struct Rva0030F14CSelectInfo
{
 _STL::list<Drawable *> *m_list;
// +0x00
 char m_pad04;
 bool m_checkKind73;
// +0x05
 char m_pad06[2];
 BitFlags<69> m_mustBe;
// +0x08
 BitFlags<69> m_mustNotBe;
// +0x24
 Int m_bestPriority;
// +0x40
};
// Retail 0x0030ECC4: the selection priority of an object (-1 without a
// template) as a TU static of the selection unit; the select callback inlines
// it and cl keeps this register-convention copy (object in EAX).
static Int selectionPriority(const Object *obj)
{
 return obj->getSelectionPriority();
}

Int Rva0030F14CSelect(Drawable *draw, void *userData)
{
 Rva0030F14CSelectInfo *info = (Rva0030F14CSelectInfo *)userData;
 if (info->m_list == 0)
 return 2;
 const ThingTemplateView *thingTemplateView = draw->getTemplate();
 if (!info->m_mustBe.test(thingTemplateView->m_kindOf))
 return 2;
 if (info->m_mustNotBe.test(thingTemplateView->m_kindOf))
 return 2;
 Object *obj = draw->getObject();
 if (info->m_checkKind73 && obj && obj->isKindOf(KINDOF_73) && obj->getTemplate()->hasKindBit(14))
 return 2;
 if (!(unsigned char)draw->rva00271745())
 return 2;
 Int minPriority = -1;
 bool changed = false;
 if (obj)
 {
  Player *localPlayer = ThePlayerList->getLocalPlayer();
  if (localPlayer && obj->getShroudStatusForPlayer(localPlayer->getPlayerIndex()) > 2)
  return 2;
  if (draw->m_state == 5)
  return 2;
  Object *other = obj->rva002931F5(false);
  if (other && other != obj)
  {
   Drawable *otherDraw = other->getDrawable();
   if (otherDraw && otherDraw->m_state == 5)
   return 2;
  }
  if (obj->m_containerID)
  {
   Object *container = TheGameLogic->findObjectByID(obj->m_containerID);
   if (container && container->getTemplate()->hasKindBit(0x6D))
   {
    if (container->testStatus(OBJECT_STATUS_3))
    return 2;
    obj = container;
    draw = container->getDrawable();
   }
  }
  Int priority = selectionPriority(obj);
  if (priority < minPriority)
  return 2;
  if (priority > info->m_bestPriority)
  {
   ((Rva00239380Holder *)info->m_list)->rva00239380();
   info->m_bestPriority = priority;
   changed = true;
  }
 }
 info->m_list->push_back(draw);
 return changed ? 1 : 0;
}
