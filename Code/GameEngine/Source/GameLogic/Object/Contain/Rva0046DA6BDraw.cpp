// cl: /O1 /G7 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// ?rva0046DA6B@Rva0046DA6B@@QAEXHMMPAVRva2225E0Filter@@@Z @0x0046DA6B 258B
// Evidence: Native46DA6B..46DB6B RET16; HordeContain-family interface at11C calls contain slot70 on secondary20 and reads owner8. Applies established Drawable272870 and two-float270644 to contained objects and ID-keyed tree at receiver54; optional rowed filter362437 and owner player28AFA9. Native frameC uses descriptor8 plus owner4; recomputing list endpoint avoids extra cached pointer. Full258 exact with all existing providers; method name and unconstrained types remain address-level inference.
// stlport
#include <map>
class Rva00270644 {public:void rva00270644(float,float);};
class Drawable {public:void rva00272870(int);};
class Player;
class Object {public:Drawable*getDrawable()const;Player*getControllingPlayer()const;};
class Rva2225E0Filter {public:bool accepts(Object*,Player*);};
#include "GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
struct Rva0046247DPair {void*a;void*b;};
class ContainView {public:virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
virtual void d31();
virtual void d32();
virtual void d33();
virtual void d34();
virtual void d35();
virtual void d36();
virtual void d37();
virtual void d38();
virtual void d39();
virtual void d40();
virtual void d41();
virtual void d42();
virtual void d43();
virtual void d44();
virtual void d45();
virtual void d46();
virtual void d47();
virtual void d48();
virtual void d49();
virtual void d50();
virtual void d51();
virtual void d52();
virtual void d53();
virtual void d54();
virtual void d55();
virtual void d56();
virtual void d57();
virtual void d58();
virtual void d59();
virtual void d60();
virtual void d61();
virtual void d62();
virtual void d63();
virtual void d64();
virtual void d65();
virtual void d66();
virtual void d67();
virtual void d68();
virtual void d69(); virtual void items(Rva0046247DPair&);};
struct Node {Node*next;Node*prev;Object*object;};
struct TreeNode: _STL::_Rb_tree_node_base {int id;};
class Rva0046DA6B {public:void rva0046DA6B(int,float,float,Rva2225E0Filter*);private:char pad[0x54];TreeNode*head;};
void Rva0046DA6B::rva0046DA6B(int flags,float a,float b,Rva2225E0Filter*filter){
 Rva0046247DPair items;
 reinterpret_cast<ContainView*>(reinterpret_cast<char*>(this)-0xFC)->items(items);
 Node*n=(*static_cast<Node**>(items.b))->next;
 Object*owner=*reinterpret_cast<Object**>(reinterpret_cast<char*>(this)-0x114);
 for(;n!=*static_cast<Node**>(items.b);n=n->next){
  Object*object=n->object;
  if(filter&&!filter->accepts(object,owner->getControllingPlayer()))continue;
  Drawable*d=object->getDrawable();
  if(d){d->rva00272870(flags);reinterpret_cast<Rva00270644*>(d)->rva00270644(a,b);}
 }
 for(TreeNode*t=static_cast<TreeNode*>(head->_M_left);t!=head;t=static_cast<TreeNode*>(_STL::_Rb_global<bool>::_M_increment(t))){
  Object*object=TheGameLogic->findObjectByID(static_cast<ObjectID>(t->id));
  if(!object)continue;
  if(filter&&!filter->accepts(object,owner->getControllingPlayer()))continue;
  Drawable*d=object->getDrawable();
  if(d){d->rva00272870(flags);reinterpret_cast<Rva00270644*>(d)->rva00270644(a,b);}
 }
}
