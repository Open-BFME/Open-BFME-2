// cl: /O1 /G7 /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// Native 0x00462DE0..0x00462E3A is a complete RET4 body. A null filter
// returns the count at receiver+38; otherwise slot70 supplies the two-word
// list handle and every child is checked against the owning Object player.
// Adjacent OpenContain-family world recursion 462E3A uses the same slot70
// result. Receiver is the secondary +20 view: its owner is at receiver-18.
// Existing Object::getControllingPlayer and filter::accepts providers give
// semantic support. Actual containment class/method and control-word type
// remain unproven; address names and the established STLport list ABI stay.
#include <list>
namespace _STL {
template<class T,class Left,class Right>
static inline bool operator!=(const _List_iterator<T,Left> &a,const _List_iterator<T,Right> &b) { return a._M_node != b._M_node; }
}

class Player;
class Object { public: Player *getControllingPlayer() const; };
class Rva2225E0Filter { public: bool accepts(Object *,Player *); };
template<int N> class CountSlots : public CountSlots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class CountSlots<0> {};
struct CountItems { void *control; _STL::list<Object *> *list; };
struct CountOwner { char unknown00[8]; Object *owner; };
class Rva00462DE0 : public CountSlots<70> {
public:
 virtual CountItems items();
 int rva00462DE0(Rva2225E0Filter *filter);
 char unknown04[0x38-4]; int total;
 Object *getOwner() const { return ((CountOwner *)((char *)this-0x20))->owner; }
};
int Rva00462DE0::rva00462DE0(Rva2225E0Filter *filter) {
 if (!filter) return total;
 int count = 0;
 CountItems result = items();
 for(_STL::list<Object *>::const_iterator it=result.list->begin(); it!=result.list->end();++it)
   if(filter->accepts(*it,getOwner()->getControllingPlayer())) ++count;
 return count;
}
