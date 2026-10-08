// ?rva003190BB@Drawable@@QAE?AURva003190BBPair@@XZ
// partial score=0.6 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva003190BB@Drawable@@QAE?AURva003190BBPair@@XZ @0x003190BB 44B: when the wheel info has
// entries, tail-dispatch its sret method (0x00538D17); otherwise return the pair at +0x44/+0x48.
struct Rva003190BBPair
{
	int m_first;
	int m_second;
};

struct Rva003190BBEntry
{
	char m_pad00[0x10];
};

struct TWheelInfo
{
	Rva003190BBEntry *m_begin;
	Rva003190BBEntry *m_end;
	Rva003190BBPair rva00538D17();
};

class Drawable
{
public:
	const TWheelInfo *getWheelInfo() const;
	Rva003190BBPair rva003190BB();

private:
	char m_pad00[0x44];
	int m_44;
	int m_48;
};

// ?rva003190BB@Drawable@@QAE?AURva003190BBPair@@XZ @0x003190BB
Rva003190BBPair Drawable::rva003190BB()
{
	const TWheelInfo *wheel = getWheelInfo();
	if (wheel != 0)
	{
		if (((char *)wheel->m_end - (char *)wheel->m_begin) >> 4 != 0)
		{
			return ((TWheelInfo *)wheel)->rva00538D17();
		}
	}
	Rva003190BBPair pair;
	pair.m_first = m_44;
	pair.m_second = m_48;
	return pair;
}
