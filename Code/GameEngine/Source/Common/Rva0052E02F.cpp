// cl: /DNDEBUG /MD /EHsc
//
// ?rva0052E02F@Rva0052E02F@@QAE_N_N@Z retail 0x0052E02F 46B: bit-22 setter at
// +0xC returning whether the bit changed. Callers in 0x0052F2EC 0x00530212.

class Rva0052E02F
{
	char _00[0xC];
	unsigned m_lo : 22;
	unsigned m_bit : 1;
public:
	bool rva0052E02F(bool value);
};

bool Rva0052E02F::rva0052E02F(bool value)
{
	if ((unsigned)m_bit == (unsigned)value)
		return false;
	m_bit = value;
	return true;
}
