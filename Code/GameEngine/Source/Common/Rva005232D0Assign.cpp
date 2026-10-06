// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD
//
// ??4Rva005232D0@@QAEAAU0@ABU0@@Z @0x005232D0 51B: memberwise assignment of a
// record whose first member is Rva00523149 (rowed pointer-taking assign
// 0x00523149, see Rva00523149Assign.cpp), then a word at +0x14, a
// list<UnicodeString> at +0x18 (rowed operator= 0x005227C0) and an AsciiString
// at +0x1C (rowed StringBase<char>::set 0x000366F0). Caller 0x00523356; owner
// unknown, so the name is address-derived.

#include "ascii_string.h"

class UnicodeString;

namespace _STL
{
template <class T>
class allocator;

template <class T, class Alloc = allocator<T> >
class list
{
public:
	list<T, Alloc> &operator=(const list<T, Alloc> &other);

private:
	void *m_node;
};
}

struct Rva00523149
{
	Rva00523149 &rva00523149(const Rva00523149 *other);

	char m_pad[0x14];
};

struct Rva005232D0
{
	Rva005232D0 &operator=(const Rva005232D0 &other);

	Rva00523149 m_00;
	int m_14;
	_STL::list<UnicodeString> m_18;
	AsciiString m_1C;
};

Rva005232D0 &Rva005232D0::operator=(const Rva005232D0 &other)
{
	m_00.rva00523149(&other.m_00);
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	return *this;
}
