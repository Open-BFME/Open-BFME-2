// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <list>
// Suppress this TU's non-retail copy of ?erase@?$list@URva002FFC74Record@@V?$allocator@URva002FFC74Record@@@_STL@@@_STL@@QAE?AU?$_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva002FFC74Record;
namespace _STL { template <> _List_iterator<Rva002FFC74Record,_Nonconst_traits<Rva002FFC74Record> > list<Rva002FFC74Record,allocator<Rva002FFC74Record> >::erase(_List_iterator<Rva002FFC74Record,_Nonconst_traits<Rva002FFC74Record> >); }

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}



// Native create_node 0x002FE8AA allocates 0x10: eight link bytes plus
// eight data bytes; its copy worker is rowed at 0x002FE87D.
struct Rva002FFC74Record
{
public:
	Rva002FFC74Record();
	Rva002FFC74Record(const Rva002FFC74Record&);
	~Rva002FFC74Record();
	Rva002FFC74Record&operator=(const Rva002FFC74Record&);
	bool operator==(const Rva002FFC74Record&) const;
	bool operator<(const Rva002FFC74Record&) const;
	unsigned char bytes[8]; // +0x00
};
void __cdecl Rva002FE87DConstruct(void *destination, const void *source);
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Construct<Rva002FFC74Record,Rva002FFC74Record>(Rva002FFC74Record *destination, const Rva002FFC74Record &source)
{ Rva002FE87DConstruct(destination, &source); }
}


// This caller's native REL32 already names the kept provider at 0x001D9990.
// Both declarations use thiscall with one object-pointer/reference argument; binding is address-proven.
#pragma comment(linker, "/alternatename:??4Rva002FFC74Record@@QAEAAU0@ABU0@@Z=??4FXBoneInfo@@QAEAAU0@ABU0@@Z")

// The native range-erase call at 0x002FFCC5 names the rowed string-list
// worker at 0x002FECD3. Preserve that established shared cleanup operation
// rather than emitting a private erase dependency with an unresolved dtor.
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
namespace _STL {
template <> list<AsciiString, allocator<AsciiString> >::iterator
list<AsciiString, allocator<AsciiString> >::erase(iterator, iterator);
template <> __declspec(dllimport) __forceinline
list<Rva002FFC74Record, allocator<Rva002FFC74Record> >::iterator
list<Rva002FFC74Record, allocator<Rva002FFC74Record> >::erase(iterator first, iterator last)
{
    typedef list<AsciiString, allocator<AsciiString> > StringList;
    return iterator((_Node *)((StringList *)this)->erase(
        StringList::iterator((_List_node<AsciiString> *)first._M_node),
        StringList::iterator((_List_node<AsciiString> *)last._M_node))._M_node);
}
}

// Instantiate the recovered member; retain only its required template dependencies.
template _STL::list<Rva002FFC74Record, _STL::allocator<Rva002FFC74Record> > & _STL::list<Rva002FFC74Record, _STL::allocator<Rva002FFC74Record> >::operator=(_STL::list<Rva002FFC74Record, _STL::allocator<Rva002FFC74Record> > const &);
