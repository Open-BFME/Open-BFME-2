// cl: /MD
// ?rva0052E0A1@Rva0052E0A1@@QAE_NH@Z retail 0x0052E0A1 45B: 2-bit field at [ecx+0xC] bits 19-20 compare-and-set returning changed. Evidence: 4 callers in 0x0052E11A/0x0052E914, shr 0x13/and 3/shl 0x13/mask 0x180000, ret 4 thiscall bool(int).
class Rva0052E0A1
{
	char m_pad[0xC];
	unsigned m_low : 19;
	unsigned m_field : 2;
	unsigned m_high : 11;
public:
	bool rva0052E0A1(int v);
};

bool Rva0052E0A1::rva0052E0A1(int v)
{
	if (m_field == (unsigned)v)
		return false;
	m_field = (unsigned)v;
	return true;
}
