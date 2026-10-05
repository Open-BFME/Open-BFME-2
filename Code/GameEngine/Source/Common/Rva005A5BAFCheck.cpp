// cl: -O1 -GR- -EHsc-
void __stdcall rva005A57BA(int x);

struct Rva005A5BAFClass
{
	char m_0[0x488];
	int m_488;
	char m_48C[0x14];
	unsigned char m_4A0;

	void rva005A5BAF();
};

// ?rva005A5BAF@Rva005A5BAFClass@@QAEXXZ @0x005A5BAF 24B: when m_488 is 0xd,
// clears the m_4A0 flag and calls the pinned stdcall callee with 1.
void Rva005A5BAFClass::rva005A5BAF()
{
	if (m_488 == 0xd)
	{
		m_4A0 = 0;
		rva005A57BA(1);
	}
}
