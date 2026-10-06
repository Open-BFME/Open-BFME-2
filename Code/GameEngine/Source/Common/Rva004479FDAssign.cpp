// cl: /MD /Oi-
//
// ?rva004479FD@Rva004479FD@@QAEAAU1@ABU1@@Z @0x004479FD 69B.
// Copy-assign: set three StringBase<wchar> at +0 +4 +8 via pinned 0x00037150
// then copy dwords at +0xC +0x10 +0x14 +0x18, return *this. Evidence: unlock
// lane; same set pin as callers; caller 0x00447B73; neighbours share flags.
template <typename T> class StringBase
{
public:
	void set(const StringBase &o);
private:
	T *m_data;
};

struct Rva004479FD
{
	StringBase<unsigned short> m_00;
	StringBase<unsigned short> m_04;
	StringBase<unsigned short> m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	Rva004479FD &rva004479FD(const Rva004479FD &o);
};

Rva004479FD &Rva004479FD::rva004479FD(const Rva004479FD &o)
{
	m_00.set(o.m_00);
	m_04.set(o.m_04);
	m_08.set(o.m_08);
	m_0C = o.m_0C;
	m_10 = o.m_10;
	m_14 = o.m_14;
	m_18 = o.m_18;
	return *this;
}
