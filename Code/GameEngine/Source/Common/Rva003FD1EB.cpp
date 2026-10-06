// cl: /MD
// ?rva003FD1EB@Rva003FD1EB@@QAEIXZ @0x003FD1EB 15B: __thiscall unsigned refcount dec
// Evidence: retail test+JBE skip dec (unsigned >0 check) then reload+ret;
// callers at 0x002B8B6C; neighbours Rva003FD1C5Xfer/Rva003FD2C2Xfer share /O1 /MD;
// colocated xfer TUs suggest refcount member at +0x04.
class Rva003FD1EB
{
	char m_pad[4];
	unsigned int m_04; // +0x04
public:
	unsigned int rva003FD1EB();
};

unsigned int Rva003FD1EB::rva003FD1EB()
{
	if (m_04 > 0)
		--m_04;
	return m_04;
}
