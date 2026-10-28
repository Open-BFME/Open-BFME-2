// ?redeployOccupants@HordeTransportContain@@QAEXXZ
// BFME1 ba7ddda7 Rva0024CAE0MaintainNestedRiders.cpp supplies the nested
// rider-maintenance algorithm. BFME2's update at477AF3 calls4779F9 first;
// its ctor and interface wrappers establish the primary receiver, +11D
// helper, and +20 removal-notification view. Native body4779F9..477AF3
// establishes list-descriptor slot108, removal slotsA8/A4, and owned
// Object::kill/GetDrawable calls. The original method name is unresolved.
// Both lists use the shared four-byte opaque element whose insertion chain
// is independently recovered. Declared virtual slots are ABI views only;
// this unit creates no interface objects or invented vtable data.
// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
#include <stl/_construct.h>
// Use the local scalar placement copy without emitting a competing template.
namespace _STL {
static inline void _Construct(int *dest, const int &value)
{ new (dest) int(value); }
}
#include <list>
#include <string.h>
#pragma intrinsic(memcpy)
#include "../../../../../Include/GameLogic/ContainmentListView.h"
typedef _STL::list<int> IntList;
// Local comparison keeps this consumer from emitting a competing iterator.
namespace _STL 
{
 template<class T, class Traits>
 static inline bool operator!=(const _List_iterator<T, Traits>&a,const _List_iterator<T, Traits>&b)
 
 {
  return a._M_node != b._M_node;
  
 }
 template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();
 template<> _List_base<int,allocator<int> >::~_List_base();
 
}
struct Rva0046247DPair
{
public:
	void *a; // +0x00
	IntList *objects; // +0x04
};
class Rva0046247D 
{
 public:void rva0046247D(Rva0046247DPair &);
 
};
class Object;
struct Coord3D;
class Rva00588E44Contain;
class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *);
	void rva00588BA8(Object *obj, bool flag);
	Object *rva00588C4E(void *contain, const struct Coord3D *obj);
	void rva00588F61(void *contain, Object *owner, enum CommandSourceType obj);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *object);
	Rva00588E44Contain *rva00588BF3(void *contain, Object *obj);
	bool rva00588D24(void *owner, Object *obj);
	void rva00588E44(void *argument);
};
class Rva00270260
{
public:
	bool rva00270260();
};
class Rva002716Holder 
{
 public:void rva00271601(unsigned char);
 
};
enum DamageType 
{
 DeathDamage=8 
};
enum DeathType 
{
 NormalDeath=0 
};
class Drawable;
// Only the accessed template prefix is established here: native477556
// tests byte115 bit20, independently agreeing with WB's kind-of109 test.
struct Rva00477513TemplateView 
{
 unsigned char prefix00[0x115];
 unsigned char flags115;
 
};
class Object 
{
 public:
 Drawable *getDrawable() const;
 void kill(DamageType,DeathType);
 void *vptr;
 const Rva00477513TemplateView *templateView;
 const Rva00477513TemplateView *getTemplate() const { return templateView; }
 
};
#define V(n) virtual void s##n()=0;
class RiderContain
{
public:
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) virtual void sA8(Object *)=0;
	V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) virtual Rva0036AE51ListView s108()=0;
};
class RemovalNotice 
{
 public:
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40)
 virtual void sA4(Object *,int)=0;
 
};
#undef V
class Thing;
struct Rva0047727EObjectPositionView;
class HordeTransportContain 
{
 public:
 void rva004779F9();
 void rva0047727E(Thing *object);
 void redeployOccupants();
 void rva00463A4D(ContainmentList objects, int context);
 private:
 unsigned char prefix00[8];
 Rva0047727EObjectPositionView *m_object;
 
};
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_List_node@H@_STL@@@_STL@@QBEXPAU?$_List_node@H@2@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<_List_node<int> >::deallocate(_List_node<int> *, size_t) const; }
class Thing 
{
 public: void setPosition(const Coord3D *position);
 
};
// Native477513..4775FD is a complete EH-protected body. WB119FE80 supplies
// the list-flattening algorithm; native calls, offsets and element accesses
// establish the target-specific adaptations. BF1 f98983a7's whole
// Rva0024C940ProcessNestedRiders.cpp is a related subsystem lead, but its
// callback/first-rider algorithm differs and is not imported as this body.
// List elements remain the shared opaque four-byte containment view.
// Element shape (closer seat c3): WB keeps the element in a local (`obj = *it`) that the
// else branch passes to push_back by reference (retail: lea [ebp-0x18]), tests
// obj->getTemplate() through the inline accessor (its `this` copy is retail's mov eax,ecx),
// and passes the re-dereferenced *it to the +0x11D helper (retail: push ecx).
void HordeTransportContain::redeployOccupants() 
{
 IntList objects;
 Rva0046247DPair outer;
 ((Rva0046247D*)this)->rva0046247D(outer);
 for (IntList::iterator i=outer.objects->begin();i!=outer.objects->end();++i) 
 {
  Object *object=(Object *)*i;
  if (object->getTemplate()->flags115 & 0x20) 
  {
   RiderContain *contain=(RiderContain*)((Rva0047A040Base9E0*)((char*)this+0x11D))->rva00588B8A((Object*)*i);
   rva0047727E((Thing*)object);
   Rva0036AE51ListView nested=contain->s108();
   for (ContainmentList::iterator j=nested.b->begin();j!=nested.b->end();++j)
   objects.push_back(containmentFirstWord(*j));
   
  }
  else 
  {
   objects.push_back(*(int *)&object);
   
  }
  
 }
 rva00463A4D(*reinterpret_cast<ContainmentList *>(&objects),(int)((char*)this+0x48));
 
}
