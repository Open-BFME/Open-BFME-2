// cl: /DNDEBUG /MD /O1

// ?clear@Rva0060C45E@@QAEXXZ
// RVA 0x0060C45E, size 11. Clears dword at +0x14 if nonzero
// (cmp [ecx+0x14],0; je; and [ecx+0x14],0; ret). No callees, 12 callers in
// unwind paths. Neighbours _bfmeFormatText and Xfer::endBlock share
// /DNDEBUG /MD /O1. Honest address name; class unknown.

class Rva0060C45E
{
public:
	void clear();

private:
	char m_pad[0x14];
	int m_flag14;
};

void Rva0060C45E::clear()
{
	if (m_flag14)
		m_flag14 = 0;
}
