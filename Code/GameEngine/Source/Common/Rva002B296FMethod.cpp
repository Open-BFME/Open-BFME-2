// cl: /MD /EHsc /DNDEBUG /O1 /arch:SSE /G7
// ?rva002B296F@Rva002B296F@@QAEXXZ @0x002B296F 29B: address-named thiscall method
// Evidence: retail body writes this+0xE8, this+0x169, and this+0x16C; no donor or class identity is proven.

class Rva002B296F
{
	unsigned char m_pad_000[0xE8];
	unsigned char m_0E8;
	unsigned char m_pad_0E9[0x80];
	unsigned char m_169;
	unsigned char m_pad_16A[2];
	unsigned int m_16C;

public:
	void rva002B296F();
};

extern unsigned int g_00DBA4E8;

void Rva002B296F::rva002B296F()
{
	m_0E8 = 0;
	m_169 = 1;
	m_16C = g_00DBA4E8 << 2;
}
