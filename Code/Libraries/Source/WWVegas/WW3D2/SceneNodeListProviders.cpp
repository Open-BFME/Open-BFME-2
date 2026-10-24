// cl: /O1 /Ob0 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native providers 6FABF (45B) and 6FB50 (9B), also used by scene Set_Level,
// and the out-of-line _Slist_base<int> allocator ctor 6FA99 (38B) just before them.
// /O1 /Ob0 reproduces the outlined providers without a volatile pool access.
// SceneSpatialRescale.cpp retains the identical inline erase definition under
// its existing /O2 settings, where the real STLport base destructor inlines.
// Reference: Open-BFME-1 a7c38d3b, inputs/vendor/stlport/stl/_slist.h.
// int is the existing provider's ABI carrier; original payload spelling is unknown.
#include <slist>
struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *m_next;
	void *m_value;
};

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

struct Rva0006FB50List
{
	Gen_00943CF0_Node *head;
	// 6FB50 -> 6FABF only relinks and recycles nodes, without throwing calls.
	~Rva0006FB50List() throw();
};

// Keep the known list destructor's erase call outlined under /Ob0.
// The same inline erase definition is visible to the optimized rescale caller.
namespace _STL {
template <> _Slist_node_base *
_Slist_base<int,allocator<int> >::_M_erase_after(_Slist_node_base*,_Slist_node_base*);
}
// Access-only view; no new storage, constructed object or class identity.
struct Rva0006FB50EraseAccess : _STL::_Slist_base<int,_STL::allocator<int> > {
 using _STL::_Slist_base<int,_STL::allocator<int> >::_M_erase_after;
};
typedef char SceneClearHeadSize4[sizeof(Rva0006FB50EraseAccess)==4?1:-1];
// Select-any like the other units' copies (a strong definition duplicates theirs at link time).
inline __declspec(noinline) Rva0006FB50List::~Rva0006FB50List() throw()
{
 ((Rva0006FB50EraseAccess*)this)->_M_erase_after((_STL::_Slist_node_base*)this,0);
}

// ?bfmeAnchorRva0006FB50ListDtor absent-from-retail
void bfmeAnchorRva0006FB50ListDtor(Rva0006FB50List *p)
{
 p->Rva0006FB50List::~Rva0006FB50List();
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

// The actual STLport base destructor is the same complete nine-byte body.
template _STL::_Slist_base<int,_STL::allocator<int> >::~_Slist_base();

// STLport's _Slist_base(const allocator_type &): converts the allocator and
// clears the head, the complete 38-byte body retail keeps at 0x0006FA99.
template _STL::_Slist_base<int,_STL::allocator<int> >::_Slist_base(const _STL::allocator<int> &);
