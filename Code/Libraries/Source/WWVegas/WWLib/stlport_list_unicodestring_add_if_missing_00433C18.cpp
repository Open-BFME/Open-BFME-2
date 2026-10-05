// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Target evidence at 0x00433C18: optionally clears the UnicodeString list at
// 0x00E032DC, skips empty strings, then searches and appends only on a miss.
// stlport
#include <list>

namespace _STL
{
	template <class InputIter, class T>
	InputIter find(InputIter first, InputIter last, const T &value);
}

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "unicode_string.h"

inline bool operator==(const UnicodeString &a, const UnicodeString &b)
{
	return a.compare(b) == 0;
}

typedef _STL::list<UnicodeString, _STL::allocator<UnicodeString> > Rva00433C18List;
extern Rva00433C18List Rva00433C18Pool;

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
