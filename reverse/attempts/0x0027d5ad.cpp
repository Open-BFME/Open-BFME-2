// ?rva0027D5AD@TerrainLogic@@QAEXXZ
// partial score=0.96 date=2026-10-07
// ?rva0027D5AD@TerrainLogic@@QAEXXZ
// partial score=0.95 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?rva0027D5AD@TerrainLogic@@QAEXXZ @0x0027D5AD (51B). The caller at
// 0x00283567 is TerrainLogic slot 9 and passes its adjusted this pointer here.
// The routine drains a virtual linked-node provider and clears the +0x40 field.
class TerrainNode
{
public:
	virtual void *releasePayload(int flags);
	volatile TerrainNode *m_next;
};
class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual TerrainNode *slotA0();
	char m_pad004[0x40 - 4];
	void *m_40;
	void rva0027D5AD();
};
void TerrainLogic::rva0027D5AD()
{
	TerrainNode *node = slotA0();
	if (node != 0)
	{
		do
		{
            TerrainNode * volatile *link = &node->m_next;
            TerrainNode *next = *link;
            node->m_next = 0;
			::operator delete(node->releasePayload(0));
			node = next;
		} while (node != 0);
	}
	m_40 = 0;
}
