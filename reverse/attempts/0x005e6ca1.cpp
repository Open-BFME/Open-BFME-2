// ?FindLeaderEntry@StrategicInGameUI@@YA?AULeaderEntry@1@PAULivingWorldArmy@@@Z
// partial score=0.97 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs-c-
// StrategicInGameUIHeroArmyDetailsPanel.cpp -- StrategicInGameUI hero army
// details helpers at their WorldBuilder home (reverse/wb_name_leads.csv: WB's
// debug build names the file and StrategicInGameUI::FindLeaderEntry); retail
// supplies the bytes.
//
// Layout (target evidence): the army's summary at +0x78 holds 8-byte entries
// between +0x40 and +0x44, read through the rowed accessors 0x0040CB2C (the
// entry) and 0x0040CC0E (its id); an entry's name is at +0x04 and the army's
// leader name at +0x18.
#include "ascii_string.h"

typedef int Int;

struct ArmySummaryEntry
{
	Int m_00;
	StringBase<char> m_name;				// +0x04
};

class Rva0040CB2CIndexedField
{
public:
	Int get(Int index) const;				// 0x0040CB2C, ArmySummary::GetEntry

	char m_pad[0x40];
	char *m_begin;						// +0x40
	char *m_end;						// +0x44
};

class Rva0040CC0EIndexedField
{
public:
	Int get(Int index) const;				// 0x0040CC0E, ArmySummary::GetEntryID
};

struct LivingWorldArmy
{
	char m_pad00[0x18];
	StringBase<char> m_leaderName;				// +0x18
	char m_pad1C[0x78 - 0x1c];
	Rva0040CB2CIndexedField *m_summary;			// +0x78
};

namespace StrategicInGameUI
{
	struct LeaderEntry
	{
		LeaderEntry(Int entryID, ArmySummaryEntry *entry) : m_entryID(entryID), m_entry(entry) {}

		Int m_entryID;
		ArmySummaryEntry *m_entry;
	};

	LeaderEntry FindLeaderEntry(LivingWorldArmy *army);
}

// StrategicInGameUI::FindLeaderEntry, retail 0x005E6CA1 (108 bytes): the
// army summary entry named like the army's leader, with its id; both zero
// when none is.
StrategicInGameUI::LeaderEntry StrategicInGameUI::FindLeaderEntry(LivingWorldArmy *army)
{
	Rva0040CB2CIndexedField *summary = army->m_summary;
	Int count = (Int)(summary->m_end - summary->m_begin) >> 3;
	ArmySummaryEntry *entry;
	Int i;
	for (i = 0; i < count; ++i)
	{
		entry = (ArmySummaryEntry *)summary->get(i);
		if (entry->m_name.compare(army->m_leaderName) == 0)
			goto found;
	}
	return LeaderEntry(0, 0);
found:
	return LeaderEntry(((Rva0040CC0EIndexedField *)summary)->get(i), entry);
}
