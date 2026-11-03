// cl: /Ob0

// The element is a narrow string handle: retail assigns it through the rowed
// StringBase<char>::set 0x000366F0 (the refcounted Rva0036CA00Str handle's own
// assignment is OpaqueRefElement4::operator= 0x00239099, see Rva00403055CopyCtor.cpp).
template <class T> class StringBase
{
public:
	void set(const StringBase<T> &src);
};
#define BFME_STR_SET(dst, src) ((StringBase<char> &)(dst)).set((const StringBase<char> &)(src))

#include "../../Include/Common/Rva0036CA00Str.h"

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

private:
	void *m_item;
};

class Rva004E9B70
{
	int m_00;
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	int m_10;
	Rva00630D00UStr m_14;
	Rva00630D00UStr m_18;

public:
	Rva004E9B70 &operator=(const Rva004E9B70 &other);
};

Rva004E9B70 &Rva004E9B70::operator=(const Rva004E9B70 &other)
{
	m_00 = other.m_00;
	BFME_STR_SET(m_04, other.m_04);
	BFME_STR_SET(m_08, other.m_08);
	BFME_STR_SET(m_0C, other.m_0C);
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	return *this;
}
