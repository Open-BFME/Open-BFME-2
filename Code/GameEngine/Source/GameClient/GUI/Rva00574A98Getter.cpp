// ?rva00574A98@Rva00574A98@@QAEPAXXZ
// cl: /DNDEBUG /MD
//
// Rva00574A98::rva00574A98() at retail 0x00574A98 (13B): returns the
// address of the sub-record at +0x14 of the object stored at this+4, or 0
// when that object is null. Callers: 0x005762C1, 0x00576E68, 0x005776FF
// (Rva005770F7's ctor among them).
//
// Codegen: an unsigned local tested by a conditional expression gives
// retail's lea / neg / sbb / and branchless form; the cast-to-base and
// pointer-conditional spellings compile to a compare and branch.
class Rva00574A98
{
public:
	void *rva00574A98();
private:
	char m_pad00[4];
	unsigned int m_04;
};

void *Rva00574A98::rva00574A98()
{
	unsigned int v = m_04;
	return (void *)(v ? v + 0x14 : 0);
}
