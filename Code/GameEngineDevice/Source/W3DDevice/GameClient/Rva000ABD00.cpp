// cl: /O1 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva000ABD00@Rva000ABD00@@QAEHI@Z @0x000ABD00 25B
// Unlock bounds-checked inline int-array getter. Evidence: ret 4 single
// unsigned arg, jae 0x1000 to xor-eax fail, array at +0xb0 scale 4.

class Rva000ABD00
{
public:
	unsigned char m_0[176];
	int m_b0[4096];
	int rva000ABD00(unsigned int idx);
};

int Rva000ABD00::rva000ABD00(unsigned int idx)
{
	if (idx < 0x1000)
		return m_b0[idx];
	return 0;
}
