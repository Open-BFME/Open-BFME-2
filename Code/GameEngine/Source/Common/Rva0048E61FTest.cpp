// cl: /O1 /DNDEBUG /MD
//
// ?rva0048E61F@Rva0048E61F@@QAEHXZ @0x0048E61F 21B.
// 1 when the byte at +0x4A9 is set and the dword at +0x3E4 is not -1.
// The zero in eax is reused as the byte compare. Returning int skips the
// bool setne tail.

class Rva0048E61F
{
public:
	int rva0048E61F();

private:
	char m_pad[0x3E4];
	int m_3e4;
	char m_pad2[0x4A9 - 0x3E8];
	unsigned char m_4a9;
};

int Rva0048E61F::rva0048E61F()
{
	int n = 0;
	if (m_4a9 != (unsigned char)n && m_3e4 != -1)
		++n;
	return n;
}
