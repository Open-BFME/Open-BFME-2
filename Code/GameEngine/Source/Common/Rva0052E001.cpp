// cl: /DNDEBUG /MD /EHsc
//
// ?rva0052E001@Rva0052E001@@QAE_N_N@Z retail 0x0052E001 46B: bit-17 setter at
// +0xC returning whether the bit changed. Callers at 0x0052E82A 0x0052E8F1
// 0x0052EA3D 0x0052EC3F 0x0053003A 0x0053044E 0x005307F4 0x00530A7B.

class Rva0052E001
{
	char _00[0xC];
	unsigned m_lo : 17;
	unsigned m_bit : 1;
public:
	bool rva0052E001(bool value);
};

bool Rva0052E001::rva0052E001(bool value)
{
	if ((unsigned)m_bit == (unsigned)value)
		return false;
	m_bit = value;
	return true;
}
