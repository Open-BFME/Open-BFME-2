// cl: /DNDEBUG /MD /EHsc
//
// ?rva0052E0CE@Rva0052E0CE@@QAE_N_N@Z retail 0x0052E0CE 46B: bit-23 setter at
// +0xC returning whether the bit changed. Callers in 0x0052F2EC.

class Rva0052E0CE
{
	char _00[0xC];
	unsigned m_lo : 23;
	unsigned m_bit : 1;
public:
	bool rva0052E0CE(bool value);
};

bool Rva0052E0CE::rva0052E0CE(bool value)
{
	if ((unsigned)m_bit == (unsigned)value)
		return false;
	m_bit = value;
	return true;
}
