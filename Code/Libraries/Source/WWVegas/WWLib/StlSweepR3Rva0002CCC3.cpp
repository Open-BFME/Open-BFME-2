// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_LOWER_BOUND_EXTERN  // bind the prime-list search to its shared retail provider
// STLport frees through the game's plain _free at 0x00030830, not the CRT import.
#define free BfmeCrtImportedFree
#include <stdlib.h>
#include <malloc.h>
#undef free
extern "C" void __cdecl free(void *) throw(...);
#include "ascii_string.h"
#include <hash_set>
#include <cstddef>

namespace rts
{
	template <class T> struct hash
	{
	};
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(const AsciiString &key) const;
	};
	template <class T> struct equal_to
	{
	};
	template <> struct equal_to<AsciiString>
	{
		// Expanded in place; the file emits no out-of-line copy of this functor.
		__declspec(dllimport) __forceinline bool operator()(const AsciiString &a, const AsciiString &b) const
		{
			return a.compareNoCase(b) == 0;
		}
	};
}

// Keep the inline bucket-vector access while binding outlined copies to
// the shared retail helpers instead of emitting this unit's /O1 variants.
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::const_iterator vector<void *>::begin() const
{ return this->_M_start; }
template <> __declspec(dllimport) __forceinline
vector<void *>::size_type vector<void *>::size() const
{ return size_type(this->_M_finish - this->_M_start); }
// The bucket lookup in hashtable::_M_find<AsciiString> inlines this too; left out of
// line, this unit's _M_find copy differs from retail's 0x0002C9E7 and, first in link
// order, would be the one the link keeps.
template <> __declspec(dllimport) __forceinline
vector<void *>::const_reference vector<void *>::operator[](size_type __n) const
{ return *(begin() + __n); }
}

// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }

// bfme link decl-only end
struct Rva0002CCC3Record {char bytes[1];bool operator<(const Rva0002CCC3Record&)const;bool operator==(const Rva0002CCC3Record&)const;};
namespace _STL {template<>struct hash<Rva0002CCC3Record> {unsigned int operator()(const Rva0002CCC3Record&)const;};}
// Retail 0x0002CCC3 calls 0x002234FE, the rowed clear of
// hash_map<AsciiString, AsciiString, rts::hash<AsciiString> > (INIMacroTable.cpp).
// Instantiating the whole set over this unit's own record left its operator==
// and hash unresolved and emitted a non-retail clear, so only the destructor is
// defined here and it calls that rowed clear by its own type.
typedef _STL::hashtable<_STL::pair<AsciiString const, AsciiString>, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<_STL::pair<AsciiString const, AsciiString> >, _STL::equal_to<AsciiString>, _STL::allocator<_STL::pair<AsciiString const, AsciiString> > > Rva002234FETable;
namespace _STL {
template <> void Rva002234FETable::clear();
typedef hashtable<Rva0002CCC3Record,Rva0002CCC3Record,hash<Rva0002CCC3Record>,_Identity<Rva0002CCC3Record>,equal_to<Rva0002CCC3Record>,allocator<Rva0002CCC3Record> > Rva0002CCC3Table;
template <> Rva0002CCC3Table::~hashtable()
{
    reinterpret_cast<Rva002234FETable *>(this)->clear();
}
template Rva0002CCC3Table::~hashtable();
}
