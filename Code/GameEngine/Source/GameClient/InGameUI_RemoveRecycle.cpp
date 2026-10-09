// stlport
// cl: /O1 /DNDEBUG /MD /EHsc
// Native29DFC5..29DFE9 RET8 consumes the four-byte iterator copy and
// writes its successor to the hidden return pointer. Caller29F77E
// independently proves the member receiver and nontrivial iterator ABI.
// Unlink/recycle semantics are established by retail; the allocator and
// original method spelling remain unresolved. This member view replaces
// the former stdcall void-pointer view without adding an alias or pin.
#include <list>
class Object;
extern void *g_freeList001EB130;
using namespace _STL;
class Rva0029DFC5List { public: list<Object*>::iterator rva0029DFC5(list<Object*>::iterator); };
list<Object*>::iterator Rva0029DFC5List::rva0029DFC5(list<Object*>::iterator position)
{
 _List_node_base *node=position._M_node;
 _List_node_base *prev=node->_M_prev;
 _List_node_base *next=node->_M_next;
 prev->_M_next=next;
 next->_M_prev=prev;
 node->_M_next=static_cast<_List_node_base*>(g_freeList001EB130);
 g_freeList001EB130=node;
 return list<Object*>::iterator(static_cast<_List_node<Object*>*>(next));
}
