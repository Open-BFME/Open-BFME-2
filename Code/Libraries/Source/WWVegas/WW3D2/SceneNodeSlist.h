#ifndef BFME_SCENE_NODE_SLIST_H
#define BFME_SCENE_NODE_SLIST_H
// The reconstructed scene node lists use slist<int> (int carries the ABI; the original
// payload spelling is unknown). Their nodes come from the scene-node pool, and
// _Slist_base<int>::_M_erase_after (retail 0x0006FABF) returns each node to the pool's free
// list instead of freeing it. Every unit that instantiates slist<int> must see this
// specialization; a unit that does not emits STLport's generic erase, which frees each node
// with free(), and the link may keep that copy. Keeping the definition visible reproduces
// retail's caller codegen: with a declaration alone a caller assumes the call can throw.
#include <slist>

class Rva0006EFC8
{
public:
	bool rva0006EFC8(int arena, int size);
	void *rva00141800();

	int m_00; // +0x00 retail 0x80
	void *m_04; // +0x04 retail 0
	void *m_head; // +0x08 VA 0xDB4254 (.data RVA 0x9B4254, free-list head)
	void *(__cdecl *m_alloc)(int size, int arg); // +0x0C retail 0x42FFC0 (Rva0002FFC0Alloc pinned)
	void (__cdecl *m_free)(void *ptr, int arg); // +0x10 retail 0x42FFE0 (Rva0002FFE0Free pinned)
	int m_14; // +0x14 retail 0
};

extern Rva0006EFC8 g_BfmeSceneNodePool; // VA 0xDB424C (.data RVA 0x9B424C), 24B pool
typedef char Rva0006EFC8PoolSize24[(sizeof(Rva0006EFC8) == 0x18) ? 1 : -1];

namespace _STL {
template <> _Slist_node_base *
_Slist_base<int,allocator<int> >::_M_erase_after(_Slist_node_base*,_Slist_node_base*);
}

namespace _STL {
template <> inline _Slist_node_base *
_Slist_base<int,allocator<int> >::_M_erase_after(_Slist_node_base* head,_Slist_node_base* stop)
{
 _Slist_node_base* current=head->_M_next;
 while(current!=stop) {
  _Slist_node_base* old=current;
  current=current->_M_next;
  _Slist_node_base* freeHead=(_Slist_node_base*)g_BfmeSceneNodePool.m_head;
  old->_M_next=freeHead;
  g_BfmeSceneNodePool.m_head=old;
 }
 return head->_M_next=stop;
}
}

#endif
