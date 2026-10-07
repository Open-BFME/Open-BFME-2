// ?slot37@HordeContain@@QAE_NXZ
// partial score=0.45 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7
// stlport
// ?slot37@HordeContain@@QAE_NXZ @ 0x00470B21, 488 bytes. Vtable slot 37
// is shared by HordeContain and HorseHordeContain. Field roles below follow
// target offsets; donor semantics remain unconfirmed.
#include <map>

struct HordeSlotNode
{
	HordeSlotNode *m_next;
	HordeSlotNode *m_previous;
	int m_index;
};

struct HordeSlotList
{
	HordeSlotNode *m_head;
};

struct HordeSlotRecord
{
	int m_key;
	float m_x;
	float m_y;
	char m_tail[0x10];
};

struct Rva0046247DPair
{
	void *m_value;
	int m_key;
	int m_state;
};

class Rva0046247D
{
public:
	void rva0046247D(Rva0046247DPair &pair);
};

class HordeContain : public Rva0046247D
{
public:
	bool slot37();
private:
	char m_beforeMap[0x17c];
	_STL::map<int, int> m_indexMap;
	HordeSlotRecord *m_recordsBegin;
	HordeSlotRecord *m_recordsEnd;
	HordeSlotRecord *m_recordsCapacity;
	HordeSlotList m_candidates;
	char m_beforeCallback[0x2c8 - 0x198];
	void *m_callbackObject;
	char m_tail[0x20];
};

bool HordeContain::slot37()
{
	HordeSlotList *list = &m_candidates;
	HordeSlotRecord *records = m_recordsBegin;
	int recordCount = (int)((char *)m_recordsEnd - (char *)m_recordsBegin) / 0x1c;
	HordeSlotNode *head = list->m_head;
	if (head->m_next == head)
		return false;

	int bestIndex = recordCount;
	HordeSlotNode *bestNode = 0;
	for (HordeSlotNode *node = head->m_next; node != head; node = node->m_next)
	{
		if (node->m_index < bestIndex)
		{
			bestIndex = node->m_index;
			bestNode = node;
		}
	}
	if (bestIndex >= recordCount)
		return false;

	int key = records[bestIndex].m_key;
	Rva0046247DPair pair;
	rva0046247D(pair);
	int value = m_indexMap[key];
	if (value <= bestIndex)
		return false;

	HordeSlotRecord *record = records + value;
	HordeSlotRecord *candidate = records + bestIndex;
	float dx = record->m_x - candidate->m_x;
	float dy = record->m_y - candidate->m_y;
	if (99999.0f <= dx * dx + dy * dy)
		return false;

	m_indexMap.erase(key);
	m_candidates.m_head->m_previous = bestNode;
	return true;
}
