// cl: /DNDEBUG /MD /GX-
//
// ?rva00438268@Rva002542F3Member@@QBEHABV1@@Z, retail 0x00438268, 148 bytes.
// Equality over Rva002542F3Member (default ctor rowed 0x002542F3, copy rowed
// 0x0043831C, 0xB8 bytes). Layout per Rva002542F3MemberCtor.cpp: dword +0,
// BfmeObject872Header +4 (rowed equal 0x002634E0), float +0x14, int +0x18,
// BfmeFixedStorage128 +0x1C (rowed equal 0x0037DC8A), ints +0x9C/+0xA0/+0xA4,
// BfmeObject872Header +0xA8 (rowed equal 0x002634E0, self-compare in retail).
// Caller 0x00439DB5. Finish from stash 0x00438268 score 0.93.
class BfmeObject872Header
{
public:
	BfmeObject872Header(const BfmeObject872Header &other);
private:
	char m_pad[0x10];
};

struct BfmeFixedStorage128
{
public:
	BfmeFixedStorage128(const struct BfmeFixedStorage128 &other);
private:
	char m_pad[0x80];
};

class Rva002542F3Member
{
public:
	int rva00438268(const Rva002542F3Member &other) const;
private:
	int m_zero00;
	BfmeObject872Header m_bits04;
	float m_float14;
	int m_int18;
	BfmeFixedStorage128 m_buf1C;
	int m_zero9C;
	int m_zeroA0;
	int m_zeroA4;
	BfmeObject872Header m_bitsA8;
};

bool __cdecl Rva002634E0Equal(const void *a, const void *b);
bool __cdecl Rva0037DC8AEqual(const void *a, const void *b);

int Rva002542F3Member::rva00438268(const Rva002542F3Member &other) const
{
	if (m_zero00 != other.m_zero00)
		goto fail;
	if (!Rva002634E0Equal(&m_bits04, &other.m_bits04))
		goto fail;
	if (m_float14 != other.m_float14)
		goto fail;
	if (m_int18 != other.m_int18)
		goto fail;
	if (!Rva0037DC8AEqual(&m_buf1C, &other.m_buf1C))
		goto fail;
	if (m_zero9C != other.m_zero9C)
		goto fail;
	if (m_zeroA0 != other.m_zeroA0)
		goto fail;
	if (m_zeroA4 != other.m_zeroA4)
		goto fail;
	if (Rva002634E0Equal(&m_bitsA8, &m_bitsA8))
		return 1;
fail:
	return 0;
}
