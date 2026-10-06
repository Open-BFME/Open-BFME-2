// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva00567BD7@@QAE@ABV0@@Z @0x00567BD7 38B
// Evidence: __thiscall copy ctor (ret 4, returns this); copies +0 dword, +4 byte, +8 refptr with inc [edx+4], +0xC byte.
// Caller 0x00567F91 conditionally copy-constructs; unblocks 0x00567F91.
struct Rva00567BD7Ref
{
	int m_0;
	int m_ref;
};

class Rva00567BD7
{
public:
	Rva00567BD7(const Rva00567BD7 &that);
	int m_0;
	unsigned char m_4;
	Rva00567BD7Ref *m_8;
	unsigned char m_C;
};

Rva00567BD7::Rva00567BD7(const Rva00567BD7 &that)
{
	m_0 = that.m_0;
	m_4 = that.m_4;
	m_8 = that.m_8;
	if (m_8 != 0)
		++m_8->m_ref;
	m_C = that.m_C;
}
