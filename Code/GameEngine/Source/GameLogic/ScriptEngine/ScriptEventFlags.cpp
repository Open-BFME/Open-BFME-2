// cl: /DNDEBUG /MD
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

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/GameLogic/LuaScriptEngine.h"

void EventFlagEntry::setKeyFromName(const char *name)
{
	field00 = TheNameKeyGenerator->nameToKey(name);
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
	int finish();								// 0x00542890 (retail returns EAX)
};

// LuaScriptEngine's internal-event table. WorldBuilder's LuaScriptEngine.cpp
// names both bodies: InitializeInternalEvents (:795 asserts each
// m_internalEvents[i] name key; the same 17 event names in the same order)
// and ProcessInternalEvent (:946-968, the "Name" attribute loop).
void LuaScriptEngine::InitializeInternalEvents()
{
	field14[0].setKeyFromName("OnDamaged");
	field14[1].setKeyFromName("OnDestroyed");
	fieldDC = TheNameKeyGenerator->nameToKey("OnDestroyed");
	field14[2].setKeyFromName("OnArrived");
	field14[3].setKeyFromName("OnUnitEntered");
	field14[5].setKeyFromName("OnUnitExited");
	field14[4].setKeyFromName("OnTeamEntered");
	field14[6].setKeyFromName("OnTeamExited");
	field14[7].setKeyFromName("OnTeamDestroyed");
	field14[8].setKeyFromName("BeScary");
	field14[9].setKeyFromName("DamageIncoming");
	field14[10].setKeyFromName("OnAflame");
	field14[11].setKeyFromName("OnQuenched");
	field14[12].setKeyFromName("OnCreated");
	field14[13].setKeyFromName("OnBuildingComplete");
	field14[14].setKeyFromName("OnSlaughtered");
	field14[15].setKeyFromName("OnGenericEvent");
	field14[16].setKeyFromName("OnBuildVariation");
}

void LuaScriptEngine::ProcessInternalEvent(XmlNameSlotList *xml)
{
	int i = 0;
	if (xml->count() > 0)
	{
		do
		{
			int diff = strcmp(xml->tagAt(i), "Name");
			if (diff == 0)
			{
				NameKeyType key = TheNameKeyGenerator->nameToKey(xml->nameAt(i));
				int j;
				for (j = 0; j < 17; ++j)
				{
					if (field14[j].field00 == key)
					{
						field14[j].field04 = 1;
						break;
					}
				}
			}
			++i;
		} while (i < xml->count());
	}
	xml->finish();
}
