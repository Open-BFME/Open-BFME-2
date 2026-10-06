// cl: /MD
//
// ?get@Rva0004CABDSevenEight@@QBEHXZ, retail 0x0004CABD (16 bytes own plus
// shared 4-byte true-tail at 0x4CACD).
//
// Trivial int getter over +0xC: 1 when the dword is 7 or 8, 0 otherwise.
// Retail jumps its taken arms into the next row's int-one getter at 0x4CACD
// (xor eax,eax / inc eax / ret), so the owned size is 16 bytes to the
// false-path ret; the 4-byte true tail is the neighbour's row. Callers
// include 0x4D131 0x1F491A 0x55C521.

class Rva0004CABDSevenEight
{
public:
	int get() const;

private:
	char m_pad[0xC];
	int m_value; // +0xC
};

int Rva0004CABDSevenEight::get() const
{
	if (m_value == 7 || m_value == 8)
		return 1;
	return 0;
}
