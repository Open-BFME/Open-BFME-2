// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020EE8F@Rva0020EE8F@@QAE_NHPAUPair8@@@Z, retail 0x0020EE8F, 57 bytes.
// Eight-byte pair fetch via inner at +0x08 with byte range at +0x20/+0x24
// (count sar 3) copying 8B to out. Caller at 0x003F0ED5.
struct Pair8
{
	int m_a;
	int m_b;
};

struct Rva0020EE8FInner
{
	char m_pad[0x20];
	Pair8 *m_begin;
	Pair8 *m_end;
};

class Rva0020EE8F
{
public:
	bool rva0020EE8F(int index, Pair8 *out);

private:
	char m_pad[8];
	Rva0020EE8FInner *m_inner;
};

bool Rva0020EE8F::rva0020EE8F(int index, Pair8 *out)
{
	Rva0020EE8FInner *inner = m_inner;
	if (!inner)
		return false;
	if (index < 0)
		return false;
	unsigned count = ((char *)inner->m_end - (char *)inner->m_begin) >> 3;
	if ((unsigned)index < count) {
		*out = inner->m_begin[index];
		return true;
	}
	return false;
}
