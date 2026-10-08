// cl: /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /ICode/GameEngine/Source/Common
// stlport
// ZH Player timer purpose, independently supported by target2AC6B1/48,
//2AC7A0/70 and list helpers:8B timer {templateID,readyFrame}, node16.
#include <list>
#include "BfmeSpecialPowerTimer8.h"
namespace _STL {
template<> void _Construct<BfmeSpecialPowerTimer8,BfmeSpecialPowerTimer8>(BfmeSpecialPowerTimer8 *, const BfmeSpecialPowerTimer8 &);
template<> __declspec(noinline) _List_node<BfmeSpecialPowerTimer8> *list<BfmeSpecialPowerTimer8,allocator<BfmeSpecialPowerTimer8> >::_M_create_node(const BfmeSpecialPowerTimer8 &);
template<> __declspec(noinline) _List_node<BfmeSpecialPowerTimer8> *list<BfmeSpecialPowerTimer8,allocator<BfmeSpecialPowerTimer8> >::_M_create_node(const BfmeSpecialPowerTimer8 &x) {
 _Node *p=this->_M_node.allocate(1);
 _Construct(&p->_M_data,x);
 return p;
}
// Reference insert, with target-proven standalone create-node call.
template<> list<BfmeSpecialPowerTimer8,allocator<BfmeSpecialPowerTimer8> >::iterator list<BfmeSpecialPowerTimer8,allocator<BfmeSpecialPowerTimer8> >::insert(iterator position,const BfmeSpecialPowerTimer8 &x) {
 _Node *node=_M_create_node(x);
 _List_node_base *next=position._M_node;
 _List_node_base *previous=next->_M_prev;
 node->_M_next=next;
 node->_M_prev=previous;
 previous->_M_next=node;
 next->_M_prev=node;
 return node;
}
template void list<BfmeSpecialPowerTimer8,allocator<BfmeSpecialPowerTimer8> >::push_back(const BfmeSpecialPowerTimer8 &);

}
