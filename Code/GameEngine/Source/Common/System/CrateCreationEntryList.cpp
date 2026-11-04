// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// CrateTemplate possible-crates list machinery (retail 0x0035CAB4/0x0035CB8D/
// 0x0035CBFE). The element is the 8-byte crateCreationEntry from the landed
// CrateTemplate::parseCrateCreationEntry TU (AsciiString name plus float
// chance). The node allocator is the rowed narrow byte allocator at
// 0x000307F0 (16 bytes, null hint, via bfmealloc). The element _Construct
// helper at 0x0035CA02 is byte-identical for AsciiString-plus-dword payloads
// (pair dup_ row) and the crate entry (AsciiString plus float); a twin pin
// carries the crate spelling. Frameless 34-byte _M_create_node via the
// bfmelist shim (no TRY/UNWIND), same recipe as the UnicodeString list
// create-node TU.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?erase@?$list@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@QAE?AU?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct crateCreationEntry;
namespace _STL { template <> _List_iterator<crateCreationEntry,_Nonconst_traits<crateCreationEntry> > list<crateCreationEntry,allocator<crateCreationEntry> >::erase(_List_iterator<crateCreationEntry,_Nonconst_traits<crateCreationEntry> >); }
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct crateCreationEntry;
namespace _STL { template <> void _List_base<crateCreationEntry,allocator<crateCreationEntry> >::clear(); }
// Suppress this TU's non-retail copy of ?insert@?$list@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@QAE?AU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct crateCreationEntry;
namespace _STL { template <> _List_iterator<crateCreationEntry,_Nonconst_traits<crateCreationEntry> > list<crateCreationEntry,allocator<crateCreationEntry> >::insert(_List_iterator<crateCreationEntry,_Nonconst_traits<crateCreationEntry> >,crateCreationEntry const &); }

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
};

bool operator==(const crateCreationEntry &a, const crateCreationEntry &b);

// The unrelated sort row at 0x00288E8D belongs to ExperienceLevelSystem,
// whose caller passes an experience-level list through this historical
// template spelling. Its native merge calls ExperienceLevel::operator< at
// 0x00288621; it never orders the eight-byte crate records above.
class ExperienceLevel
{
public:
	bool operator<(const ExperienceLevel &) const;
};

namespace _STL
{

template <>
__declspec(dllimport) __forceinline bool less<crateCreationEntry>::operator()(
	const crateCreationEntry &left, const crateCreationEntry &right) const
{
	return ((const ExperienceLevel *)&left)->operator<(*(const ExperienceLevel *)&right);
}

// The crate entry copies its owning name and chance through STLport.
template <>
__declspec(noinline) inline void _Construct<crateCreationEntry, crateCreationEntry>(
	crateCreationEntry *entry, const crateCreationEntry &source)
{
	new ((void *)entry) crateCreationEntry(source);
}

}

// ?_M_create_node@?$list@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@IAEPAU?$_List_node@UcrateCreationEntry@@@2@ABUcrateCreationEntry@@@Z @0x35CAB4
template <>
_STL::_List_node<crateCreationEntry> *
_STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >::_M_create_node(
	const crateCreationEntry &__x)
{
	_STL::_List_node<crateCreationEntry> *__p =
		(_STL::_List_node<crateCreationEntry> *)_STL::allocator<char>::allocate(16, 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}

// Instantiate the retained operations without unrelated list members.
template _STL::_List_node<crateCreationEntry> *_STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >::_M_create_node(const crateCreationEntry &);
template void _STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >::sort();
