// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E06B8@Rva002E06B8@@QAEPAVGameSlot@@XZ @0x002E06B8 55B find slot matching this plus 0x14
// Evidence: global TheGameInfo and callee rowed 0x003FF29F GameInfo getSlot; callers 0x002B336E 0x002E06EF; neighbours 0x002E0675 setter and 0x002E071E compare share /O1
class GameSlot
{
public:
	char m_pad[4];
	int m_4;
	char m_pad2[0x4c - 8];
	int m_4c;
	char m_pad3[0x60 - 0x50];
	unsigned char m_60;
};

class GameInfo
{
public:
	GameSlot *getSlot(int i);
};

extern GameInfo *TheGameInfo;

class Rva002E06B8
{
public:
	GameSlot *rva002E06B8();
	void *rva002E06EF();
private:
	char m_pad[0x14];
	int m_14;
};

GameSlot *Rva002E06B8::rva002E06B8()
{
	GameInfo *gi = TheGameInfo;
	if (gi == 0)
		return 0;
	for (int i = 0; i < 8; ++i)
	{
		GameSlot *slot = gi->getSlot(i);
		if (slot->m_4 == 1)
			continue;
		if (slot->m_4c == m_14)
			return slot;
	}
	return 0;
}

void *Rva002E06B8::rva002E06EF()
{
	GameSlot *slot = rva002E06B8();
	if (slot == 0)
		return 0;
	return slot->m_60 ? (void *)((char *)slot + 0x64) : 0;
}
