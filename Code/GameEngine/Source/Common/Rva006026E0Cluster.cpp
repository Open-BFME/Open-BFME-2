// Trivial allocator shims that sit inside the 0x006026E0 run of int-zero
// getters (IntZeroGetters.cpp), two cdecl callback slots at +0x54 and
// +0x58. They follow strstreambuf::pcount 0x006026C0 and precede _M_setup
// 0x00602740 (stlport_strstream_str.cpp), so they are likely STLport's
// strstreambuf::_M_alloc/_M_free; the rows keep the address names. Identity is not recovered: names are
// derived from their addresses. No // cl: line so the frameless /O2 shapes
// match, the same defaults the neighbouring zero getters rely on.

#include <new>

class Rva006026E0
{
public:
	char m_pad00[0x4];
	void *m_p04;
	void *m_p08;
	void *m_p0c;
	void *m_p10;
	char m_pad14[0x40];
	void *(__cdecl *m_fn54)(unsigned n);
	void *(__cdecl *m_fn58)(void *p);

	void *alloc(unsigned n);
	void free(void *p);
};

void *Rva006026E0::alloc(unsigned n)
{
	if (m_fn54)
		return m_fn54(n);
	return operator new[](n);
}

void Rva006026E0::free(void *p)
{
	if (p)
	{
		if (m_fn58)
			m_fn58(p);
		else
			operator delete[](p);
	}
}
