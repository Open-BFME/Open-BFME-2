// cl: /O1 /DNDEBUG /MD
//
// StrategicInGameUIQueueUnitButton.cpp -- StrategicInGameUI::QueueUnitButton
// members at their WorldBuilder home (reverse/wb_name_leads.csv); retail
// supplies the bytes. Target facts: the button keeps the region id at +0x18
// and the queued unit's id at +0x20; the region's virtual slot 13 (+0x34)
// gives its build queue of ids.

struct QueueUnitButtonIds
{
	int *m_start;
	int *m_finish;

	unsigned int size() const { return m_finish - m_start; }
};

class QueueUnitButtonRegion
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual const QueueUnitButtonIds *getBuildQueue();
};

// The region lookup by id (rowed 0x005F88F4, address-named).
int Rva005F88F4Get(int regionID);

class Keyboard
{
public:
	bool isShift();
};
extern Keyboard *TheKeyboard;

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);
};
extern MessageStream *TheMessageStream;

// The last position before start (the whole queue when start is out of
// range) holding id, or -1 (inlined in retail).
static inline int FindQueuedBefore(const QueueUnitButtonIds *queue, int id, int start)
{
	int i = (start >= 0 && (unsigned int)start < queue->size()) ? start : queue->size();
	while (i > 0)
	{
		--i;
		if (queue->m_start[i] == id)
			return i;
	}
	return -1;
}

namespace StrategicInGameUI
{
class QueueUnitButton
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	// Slot 4 (pointer at 0x00879CDC).
	virtual void OnRightClicked();

private:
	unsigned char m_pad04[0x18 - 0x04];
	int m_regionID; // +0x18
	unsigned char m_pad1c[0x20 - 0x1C];
	int m_unitID; // +0x20
};
}

// StrategicInGameUI::QueueUnitButton::OnRightClicked, retail 0x005F8B1C
// (184 bytes; WorldBuilder lines 243..263, wb-name-unverified): dequeues one
// (five with shift) of this unit from the region's build queue, newest
// first, by message 0x6AD (region, unit).
void StrategicInGameUI::QueueUnitButton::OnRightClicked()
{
	QueueUnitButtonRegion *region = (QueueUnitButtonRegion *)Rva005F88F4Get(m_regionID);
	if (!region)
		return;

	int count = TheKeyboard->isShift() ? 5 : 1;
	int index = -1;
	for (; count > 0; --count)
	{
		index = FindQueuedBefore(region->getBuildQueue(), m_unitID, index);
		if (index < 0)
			break;
		GameMessage *msg = TheMessageStream->appendMessage(0x6AD);
		msg->appendIntegerArgument(m_regionID);
		msg->appendIntegerArgument(m_unitID);
	}
}
