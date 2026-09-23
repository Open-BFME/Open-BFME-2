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

const char *XmlNameSlotList::nameAt(int index)
{
	if (index < 0 || index >= m_count)
		return 0;
	return m_slots[index].name;
}

class Rva002E2970Host
{
	char m_pad0[0x14];
	EventFlagEntry m_entries[17];
	char m_pad9C[0xDC - 0x9C];
	NameKeyType m_onDestroyedKey;

public:
	void initEventKeys();
	void applyNameFlags(XmlNameSlotList *xml);
};

void Rva002E2970Host::initEventKeys()
{
	m_entries[0].setKeyFromName("OnDamaged");
	m_entries[1].setKeyFromName("OnDestroyed");
	m_onDestroyedKey = TheNameKeyGenerator->nameToKey("OnDestroyed");
	m_entries[2].setKeyFromName("OnArrived");
	m_entries[3].setKeyFromName("OnUnitEntered");
	m_entries[5].setKeyFromName("OnUnitExited");
	m_entries[4].setKeyFromName("OnTeamEntered");
	m_entries[6].setKeyFromName("OnTeamExited");
	m_entries[7].setKeyFromName("OnTeamDestroyed");
	m_entries[8].setKeyFromName("BeScary");
	m_entries[9].setKeyFromName("DamageIncoming");
	m_entries[10].setKeyFromName("OnAflame");
	m_entries[11].setKeyFromName("OnQuenched");
	m_entries[12].setKeyFromName("OnCreated");
	m_entries[13].setKeyFromName("OnBuildingComplete");
	m_entries[14].setKeyFromName("OnSlaughtered");
	m_entries[15].setKeyFromName("OnGenericEvent");
	m_entries[16].setKeyFromName("OnBuildVariation");
}
