// cl: /DNDEBUG /MD /EHsc
//
// ?rva0052E05D@Rva0052E05D@@QAE_N_N@Z retail 0x0052E05D 46B: bit-18 setter at
// +0xC returning whether the bit changed. Callers in 0x0052E11A 0x0052E3E6.

class Rva0052E05D
{
	char _00[0xC];
	unsigned m_lo : 18;
	unsigned m_bit : 1;
public:
	bool rva0052E05D(bool value);
};

bool Rva0052E05D::rva0052E05D(bool value)
{
	if ((unsigned)m_bit == (unsigned)value)
		return false;
	m_bit = value;
	return true;
}
