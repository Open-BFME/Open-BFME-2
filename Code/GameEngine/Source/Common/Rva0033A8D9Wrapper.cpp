// cl: /MD
// ?rva0033A8D9@Rva0033A8D9@@QBE_NPBX@Z @0x0033A8D9 23B
// Forwarder over the 32-dword dual-mask tester at 0x0033A453: tests the
// caller-supplied 128-byte mask (this for the callee) against the required
// mask at +0x04 and the exempt mask at +0x84. Same Object260 layout
// (word + 128B + 128B = 0x104) as the 0x0033A9A5 array elements and the
// 0x00507558/0x00373EC6 prerequisite pairs. Callee rowed at 0x0033A453.
class Rva0033A453
{
public:
	bool rva0033A453(const void *required, const void *exempt) const;
};

class Rva0033A8D9
{
public:
	bool rva0033A8D9(const void *mask) const;

private:
	int m_00;
	unsigned m_need[32];
	unsigned m_ban[32];
};

bool Rva0033A8D9::rva0033A8D9(const void *mask) const
{
	return ((const Rva0033A453 *)mask)->rva0033A453(m_need, m_ban);
}
