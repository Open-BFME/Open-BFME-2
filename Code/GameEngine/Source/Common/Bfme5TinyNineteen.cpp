// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Three more: a push at the head of the owner's list, a snapshot that copies a
// word and a three-word struct, and a search along a global list that hands
// back the node it stopped on.

class BfmeEntryCK
{
public:
	int m_bfmeTag;						// +0x00
	BfmeEntryCK *m_bfmeNext;				// +0x04
	int m_bfmeGap[3];					// +0x08
	void *m_bfmeKey;					// +0x14
};

class TimedOp;
extern TimedOp *g_timedOperationHead;		// retail 0x012ED584

// ?bfmeFind@@YAPAVBfmeEntryCK@@PAX@Z
BfmeEntryCK * __cdecl bfmeFind(void *key)
{
	BfmeEntryCK *entry = (BfmeEntryCK *)g_timedOperationHead;

	while (entry)
	{
		if (entry->m_bfmeKey == key)
			break;

		entry = entry->m_bfmeNext;
	}

	return entry;
}
