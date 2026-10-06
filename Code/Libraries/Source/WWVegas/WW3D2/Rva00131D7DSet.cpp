// cl: /DNDEBUG /MD
// ?rva00131D7D@Rva00131D7D@@QAEXI@Z, retail 0x00131D7D, 28 bytes.
// Unlock: splits DWORD arg into three bytes at +0/+4/+8 (B G R). No callees.
// Evidence: unlock lane, caller at 0x0013235C, prev/next TU flags.

class Rva00131D7D
{
public:
	void rva00131D7D(unsigned int c);
	int m_00;
	int m_04;
	int m_08;
};

void Rva00131D7D::rva00131D7D(unsigned int c)
{
	m_00 = (c >> 16) & 0xFF;
	m_04 = (c >> 8) & 0xFF;
	m_08 = c & 0xFF;
}
