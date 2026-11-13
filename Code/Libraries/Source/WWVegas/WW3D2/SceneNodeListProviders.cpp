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
#include "Gen_00943CF0_Node.h"

#include "Rva0006FB50List.h"

// Keep the known list destructor's erase call outlined under /Ob0.
// The same inline erase definition is visible to the optimized rescale caller.
#include "SceneNodeSlist.h"
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

// The actual STLport base destructor is the same complete nine-byte body.
template _STL::_Slist_base<int,_STL::allocator<int> >::~_Slist_base();

// STLport's _Slist_base(const allocator_type &): converts the allocator and
// clears the head, the complete 38-byte body retail keeps at 0x0006FA99.
template _STL::_Slist_base<int,_STL::allocator<int> >::_Slist_base(const _STL::allocator<int> &);
