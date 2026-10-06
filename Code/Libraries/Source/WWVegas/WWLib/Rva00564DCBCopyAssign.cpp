// cl: /DNDEBUG /MD
// ??4Rva00564DCB@@QAEAAU0@ABU0@@Z @0x00564DCB 39B.
// Copy-assignment over 0x10-byte elements (caller 0x005657B2 strides dst
// and src by 0x10): copies dword +4, assigns the OpaqueRefElement4 at +8
// through its rowed operator= 0x00239099, copies byte +0xC; dword +0 is
// intentionally not assigned. Returns *this. Unblocks 0x005657B2.

struct OpaqueRefElement4
{
	void *m_referent;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva00564DCB
{
	Rva00564DCB &operator=(const Rva00564DCB &that);

private:
	unsigned int m_0;
	unsigned int m_4;
	OpaqueRefElement4 m_8;
	unsigned char m_flagC;
};

Rva00564DCB &Rva00564DCB::operator=(const Rva00564DCB &that)
{
	m_4 = that.m_4;
	m_8 = that.m_8;
	m_flagC = that.m_flagC;
	return *this;
}
