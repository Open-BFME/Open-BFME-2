// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport

// ?Rva00502EC6::Rva00502EC6 @0x00502EC6 67B.
// Target facts: the static initializer at VA 0x00BB342C constructs
// g_Va00E04508 here; the body clears byte +0, then calls 0x00502D48,
// 0x004FFE96 and 0x0033C432 with this+4, this+0x10 and this+0x1C. The
// data ledger gives the global 56 bytes, and its existing dtor thunk
// 0x007B9049 calls 0x00502D03.
// Structural inference: the first two subobjects each occupy 12 bytes from
// the next observed offset. The last call reuses the matched map<int,void*>
// constructor at 0x0033C432 only as an ICF ABI view; target member types,
// class purpose and remaining storage are unknown.
#include <map>

class Rva00502D48
{
public:
	Rva00502D48();
	~Rva00502D48();

private:
	char m_opaque[0x0C];
};

class Rva004FFE96
{
public:
	Rva004FFE96();
	~Rva004FFE96();

private:
	char m_opaque[0x0C];
};

class Rva00502EC6
{
public:
	Rva00502EC6();
	~Rva00502EC6();

private:
	unsigned char m_flag00;
	char m_pad01[3];
	Rva00502D48 m_subobject04;
	Rva004FFE96 m_subobject10;
	_STL::map<int, void *> m_subobject1C;
};

Rva00502EC6::Rva00502EC6()
	: m_flag00(0)
{
}
