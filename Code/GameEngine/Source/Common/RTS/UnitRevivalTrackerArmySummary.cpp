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
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Xfer;

enum KindOfType
{
	KINDOF_90 = 90,
	KINDOF_128 = 128
};

class ThingTemplate
{
public:
	__declspec(dllimport) __forceinline bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

	char unknown00[0x64];
	AsciiString name; // +0x64
	char unknown68[0x108 - 0x68];
	unsigned char m_kindOf[0x20]; // +0x108
};

class Rva001EAE6FHelper
{
	char m_data[0x80];
public:
	Rva001EAE6FHelper *clear80() throw();
	// Keep the existing clear worker while constructing this member in order.
	__forceinline Rva001EAE6FHelper() throw() { clear80(); }
};
class Rva004E04FD
{
	char m_data[0x18];
public:
	Rva004E04FD() throw();
};
class Object;

class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	UnitRevivalEntry(Object *object);
	UnitRevivalEntry(const UnitRevivalEntry &that);
	~UnitRevivalEntry();
	UnitRevivalEntry &operator=(const UnitRevivalEntry &that);
	void *getThingTemplate();
	void setThingTemplateName(const AsciiString &name);
	void rva0037E473(Xfer *xfer);

	int m_00;
	int m_04;
	float m_08;
	int m_0C;
	int m_10;
	Rva001EAE6FHelper m_14;
	int m_94;
	int m_98;
	unsigned int m_9C; // build time, from the template's float via _ftol
	bool m_A0;
	bool m_A1;
	int m_A4;
	int m_A8;
	int m_AC;
	Rva004E04FD m_B0;
	int m_C8;
	float m_CC;
	int m_D0;
	AsciiString m_str; // +0xD4
};

class Rva002E2903Player
{
public:
	bool rva002E1CA7(UnitRevivalEntry *entry);
};

// Rows 0x0040F10F (ArmySummarySystem::AddDeadHeroEntry, Rva0040ECCF.cpp) and
// 0x002E2F39 (Rva002E2F39::rva002E2F39), called by their row names.
struct Rva002E2D10Record;
class Rva002E2F39
{
public:
	void rva002E2F39(const Rva002E2D10Record &record);
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
	int getPlayerIndex() const { return m_playerIndex; }
	int getLivingWorldPlayerID() const { return m_livingWorldPlayerID; }

private:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
	unsigned char m_pad58[0x3AC - 0x58];
	int m_livingWorldPlayerID; // +0x3AC
};

class UnitRevivalTracker
{
public:
	void retrieveHeroesForArmySummary(ArmySummarySystem *summary);

protected:
	virtual void xfer(Xfer *xfer);

private:
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
		const ThingTemplate *thingTemplate = (const ThingTemplate *)entry->getThingTemplate();
		if (thingTemplate && thingTemplate->isKindOf(KINDOF_90) && thingTemplate->isKindOf(KINDOF_128))
		{
			if (lwPlayer->rva002E1CA7(entry))
				summary->AddDeadHeroEntry(entry);
			else
				((Rva002E2F39 *)lwPlayer)->rva002E2F39(*(const Rva002E2D10Record *)entry);
		}
	}
}
