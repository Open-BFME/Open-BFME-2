// cl: /DNDEBUG /MD /O1
// BFME1 Rva002E2970ApplyNameFlags.cpp donor (BFME1 retail 0x002E2970).
// BFME2 ScriptEngine event-flag host: init NameKeys for On* events, then
// apply XML Name tags. BFME2 has 17 entries (base +0x14, key +0xDC) where
// BFME1 has 13 (base +0x10); extra events are OnBuildingComplete,
// OnSlaughtered, OnGenericEvent and OnBuildVariation.

#include <string.h>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct EventFlagEntry
{
	NameKeyType key;
	unsigned char flag;
	char pad[3];

	void setKeyFromName(const char *name);
};

void EventFlagEntry::setKeyFromName(const char *name)
{
	key = TheNameKeyGenerator->nameToKey(name);
}

struct XmlNameSlot
{
	char tag[0x21];
	char name[0x40];
};

class XmlNameSlotList
{
	char m_pad[0x28];
	int m_count;
	XmlNameSlot m_slots[];

public:
	int count();
	const char *tagAt(int index);
	const char *nameAt(int index);
	void finish();
};

const char *XmlNameSlotList::tagAt(int index)
{
	if (index < 0 || index >= m_count)
		return 0;
	return m_slots[index].tag;
}
