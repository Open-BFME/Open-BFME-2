// cl: /O1 /G7 /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail 24-byte-node pool; original template and application owner unknown.
// Reference algorithm: matched 16-byte sibling FreelistPoolPop.cpp at
// 1EAEF9. Target [2E8548,2E85AD) independently establishes stride24,
// six-word pool storage and the allocator callback ABI. /G7 preserves IMUL.
// Field names describe their observed use rather than original identities.
#include "../../../../GameEngine/Include/Common/Rva002E8548Pool.h"

bool Rva002E8548::rva002E8548(int arena, int size)
{
retry:
	if (arena != 0)
		goto carve;
	if (size != 0) {
		if (size == -1)
			return false;
		arena = (int)m_alloc(size, m_14);
		if (arena == 0)
			return false;
		goto retry;
	}
	size = m_00 * 24 + 4;
	goto retry;
carve:
	void *old = m_04;
	*(void **)arena = old;
	int aligned = (arena + 15) & ~7;
	void *end = (char *)arena + size - 0x30;
	*(int *)((char *)arena + 4) = size;
	m_04 = (void *)arena;
	m_head = (void *)aligned;
	if ((unsigned int)aligned > (unsigned int)end)
		goto done;
	do {
		int next = aligned + 0x18;
		*(int *)aligned = next;
		aligned = next;
	} while ((unsigned int)aligned <= (unsigned int)end);
done:
	*(int *)aligned = 0;
	return true;
}

// Native [2EB448,2EB46E) retries own verified grow then unlinks head+8.
void *Rva002E8548::rva002EB448()
{
retry:
	if ( m_head == 0 )
	{
		if ( rva002E8548( 0, 0 ) )
			goto retry;
		return 0;
	}
	void *node = m_head;
	m_head = *(void **)node;
	return node;
}


#include <map>
void *__cdecl Rva0002FFC0Alloc(int size, int context);
void __cdecl Rva0002FFE0Free(void *block, int context);
// Native initialized image at DBD4C8: 128 nodes; null block/free lists;
// allocator/free callbacks 42FFC0/42FFE0; context zero. Both full callbacks
// are independently rowed. One 24-byte owner replaces the old 4-byte stub.
// ScienceStore uses the same verified pool layout and callbacks at DB9440.
Rva002E8548 g_Va00DB9440 = { 128, 0, 0, Rva0002FFC0Alloc, Rva0002FFE0Free, 0 };
Rva002E8548 g_Va00DBD4C8 = { 128, 0, 0, Rva0002FFC0Alloc, Rva0002FFE0Free, 0 };
// Native insertion compares the first payload word unsigned; the creator
// copies two words at node+16. The second word is an opaque storage view;
// its application type and the original map instantiation remain unknown.
typedef _STL::pair<const unsigned int,unsigned int> Pair;
// Native unsigned comparison is a verified storage predicate; the original
// comparator type is unknown. Avoid emitting a wrong shared less<unsigned>.
struct Rva002F0DD6Less {
    // ?Rva002F0DD6Less::operator() present-unmatched
    bool operator()(const unsigned int &a, const unsigned int &b) const { return a < b; }
};
typedef _STL::_Rb_tree<unsigned int,Pair,_STL::_Select1st<Pair>,Rva002F0DD6Less,_STL::allocator<Pair> > Tree;

namespace _STL { void dup_0060C9D9(Pair *, const Pair &); }

// The target has a full 23-byte two-word copy at 0x0060C9D9, but its
// instantiated identity is unknown; use an address-derived call placeholder.
#pragma comment(linker, "/alternatename:?dup_0060C9D9@_STL@@YAXPAU?$pair@$$CBII@1@ABU21@@Z=??$_Construct@U?$pair@$$CBHH@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBHH@0@ABU10@@Z")
// Native [2EF25B,2EF27D),34B RET4 ignores incoming ECX and uses the
// global pool. A stdcall address-named view preserves that observed ABI.
void *__stdcall rva002EF25B(const Pair &value)
{
    _STL::_Rb_tree_node<Pair> *node = (_STL::_Rb_tree_node<Pair> *)g_Va00DBD4C8.rva002EB448();
    _STL::dup_0060C9D9(&node->_M_value_field, value);
    return node;
}

// Retail's member call supplies ECX but the independently verified34B
// creator ignores it. Both call views take one stack value pointer and RET4;
// binding to the address-named stdcall view preserves that full ABI.
namespace _STL {
template <> _Rb_tree_node<Pair> *Tree::_M_create_node(const Pair &value);
}
#pragma comment(linker, "/alternatename:?_M_create_node@?$_Rb_tree@IU?$pair@$$CBII@_STL@@U?$_Select1st@U?$pair@$$CBII@_STL@@@2@URva002F0DD6Less@@V?$allocator@U?$pair@$$CBII@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBII@_STL@@@2@ABU?$pair@$$CBII@2@@Z=?rva002EF25B@@YGPAXABU?$pair@$$CBII@_STL@@@Z")
template Tree::iterator Tree::_M_insert(_STL::_Rb_tree_node_base*,_STL::_Rb_tree_node_base*,const Pair&,_STL::_Rb_tree_node_base*);
