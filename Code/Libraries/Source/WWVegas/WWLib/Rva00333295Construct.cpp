// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00333295Construct@@YAXPAVRva00332EC8@@ABV1@@Z @0x00333295 18B
// retail 0x00333295 18 bytes chain Construct wrapper null-check plus copy ctor
// via rowed Rva00332EC8 copy 0x00332EC8 callers 0x00333329 0x00333354 unblocks 0x00333341 0x0033331B
// neighbours prev 0x00333283 Construct and next 0x003332A7 uninitialized_copy

#include <new>

class BfmeObject872Header
{
public:
	BfmeObject872Header(const BfmeObject872Header &that) throw();
private:
	char m_data[16];
};

class Rva00332EC8
{
public:
	Rva00332EC8(const Rva00332EC8 &that) throw();
private:
	unsigned int m_key;
	BfmeObject872Header m_a;
	BfmeObject872Header m_b;
};

void Rva00333295Construct(Rva00332EC8 *dest, const Rva00332EC8 &src)
{
	if (dest)
		new (dest) Rva00332EC8(src);
}
