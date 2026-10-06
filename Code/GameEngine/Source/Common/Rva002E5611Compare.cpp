// cl: /MD
// ?rva002E5611@Rva002E5611@@QAEHABV1@@Z, retail 0x002E5611, 103 bytes.
// Signed 64-bit compare of the (high at +8 low at +c) pair against the same
// pair in the argument. Each side builds (__int64)high * 0x100000000 + low
// which emits the rowed __allmul at 0x00629580 plus add/adc; the two
// if (a > b) return 1 / if (a < b) return -1 checks emit the jl/jg plus
// unsigned low compare shape. Caller at 0x002E5DF9 passes
// (this+0xC this lea esi+0xC) with a stack local so both sides share layout.
// Neighbours 0x002E55E3 deleting dtor and 0x002E5678 compareStringLookUpLess.
class Rva002E5611
{
public:
	int rva002E5611(const Rva002E5611 &other);
private:
	int m_00;
	int m_04;
	int m_high;
	int m_low;
};

int Rva002E5611::rva002E5611(const Rva002E5611 &other)
{
	__int64 a = (__int64)m_high * 0x100000000i64 + m_low;
	__int64 b = (__int64)other.m_high * 0x100000000i64 + other.m_low;
	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
}
