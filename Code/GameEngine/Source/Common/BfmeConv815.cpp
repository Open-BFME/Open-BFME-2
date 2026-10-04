// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

struct BfmeItemE63
{
	unsigned char pad[0x14];
	void *m_p14;
	unsigned char pad2[0x24 - 0x18];
	char m_flag24;
	bool checkValid();
};

BfmeItemE63* __cdecl bfmeFindItemE63(int id);

struct BfmeThingE63
{
	unsigned char pad[8];
	int m_id;
	bool isValid();
};

bool BfmeThingE63::isValid()
{
	int id = m_id;
	BfmeItemE63 *item = bfmeFindItemE63(id);
	if (item && item->m_p14 && !item->m_flag24 && item->checkValid())
		return true;
	return false;
}
