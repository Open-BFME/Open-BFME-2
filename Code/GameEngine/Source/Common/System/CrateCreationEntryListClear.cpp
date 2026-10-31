// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?clear@?$_List_base@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@QAEXXZ, retail 0x002887EA, 50 bytes.
// List_base clear for crateCreationEntry via _free 0x00030830. Retail calls the
// element deleting dtor virtually (lea ecx,[ebx+8]; mov eax,[ecx]; push 0;
// call [eax]), so the element has a virtual dtor; a virtual ~crateCreationEntry
// reproduces the 50B shape byte-exact. Callee of ~_List_base<crateCreationEntry>
// at 0x002889A4 (retail REL32 at +0x04 targets this address).
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}


#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct crateCreationEntry;
namespace _STL { template <> _List_node<crateCreationEntry> * list<crateCreationEntry,allocator<crateCreationEntry> >::_M_create_node(crateCreationEntry const &); }
// Suppress this TU's non-retail copy of ?insert@?$list@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@QAE?AU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct crateCreationEntry;
namespace _STL { template <> _List_iterator<crateCreationEntry,_Nonconst_traits<crateCreationEntry> > list<crateCreationEntry,allocator<crateCreationEntry> >::insert(_List_iterator<crateCreationEntry,_Nonconst_traits<crateCreationEntry> >,crateCreationEntry const &); }

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
	virtual ~crateCreationEntry() {}
};

bool operator==(const crateCreationEntry &a, const crateCreationEntry &b);
bool operator<(const crateCreationEntry &a, const crateCreationEntry &b);

template void _STL::_List_base<crateCreationEntry, _STL::allocator<crateCreationEntry> >::clear();
template _STL::list<crateCreationEntry>::iterator _STL::list<crateCreationEntry>::erase(iterator);
template _STL::list<crateCreationEntry>::iterator _STL::list<crateCreationEntry>::erase(iterator, iterator);
template _STL::list<crateCreationEntry>::~list();
template void _STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >::swap(_STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> > &);
