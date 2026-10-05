// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva003F2A11@Rva003F2A11@@QAEAAV1@ABV1@@Z @0x003F2A11 45B
// __thiscall copy-assignment: AsciiString at +4 via rowed StringBase::set,
// dword at +8, _STL::vector<BfmePod8> at +0xC via rowed operator=, return *this.
// Evidence: unlock lane; callees rowed 0x000366F0 set and 0x001D9BEE vector op=;
// layout +4/+8/+0xC from the two calls plus the dword move; 1 stack arg (ret 4).
#include "ascii_string.h"

struct BfmePod8 { int a[2]; };

namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector
{
public:
	vector &operator=(const vector &);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};
}

class Rva003F2A11
{
public:
	Rva003F2A11 &rva003F2A11(const Rva003F2A11 &other);

private:
	void *m_pad0;
	AsciiString m_str;
	unsigned int m_08;
	_STL::vector<BfmePod8> m_vec;
};

Rva003F2A11 &Rva003F2A11::rva003F2A11(const Rva003F2A11 &other)
{
	((StringBase<char> *)&m_str)->set(*(const StringBase<char> *)&other.m_str);
	m_08 = other.m_08;
	m_vec = other.m_vec;
	return *this;
}

Rva003F2A11 *Rva003F2A3E(Rva003F2A11 *src, Rva003F2A11 *last, Rva003F2A11 *dest)
{
	int n = last - src;
	if (n <= 0)
		return dest;
	for (int k = n; k != 0; --k) {
		dest->rva003F2A11(*src);
		++src;
		++dest;
	}
	return dest;
}
