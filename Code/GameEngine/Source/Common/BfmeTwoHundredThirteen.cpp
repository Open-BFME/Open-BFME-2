// A row of listeners called back to front (trimmed from a two-errand donor;
// the other one is declared-only).

class BfmeThingIO;

struct BfmeSlotIO
{
	void (__cdecl *m_bfmeTell)(void *what, BfmeThingIO *thing, void *note);
	void *m_bfmeNote;
};

class BfmeThingIO
{
public:
	void bfmeTellIO(void *what);

private:
	unsigned char m_bfmeHead[0x24];		// 0x00
	BfmeSlotIO *m_bfmeSlots;		// 0x24
	unsigned char m_bfmeGap[4];		// 0x28
	unsigned int m_bfmeCount;		// 0x2c
};

// ?bfmeTellIO@BfmeThingIO@@QAEXPAX@Z
void BfmeThingIO::bfmeTellIO(void *what)
{
	unsigned int at = m_bfmeCount;

	while (at > 0)
	{
		m_bfmeSlots[at - 1].m_bfmeTell(what, this, m_bfmeSlots[at - 1].m_bfmeNote);

		--at;
	}
}
