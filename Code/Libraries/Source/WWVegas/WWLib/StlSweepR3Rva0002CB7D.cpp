// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <hash_map>
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

struct Rva0002C9E7Value
{
	AsciiString m_text;
};

typedef _STL::hash_map<AsciiString, Rva0002C9E7Value, rts::hash<AsciiString>, rts::equal_to<AsciiString> > MacroMap;

// The table is the case-insensitive AsciiString-keyed one: this find's only
// call goes to the rowed _M_find<AsciiString> at 0x0002C9E7
// (stlport_hashtable_nocase_asciistring_m_find.cpp, whose doc names this body
// 0x0002CB7D as its caller). Key, functors and placeholder value repeat that
// unit's view; _M_find is declared only so its row serves the call.
typedef _STL::pair<const AsciiString, Rva0002C9E7Value> NoCaseAsciiValue;
typedef _STL::hashtable<NoCaseAsciiValue, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<NoCaseAsciiValue>, rts::equal_to<AsciiString>,
	_STL::allocator<NoCaseAsciiValue> > NoCaseAsciiHashtable;
template NoCaseAsciiHashtable::iterator NoCaseAsciiHashtable::find<AsciiString>(const AsciiString &);
// The outer hash_map::find at retail 0x0002CCAF (20 bytes): forwards the
// result slot and the argument to the table member above.
template MacroMap::iterator MacroMap::find(const AsciiString &);
