// ?rva00574A98@Rva00574A98@@QAEIXZ
// partial score=0.9 date=2026-10-06
// cl: /DNDEBUG /MD
// ?rva00574A98@Rva00574A98@@QAEIXZ, retail 0x00574A98 13 bytes.
// Tiny unlock branchless cond-return via neg-sbb-and. Evidence: callers
// 0x005762C1 0x00576E68 0x005776FF plus unblocks 0x0057621A 0x00576DF1
// 0x005776A7 plus neighbour dtor/getter same TU family. Honest address name.
class Rva00574A98
{
public:
	unsigned int rva00574A98();
private:
	char m_pad00[4];
	unsigned int m_04;
};

unsigned int Rva00574A98::rva00574A98()
{
	unsigned int v = m_04;
	return (v ? 0xFFFFFFFFu : 0u) & (v + 0x14);
}
