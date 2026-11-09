// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Target evidence at 0x00433C18: optionally clears the UnicodeString list at
// 0x00E032DC, skips empty strings, then searches and appends only on a miss.
// stlport
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


namespace _STL
{
	template <class InputIter, class T>
	InputIter find(InputIter first, InputIter last, const T &value);
}

#include "../../../../GameEngine/Include/Common/BfmeStringData.h"

#include "unicode_string.h"
// bfme link decl-only begin
namespace _STL { template <> _List_iterator<UnicodeString, _Nonconst_traits<UnicodeString> > list<UnicodeString, allocator<UnicodeString> >::insert(_List_iterator<UnicodeString, _Nonconst_traits<UnicodeString> >, UnicodeString const &); }
// bfme link decl-only end

inline bool operator==(const UnicodeString &a, const UnicodeString &b)
{
	return a.compare(b) == 0;
}

typedef _STL::list<UnicodeString, _STL::allocator<UnicodeString> > Rva00433C18List;
// The list object at 0x00E032DC is owned as g_Va00E032DC (Rva007B6880Thunks.cpp).
extern unsigned int theBriefingList;
#define Rva00433C18Pool (*(Rva00433C18List *)&theBriefingList)

void Rva00433C18(const UnicodeString &value, bool clearFirst)
{
	if (clearFirst)
		Rva00433C18Pool.clear();
	if (value.isEmpty())
		return;
	if (_STL::find(Rva00433C18Pool.begin(), Rva00433C18Pool.end(), value) ==
		Rva00433C18Pool.end())
		Rva00433C18Pool.push_back(value);
}
