// cl: /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?exitObjectViaDoor@HordeTransportContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// Retail 0x004775FD..0x004776E7 (234 B) RET 8 with an EH frame.
//
// Target facts: ctor 0x00477003 installs the ExitInterface table at module
// +0x30 whose slot 2 is this entry; AIExitStateMethods supplies the
// Object*/ExitDoorType ABI. The receiver is passed unchanged to the parent
// exit at 0x0046525F (named OpenContain::exitObjectViaDoor by WorldBuilder
// twin 0x01196CE0 and by the full native body 0x0046525F..0x004656DF).
// A non-horde object (template +0x115 bit 0x20 clear) exits through the
// parent directly. A horde reads the rider contain from Object +0x250
// (contain slot 0x7C) and copies its rider list through slot 0x108 and the
// list helper 0x0036AE51. Riders whose Object +0x454 byte is clear are
// removed (slot 0xA8) and exited first; then every rider is removed and
// exited; finally the horde object itself exits.
// Donor: BFME1 575ba2b04 OpenContainExitObjectViaDoor.cpp establishes the
// parent interface route. The existing pin at 0x004775FD names this
// method; the old private rva004775FD spelling is retired with it.
// Views model only accessed prefixes; the inline template and isHorde
// accessors reproduce the ECX input and the early receiver spill.
#include <list>
#include "../../../../../Include/GameLogic/ContainmentListView.h"
typedef ContainmentList IntList;
namespace _STL {
template<class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>&a,const _List_iterator<T, Traits>&b)
{ return a._M_node != b._M_node; }
template<> _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();}

class ExitObjectContain;
struct ExitTemplateView {char pad[0x115];unsigned char flags;bool isHorde()const{return(flags&0x20)!=0;}};
struct ExitObjectView {void*vptr;ExitTemplateView*type;char pad8[0x248];ExitObjectContain*contain;};
class Object {public:
 __forceinline ExitTemplateView*getTemplate()const{return ((const ExitObjectView*)this)->type;}
 __forceinline ExitObjectContain*exitContain()const{return ((const ExitObjectView*)this)->contain;}
 bool exitFlag454()const{return *((const unsigned char*)this+0x454)!=0;}
};
#define V(n) virtual void s##n()=0;
class RiderContain {public:
V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41)
virtual void sA8(Object *)=0;
V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52)
V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65)
virtual Rva0036AE51ListView s108()=0;
};
#undef V
enum ExitDoorType {DOOR_1=0};
template<int N> class ExitGetSlots:public ExitGetSlots<N-1>{public:virtual void gap(char(*)[N])=0;};
template<>class ExitGetSlots<0>{};
class ExitObjectContain:public ExitGetSlots<31>{public:virtual RiderContain*get()=0;};
class OpenContain{public:virtual void exitObjectViaDoor(Object*,ExitDoorType);};
class HordeTransportContain:public OpenContain{public:virtual void exitObjectViaDoor(Object*,ExitDoorType);};

void HordeTransportContain::exitObjectViaDoor(Object*newObj,ExitDoorType exitDoor){
 if(!newObj->getTemplate()->isHorde()){OpenContain::exitObjectViaDoor(newObj,exitDoor);return;}
 RiderContain*contain=newObj->exitContain()->get();if(!contain)return;
 IntList objects=contain->s108().rva0036AE51();
 for(IntList::iterator it=objects.begin();it!=objects.end();++it){Object*rider=(Object*)containmentFirstWord(*it);if(!rider->exitFlag454()){contain->sA8(rider);OpenContain::exitObjectViaDoor(rider,exitDoor);}}
 for(IntList::iterator it=objects.begin();it!=objects.end();++it){Object*rider=(Object*)containmentFirstWord(*it);contain->sA8(rider);OpenContain::exitObjectViaDoor(rider,exitDoor);}
 OpenContain::exitObjectViaDoor(newObj,exitDoor);
}
