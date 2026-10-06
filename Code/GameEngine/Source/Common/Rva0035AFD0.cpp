// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?rva0035AFD0@Rva0035AFD0@@QAEHXZ retail 0x0035AFD0 20B
// Evidence: packet's Ghidra boundary and caller at 0x0031B7A2; class identity
// is unproven, and the body reads a byte at +0x103 and an int at +0xb0.

class Rva0035AFD0
{
public:
	int rva0035AFD0();

private:
	char m_pad[0xb0];
	int m_b0;
	char m_pad2[0x4f];
	char m_103;
};

int Rva0035AFD0::rva0035AFD0()
{
	if (m_103)
		return 5;
	return m_b0;
}
