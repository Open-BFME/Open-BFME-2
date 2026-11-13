// stlport
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// Target:5259B9 checks template110 bit26/119 bit7 then image provider33B634;
// list10 hero payload and list14 builder payload retain native24-byte data prefix.
// Existing525D9A append establishes builder12-byte {id,bool,pad,float} payload.
// Listener walk525407 has receiver pointer range0/4,capacity8 and reentrant indexC.
// LatchRestore follows ZH Common/LatchRestore.h with independently observed4B index.
#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class Object;class ThingTemplate;class Image;
const Image *getButtonImage(ThingTemplate *,Object *);
#include "../../../../../Include/Common/ThingTemplate.h"
class Object {public:void *vptr;ThingTemplate *templ;char pad08[0x74-8];int id;};
#include "../../../../../Include/Common/HeroButtonInfo.h"
struct BuilderButtonInfo {int id;bool used;char pad[3];float value;};
typedef _STL::list<HeroButtonInfo> HeroInfoList;
typedef _STL::list<BuilderButtonInfo> BuilderInfoList;
namespace _STL {
 template<> HeroInfoList::iterator list<HeroButtonInfo>::erase(HeroInfoList::iterator);
 template<> BuilderInfoList::iterator list<BuilderButtonInfo>::erase(BuilderInfoList::iterator);
}
struct HeroNodeRef {HeroNodeRef(){} HeroNodeRef(const HeroNodeRef&r):node(r.node){} void *node;};
class Rva005259B9Listener {public:virtual void v0();virtual void v1();virtual void v2();virtual void removeHero(HeroNodeRef);virtual void removeBuilder(HeroNodeRef);};
typedef void(Rva005259B9Listener::*HeroNotify)(HeroNodeRef);
struct HeroCall {HeroNotify method;HeroNodeRef arg;__forceinline void operator()(Rva005259B9Listener*l)const{(l->*method)(arg);}};
template<class T> class LatchRestore {
protected:T valueToRestore;T &whereToRestore;
public:LatchRestore(T &dest,const T &src):whereToRestore(dest){valueToRestore=dest;dest=src;}
 virtual ~LatchRestore(){whereToRestore=valueToRestore;}
};
struct Pod12Node00525D9A;
struct NodeRef00525D9A {NodeRef00525D9A(Pod12Node00525D9A*p):m_ptr(p){} Pod12Node00525D9A*m_ptr;};
class Holder00525D9A {
public:
 __declspec(noinline) void Rva005258F8(int,NodeRef00525D9A);
 template<class T,class Traits> __declspec(noinline) void Rva005258F8(int,_STL::_List_iterator<T,Traits>);
 __declspec(noinline) void rva00525407(const HeroCall &);
private:Rva005259B9Listener **begin,**end,**capacity;unsigned int index;
};
void Holder00525D9A::Rva005258F8(int fn,NodeRef00525D9A node) {union{int fn;HeroNotify method;} binding;binding.fn=fn;HeroCall tmp;tmp.method=binding.method;tmp.arg.node=node.m_ptr;rva00525407(tmp);}
void Holder00525D9A::rva00525407(const HeroCall &call) {
 unsigned int i=0;LatchRestore<unsigned int> latch(index,i);
 while(i<(unsigned int)(end-begin)) {index++;call(begin[i]);i=index;}
}
class HeroSelectData:public Holder00525D9A {
public:__declspec(noinline) void rva005259B9(Object *);HeroInfoList heroes;BuilderInfoList builders;
};
void HeroSelectData::rva005259B9(Object *obj) {
 const unsigned int heroBit=0x4000000;ThingTemplate *thingTemplate=obj->templ;
 if(!(thingTemplate->m_kindof[2]&heroBit) && !(thingTemplate->m_kindof[4] & 0x8000U))return;
 if(!getButtonImage(thingTemplate,obj))return;
 int id=obj->id;thingTemplate=obj->templ;
 if(thingTemplate->m_kindof[2]&heroBit) {
  for(HeroInfoList::iterator it=heroes.begin();it!=heroes.end();++it) {
   if(id==it->id){union{HeroNotify method;int fn;} binding={&Rva005259B9Listener::removeHero};Rva005258F8(binding.fn,(Pod12Node00525D9A*)it._M_node);heroes.erase(it);break;}
  }
 }else if(thingTemplate->m_kindof[4] & 0x8000U) {
  for(BuilderInfoList::iterator it=builders.begin();it!=builders.end();++it) {
   if(id==it->id){union{HeroNotify method;int fn;} binding={&Rva005259B9Listener::removeBuilder};Rva005258F8(binding.fn,(Pod12Node00525D9A*)it._M_node);builders.erase(it);break;}
  }
 }
}

// Native525A80..525A87 loads receiver word0 then jumps to removeHero5259B9.
// Keep the existing pin's raw32-bit argument view; the provider interprets
// the argument as an Object pointer. Original wrapper name/type unknown.
struct Rva002D37Sub {
    HeroSelectData *implementation;
    void rva00525A80(int objectWord);
};
void Rva002D37Sub::rva00525A80(int objectWord)
{
    implementation->rva005259B9(reinterpret_cast<Object *>(objectWord));
}

// The add-hero caller passes STLport's nontrivial iterator temporary directly.
// This overload is a byte-and-relocation twin of the rowed 30-byte raw-node
// implementation at 0x005258F8 (including its rva00525407 call). Its definition
// stays in that owner's unit so the fold pin can prove the whole body.
struct BfmePod12 { char payload[12]; BfmePod12(const BfmePod12 &); ~BfmePod12(); };
template<class T,class Traits>
void Holder00525D9A::Rva005258F8(int fn,_STL::_List_iterator<T,Traits> node) {
 union{int fn;HeroNotify method;} binding;binding.fn=fn;
 HeroCall tmp;tmp.method=binding.method;tmp.arg.node=node._M_node;rva00525407(tmp);
}
template void Holder00525D9A::Rva005258F8(int,_STL::list<BfmePod12>::iterator);
