// cl: /O1 /DNDEBUG /MD
//
// ?rva004B0942@Rva004B0942@@QAEPAXXZ @0x004B0942 26B.
// The slot at +0x20 is created from the dword at +8 by the cdecl helper
// 0x00498725 the first time it is read, then returned.

void *__cdecl rva00498725(void *arg);

class Rva004B0942
{
public:
	void *rva004B0942();

private:
	char m_pad[8];
	void *m_arg8;
	char m_padC[0x20 - 0x0C];
	void *m_slot20;
};

void *Rva004B0942::rva004B0942()
{
	if (m_slot20 == 0)
		m_slot20 = rva00498725(m_arg8);
	return m_slot20;
}
