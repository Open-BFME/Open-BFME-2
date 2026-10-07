// cl: /Ireference/shims/bfme2_ascii
//
// Target 0x004B5293 (88B), Ghidra boundary FUN_008b5293. Retail derives an
// eight-byte vector length, appends one record, then reads three INI tokens
// and calls AsciiString::set at record offsets +0/+4; the middle token result
// is discarded. The four-argument INI field
// callback ABI is supported by the stack reads and callees. It likely parses
// a two-string SubObjectsUpgrade record; the exact key and callback identity
// are unresolved, so the target symbol remains address-derived.

#include "ascii_string.h"

struct BfmeStringRecord000B94D2
{
	AsciiString m_first;
	AsciiString m_second;
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	typedef unsigned int size_type;
	void resize(size_type newSize);

	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
};

void __cdecl rva004B5293(INI *ini, void *instance, void *store, const void *userData)
{
	_STL::vector<BfmeStringRecord000B94D2> *records =
		(_STL::vector<BfmeStringRecord000B94D2> *)store;
	unsigned int newSize = (unsigned int)(records->m_finish - records->m_start) + 1;
	records->resize(newSize);

	BfmeStringRecord000B94D2 *record = records->m_finish - 1;
	const char *token = ini->getNextTokenOrNull(0);
	if (token != 0)
		record->m_first.set(token);

	ini->getNextTokenOrNull(0);
	token = ini->getNextTokenOrNull(0);
	if (token != 0)
		record->m_second.set(token);
}
