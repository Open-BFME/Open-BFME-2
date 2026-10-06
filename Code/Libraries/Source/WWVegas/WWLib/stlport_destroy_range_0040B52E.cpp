// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0040B52EDestroy@@YAXPAUDestroyElem0040B52E@@0@Z, retail 0x0040B52E,
// 25 bytes. Unlock lane: destroy range over 16-byte elements with narrow
// string at +0 via rowed BasicStringCharDtor_dup 0x0007FAB3. Unblocks
// 0x0040B560, 0x0040B5DE, 0x0040B61A.
#include <string>

struct DestroyElem0040B52E
{
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_str;
	int m_pad;
};

extern "C" void __cdecl free(void *p);

class Rva0040B5DE
{
public:
	void rva0040B5DE();

private:
	DestroyElem0040B52E *m_begin;
	DestroyElem0040B52E *m_finish;
};

void __cdecl Rva0040B52EDestroy(DestroyElem0040B52E *first, DestroyElem0040B52E *last)
{
	for (; first != last; ++first)
		first->m_str.~basic_string();
}

void Rva0040B5DE::rva0040B5DE()
{
	Rva0040B52EDestroy(m_begin, m_finish);
	void *storage = m_begin;
	if (storage)
		free(storage);
}
