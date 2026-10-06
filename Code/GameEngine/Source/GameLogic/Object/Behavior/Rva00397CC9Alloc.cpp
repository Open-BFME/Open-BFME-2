// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00397CC9Alloc@@YGPAXABURva0039627D@@@Z @0x00397CC9 34B
// Allocate 0x20-byte tree node via rowed allocator<char>::allocate 0x000307F0
// then construct Rva0039627D value at +0x10 via rowed _Construct 0x0039695E.
// Evidence: frameless push esi, allocate 0x20 hint 0, src from caller arg,
// dst lea esi+0x10, callers 2x in 0x0039834C set links after return.
#include <memory>
struct BfmeStringRecord004071F7 {
	unsigned char m_body[12];
	BfmeStringRecord004071F7(const BfmeStringRecord004071F7 &other);
};
struct Rva0039627D {
	void *m_00;
	BfmeStringRecord004071F7 m_04;
	Rva0039627D(const Rva0039627D &other);
};

void *__stdcall Rva00397CC9Alloc(const Rva0039627D &src)
{
	char *p = _STL::allocator<char>::allocate(0x20, 0);
	_STL::_Construct((Rva0039627D *)(p + 0x10), src);
	return p;
}

struct Rva0039834C
{
	void *rva00397CC9(const Rva0039627D &src);
};

// Retail tree insertion calls this member with the tree in ECX; the body does
// not inspect that receiver and folds with the free allocation helper above.
void *Rva0039834C::rva00397CC9(const Rva0039627D &src)
{
	char *p = _STL::allocator<char>::allocate(0x20, 0);
	_STL::_Construct((Rva0039627D *)(p + 0x10), src);
	return p;
}
