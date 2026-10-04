// cl: /O1 /MD
// ?rva004F0681@Rva004F0681@@QAEEXZ @0x004F0681 37B TeamInQueue-area predicate.
// Evidence: contiguous with TeamInQueue::isMinimumBuilt 0x004F06A6 (ends 0x004F06A6); triple deref +0x1C/+0x30/+0x1F8 gated >=1 then +0x24 plus value vs TheGameLogic+0x40 unsigned above; caller 0x004F1653+0x23; prev/next share /O1.
struct Rva004F0681Inner
{
	char m_pad00[0x1F8];
	int m_1F8;
};

struct Rva004F0681Mid
{
	char m_pad00[0x30];
	Rva004F0681Inner *m_30;
};

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;

class Rva004F0681
{
public:
	unsigned char rva004F0681();

private:
	char m_pad00[0x1C];
	Rva004F0681Mid *m_1C;
	char m_pad20[4];
	int m_24;
};

unsigned char Rva004F0681::rva004F0681()
{
	int v = m_1C->m_30->m_1F8;
	if (v < 1)
		return false;
	unsigned int c = (unsigned int)m_24 + (unsigned int)v;
	return TheGameLogic->m_40 > c;
}
