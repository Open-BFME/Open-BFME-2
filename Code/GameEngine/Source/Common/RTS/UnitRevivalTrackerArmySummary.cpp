// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// UnitRevivalTracker::retrieveHeroesForArmySummary, retail 0x0037EB3C (174 bytes):
// ?retrieveHeroesForArmySummary@UnitRevivalTracker@@QAEXPAVArmySummarySystem@@@Z
// Identity (target): WorldBuilder's debug UnitRevivalTracker.cpp
// UnitRevivalTracker::retrieveHeroesForArmySummary calls, in retail's
// order, the living-world player lookup (0x002B51F8),
// UnitRevivalEntry::getThingTemplate (0x0037E270), two kind-of tests, the
// player's 0x002E1CA7 test, then ArmySummarySystem::AddDeadHeroEntry
// (WB-named, 0x0040F10F) or the player's 0x002E2F39.
// Body (target): nothing when the owner (+0x10) has no living-world id
// (Player +0x3AC == -1) or no living-world player; otherwise each revival
// entry (vector at +0x04, 0xD8 bytes each) whose template has kinds 90 and
// 128 goes to the army summary when the living-world player accepts it,
// else back to that player. Kind indices are read off the tested bits.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <vector>

enum KindOfType
{
	KINDOF_90 = 90,
	KINDOF_128 = 128
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

class UnitRevivalEntry
{
public:
	UnitRevivalEntry(const UnitRevivalEntry &that);
	~UnitRevivalEntry();
	UnitRevivalEntry &operator=(const UnitRevivalEntry &that);
	void *getThingTemplate();

private:
	char m_bytes[0xD8];
};

class Rva002E2903Player
{
public:
	bool rva002E1CA7(UnitRevivalEntry *entry);
	void rva002E2F39(UnitRevivalEntry *entry);
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class ArmySummarySystem
{
public:
	void AddDeadHeroEntry(UnitRevivalEntry *entry);
};

class Player
{
public:
	int getLivingWorldPlayerID() const { return m_livingWorldPlayerID; }

private:
	unsigned char m_pad000[0x3AC];
	int m_livingWorldPlayerID; // +0x3AC
};

class UnitRevivalTracker
{
public:
	void retrieveHeroesForArmySummary(ArmySummarySystem *summary);

private:
	void *m_vtbl;
	_STL::vector<UnitRevivalEntry> m_entries; // +0x04
	Player *m_player; // +0x10
};

void UnitRevivalTracker::retrieveHeroesForArmySummary(ArmySummarySystem *summary)
{
	int id = m_player->getLivingWorldPlayerID();
	if (id == -1)
		return;
	Rva002E2903Player *lwPlayer = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(id, 0);
	if (!lwPlayer)
		return;
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		UnitRevivalEntry *entry = &m_entries[i];
		const ThingTemplate *tmpl = (const ThingTemplate *)entry->getThingTemplate();
		if (tmpl && tmpl->isKindOf(KINDOF_90) && tmpl->isKindOf(KINDOF_128))
		{
			if (lwPlayer->rva002E1CA7(entry))
				summary->AddDeadHeroEntry(entry);
			else
				lwPlayer->rva002E2F39(entry);
		}
	}
}
