// cl: /MD
//
// ?rva001E3459@Rva001E3459@@QAEXH_N@Z, retail 0x001E3459, 31 bytes.
// Flag bit set/clear at +0x44: mask=1<<bit; if on m|=mask else m&=~mask.
// ret 8 with byte compare on second arg. Called at 0x001E43C7 etc.
// Owner identity unproven, honest Rva name.

class Rva001E3459
{
public:
	void rva001E3459(int bit, bool on);
private:
	int m_pad00[0x44 / 4]; // +0x00..+0x43
	int m_flags44; // +0x44
};

void Rva001E3459::rva001E3459(int bit, bool on)
{
	if (on)
		m_flags44 |= (1 << bit);
	else
		m_flags44 &= ~(1 << bit);
}
