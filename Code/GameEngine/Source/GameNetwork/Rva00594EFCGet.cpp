// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// ?rva00594EFC@Rva00594EFC@@QAEHXZ, retail 0x00594EFC, 11 bytes. Clears the
// dword at +0x17C then returns the dword at +4. Evidence: retail
// `and [ecx+0x17c],0; mov eax,[ecx+4]; ret`, thiscall (reads ecx, ret 0),
// single caller at 0x00519CE5 in unclaimed FUN_009194f6.

class Rva00594EFC
{
public:
	int rva00594EFC();

private:
	char m_pad0[4];
	int m_04;
	char m_pad1[0x17C - 8];
	int m_17C;
};

int Rva00594EFC::rva00594EFC()
{
	m_17C = 0;
	return m_04;
}
