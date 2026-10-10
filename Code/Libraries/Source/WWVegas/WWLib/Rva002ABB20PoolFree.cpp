// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 002ABB20..002ABB44 RET8; WB11DDC90 pop_front inlines this same
// pooled-node unlink/free-list operation. Native4907AA carries the hidden
// iterator result and by-value iterator, matching this unused-this ABI.
// Replace the former stdcall free-function view with the actual template
// member binding its callers use. The element name remains address-derived.
// g_freeList is the existing DA60F0 owner; no new address or alias is admitted.

#include <list>
struct Rva004907AAElement {unsigned int id;bool operator<(const Rva004907AAElement&)const;bool operator==(const Rva004907AAElement&)const;};
extern void *g_freeList;
template<> _STL::list<Rva004907AAElement,_STL::allocator<Rva004907AAElement> >::iterator _STL::list<Rva004907AAElement,_STL::allocator<Rva004907AAElement> >::erase(iterator position)
{
 _STL::_List_node_base *n=position._M_node;
 _STL::_List_node_base *prev=n->_M_prev;
 _STL::_List_node_base *next=n->_M_next;
 prev->_M_next=next;
 next->_M_prev=prev;
 n->_M_next=(_STL::_List_node_base*)g_freeList;
 g_freeList=n;
 return iterator((_STL::_List_node<Rva004907AAElement>*)next);
}

template _STL::list<Rva004907AAElement,_STL::allocator<Rva004907AAElement> >::iterator _STL::list<Rva004907AAElement,_STL::allocator<Rva004907AAElement> >::erase(iterator);
